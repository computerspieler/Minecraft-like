#include <string>
#include <fstream>

#include "typedef.h"
#include "debug.h"
#include "texture.h"
#include "bmp_reader.h"
#include "color.h"

using namespace Render;

Texture* Image::BMP::load_Texture(std::string filename){
	Texture *texture = NULL;
	std::ifstream file;
	FileHeader file_header;
	DIBHeader  dib_header;
	int compression;
	int pixel_x, pixel_y;
	char pixel_buffer;
	Color pixel_color;

	// Open the file
	Debug::Info << "Loading " << filename << std::endl;
	file.open(filename, std::ios::in | std::ios::binary);

	if(!file.is_open()){
		Debug::Error << "Unable to load the file" << std::endl;
		return NULL;
	}

	// Read the header
	file.read((char*)(&file_header.signature), 2);
	file.read((char*)(&file_header.file_size), 4);
	file.read((char*)(&file_header.reserved_0), 2);
	file.read((char*)(&file_header.reserved_1), 2);
	file.read((char*)(&file_header.pixel_array_address), 4);

	// Check if the signature is valid
	if(file_header.signature != 0x4D42){
		Debug::Error << "Invalid bitmap file";
		file.close();
		return NULL;
	}

	// Read the DIB header
	file.read((char*)(&dib_header.header_size), 4);

	// The DIB header size can help to distinguish which type of
	// header we will have
	
	switch(dib_header.header_size){
		case 12:	// BitmapCoreHeader
			file.read((char*)(&dib_header.width) , 2);
			file.read((char*)(&dib_header.height), 2);

			file.read((char*)(&dib_header.color_planes), 2);	
			file.read((char*)(&dib_header.color_depth) , 2);
			break;

		case 40:	// BitmapInfoHeader
			file.read((char*)(&dib_header.width) , 4);
			file.read((char*)(&dib_header.height), 4);

			file.read((char*)(&dib_header.color_planes), 2);	
			file.read((char*)(&dib_header.color_depth) , 2);

			file.read((char*)(&compression), 4);
			if(compression != 0){
				Debug::Error << "Unsupported compressed bitmap" << std::endl;
				file.close();
				return NULL;
			}

			file.seekg(46);
			file.read((char*)(&dib_header.color_palette), 4);
			if(dib_header.color_palette != 0){
				// TODO: Support color palette
				Debug::Error << "Unsupported color palette" << std::endl;
				file.close();
				return NULL;
			}

			break;

		default:
			Debug::Error << "Unsupported header format" << std::endl;
			file.close();
			return NULL;
	}

	texture = new Texture(dib_header.width, dib_header.height);	

	file.seekg(dib_header.header_size + FILE_HEADER_SIZE);
	for(pixel_y = dib_header.height-1; pixel_y >= 0; pixel_y--){
		for(pixel_x = 0; pixel_x < dib_header.width; pixel_x++){

			// Color depth = number of bits per pixel		
			switch(dib_header.color_depth){	
				case 1:
					if(pixel_x % 8 == 0)
						file.read((char*)&pixel_buffer, 1);
					
					if(pixel_buffer & (0x80 >> (pixel_x % 8)))
						pixel_color = {255, 255, 255, 255};
					else
						pixel_color = {0, 0, 0, 255};
					break;

				case 8:
					file.read((char*)&pixel_buffer, 1);
					// For now, we will suppose that 8 bit depth and 0 color palette
					// = 8 bits grayscale bitmap
					if(dib_header.color_palette == 0)
						pixel_color = {pixel_buffer,
							       pixel_buffer,
							       pixel_buffer,
							       255};
					
					break;
				case 16:

					break;	

				case 24:
					pixel_color.alpha = 255;	
					file.read((char*)&pixel_color.red,   1);
					file.read((char*)&pixel_color.green, 1);
					file.read((char*)&pixel_color.blue,  1);
				
					break;

				case 32:
					file.read((char*)&pixel_color.red,   1);
					file.read((char*)&pixel_color.green, 1);
					file.read((char*)&pixel_color.blue,  1);
					file.read((char*)&pixel_color.alpha, 1);
					break;

				default:
					Debug::Error << "Unsupported color depth" << std::endl;
			}
			texture->Pixel_Set(pixel_x, pixel_y, pixel_color);
		}
	}

	file.close();

	return texture;
}
