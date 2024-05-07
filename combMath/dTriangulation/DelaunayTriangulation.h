#pragma once

#include <iostream>
#include <vector>

struct Node
{
	float x, y;
};

struct Rib
{
	std::vector<Node> nodes;
};

class DelaunayTriangulation
{
public:
	DelaunayTriangulation(std::vector<Node>& nodes)
	{
		m_ribs = BuildTriangulation(nodes);
	}

	std::vector<Rib> GetRibs() const { return m_ribs; }

private:
	std::vector<Rib> m_ribs;

	std::vector<Rib> MBO(std::vector<Node> const& nodes);

	std::vector<Rib> BuildTriangulation(std::vector<Node>& nodes);
};