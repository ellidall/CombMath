#pragma once

#include <algorithm>
#include <iostream>
#include <limits>
#include "Edge.h"

class DelaunayTriangulation
{
public:
	using Vertices = std::vector<std::shared_ptr<Vertex>>;
	using Edges = std::vector<std::shared_ptr<Edge>>;
	using Triangles = std::vector<std::shared_ptr<Triangle>>;

	DelaunayTriangulation(std::vector<Vertex> vertices);

	Vertices m_vertices;
	Edges m_edges;
	Edges m_border;
	Triangles m_triangles;

	Vertices GetVertices() const;
	Edges GetEdges() const;
	Triangles GetTriangles() const;

private:
	std::tuple<std::shared_ptr<Vertex>, std::shared_ptr<Vertex>, std::shared_ptr<Vertex>> OrientVerticesCCW(
		std::shared_ptr<Vertex>& v1, std::shared_ptr<Vertex>& v2, std::shared_ptr<Vertex>& v3) const;

	bool IsDelaunay(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;

	bool UpdateEdge(const std::shared_ptr<Edge>& existingEdge, const std::shared_ptr<Edge>& newEdge, std::shared_ptr<Triangle> triangle);

	void AddTriangleIfNotExists(const std::shared_ptr<Triangle>& triangle);

	void AddEdgeIfNotExists(const std::shared_ptr<Edge>& newEdge, const std::shared_ptr<Triangle>& triangle);

	bool IsEdgeIntersecting(const std::shared_ptr<Edge>& newEdge) const;

	void InitializeElementsIfDelaunay(std::shared_ptr<Edge>& edge);

	void BuildTriangulation();
};