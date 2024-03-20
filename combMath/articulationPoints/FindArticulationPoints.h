#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Edge
{
	int dest;

	Edge(int d): dest(d){}
};

struct Vertex
{
	bool visited;
	int low;
	int disc;
	bool articulationPoint;

	Vertex(): visited(false), low(0), disc(0), articulationPoint(false){}
};

struct Graph
{
	std::vector<std::vector<Edge>> adjList;
	std::vector<Vertex> vertices;

	Graph(int verticesCount): adjList(verticesCount), vertices(verticesCount){}

	void addEdge(int src, int dest)
	{
		adjList[src].emplace_back(dest);
		adjList[dest].emplace_back(src);
	}
};
