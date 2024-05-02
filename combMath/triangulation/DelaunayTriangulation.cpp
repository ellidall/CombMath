#include "DelaunayTriangulation.h"

DelaunayTriangulation::Vertices DelaunayTriangulation::GetVertices() const { return m_vertices; }

DelaunayTriangulation::Edges DelaunayTriangulation::GetEdges() const { return m_edges; }

DelaunayTriangulation::Triangles DelaunayTriangulation::GetTriangles() const { return m_triangles; }

std::tuple<std::shared_ptr<Vertex>, std::shared_ptr<Vertex>, std::shared_ptr<Vertex>> DelaunayTriangulation::OrientVerticesCCW(
	std::shared_ptr<Vertex>& v1, std::shared_ptr<Vertex>& v2, std::shared_ptr<Vertex>& v3) const
{
	// Ќайдем центральную точку
	double centerX = (v1->m_x + v2->m_x + v3->m_x) / 3.0;
	double centerY = (v1->m_y + v2->m_y + v3->m_y) / 3.0;
	std::cout << "CenterX: " << centerX << ", CenterY: " << centerY << std::endl;
	// —оздаем вектор указателей на вершины
	std::vector<std::shared_ptr<Vertex>> vertices = { v1, v2, v3 };

	// —ортируем вершины по углу, который они образуют с центром
	std::sort(vertices.begin(), vertices.end(), [&](const auto& vertex1, const auto& vertex2) {
		double angle1 = std::atan2(vertex1->m_y - centerY, vertex1->m_x - centerX);
		double angle2 = std::atan2(vertex2->m_y - centerY, vertex2->m_x - centerX);
		return angle1 < angle2;
	});

	// ¬озвращаем отсортированные вершины
	return std::make_tuple(vertices[0], vertices[1], vertices[2]);
}

//bool DelaunayTriangulation::IsDelaunay(const Vertex& v1, const Vertex& v2, const Vertex& v3) const
//{
//	// ѕровер€ем, чтобы вершины треугольника были различными
//	if (v1 == v2 || v1 == v3 || v2 == v3)
//		return false;
//
//	// ќриентируем вершины против часовой стрелки
//	std::shared_ptr<Vertex> orientedV1 = std::make_shared<Vertex>(v1);
//	std::shared_ptr<Vertex> orientedV2 = std::make_shared<Vertex>(v2);
//	std::shared_ptr<Vertex> orientedV3 = std::make_shared<Vertex>(v3);
//	std::tie(orientedV1, orientedV2, orientedV3) = OrientVerticesCCW(orientedV1, orientedV2, orientedV3);
//	std::cout << "Oriented: " << std::endl;
//	std::cout << "(" << orientedV1->m_x << ", " << orientedV1->m_y << "), "
//			  << "(" << orientedV2->m_x << ", " << orientedV2->m_y << "), "
//			  << "(" << orientedV3->m_x << ", " << orientedV3->m_y << ")" << std::endl;
//
//	double ax = orientedV1->m_x - orientedV3->m_x;
//	double ay = orientedV1->m_y - orientedV3->m_y;
//	double bx = orientedV2->m_x - orientedV3->m_x;
//	double by = orientedV2->m_y - orientedV3->m_y;
//	double cx = orientedV1->m_x - orientedV2->m_x;
//	double cy = orientedV1->m_y - orientedV2->m_y;
//
//	double ab = ax * by - ay * bx;
//	double ac = ax * cy - ay * cx;
//	double bc = bx * cy - by * cx;
//	double cc = cx * cx + cy * cy;
//
//	// ѕровер€ем, чтобы определитель матрицы не был близок к нулю
//	if (std::abs(cc) < std::numeric_limits<double>::epsilon())
//		return false;
//
//	double circumcenterX = (ab * (orientedV2->m_y + orientedV3->m_y) + ac * (orientedV1->m_y + orientedV3->m_y) + bc * (orientedV1->m_y + orientedV2->m_y)) / (2 * cc);
//	double circumcenterY = (ab * (orientedV2->m_x + orientedV3->m_x) + ac * (orientedV1->m_x + orientedV3->m_x) + bc * (orientedV1->m_x + orientedV2->m_x)) / (2 * cc);
//
//	double radiusSquared = (orientedV1->m_x - circumcenterX) * (orientedV1->m_x - circumcenterX) + (orientedV1->m_y - circumcenterY) * (orientedV1->m_y - circumcenterY);
//
//	for (const std::shared_ptr<Vertex>& vertexPtr : m_vertices)
//	{
//		const Vertex& vertex = *vertexPtr;
//		if (!(vertex == *orientedV1) && !(vertex == *orientedV2) && !(vertex == *orientedV3))
//		{
//			double distanceSquared = (vertex.m_x - circumcenterX) * (vertex.m_x - circumcenterX) + (vertex.m_y - circumcenterY) * (vertex.m_y - circumcenterY);
//			if (distanceSquared < radiusSquared)
//			{
//				return false;
//			}
//		}
//	}
//
//	return true;
//}

