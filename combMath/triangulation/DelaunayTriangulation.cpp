#include "DelaunayTriangulation.h"

DelaunayTriangulation::DelaunayTriangulation(std::vector<Vertex> vertices)
{
	for (const auto vertex : vertices)
	{
		const auto vertexPtr = std::make_shared<Vertex>(vertex);
		m_vertices.push_back(vertexPtr);
	}
	std::sort(m_vertices.begin(), m_vertices.end(), [](const auto& lhs, const auto& rhs) {
		return lhs->m_x < rhs->m_x;
	});
}

Vertex::Vertices DelaunayTriangulation::GetVertices()
{
	return m_vertices;
}