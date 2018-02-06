/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
    int row, col, size;
    row = theSource.getRows();
    col = theSource.getColumns();
    size = theTiles.size();

    vector<Point<3>> p1;
    Point<3> p2, p3;
    map<Point<3>, TileImage> m;
    MosaicCanvas* ret = new MosaicCanvas(row, col);

    for(int i=0; i<size; i++){
	RGBAPixel r1 = theTiles[i].getAverageColor();
	p2[0] = (double)r1.red;
	p2[1] = (double)r1.green;
	p3[2] = (double)r1.blue;
	p1.push_back(p2);
	m.insert(pair<Point<3>, TileImage>(p2, theTiles[i]));
    }

    KDTree<3> k = KDTree<3>(p1);

    for(int i=0; i<row; i++){
	for(int j=0; j<col; j++){
	    RGBAPixel r2 = theSource.getRegionColor(i, j);
	    p3[0] = (double)r2.red;
	    p3[1] = (double)r2.green;
	    p3[2] = (double)r2.blue;
	    Point<3> p4 = k.findNearestNeighbor(p3);
	    ret->setTile(i, j, m.find(p4)->second);
	}
    }

    return ret;
}