bool DelaunayTriangulation::IsDelaunay(const Vertex& v2, const Vertex& v3, const Vertex& v4) const
{
	if (v2 == v3 || v3 == v4 || v4 == v2)
		return false;

	bool isDelaunay = true;
	for (const auto& vertexPtr : m_vertices)
	{
		const Vertex v1 = *vertexPtr;
		float s1 = (v1.m_x - v2.m_x) * (v1.m_x - v4.m_x) + (v1.m_y - v2.m_y) * (v1.m_y - v4.m_y);
		float s2 = (v3.m_x - v2.m_x) * (v3.m_x - v4.m_x) + (v3.m_y - v2.m_y) * (v3.m_y - v4.m_y);

		if (s1 < 0 && s2 < 0)
		{
			return false;
		}
		if (s1 >= 0 && s2 >= 0)
		{
			isDelaunay = isDelaunay && true;
			continue;
		}

		const bool check = ((v1.m_x - v2.m_x) * (v1.m_y - v4.m_y) - (v1.m_x - v4.m_x) * (v1.m_y - v2.m_y))
			* ((v3.m_x - v2.m_x) * (v3.m_x - v4.m_x) + (v3.m_y - v2.m_y) * (v3.m_y - v4.m_y))
			+ ((v1.m_x - v2.m_x) * (v1.m_x - v4.m_x) + (v1.m_y - v2.m_y) * (v1.m_y - v4.m_y))
			* ((v3.m_x - v2.m_x) * (v3.m_y - v4.m_y) - (v3.m_x - v4.m_x) * (v3.m_y - v2.m_y))
			>= 0.0;
		isDelaunay = isDelaunay && check; 
	}
	return isDelaunay;
}

void DelaunayTriangulation::AddTriangleIfNotExists(const std::shared_ptr<Triangle>& triangle)
{
	bool isTriangleExist = false;
	for (const auto& existingTriangle : m_triangles)
	{
		if (*existingTriangle == *triangle)
		{
			isTriangleExist = true;
		}
	}
	if (!isTriangleExist)
	{
		m_triangles.push_back(triangle);
	}
}

bool DelaunayTriangulation::UpdateEdge(const std::shared_ptr<Edge>& existingEdge,
	const std::shared_ptr<Edge>& newEdge, std::shared_ptr<Triangle> triangle)
{
	if (*existingEdge == *newEdge)
	{
		if (existingEdge->m_triangle1 == nullptr)
		{
			existingEdge->m_triangle1 = triangle;
		}
		else if (existingEdge->m_triangle1 != nullptr && existingEdge->m_triangle2 == nullptr)
		{
			existingEdge->m_triangle2 = triangle;
		}
		return true;
	}
	return false;
}

void DelaunayTriangulation::AddEdgeIfNotExists(const std::shared_ptr<Edge>& newEdge, const std::shared_ptr<Triangle>& triangle)
{
	if (!std::any_of(m_edges.begin(), m_edges.end(), [&](const auto& existingEdge)
		{ return UpdateEdge(existingEdge, newEdge, triangle); }))
	{
		m_edges.push_back(newEdge);
	}
}

// провер€ть направлоение по веторному произведению
bool DelaunayTriangulation::IsEdgeIntersecting(const std::shared_ptr<Edge>& newEdge) const
{
	for (const auto& existingEdge : m_edges)
	{
		const auto& p1 = existingEdge->m_vertex1;
		const auto& p2 = existingEdge->m_vertex2;
		const auto& q1 = newEdge->m_vertex1;
		const auto& q2 = newEdge->m_vertex2;

		double vp1q1x = q1->m_x - p1->m_x;
		double vp1q1y = q1->m_y - p1->m_y;
		double vp1q2x = q2->m_x - p1->m_x;
		double vp1q2y = q2->m_y - p1->m_y;
		double vp2q1x = q1->m_x - p2->m_x;
		double vp2q1y = q1->m_y - p2->m_y;
		double vp2q2x = q2->m_x - p2->m_x;
		double vp2q2y = q2->m_y - p2->m_y;

		double cross1 = vp1q1x * vp1q2y - vp1q1y * vp1q2x;
		double cross2 = vp2q1x * vp2q2y - vp2q1y * vp2q2x;

		// ≈сли векторные произведени€ имеют противоположные знаки, то отрезки пересекаютс€
		if (cross1 * cross2 < 0)
			return true;
	}
	return false;
}

