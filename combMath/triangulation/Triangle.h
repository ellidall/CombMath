#pragma once

#include "Vertex.h"

class Triangle
{
public:
	Triangle(Vertex::Vertices vertices) : m_vertices(vertices) {}

	Vertex::Vertices m_vertices;
};