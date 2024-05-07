#include "DelaunayTriangulation.h"

int main()
{
	/*std::vector<struct Node> nodes = {
		{ 0, 0 },
		{ 10, 0 },
		{ 10, 10 },
		{ 0, 10 },
	};*/
	/*std::vector<struct Node> nodes = {
		{ 0, 0 },
		{ 10, 0 },
		{ 10, 10 },
		{ 0, 10 },
		{ 5, 5 },
	};*/
	std::vector<struct Node> nodes = {
		{ 0, 3 },
		{ 10, 0 },
		{ 5, 7 },
		{ 13, 7 },
		{ 8, 4 },
		{ 12, 11 },
		{ 0, 13 },
	};

	DelaunayTriangulation dt(nodes);

	for (auto& r : dt.GetRibs())
	{
		std::cout << "(" << r.nodes[0].x << ", " << r.nodes[0].y << "), "
				  << "(" << r.nodes[1].x << ", " << r.nodes[1].y << ")," << std::endl;
	}
	std::cout << "-------------" << std::endl;

	return EXIT_SUCCESS;
}
