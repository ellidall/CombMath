#include "FindMinCost.h"
#define BOOST_TIMER_ENABLE_DEPRECATED
#include <boost/timer.hpp>

std::string GetFileName(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("Invalid argument count\nUsage: 1.1.exe <inputFile>");
	}
	return (argv[1]);
}

void PrintResults(int minCost, const std::vector<int>& minPath, double elapsedTime)
{
	std::cout << "Minimum path cost: " << minCost << '\n';
	std::cout << "Minimum path: ";
	for (int v : minPath)
	{
		std::cout << v << "->";
	}
	std::cout << minPath[0] << '\n';
	std::cout << "Program running time: " << elapsedTime << '\n';
}

int main(int argc, char* argv[])
{
	boost::timer t;
	t.restart();
	std::vector<int> minPath;
	int minCost;

	try
	{
		std::string inputFileName = GetFileName(argc, argv);
		minCost = CopyGraphWithFindingMinCost(inputFileName, minPath);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	PrintResults(minCost, minPath, t.elapsed());
    
    return EXIT_SUCCESS;
}