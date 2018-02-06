#ifndef __DSETS_H__
#define __DSETS_H__

#include <vector>

class DisjointSets{
private:
    std::vector<int> v;

public:
    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
};

#endif

