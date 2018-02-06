#ifndef __RGBAPIXEL_H__
#define __RGBAPIXEL_H__

#include <cstdint>
using std::uint8_t;

class RGBAPixel{
public:
uint8_t red;
uint8_t green;
uint8_t blue;
uint8_t alpha;

public:
RGBAPixel();
RGBAPixel(uint8_t red, uint8_t green, uint8_t blue);
};

#endif
