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
	Matrix matrix1 = {
		{  2, -1, -1,  0 },
		{ -1,  3, -1, -1 },
		{ -1, -1,  3, -1 },
		{  0, -1, -1,  2 }
	};
	int det1 = GetMatrixDet(matrix1);
	REQUIRE(det1 == 0);

	Matrix matrix2 = {
		{ 3, -1, -1 },
		{ -1, 3, -1 },
		{ -1, -1, 2 }
	};
	int det2 = GetMatrixDet(matrix2);
	REQUIRE(det2 == 8);
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
}