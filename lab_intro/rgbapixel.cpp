#include "rgbapixel.h"

RGBAPixel::RGBAPixel(){
	red = 0;
	green = 0;
	blue = 0;
	alpha = 255;
}

RGBAPixel::RGBAPixel(uint8_t red, uint8_t green, uint8_t blue){
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = 255;
}
