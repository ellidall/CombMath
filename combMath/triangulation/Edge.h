#pragma once

#include <memory>
#include "Vertex.h"
#include "Triangle.h"

class Edge
{
public:
	Edge(
		std::shared_ptr<Vertex> vertex1,
		std::shared_ptr<Vertex> vertex2,
		std::shared_ptr<Triangle> triangle1,
		std::shared_ptr<Triangle> triangle2
	)
		: m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_triangle1(triangle1)
		, m_triangle2(triangle2)
	{
	}

	std::shared_ptr<Vertex> m_vertex1;
	std::shared_ptr<Vertex> m_vertex2;
	std::shared_ptr<Triangle> m_triangle1;
	std::shared_ptr<Triangle> m_triangle2;

	bool operator==(const Edge& other) const
	{
		return (
			(*m_vertex1 == *other.m_vertex1 && *m_vertex2 == *other.m_vertex2) || (*m_vertex1 == *other.m_vertex2 && *m_vertex2 == *other.m_vertex1));
	}

	bool operator!=(const Edge& other) const
	{
		return (*m_vertex1 != *other.m_vertex1 || *m_vertex2 != *other.m_vertex2 || *m_vertex1 != *other.m_vertex2 || *m_vertex2 != *other.m_vertex1);
	}
};