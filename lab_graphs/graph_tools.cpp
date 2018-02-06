/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    int ret = 0;
    vector<Edge> edgeVector = graph.getEdges();

    if(edgeVector.size() != 0){
	Edge edge = edgeVector[0];
	ret = edge.weight;

	for(size_t i=1; i<edgeVector.size(); i++){
	    Edge tempEdge = edgeVector[i];
	    if(ret > tempEdge.weight){
		ret = tempEdge.weight;
		edge = tempEdge;
	    }
	}
	graph.setEdgeLabel(edge.source, edge.dest, "MIN");
    }

    return ret;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    int ret = 0;

    if(start != end){
	std::unordered_map<Vertex, Vertex> p;
	std::queue<Vertex> q;
	q.push(start);

	bool flag = false;
	Vertex v;
	while(!flag && q.size() > 0){
	    v = q.front();
	    q.pop();

	    std::vector<Vertex> a = graph.getAdjacent(v);
	    for(size_t i=0; i<a.size(); i++){
		if(a[i] != end){
		    auto res = p.find(a[i]);
		    if(res == p.end()){
			p[a[i]] = v;
			q.push(a[i]);
		    }
		}
		else{
		    p[a[i]] = v;
		    flag = true;
		    break;
		}
	    }
	}
	v = end;

	for(ret=0; v != start; ret++){
	    graph.setEdgeLabel(v, p[v], "MINPATH");
	    v = p[v];
	}
    }

    return ret;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    std::vector<Edge> edgeVector = graph.getEdges();
    std::sort(edgeVector.begin(), edgeVector.end());
    std::vector<Vertex> vertexVector = graph.getVertices();
    int size = vertexVector.size();
    std::unordered_map<Vertex, int> idx;

    for(int i=0; i<size; i++){
	idx[vertexVector[i]] = i;
    }

    DisjointSets set;
    set.addelements(size);

    int count = 0;
    for(size_t i=0; i<edgeVector.size(); i++){
	Vertex tempVertex1 = edgeVector[i].source;
	Vertex tempVertex2 = edgeVector[i].dest;
	int tempIndex1 = idx[tempVertex1];
	int tempIndex2 = idx[tempVertex2];
	if(set.find(tempIndex1) != set.find(tempIndex2)){
	    set.setunion(set.find(tempIndex1), set.find(tempIndex2));
	    graph.setEdgeLabel(tempVertex1, tempVertex2, "MST");
	    count++;
	}
	if(count + 1 == size){break;}
    }
}

