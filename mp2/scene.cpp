#include <cstring>
#include "scene.h"

Scene::Scene(int max){
    this->max = max;
    image_arr = new Image*[max];
    x_arr = new int[max];
    y_arr = new int[max];

    for(int i=0; i<max; i++){
	image_arr[i] = NULL;
	x_arr[i] = 0;
	y_arr[i] = 0;
    }
}

Scene::~Scene(){
    clear();
}

void Scene::clear(){
    for(int i=0; i<max; i++){
	if(image_arr[i] != NULL){
	    delete image_arr[i];
	    image_arr[i] = NULL;
	}
    }
    if(image_arr != NULL){
	delete[] image_arr;
	image_arr = NULL;
    }
    if(x_arr != NULL){
	delete[] x_arr;
	x_arr = NULL;
    }
    if(y_arr != NULL){
	delete[] y_arr;
	y_arr = NULL;
    }
}

Scene::Scene(const Scene& source){
    copy(source);
}

void Scene::copy(const Scene& source){
    max = source.max;
    image_arr = new Image*[max];
    x_arr = new int[max];
    y_arr = new int[max];

    for(int i=0; i<max; i++){
	if(source.image_arr[i] == NULL){
	    image_arr[i] = NULL;
	    x_arr[i] = 0;
	    y_arr[i] = 0;
	}
	else{
	    image_arr[i] = new Image;
	    *(image_arr[i]) = *(source.image_arr[i]);
	    x_arr[i] = source.x_arr[i];
	    y_arr[i] = source.y_arr[i];
	}
    }
}

const Scene& Scene::operator=(const Scene& source){
    if(this != &source){
	clear();
	copy(source);
    }
    return *this;
}

void Scene::changemaxlayers(int newmax){
    if(max == newmax){return;}
    else if(max > newmax){
	for(int i=newmax; i<max; i++){
	    if(image_arr[i] == NULL){
		std::cout << "invalid newmax" << endl;
		return;
	    }
	}
    }

    Image** temp_image_arr = new Image*[newmax];
    int* temp_x_arr = new int[newmax];
    int* temp_y_arr = new int[newmax];

    for(int i=0; i<newmax; i++){
	if(i < max){
	    temp_image_arr[i] = new Image;
	    *(temp_image_arr[i]) = *(image_arr[i]);
	    temp_x_arr[i] = x_arr[i];
	    temp_y_arr[i] = y_arr[i];
	}
	else{
	    temp_image_arr[i] = NULL;
	    temp_x_arr = 0;
	    temp_y_arr = 0;
	}
    }
    clear();
    max = newmax;
    image_arr = temp_image_arr;
    x_arr = temp_x_arr;
    y_arr = temp_y_arr;
}

void Scene::addpicture(const char* FileName, int index, int x, int y){
    if(index < 0 || index >= max){
	std::cout << "index out of bounds" << endl;
	return;
    }
    Image* temp_image = new Image;
    string filename(FileName);
    temp_image->readFromFile(filename);
    if(image_arr[index] != NULL){
	delete image_arr[index];
	image_arr[index] = NULL;
    }
    image_arr[index] = temp_image;
    x_arr[index] = x;
    y_arr[index] = y;
}

void Scene::changelayer(int index, int newindex){
    if(index == newindex){return;}
    if(index < 0 || index >= max || newindex < 0 || newindex >= max){
	std::cout << "invalid index" << endl;
	return;
    }
    if(image_arr[newindex] != NULL){
	delete image_arr[newindex];
	image_arr[newindex] = NULL;
    }

    image_arr[newindex] = image_arr[index];
    image_arr[index] = NULL;
    x_arr[newindex] = x_arr[index];
    y_arr[newindex] = y_arr[index];
    x_arr[index] = 0;
    y_arr[index] = 0;
}

void Scene::translate(int index, int xcoord, int ycoord){
    if(index < 0 || index >= max || image_arr[index] == NULL){std::cout << "invalid index" << endl;}
    else{
	x_arr[index] = xcoord;
	y_arr[index] = ycoord;
    }
}

void Scene::deletepicture(int index){
    if(index < 0 || index >= max || image_arr[index] == NULL){std::cout << "invalid index" << endl;}
    else{
	delete image_arr[index];
	image_arr[index] = NULL;
	x_arr[index] = 0;
	y_arr[index] = 0;
    }
}

Image* Scene::getpicture(int index) const{
    Image* image_ptr = NULL;

    if(index < 0 || index >= max || image_arr[index] == NULL){std::cout << "invalid index" << endl;}
    else{image_ptr = image_arr[index];}

    return image_ptr;
}

Image Scene::drawscene() const{
    size_t width = 0;
    size_t height = 0;

    for(int i=0; i<max; i++){
	if(image_arr[i] == NULL){continue;}
	size_t curr_width = image_arr[i]->width() + (size_t)x_arr[i];
	size_t curr_height = image_arr[i]->height() + (size_t)y_arr[i];
	if(width < curr_width){width = curr_width;}
	if(height < curr_height){height = curr_height;}
    }

    Image temp_image;
    temp_image.resize(width,height);

    for(int i=0; i<max; i++){
	if(image_arr[i] == NULL){continue;}
	size_t x_offset = (size_t)x_arr[i];
	size_t y_offset = (size_t)y_arr[i];
	for(size_t y=0; y<image_arr[i]->height(); y++){
	    for(size_t x=0; x<image_arr[i]->width(); x++){
		*(temp_image(x+x_offset,y+y_offset)) = *((*image_arr[i])(x,y));
	    }
	}
    }

    return temp_image;
}
