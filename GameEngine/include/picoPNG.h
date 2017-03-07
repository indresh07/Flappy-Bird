#ifndef PICOPNG_H_INCLUDED
#define PICOPNG_H_INCLUDED

#include<vector>
#include<cstdint>
namespace gameEngine{
    extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, std::size_t in_size, bool convert_to_rgba32 = true);

}

#endif // PICOPNG_H_INCLUDED
