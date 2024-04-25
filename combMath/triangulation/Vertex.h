#pragma once

#include <vector>
#include <memory>

class Vertex
{
public:
	using Vertices = std::vector<std::shared_ptr<Vertex>>;

	Vertex(double x, double y) : m_x(x), m_y(y) {}

	double m_x;
	double m_y;
};