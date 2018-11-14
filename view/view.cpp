#include <png.h>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include <string>
#include "view.hpp"


namespace view {

std::tuple<unsigned char**, int, int> getPNGPixels(const std::string& fn) {
  FILE* fp = fopen(fn.c_str(), "rb");
  if(not fp) {
    std::cerr << "[ERROR] " << fn << "is not a file" << std::endl;
    throw ImageException(fn + " is not a file");
  }
  png_byte signature[8];
  fread(signature, 1, 8, fp);
  if(png_sig_cmp(signature, 0, 8)) {
    std::cout << "[ERROR] " << fn << " is not a png file" << std::endl;
    throw ImageException(fn + " is not a png file");
  }
  
  // Create png_ptr
  png_structp png_ptr = png_create_read_struct(
    PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr
  );
  if(not png_ptr) {
    std::cout << "[ERROR] cannot create png object" << std::endl;
    throw ImageException("Cannot create png object");
  }

  // Create info_ptr
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if(not info_ptr) {
    std::cout << "[ERROR] cannot create png info object" << std::endl;
    throw ImageException("Cannot create png info object");
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);
  png_read_info(png_ptr, info_ptr);
  
  int width = png_get_image_width(png_ptr, info_ptr);
  int height = png_get_image_height(png_ptr, info_ptr);
  png_byte color_type = png_get_color_type(png_ptr, info_ptr);
  png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  int passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);

  std::cout << "[INFO] Width of " << width << std::endl;
  std::cout << "[INFO] Height of " << height << std::endl;
  std::cout << "[INFO] Depth of " << static_cast<int>(bit_depth) << std::endl;
  
  // Creating raw data
  png_bytep* row_pointers = new png_bytep[height];
  for(int i = 0; i < height; ++i) {
    row_pointers[i] = new png_byte[png_get_rowbytes(png_ptr, info_ptr)];
  }
 
  std::cout << "[INFO]: rowbytes: " << static_cast<int>(png_get_rowbytes(png_ptr, info_ptr)) << std::endl;
 
  // Loading image
  png_read_image(png_ptr, row_pointers);
  fclose(fp);

  return std::make_tuple(static_cast<unsigned char**>(row_pointers), height, width);
}

}
