#include "maze.h"

using namespace std;

SquareMaze::SquareMaze() : width(0), height(0){
    downWall.clear();
    rightWall.clear();
    exit = -1;
}

void SquareMaze::makeMaze(int width, int height){
    this->width = width;
    this->height = height;

    int s = width * height;
    srand(time(NULL));

    downWall.clear();
    rightWall.clear();

    downWall = std::vector<bool>(s, true);
    rightWall = std::vector<bool>(s, true);

    DisjointSets dSets;
    dSets.addelements(s);

    for(int i=0; i<s-1; ){
	for(int j=0; j<s; j++){
	    int randNum = (rand()%10)/10.0;
	    if(randNum <= 0.9){
		bool flag = rand()%10 > 4 ? true : false;
		if((!flag || width!=(j%width+1)) && (flag || height!=(j/width+1)) && (!flag || dSets.find(j)!=dSets.find(j+1)) && (flag || dSets.find(j)!=dSets.find(j+width))){
		    if(flag){
			dSets.setunion(j, j + 1);
			rightWall[j] = false;
		    }
		    else{
			dSets.setunion(j, j + width);
			downWall[j] = false;
		    }
		    i++;
		}
	    }
	}
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
    bool ret = false;
    int idx = y*width + x;
    if(x>=0 && y>=0 && x<width && y<height){
	if((dir!=0 || x!=width-1) && (dir!=1 || y!=height-1) && (dir!=2 || x!=0) && (dir!=3 || y!=0)){
	    switch(dir){
	    case 0:	ret = rightWall[idx]		? false : true;	break;
	    case 1:	ret = downWall[idx]		? false : true;	break;
	    case 2:	ret = rightWall[idx-1]		? false : true;	break;
	    case 3:	ret = downWall[idx-width]	? false : true; break;
	    }
	}
    }
    return ret;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    int idx = y * width + x;
    switch(dir){
    case 0:	rightWall[idx] = exists;	break;
    case 1:	downWall[idx] = exists;		break;
    }
}

std::vector<int> SquareMaze::solveMaze(){
    int index, idx, x, y, z, s;
    s = width * height;

    std::vector<int> ret;
    std::vector<int> out;
    std::vector<int> length(s, -1);
    std::vector<int> parent(s, -1);
    std::vector<int> path(s, -1);
    std::queue<int> q;

    q.push(0);

    while(!q.empty()){
	idx = q.front();
	x = idx % width;
	y = idx / width;
	for(int i=0; i<4; i++){
	    z = (i%2==0) ? 1 : width;
	    if(i > 1){z *= -1;}
	    index = idx + z;
	    if(canTravel(x, y, i)){
		if(length[index] < 0){
		    length[index] = length[idx] + 1;
		    path[index] = i;
		    parent[index] = idx;
		    q.push(index);
		}
	    }
	}
	q.pop();
    }

    int curr_d, temp_d, temp_exit;
    curr_d = -1;

    for(int i=width*(height-1); i<s; i++){
	temp_d = length[i];
	if(curr_d < temp_d){
	    curr_d = temp_d;
	    exit = i;
	}
    }
    temp_exit = exit;

    while(temp_exit > 0){
	out.push_back(path[temp_exit]);
	temp_exit = parent[temp_exit];
    }
    ret.clear();

    while(!out.empty()){
	ret.push_back(out.back());
	out.pop_back();
    }

    return ret;
}


PNG* SquareMaze::drawMaze() const{
    PNG* ret = new PNG(width*10+1, height*10+1);
    bool flag = true;
    int k, l, m, n, s;
    s = width * height;
    k = width;
    n = 10;
    for(int j=0; j<2; j++){
	for(int i=n; i<k*10+1; i++){
	    if(flag){l = i; m = 0;}
	    else{l = 0;	m = i;}
	    (*ret)(l,m)->red = 0;
	    (*ret)(l,m)->green = 0;
	    (*ret)(l,m)->blue = 0;
    	}
	k = height;
	n = 0;
	flag = false;
    }

    for(int i=0; i<s; i++){
	int x, y;
	x = i % width;
	y = i / width;

	if(rightWall[i]){
	    for(int j=0; j<=10; j++){
		(*ret)(x*10+10, y*10+j)->red = 0;
		(*ret)(x*10+10, y*10+j)->green = 0;
		(*ret)(x*10+10, y*10+j)->blue = 0;
	    }
	}
	if(downWall[i]){
	    for(int j=0; j<=10; j++){
		(*ret)(x*10+j, y*10+10)->red = 0;
		(*ret)(x*10+j, y*10+10)->green = 0;
		(*ret)(x*10+j, y*10+10)->blue = 0;
	    }
	}
    }

    return ret;
}

PNG* SquareMaze::drawMazeWithSolution(){
    PNG* ret = drawMaze();
    std::vector<int> solve = solveMaze();
    int s, x, y, exit_x, exit_y;
    s = solve.size();
    x = 5; y = 5;
    exit_x = exit % width;
    exit_y = exit / width;

    for(int i=0; i<s; i++){
	int j, k, l, m, n;
	bool isX, flip;

	switch(solve[i]){
	case 0:	isX=true;	flip=false;	j=10;	k=0;	break;
	case 1:	isX=false;	flip=false;	j=0;	k=10;	break;
	case 2:	isX=true;	flip=true;	j=-10;	k=0;	break;
	case 3:	isX=false;	flip=true;	j=0;	k=-10;	break;
	}

	m = 0;	n = 0;
	for(l=0; l<=10; l++){
	    if(isX){m = l;} else{n = l;}
	    if(flip){m *= -1; n *= -1;}
	    (*ret)(x+m, y+n)->red = 255;
	    (*ret)(x+m, y+n)->green = 0;
	    (*ret)(x+m, y+n)->blue = 0;
	}

	x += j;
	y += k;
    }

    for(int i=1; i<=9; i++){
	(*ret)(exit_x*10+i, exit_y*10+10)->red = 255;
	(*ret)(exit_x*10+i, exit_y*10+10)->green = 255;
	(*ret)(exit_x*10+i, exit_y*10+10)->blue = 255;
    }

    return ret;
}
