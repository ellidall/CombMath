#pragma once

#include "Vertex.h"

class Triangle
{
public:
	Triangle(std::shared_ptr<Vertex> vertex1, std::shared_ptr<Vertex> vertex2, std::shared_ptr<Vertex> vertex3)
		: m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
	{
	}

	std::shared_ptr<Vertex> m_vertex1;
	std::shared_ptr<Vertex> m_vertex2;
	std::shared_ptr<Vertex> m_vertex3;

	std::shared_ptr<Vertex> GetVertex1() const { return m_vertex1; }
	std::shared_ptr<Vertex> GetVertex2() const { return m_vertex2; }
	std::shared_ptr<Vertex> GetVertex3() const { return m_vertex3; }

	bool operator==(const Triangle& other) const
	{
		return (
			(*m_vertex1 == *other.m_vertex1 || *m_vertex1 == *other.m_vertex2 || *m_vertex1 == *other.m_vertex3)
			&& (*m_vertex2 == *other.m_vertex1 || *m_vertex2 == *other.m_vertex2 || *m_vertex2 == *other.m_vertex3)
			&& (*m_vertex3 == *other.m_vertex1 || *m_vertex3 == *other.m_vertex2 || *m_vertex3 == *other.m_vertex3))
			|| ((*m_vertex1 == *other.m_vertex2 || *m_vertex1 == *other.m_vertex3)
				&& (*m_vertex2 == *other.m_vertex1 || *m_vertex2 == *other.m_vertex3)
				&& (*m_vertex3 == *other.m_vertex1 || *m_vertex3 == *other.m_vertex2))
			|| ((*m_vertex1 == *other.m_vertex3) && (*m_vertex2 == *other.m_vertex2)
				&& (*m_vertex3 == *other.m_vertex1)) || ((*m_vertex1 == *other.m_vertex3)
				&& (*m_vertex2 == *other.m_vertex1) && (*m_vertex3 == *other.m_vertex2))
			|| ((*m_vertex1 == *other.m_vertex2) && (*m_vertex2 == *other.m_vertex3)
				&& (*m_vertex3 == *other.m_vertex1)) || ((*m_vertex1 == *other.m_vertex1)
				&& (*m_vertex2 == *other.m_vertex3) && (*m_vertex3 == *other.m_vertex2)
		);
	}
};