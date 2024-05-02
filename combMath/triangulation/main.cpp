#include <iostream>
#include <iomanip>
#include "DelaunayTriangulation.h"

int main()
{
	/*std::vector<Vertex> vertices = {
		Vertex(0.0, 0.0),
		Vertex(10.0, 0.0),
		Vertex(5.0, 5.0),
		Vertex(0.0, 10.0),
		Vertex(10.0, 10.0),
	};*/
	/*std::vector<Vertex> vertices = {
		Vertex(0.0, 0.0),
		Vertex(10.0, 0.0),
		Vertex(0.0, 10.0),
		Vertex(10.0, 10.0),
	};*/
	std::vector<Vertex> vertices = {
		Vertex(0.0, 0.0),
		Vertex(10.0, 0.0),
		Vertex(0.0, 10.0),
		Vertex(2.0, 10.0),
	};

	DelaunayTriangulation dt(vertices);

	/*std::cout << "Verticies:" << std::endl;
	const auto vertexPtrs = dt.GetVertices();
	for (const auto vertexPtr : vertexPtrs)
	{
		std::cout << "(" << std::fixed << std::setprecision(2) << std::setw(6) << vertexPtr->m_x 
			<< ", " << std::fixed << std::setprecision(2) << std::setw(6) << vertexPtr->m_y << ")" 
			<< std::endl;
	}*/

	std::cout << "Edges:" << std::endl;
	const auto edgePtrs = dt.GetEdges();
	for (const auto edgePtr : edgePtrs)
	{
		std::cout << "(" << edgePtr->m_vertex1->m_x << ", " << edgePtr->m_vertex1->m_y << "), "
				  << "(" << edgePtr->m_vertex2->m_x << ", " << edgePtr->m_vertex2->m_y << ")"
				  << std::endl;
	}

	std::cout << "Triangles:" << std::endl;
	const auto trianglePtrs = dt.GetTriangles();
	for (const auto trianglePtr : trianglePtrs)
	{
		std::cout << "(" << trianglePtr->GetVertex1()->m_x << ", " << trianglePtr->GetVertex1()->m_y << "), "
			<< "(" << trianglePtr->GetVertex2()->m_x << ", " << trianglePtr->GetVertex2()->m_y << "), "
			<< "(" << trianglePtr->GetVertex3()->m_x << ", " << trianglePtr->GetVertex3()->m_y << ") "
			<< std::endl;
	}

	return EXIT_SUCCESS;
}