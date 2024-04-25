#pragma once

#include <algorithm>
#include "Triangle.h"

class DelaunayTriangulation
{
public:
	DelaunayTriangulation(std::vector<Vertex> vertices);

	Vertex::Vertices m_vertices;

	Vertex::Vertices GetVertices();
};