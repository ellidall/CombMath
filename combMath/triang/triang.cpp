#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>	

struct Point
{
	double x, y;
	Point(double _x, double _y)
		: x(_x)
		, y(_y)
	{
	}
	bool operator==(const Point& other) const
	{
		return x == other.x && y == other.y;
	}
};

struct Edge
{
	Point a, b;
	bool isUsedInTriangle1;
	bool isUsedInTriangle2;

	Edge(Point _a, Point _b)
		: a(_a)
		, b(_b)
		, isUsedInTriangle1(false)
		, isUsedInTriangle2(false)
	{
	}

	Edge(Point _a, Point _b, bool _isUsedInTriangle1)
		: a(_a)
		, b(_b)
		, isUsedInTriangle1(_isUsedInTriangle1)
		, isUsedInTriangle2(false)
	{
	}

	Edge(Point _a, Point _b, bool _isUsedInTriangle1, bool _isUsedInTriangle2)
		: a(_a)
		, b(_b)
		, isUsedInTriangle1(_isUsedInTriangle1)
		, isUsedInTriangle2(_isUsedInTriangle2)
	{
	}
};

struct Triangle
{
	Point a, b, c;
	Triangle(Point _a, Point _b, Point _c)
		: a(_a)
		, b(_b)
		, c(_c)
	{
	}
};

// Функция для проверки, лежит ли точка d внутри окружности, описанной вокруг треугольника abc
bool isInCircle(const Point& a, const Point& b, const Point& c, const Point& d)
{
	double ax = a.x - d.x, ay = a.y - d.y;
	double bx = b.x - d.x, by = b.y - d.y;
	double cx = c.x - d.x, cy = c.y - d.y;
	double ab = ax * (by - cy) - ay * (bx - cx);
	double bc = bx * (cy - ay) - by * (cx - ax);
	double ca = cx * (ay - by) - cy * (ax - bx);
	return (ab * bc > 0) && (bc * ca > 0);
}

bool isDelaunay(const std::vector<Point>& points, const Triangle& t)
{
	const Point& p1 = t.a;
	const Point& p2 = t.b;
	const Point& p3 = t.c;

	double a1 = p2.x - p1.x;
	double b1 = p2.y - p1.y;
	double c1 = (a1 * a1 + b1 * b1) / 2;

	double a2 = p3.x - p1.x;
	double b2 = p3.y - p1.y;
	double c2 = (a2 * a2 + b2 * b2) / 2;

	double det = a1 * b2 - a2 * b1;
	if (std::abs(det) < 1e-10)
		return false;

	double x = (b2 * c1 - b1 * c2) / det;
	double y = (a1 * c2 - a2 * c1) / det;

	for (const Point& p : points)
	{
		if (p != p1 && p != p2 && p != p3)
		{
			double dx = p.x - x;
			double dy = p.y - y;
			if (dx * dx + dy * dy < (p1.x - x) * (p1.x - x) + (p1.y - y) * (p1.y - y))
				return false;
		}
	}

	return true;
}

// Функция для построения триангуляции Делоне
std::vector<Triangle> delaunayTriangulation(std::vector<Point>& points)
{
	std::vector<Triangle> triangles;
	std::vector<Edge> edges;
	Edge initialEdge(points[0], points[1], true);
	edges.push_back(initialEdge);

	for (size_t i = 2; i < points.size(); i++)
	{
		Triangle t(initialEdge.a, initialEdge.b, points[i]);
		if (isDelaunay(points, t))
		{
			triangles.push_back(t);
			Edge e1(initialEdge.a, points[i]);
			Edge e1(initialEdge.b, points[i]);
			break;
		}
	}







	//// Создание супертреугольника, содержащего все точки
	//double minX = points[0].x, minY = points[0].y;
	//double maxX = points[0].x, maxY = points[0].y;
	//for (const Point& p : points)
	//{
	//	minX = std::min(minX, p.x);
	//	minY = std::min(minY, p.y);
	//	maxX = std::max(maxX, p.x);
	//	maxY = std::max(maxY, p.y);
	//}
	//double dx = maxX - minX;
	//double dy = maxY - minY;
	//double deltaMax = std::max(dx, dy);
	//Point a(minX - 20 * deltaMax, minY - 2 * deltaMax);
	//Point b(minX - 20 * deltaMax, maxY + 2 * deltaMax);
	//Point c(maxX + 20 * deltaMax, maxY + 2 * deltaMax);
	//triangles.emplace_back(a, b, c);

	//// Добавление точек и обновление триангуляции
	//for (const Point& p : points)
	//{
	//	std::vector<Triangle> badTriangles;
	//	for (const Triangle& t : triangles)
	//	{
	//		if (isInCircle(t.a, t.b, t.c, p))
	//		{
	//			badTriangles.push_back(t);
	//		}
	//	}
	//	std::vector<Point> polygon;
	//	for (const Triangle& t : badTriangles)
	//	{
	//		polygon.push_back(t.a);
	//		polygon.push_back(t.b);
	//		polygon.push_back(t.c);
	//		triangles.erase(std::remove_if(triangles.begin(), triangles.end(), [&](const Triangle& t) {
	//			return (t.a == t.a) || (t.b == p) || (t.c == p);
	//		}),
	//			triangles.end());
	//	}
	//	for (const Point& vertex : polygon)
	//	{
	//		triangles.emplace_back(vertex, p, polygon[(polygon.size() + 1) % polygon.size()]);
	//	}
	//}

	//// Удаление всех треугольников, содержащих вершины супертреугольника
	//triangles.erase(std::remove_if(triangles.begin(), triangles.end(), [&](const Triangle& t) {
	//	return (t.a == a || t.a == b || t.a == c || t.b == a || t.b == b || t.b == c || t.c == a || t.c == b || t.c == c);
	//}),
	//	triangles.end());

	return triangles;
}

int main()
{
	std::vector<Point> points = {
		Point(0.0, 0.0),
		Point(10.0, 0.0),
		Point(5.0, 5.0),
		Point(0.0, 10.0),
		Point(10.0, 10.0),
	};

	std::sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
		return p1.y < p2.y;
	});

	std::vector<Triangle> triangles = delaunayTriangulation(points);

	std::cout << "Delaunay Triangulation:" << std::endl;
	for (const Triangle& t : triangles)
	{
		std::cout << "(" << t.a.x << ", " << t.a.y << ") ";
		std::cout << "(" << t.b.x << ", " << t.b.y << ") ";
		std::cout << "(" << t.c.x << ", " << t.c.y << ")" << std::endl;
	}

	return 0;
}