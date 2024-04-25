#pragma once

#include <memory>
#include "Vertex.h"
#include "Triangle.h"

class Edge
{
public:
	using Triangles = std::vector<std::shared_ptr<Triangle>>;

	Edge(Vertex::Vertices vertices, Triangles triangles)
		: m_vertices(vertices)
		, m_triangles(triangles)
	{
	}

	Vertex::Vertices m_vertices;
	Triangles m_triangles;
};