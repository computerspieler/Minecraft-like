#include <assert.h>
#include <stdio.h>

#include "reader.h"
#include "typedef.h"
#include "texture.h"

const int FILE_HEADER_SIZE = 14;

typedef struct FileHeader{
	ushort signature;
	uint   file_size;
	uint   pixel_array_address;
} FileHeader;

typedef struct DIBHeader{
	uint header_size;
		int width;
		int height;
	ushort color_planes;
	ushort color_depth;
	uint   color_palette;
} DIBHeader;


Texture texture_load(FILE *f)
{
	Texture output;
	FileHeader file_header;
	DIBHeader  dib_header;
	int compression;
	int pixel_x, pixel_y;
	char pixel_buffer;
	Color pixel_color;

	/* Read the header */
    fread(&file_header.signature, 2, 1, f);
	fread(&file_header.file_size, 4, 1, f);
    fseek(f, 4, SEEK_CUR);
	fread(&file_header.pixel_array_address, 4, 1, f);

	/* Check if the signature is valid */
	if(file_header.signature != 0x4D42) {
		fprintf(stderr, "Invalid bitmap file\n");
		return texture_create(0, 0);
	}

	/* Read the DIB header */
	fread(&dib_header.header_size, 4, 1, f);

    /*
        The DIB header size can help to distinguish which type of
    	header we will have
	*/
	switch(dib_header.header_size) {
		case 12:	/* BitmapCoreHeader */
			fread(&dib_header.width , 2, 1, f);
			fread(&dib_header.height, 2, 1, f);

			fread(&dib_header.color_planes, 2, 1, f);	
			fread(&dib_header.color_depth, 2, 1, f);
			break;

		case 40:	/* BitmapInfoHeader */
			fread(&dib_header.width, 4, 1, f);
			fread(&dib_header.height, 4, 1, f);

			fread(&dib_header.color_planes, 2, 1, f);	
			fread(&dib_header.color_depth, 2, 1, f);

			fread(&compression, 4, 1, f);
			if(compression != 0){
				fprintf(stderr, "Unsupported compressed bitmap");
				return texture_create(0, 0);
			}

			fseek(f, 46, SEEK_SET);
			fread(&dib_header.color_palette, 4, 1, f);
			if(dib_header.color_palette != 0){
				/* TODO: Support color palette */
				fprintf(stderr, "Unsupported color palette");
				return texture_create(0, 0);
			}

			break;

		default:
			fprintf(stderr, "Unsupported header format");
			return texture_create(0, 0);
	}

	output = texture_create(dib_header.width, dib_header.height);	

	fseek(f, dib_header.header_size + FILE_HEADER_SIZE, SEEK_SET);
	for(pixel_y = dib_header.height-1; pixel_y >= 0; pixel_y--){
		for(pixel_x = 0; pixel_x < dib_header.width; pixel_x++){

			/* Color depth = number of bits per pixel */
			switch(dib_header.color_depth){	
				case 1:
					if(pixel_x % 8 == 0)
						fread(&pixel_buffer, 1, 1, f);
					
					if(pixel_buffer & (0x80 >> (pixel_x % 8)))
						pixel_color = (Color) {255, 255, 255, 255};
					else
						pixel_color = (Color) {0, 0, 0, 255};
					break;

				case 8:
					fread(&pixel_buffer, 1, 1, f);
                    /*
					    For now, we will suppose that 8 bit depth and 0 color palette
					    = 8 bits grayscale bitmap
                    */
					if(dib_header.color_palette == 0)
						pixel_color = (Color) {pixel_buffer, pixel_buffer, pixel_buffer, 255};
					break;

				case 16:
					assert(false);
					break;	

				case 24:
					pixel_color.alpha = 255;	
					fread(&pixel_color.red,   1, 1, f);
					fread(&pixel_color.green, 1, 1, f);
					fread(&pixel_color.blue,  1, 1, f);
					break;

				case 32:
					fread(&pixel_color.red,   1, 1, f);
					fread(&pixel_color.green, 1, 1, f);
					fread(&pixel_color.blue,  1, 1, f);
					fread(&pixel_color.alpha, 1, 1, f);
					break;

				default:
					fprintf(stderr, "Unsupported color depth\n");
			        return texture_create(0, 0);
			}
			texture_put_pixel(&output, pixel_x, pixel_y, pixel_color);
		}
	}

    return output;
}

