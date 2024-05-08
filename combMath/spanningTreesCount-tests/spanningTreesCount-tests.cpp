#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../spanningTreesCount/SpanningTrees.h"

TEST_CASE("Test BuildKirchhoffMatrixByAdjacencyMatrix")
{
	const Matrix adjacencyMatrix = {
		{ 0, 1, 1, 0 },
		{ 1, 0, 1, 1 },
		{ 1, 1, 0, 1 },
		{ 0, 1, 1, 0 }
	};
	const Matrix kirchhoffMatrix = BuildKirchhoffMatrixByAdjacencyMatrix(adjacencyMatrix);
	const Matrix expectedMatrix = {
		{  2, -1, -1,  0 },
		{ -1,  3, -1, -1 },
		{ -1, -1,  3, -1 },
		{  0, -1, -1,  2 },
	};

	REQUIRE(AreMatricesEqual(kirchhoffMatrix, expectedMatrix));
}

TEST_CASE("Test CreateMinorMatrix")
{
	const Matrix matrix = {
		{ 0, 1, 1, 0 },
		{ 1, 0, 1, 1 },
		{ 1, 1, 0, 1 },
		{ 0, 1, 1, 0 }
	};
	const Matrix minor = CreateMinorMatrix(matrix, 0);
	const Matrix expectedMatrix = {
		{ 0, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 0 }
	};

	REQUIRE(AreMatricesEqual(minor, expectedMatrix));
}

TEST_CASE("Test GetMatrixDet")
{
	WHEN("det = 0")
	{
		Matrix matrix = {
			{ 2, -1, -1, 0 },
			{ -1, 3, -1, -1 },
			{ -1, -1, 3, -1 },
			{ 0, -1, -1, 2 }
		};
		int det = GetMatrixDet(matrix);
		REQUIRE(det == 0);
	}
	WHEN("det <> 0")
	{
		Matrix matrix = {
			{ 3, -1, -1 },
			{ -1, 3, -1 },
			{ -1, -1, 2 }
		};
		int det = GetMatrixDet(matrix);
		REQUIRE(det == 8);
	}
}

TEST_CASE("Test CountSpanningTreesByKirchhoffMatrix")
{
	WHEN("Arbitrary adjacency matrix")
	{
		const Matrix adjacencyMatrix = {
			{ 0, 1, 1, 0 },
			{ 1, 0, 1, 1 },
			{ 1, 1, 0, 1 },
			{ 0, 1, 1, 0 }
		};
		const Matrix kirchhoffMatrix = BuildKirchhoffMatrixByAdjacencyMatrix(adjacencyMatrix);
		int count = CountSpanningTreesByKirchhoffMatrix(kirchhoffMatrix);
		REQUIRE(count == 8);
	}
	WHEN("Ñhecking Cayley's formula with a complete 5*5 graph")
	{
		const Matrix adjacencyMatrix = {
			{ 0, 1, 1, 1, 1 },
			{ 1, 0, 1, 1, 1 },
			{ 1, 1, 0, 1, 1 },
			{ 1, 1, 1, 0, 1 },
			{ 1, 1, 1, 1, 0 },
		};
		const Matrix kirchhoffMatrix = BuildKirchhoffMatrixByAdjacencyMatrix(adjacencyMatrix);
		int count = CountSpanningTreesByKirchhoffMatrix(kirchhoffMatrix);
		REQUIRE(count == 125);
	}
	WHEN("binary tree")
	{
		const Matrix adjacencyMatrix = {
			{ 0, 1, 1, 0, 0 },
			{ 1, 0, 0, 1, 1 },
			{ 1, 0, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
			{ 0, 1, 0, 0, 0 },
		};
		const Matrix kirchhoffMatrix = BuildKirchhoffMatrixByAdjacencyMatrix(adjacencyMatrix);
		int count = CountSpanningTreesByKirchhoffMatrix(kirchhoffMatrix);
		REQUIRE(count == 1);
	}
}