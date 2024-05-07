#include "SpanningTrees.h"

int main()
{
	const Matrix adjacencyMatrix = {
		{ 0, 1, 1, 0 },
		{ 1, 0, 1, 1 },
		{ 1, 1, 0, 1 },
		{ 0, 1, 1, 0 }
	};

	const Matrix kirchhoffMatrix = BuildKirchhoffMatrixByAdjacencyMatrix(adjacencyMatrix);
	int result = CountSpanningTreesByKirchhoffMatrix(kirchhoffMatrix);
	std::cout << "Spanning trees count: " << result << std::endl;

	return EXIT_SUCCESS;
}