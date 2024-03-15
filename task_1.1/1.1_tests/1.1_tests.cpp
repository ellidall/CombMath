#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../1.1/FindMinCost.h"

using namespace std;

SCENARIO("GetGraphSizeFromFile")
{
	WHEN("Ñorrect input")
	{
		istringstream input("10\n1 2\n3 4");

		THEN("Ñorrect input")
		{
			REQUIRE(GetGraphSizeFromFile(input) == 10);
		}
	}

	WHEN("Graph size is not initialized correctly")
	{
		istringstream input("10 1\n1 2\n3 4");

		THEN("Exception")
		{
			REQUIRE_THROWS_AS(GetGraphSizeFromFile(input), invalid_argument);
		}
	}
}

SCENARIO("FindMinCostUnchecked")
{
	WHEN("Correct graph")
	{
		vector<std::vector<int>> graph = {
			{0, 2, 3},
			{1, 0, 3},
			{1, 2, 0}
		};
		vector<int> minPath;

		THEN("Correct return")
		{
			REQUIRE(FindMinCostUnchecked(graph, minPath) == 6);
		}
	}
}

SCENARIO("CopyGraphWithFindingMinCost")
{
	WHEN("Unable to open input file")
	{
		string inputFileName = "123";
		vector<int> minPath;

		THEN("Error: Unable to open input file")
		{
			REQUIRE_THROWS_AS(CopyGraphWithFindingMinCost(inputFileName, minPath), ios_base::failure);
		}
	}

	WHEN("Graph is 'incomplete'")
	{
		string inputFileName = "incomplete_graph.txt";
		vector<int> minPath;

		THEN("Error: graph is 'incomplete'")
		{
			REQUIRE_THROWS_AS(CopyGraphWithFindingMinCost(inputFileName, minPath), invalid_argument);
		}
	}

	WHEN("Number of elements does not match the dimension of the graph")
	{
		string inputFileName = "incomplete_graph.txt";
		vector<int> minPath;

		THEN("Error: graph is not built correctly")
		{
			REQUIRE_THROWS_AS(CopyGraphWithFindingMinCost(inputFileName, minPath), invalid_argument);
		}
	}

	WHEN("Number of rows does not match the dimension of the graph")
	{
		string inputFileName = "incomplete_graph.txt";
		vector<int> minPath;

		THEN("Error: graph is not built correctly")
		{
			REQUIRE_THROWS_AS(CopyGraphWithFindingMinCost(inputFileName, minPath), invalid_argument);
		}
	}

	WHEN("Correct input file")
	{
		string inputFileName = "./1.1/x64/Release/input10.txt";
		vector<int> minPath;

		THEN("Correct return")
		{
			REQUIRE(CopyGraphWithFindingMinCost(inputFileName, minPath) == 460);
		}
	}
}