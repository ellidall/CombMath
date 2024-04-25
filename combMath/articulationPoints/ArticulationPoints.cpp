#include "FindArticulationPoints.h"

int main()
{
	try
	{
		Graph graph = InitializeGraph();
		std::vector<size_t> articulationPoints = FindArticulationPoints(graph);
		PrintArticulationPoints(articulationPoints);
	} 
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	

	return 0;
}