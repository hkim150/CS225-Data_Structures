#ifndef __SCENE_H__
#define __SCENE_H__

#include "image.h"

class Scene{
private:
    Image** image_arr;
    int* x_arr;
    int* y_arr;
    int max;
public:
    Scene(int max);
    ~Scene();
    Scene(const Scene& source);
    void copy(const Scene& source);
    void clear();
    const Scene& operator=(const Scene &source);
    void changemaxlayers(int newmax);
    void addpicture(const char* FileName, int index, int x, int y);
    void changelayer(int index, int newindex);
    void translate(int index, int xcoord, int ycoord);
    void deletepicture(int index);
    Image* getpicture(int index) const;
    Image drawscene() const;
};

#endif
