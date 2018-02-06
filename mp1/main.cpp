#include <iostream>
#include "rgbapixel.h"
#include "png.h"

using std::uint8_t;

/// This function takes a PNG image as a parameter
/// and returns 180 degrees rotated image.
/// It does not switch the original image.
/// It makes a new PNG and saves and returns the rotated image.
PNG rotate180(PNG original){
    size_t width = original.width();
    size_t height = original.height();
    PNG newImage(width, height);

    for(size_t y=0; y<height; y++){
	for(size_t x=0; x<width; x++){
	    newImage(x,y)->red = original(width-x-1, height-y-1)->red;
	    newImage(x,y)->green = original(width-x-1, height-y-1)->green;
	    newImage(x,y)->blue = original(width-x-1, height-y-1)->blue;
	    newImage(x,y)->alpha = original(width-x-1, height-y-1)->alpha;
	}
    }

    return newImage;
}

int main(){
    PNG image;

    image.readFromFile("in.png");

    image = rotate180(image);

    image.writeToFile("out.png");

    return 0;
}
