#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "png.h"

class Image : public PNG{
public:
    void flipleft();
    void adjustbrightness(int r, int g, int b);
    void invertcolors();
};

#endif
