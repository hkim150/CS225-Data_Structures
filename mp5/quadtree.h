/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
    Quadtree();
    Quadtree(Quadtree const& q);
    Quadtree(PNG const& png, int res);
    ~Quadtree();
    Quadtree operator=(Quadtree const& q);
    void buildTree(PNG const& png, int res);
    RGBAPixel getPixel(int x, int y) const;
    PNG decompress() const;
    void clockwiseRotate();
    void prune(int tol);
    int pruneSize(int tol) const;
    int idealPrune(int numLeaves) const;
  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
	QuadtreeNode();
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */

    int resolution;

    QuadtreeNode* copy(QuadtreeNode* const n);
    void copy(Quadtree const& q);
    void clear(QuadtreeNode* n);
    void clear();
    Quadtree::QuadtreeNode* buildTree(PNG const& png, int res, int x, int y);
    RGBAPixel getPixel(QuadtreeNode* n, int res, int x, int y) const;
    void decompress(QuadtreeNode* n, PNG& png, int res, int x, int y) const;
    void clockwiseRotate(QuadtreeNode* q);
    void prune(QuadtreeNode* n, RGBAPixel mean);
    bool isPrune(QuadtreeNode* n1, QuadtreeNode* n2, int tol) const;
    void prune(QuadtreeNode* n, int tol);
    int pruneSize(QuadtreeNode* n, int tol) const;
    int idealPrune(int numLeaves, int lowBound, int highBound) const;


/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
