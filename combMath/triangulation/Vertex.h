#pragma once

#include <vector>
#include <memory>

class Vertex
{
public:
	Vertex(double x, double y) : m_x(x), m_y(y) {}

	double m_x;
	double m_y;

	bool operator==(const Vertex& other) const
	{
		return (m_x == other.m_x && m_y == other.m_y);
	}

	bool operator!=(const Vertex& other) const
	{
		return (m_x != other.m_x || m_y != other.m_y);
	}
};