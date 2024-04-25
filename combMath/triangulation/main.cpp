#include <iostream>
#include "DelaunayTriangulation.h"

int main()
{
	std::vector<Vertex> vertices = {
		Vertex(0.0, 10.0),
		Vertex(1.0, 0.0),
		Vertex(0.0, 1.0),
		Vertex(1.0, 1.0),
		Vertex(0.5, std::sqrt(0.5))
	};

	DelaunayTriangulation dt(vertices);

	const auto vertexPtrs = dt.GetVertices();
	for (const auto vertexPtr : vertexPtrs)
	{
		std::cout << "x = " << vertexPtr->m_x << "   y = " << vertexPtr->m_y << std::endl;
	}

	return EXIT_SUCCESS;
}