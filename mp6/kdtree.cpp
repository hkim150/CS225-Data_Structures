/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    return first[curDim] == second[curDim] ? (first < second ? true : false) : (first[curDim] < second[curDim] ? true : false);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int pot = 0;
    int cur = 0;

    for(int i=0; i<Dim; i++){
	pot += pow((potential[i] - target[i]), 2);
	cur += pow((currentBest[i] - target[i]), 2);
    }

    return pot == cur ? (potential < currentBest ? true : false) : (pot < cur ? true : false);
}

template <int Dim>
int KDTree<Dim>::partition(int dim, int piv, int start, int end){
    int ret = start;
    Point<Dim> val = points[piv];
    swap(piv, end);
    
    for(int i=start; i<end; i++){
	if(smallerDimVal(points[i], val, dim) || points[i] == val){
	    swap(i, ret);
	    ret++;
	}
    }
    swap(end, ret);

    return ret;
}

template <int Dim>
void KDTree<Dim>::choose(int dim, int mean, int start, int end){
    if(start < end){
	int piv = start;
	int newPiv = partition(dim, piv, start, end);
	if(newPiv != mean){
	    newPiv < mean ? choose(dim, mean, newPiv+1, end) : choose(dim, mean, start, newPiv-1);
	}
    }
}

template <int Dim>
void KDTree<Dim>::swap(int start, int end){
    Point<Dim> temp = points[start];
    points[start] = points[end];
    points[end] = temp;
}

template <int Dim>
void KDTree<Dim>::buildTree(int dim, int start, int end){
    if(start < end){
	int mean = (start + end)/2;
	choose(dim, mean, start, end);
	if(start < mean){buildTree((dim+1)%Dim, start, mean-1);}
	if(mean < end){buildTree((dim+1)%Dim, mean+1, end);}
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if(!newPoints.empty()){
	points = newPoints;
	buildTree(0, 0, newPoints.size()-1);
    }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, const Point<Dim>& p, int dim, int start, int end) const{
    Point<Dim> cur = p;
    if(start != end){
	int mean = (start + end)/2;
	bool flag = true;
	if(smallerDimVal(query, points[mean], dim) && start < mean){cur = findNearestNeighbor(query, cur, (dim+1)%Dim, start, mean-1);}
	if(smallerDimVal(points[mean], query, dim) && end > mean){
	    cur = findNearestNeighbor(query, cur, (dim+1)%Dim, mean+1, end);
	    flag = false;
	}
	if(shouldReplace(query, cur, points[mean])){cur = points[mean];}

	int diff = pow(points[mean][dim] - query[dim], 2);
	int diff2 = 0;

	for(int i=0; i<Dim; i++){
	    diff2 += pow((query[i] - cur[i]), 2);
	}

	if(!(diff > diff2)){
	    if(flag && end > mean){cur = findNearestNeighbor(query, cur, (dim+1)%Dim, mean+1, end);}
	    if(!flag && start < mean){cur = findNearestNeighbor(query, cur, (dim+1)%Dim, start, mean-1);}
	}
    }
    else{cur = shouldReplace(query, cur, points[start]) ? points[start] : p;}
    return cur;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    if(!points.empty()){
	Point<Dim> p = points[(points.size()-1)/2];
	return findNearestNeighbor(query, p, 0, 0, points.size()-1);
    }
    return Point<Dim>();
}

