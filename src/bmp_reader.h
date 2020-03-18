#ifndef _BMP_READER_H_
#define _BMP_READER_H_

#include <fstream>
#include <string>

#include "typedef.h"

namespace Render {
	namespace Image{
		namespace BMP{
			#define FILE_HEADER_SIZE 14 
			typedef struct FileHeader{
				ushort signature;
				uint   file_size;
				ushort reserved_0;
				ushort reserved_1;
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

			Texture* load_Texture(std::string filename);
		};
	};
};

#endif
