/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */

#include <iostream>
#include "quadtree.h"

Quadtree::Quadtree() : root(NULL), resolution(0){}

Quadtree::Quadtree(Quadtree const& q){copy(q);}

Quadtree::Quadtree(PNG const& png, int res){
    root = buildTree(png, res, 0, 0);
    resolution = res;
}

Quadtree::~Quadtree(){clear();}

Quadtree::QuadtreeNode::QuadtreeNode(){
    nwChild = NULL;
    neChild = NULL;
    swChild = NULL;
    seChild = NULL;
    element = RGBAPixel();
}

Quadtree::QuadtreeNode* Quadtree::copy(QuadtreeNode* const n){
    if(n != NULL){return NULL;}
    
    QuadtreeNode* ret = new QuadtreeNode();
    ret->nwChild = copy(n->nwChild);
    ret->neChild = copy(n->neChild);
    ret->swChild = copy(n->swChild);
    ret->seChild = copy(n->seChild);

    ret->element = n->element;

    return ret;
}

void Quadtree::copy(Quadtree const& q){
    root = copy(q.root);
    resolution = q.resolution;
}

Quadtree Quadtree::operator=(Quadtree const& q){
    if(this != &q){
	clear();
	copy(q);
    }
    return *this;
}

void Quadtree::clear(QuadtreeNode* n){
    if(n){
	clear(n->nwChild);
	clear(n->neChild);
	clear(n->swChild);
	clear(n->seChild);

	delete n;
	n = NULL;
    }
}

void Quadtree::clear(){
    clear(root);
    resolution = 0;
}

Quadtree::QuadtreeNode* Quadtree::buildTree(PNG const& png, int res, int x, int y){
    QuadtreeNode* ret = new QuadtreeNode();
    if(resolution == 1){
	ret->nwChild = NULL;
	ret->neChild = NULL;
	ret->swChild = NULL;
	ret->seChild = NULL;
	ret->element = *(png(x,y));
    }
    else{
	int r = res/2;
	ret->nwChild = buildTree(png, r, x, y);
	ret->neChild = buildTree(png, r, x + r, y);
	ret->swChild = buildTree(png, r, x, y + r);
	ret->seChild = buildTree(png, r, x + r, y + r);

    (ret->element).red = ((ret->neChild->element).red + (ret->seChild->element).red + (ret->nwChild->element.red) + (ret->swChild->element).red)/4;
    (ret->element).green = ((ret->neChild->element).green + (ret->seChild->element).green + (ret->nwChild->element).green + (ret->swChild->element).green)/4;
    (ret->element).blue = ((ret->neChild->element).blue + (ret->seChild->element).blue + (ret->nwChild->element).blue + (ret->swChild->element).blue)/4;
    }

    return ret;
}

void Quadtree::buildTree(PNG const& png, int res){
    root = buildTree(png, res, 0, 0);
    resolution = res;
}

RGBAPixel Quadtree::getPixel(QuadtreeNode* n, int res, int x, int y) const{
    if(n == NULL){return RGBAPixel();}
    if(resolution == 1 || n->nwChild == NULL){return n->element;}

    int r = res/2;
    int ret_x = x;
    int ret_y = y;
    QuadtreeNode* ret_node;

    if(x >= r && y >= r){ret_node = n->seChild;}
    else if(x < r && y >= r){ret_node = n->swChild;}
    else if(x >= r && y < r){ret_node = n->neChild;}
    else{ret_node = n->nwChild;}

    if(x >= r){ret_x -= r;}
    if(y >= r){ret_y -= r;}
    
    return getPixel(ret_node, r, ret_x, ret_y);
}

RGBAPixel Quadtree::getPixel(int x, int y) const{
    if(root && x >= 0 && x < resolution && y >= 0 && y < resolution){return getPixel(root, resolution, x, y);}
    return RGBAPixel();
}

void Quadtree::decompress(QuadtreeNode* n, PNG& png, int res, int x, int y) const{
    if(n->nwChild){
	int r = res/2;
	decompress(n->nwChild, png, r, x, y);
	decompress(n->neChild, png, r, x+r, y);
	decompress(n->swChild, png, r, x, y+r);
	decompress(n->seChild, png, r, x+r, y+r);
    }
    else{
	for(int i=0; i<res; i++){
	    for(int j=0; j<res; j++){
		*(png(x+i,y+j)) = n->element;
	    }
	}
    }
}

PNG Quadtree::decompress() const{
    if(root){
	PNG ret = PNG(resolution, resolution);
	decompress(root, ret, resolution, 0, 0);
	return ret;
    }
    return PNG();
}

void Quadtree::clockwiseRotate(QuadtreeNode* n){
    if(n == NULL){return;}

    QuadtreeNode* temp;

    clockwiseRotate(n->nwChild);
    clockwiseRotate(n->neChild);
    clockwiseRotate(n->swChild);
    clockwiseRotate(n->seChild);

    temp = n->nwChild;
    n->nwChild = n->swChild;
    n->swChild = n->seChild;
    n->seChild = n->neChild;
    n->neChild = temp;
}

void Quadtree::clockwiseRotate(){clockwiseRotate(root);}

bool Quadtree::isPrune(QuadtreeNode* root, QuadtreeNode* n, int tol) const{
    if(n == NULL){return true;}
    if(n->nwChild == NULL){
	int r_diff, g_diff, b_diff, diff;
	r_diff = (root->element).red - (n->element).red;
	g_diff = (root->element).green - (n->element).green;
	b_diff = (root->element).blue - (n->element).blue;
	diff = r_diff*r_diff + g_diff*g_diff + b_diff*b_diff;
	return diff <= tol ? true : false;
    }
    bool nw, ne, sw, se;
    nw = isPrune(root, n->nwChild, tol);
    ne = isPrune(root, n->neChild, tol);
    sw = isPrune(root, n->swChild, tol);
    se = isPrune(root, n->seChild, tol);
    return nw && ne && sw && se;
}

void Quadtree::prune(QuadtreeNode* n, int tol){
    if(n == NULL){return;}
    if(isPrune(n, n, tol)){
	clear(n->nwChild);
	clear(n->neChild);
	clear(n->swChild);
	clear(n->seChild);
	return;
    }
    prune(n->nwChild, tol);
    prune(n->neChild, tol);
    prune(n->swChild, tol);
    prune(n->seChild, tol);
}

void Quadtree::prune(int tol){if(root){prune(root, tol);}}

int Quadtree::pruneSize(QuadtreeNode* n, int tol) const{
    int ret = 0;
    if(n){
	if(isPrune(n, n, tol)){ret++;}
	else{
	    int nw, ne, sw, se;

	    nw = pruneSize(n->nwChild, tol);
	    ne = pruneSize(n->neChild, tol);
	    sw = pruneSize(n->swChild, tol);
	    se = pruneSize(n->seChild, tol);

	    ret = nw + ne + sw + se;
	}
    }
    return ret;
}

int Quadtree::pruneSize(int tol) const{return pruneSize(root, tol);}

int Quadtree::idealPrune(int numLeaves, int lowBound, int highBound) const{
    if(highBound - lowBound > 0){return highBound;}

    int mean, num;

    mean = (lowBound + highBound)/2;
    num = pruneSize(mean);

    return num > numLeaves ? idealPrune(numLeaves, mean, highBound) : idealPrune(numLeaves, lowBound, mean);
}

int Quadtree::idealPrune(int numLeaves) const{return idealPrune(numLeaves, 0, 255*255*3);}
