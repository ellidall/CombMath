#include "DelaunayTriangulation.h"
#include <algorithm>
#include <numbers>
#include <limits>
#include <set>

bool eqF(float const& a, float const& b)
{
	constexpr double eps = std::numeric_limits<double>::epsilon();
	return (double) abs(a - b) < eps;
}

bool operator==(Node const& n1, Node const& n2)
{
	return eqF(n1.x, n2.x) && eqF(n1.y, n2.y);
}

bool operator!=(Node const& n1, Node const& n2)
{
	return !(n1 == n2);
}

float operator^(Node const& a, Node const& b)
{
	return a.x * b.y - b.x * a.y;
}

Node operator-(Node const& a, Node const& b)
{
	return Node(a.x - b.x, a.y - b.y);
}

float operator*(Node const& a, Node const& b)
{
	return a.x * b.x + a.y * b.y;
}

bool operator==(Rib const& r1, Rib const& r2)
{
	return r1.nodes[0] == r2.nodes[0] && r1.nodes[1] == r2.nodes[1]
		|| r1.nodes[0] == r2.nodes[1] && r1.nodes[1] == r2.nodes[0];
}

bool IsRibInVector(std::vector<Rib> const& v, Rib const& rib)
{
	for (auto& r : v)
	{
		if (r != rib)
			continue;
		return true;
	}
	return false;
}

float RibDist(Rib const& rib)
{
	auto& n1 = rib.nodes[0];
	auto& n2 = rib.nodes[1];
	return sqrt((n2.x - n1.x) * (n2.x - n1.x) + (n2.y - n1.y) * (n2.y - n1.y));
}

float RibsAngle(Rib const& r1, Rib const& r2)
{
	auto& n1 = r1.nodes[0];
	auto& n2 = r1.nodes[1];
	auto& n3 = r2.nodes[0];
	auto& n4 = r2.nodes[1];
	return ((n2 - n1) * (n4 - n3)) / RibDist(r1) / RibDist(r2);
}

bool IsNodeAboveRib(Node const& node, Rib const& rib)
{
	auto& ribNode1 = rib.nodes[0];
	auto& ribNode2 = rib.nodes[1];
	return ((node - ribNode1) ^ (ribNode2 - ribNode1)) < 0;
}

void FindNextNodeToLink(
	std::vector<Node> const& nodes,
	Rib const& rib,
	std::vector<bool>& passedRibs,
	std::vector<Rib>& result)
{
	if (std::all_of(passedRibs.begin(), passedRibs.end(), [](bool v) { return v; }))
	{
		return;
	}

	float maxAngle = 2 * std::numbers::pi;
	int nodeIndex = 0;

	for (int i = 2; i < nodes.size(); ++i)
	{
		if (!IsNodeAboveRib(nodes[i], rib))
		{
			continue;
		}

		Rib tempRib1;
		tempRib1.nodes = { nodes[i], rib.nodes[0] };
		Rib tempRib2;
		tempRib2.nodes = { nodes[i], rib.nodes[1] };

		auto angle = RibsAngle(tempRib1, tempRib2);
		if (angle < maxAngle)
		{
			maxAngle = angle;
			nodeIndex = i;
		}
	}

	if (nodeIndex == 0)
		return;

	Rib findedRib1;
	findedRib1.nodes = { rib.nodes[0], nodes[nodeIndex] };
	Rib findedRib2;
	findedRib2.nodes = { nodes[nodeIndex], rib.nodes[1] };

	if (!IsRibInVector(result, findedRib1))
		result.push_back(findedRib1);
	if (!IsRibInVector(result, findedRib2))
		result.push_back(findedRib2);

	if (passedRibs[nodeIndex])
		return;
	passedRibs[nodeIndex] = true;

	FindNextNodeToLink(nodes, findedRib1, passedRibs, result);
	FindNextNodeToLink(nodes, findedRib2, passedRibs, result);
}

std::vector<Node> FindNodesOfMbo(std::vector<Node> nodes)
{
	Node n0 = nodes[0];
	for (auto& n : nodes)
		if (n.x < n0.x || (n.x == n0.x && n.y < n0.y))
			n0 = n;

	std::sort(nodes.begin(), nodes.end(), [&n0](Node a, Node b) { return ((a - n0) ^ (b - n0)) > 0; });

	std::vector<Node> hull;
	for (auto& n : nodes)
	{
		while (hull.size() >= 2)
		{
			Node new_vector = n - hull.back();
			Node last_vector = hull.back() - hull[hull.size() - 2];
			if ((new_vector ^ last_vector) > 0)
				hull.pop_back();
			else
				break;
		}
		hull.push_back(n);
	}

	return hull;
}

std::vector<Rib> LinkNotesIntoRib(std::vector<Node> const& nodes)
{
	std::vector<Rib> ribs;
	Rib firstRib;
	firstRib.nodes = { nodes[0], nodes[nodes.size() - 1] };
	ribs.push_back(firstRib);

	for (int i = 0; i < nodes.size() - 1; ++i)
	{
		Rib rib;
		rib.nodes = { nodes[i], nodes[i + 1] };
		ribs.push_back(rib);
	}

	return ribs;
}

std::vector<Rib> DelaunayTriangulation::MBO(std::vector<Node> const& nodes)
{
	return LinkNotesIntoRib(FindNodesOfMbo(nodes));
}

std::vector<Rib> DelaunayTriangulation::BuildTriangulation(std::vector<Node>& nodes)
{
	if (nodes.size() < 3)
	{
		return {};
	}

	std::sort(nodes.begin(), nodes.end(), [](Node& node1, Node& node2) { return node1.y > node2.y; });

	std::vector<Rib> result = MBO(nodes);
	std::vector<bool> passedRibs(nodes.size() + 1, false);

	Rib firstRib;
	if (nodes[0].x > nodes[1].x)
	{
		firstRib.nodes = { nodes[0], nodes[1] };
	}
	else
	{
		firstRib.nodes = { nodes[1], nodes[0] };
	}
	passedRibs[0] = passedRibs[1] = true;

	FindNextNodeToLink(nodes, firstRib, passedRibs, result);

	return result;
}