void DelaunayTriangulation::InitializeElementsIfDelaunay(std::shared_ptr<Edge>& edge)
{
	std::shared_ptr<Vertex> v1 = edge->m_vertex1;
	std::shared_ptr<Vertex> v2 = edge->m_vertex2;

	double centerX = (v1->m_x + v2->m_x) / 2.0;
	double centerY = (v1->m_y + v2->m_y) / 2.0;

	std::shared_ptr<Vertex> v3 = nullptr;
	double maxAngle = -1.0;

	for (size_t i = 2; i < m_vertices.size(); i++)
	{
		std::shared_ptr<Vertex> candidate = m_vertices[i];
		// ¬ычисл€ем угол между векторами v1->v3 и v2->v3
		double angle = std::atan2(candidate->m_y - centerY, candidate->m_x - centerX);

		if (angle > maxAngle)
		{
			// ѕровер€ем, что треть€ вершина не лежит на пр€мой, проход€щей через v1 и v2
			if (!((candidate == v1) || (candidate == v2)))
			{
				v3 = candidate;
				maxAngle = angle;
				auto triangle = std::make_shared<Triangle>(v1, v2, v3);

				auto newEdge1 = std::make_shared<Edge>(v1, v2, triangle, nullptr);
				auto newEdge2 = std::make_shared<Edge>(v2, v3, triangle, nullptr);
				auto newEdge3 = std::make_shared<Edge>(v3, v1, triangle, nullptr);
				if (IsEdgeIntersecting(newEdge1) || IsEdgeIntersecting(newEdge2) || IsEdgeIntersecting(newEdge3))
					continue;
				AddEdgeIfNotExists(newEdge1, triangle);
				AddEdgeIfNotExists(newEdge2, triangle);
				AddEdgeIfNotExists(newEdge3, triangle);

				AddTriangleIfNotExists(triangle);

				break;
			}
		}
	}

	for (size_t i = 2; i < m_vertices.size(); i++)
	{
		std::shared_ptr<Vertex> v3 = m_vertices[i];
		if (IsDelaunay(*v1, *v2, *v3))
		{
			auto triangle = std::make_shared<Triangle>(v1, v2, v3);

			auto newEdge1 = std::make_shared<Edge>(v1, v2, triangle, nullptr);
			auto newEdge2 = std::make_shared<Edge>(v2, v3, triangle, nullptr);
			auto newEdge3 = std::make_shared<Edge>(v3, v1, triangle, nullptr);
			if (IsEdgeIntersecting(newEdge1) || IsEdgeIntersecting(newEdge2) || IsEdgeIntersecting(newEdge3))
				continue;
			AddEdgeIfNotExists(newEdge1, triangle);
			AddEdgeIfNotExists(newEdge2, triangle);
			AddEdgeIfNotExists(newEdge3, triangle);

			AddTriangleIfNotExists(triangle);
			
			break;
		}
	}
}

void DelaunayTriangulation::BuildTriangulation()
{
	auto initialEdge = std::make_shared<Edge>(m_vertices[0], m_vertices[1], nullptr, nullptr);
	m_edges.push_back(initialEdge);

	size_t index = 0;
	while (index < m_edges.size())
	{
		InitializeElementsIfDelaunay(m_edges[index]);
		++index;
	}

	return;
}

DelaunayTriangulation::DelaunayTriangulation(std::vector<Vertex> vertices)
{
	for (const Vertex& vertex : vertices)
	{
		const auto vertexPtr = std::make_shared<Vertex>(vertex);
		m_vertices.emplace_back(vertexPtr);
	}
	std::sort(m_vertices.begin(), m_vertices.end(), [](const std::shared_ptr<Vertex>& v1, const std::shared_ptr<Vertex>& v2) {
		return v1->m_y < v2->m_y;
	});

	BuildTriangulation();
}