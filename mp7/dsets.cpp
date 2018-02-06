#include "dsets.h"

void DisjointSets::addelements(int num){
    for(int i=0; i<num; i++){
	v.push_back(-1);
    }
}

int DisjointSets::find(int elem){
    int s = v.size();
    if(elem >= 0 && elem < s){
	int r = elem;
	while(v[r] >= 0){
	    r = v[r];
	}
	while(r != elem){
	    int temp = v[elem];
	    v[elem] = r;
	    elem = temp;
	}
	return r;
    }
    return elem;
}

void DisjointSets::setunion(int a, int b){
    int s = v.size();
    if(a >= 0 && a < s && b >= 0 && b < s){
	int numA, numB;
	numA = find(a);
	numB = find(b);
	if(numA != numB){
	    if(v[numA] > v[numB]){
		v[numB] += v[numA];
		v[numA] = numB;
	    }
	    else{
		v[numA] += v[numB];
		v[numB] = numA;
	    }
	}
    }
}
