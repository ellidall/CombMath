#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../articulationPoints/FindArticulationPoints.h"

using namespace std;

SCENARIO("FindArticulationPoints")
{
	WHEN("Graph of two vertices")
	{
		Graph graph(2);
		graph.addEdge(0, 1);

		THEN("Ñorrect execution of the program")
		{
			REQUIRE(FindArticulationPoints(graph).empty());
		}
	}

	WHEN("Large dihedral graph")
	{
		Graph graph(6);
		graph.addEdge(0, 1);
		graph.addEdge(1, 2);
		graph.addEdge(2, 3);
		graph.addEdge(3, 4);
		graph.addEdge(4, 5);
		graph.addEdge(5, 0);

		THEN("Ñorrect execution of the program")
		{
			REQUIRE(FindArticulationPoints(graph).empty());
		}
	}

	WHEN("Complete graph")
	{
		Graph graph(6);
		graph.addEdge(0, 1);
		graph.addEdge(0, 2);
		graph.addEdge(0, 3);
		graph.addEdge(0, 4);
		graph.addEdge(0, 5);
		graph.addEdge(1, 2);
		graph.addEdge(1, 3);
		graph.addEdge(1, 4);
		graph.addEdge(1, 5);
		graph.addEdge(2, 3);
		graph.addEdge(2, 4);
		graph.addEdge(2, 5);
		graph.addEdge(3, 4);
		graph.addEdge(3, 5);
		graph.addEdge(4, 5);
		graph.addEdge(5, 0);

		THEN("Ñorrect execution of the program")
		{
			REQUIRE(FindArticulationPoints(graph).empty());
		}
	}

	WHEN("Large strongly connected but incomplete graph")
	{
		Graph graph(11);
		graph.addEdge(0, 1);
		graph.addEdge(0, 6);
		graph.addEdge(6, 8);
		graph.addEdge(8, 7);
		graph.addEdge(8, 9);
		graph.addEdge(1, 10);
		graph.addEdge(1, 2);
		graph.addEdge(2, 4);
		graph.addEdge(4, 3);
		graph.addEdge(3, 5);

		std::vector<size_t> expectedVector = { 0, 1, 2, 3, 4, 6, 8 };

		THEN("Ñorrect execution of the program")
		{
			REQUIRE(FindArticulationPoints(graph) == expectedVector);
		}
	}

	WHEN("An arbitrary graph")
	{
		Graph graph = InitializeGraph();
		std::vector<size_t> expectedVector = { 1, 3 };

		THEN("Ñorrect execution of the program")
		{
			REQUIRE(FindArticulationPoints(graph) == expectedVector);
		}
	}
}