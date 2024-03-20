#include "FindMinCost.h"

int GetGraphSizeFromFile(std::istream& inputFile)
{
	int graphSize;
	std::string firstLine;
	std::getline(inputFile, firstLine);
	std::istringstream stream(firstLine);
	if (!(stream >> graphSize))
	{
		throw std::runtime_error("Error while reading a file");
	}
	std::string remains;
	if (stream >> remains)
	{
		throw std::invalid_argument("Error: graph is not built correctly\nUsage:\n<graph_size>\n<graph>");
	}

	return graphSize;
}

int FindMinCostUnchecked(const std::vector<std::vector<int>>& graph, std::vector<int>& minPath)
{
	int minCost = (std::numeric_limits<int>::max)();
	int N = graph.size();
	std::vector<int> vertex(N);
	std::iota(vertex.begin(), vertex.end(), 0);

	do
	{
		int current—ost = 0;
		for (int i = 0; i < N - 1; ++i)
		{
			current—ost += graph[vertex[i]][vertex[i + 1]];
		}
		current—ost += graph[vertex[N - 1]][vertex[0]];
		if (current—ost < minCost)
		{
			minCost = current—ost;
			minPath = vertex;
		}
	} while (std::next_permutation(vertex.begin() + 1, vertex.end()));

	return minCost;
}

int CopyGraphWithFindingMinCost(const std::string& inputFileName, std::vector<int>& minPath)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		throw std::ios_base::failure("Error: Unable to open file " + inputFileName);
	}

	std::vector<std::vector<int>> graph;
	int graphSize = GetGraphSizeFromFile(inputFile);

	std::string line;
	while (std::getline(inputFile, line))
	{
		std::istringstream stream(line);
		std::vector<int> graphLine;
		int number;
		int zeroCount{};
		while (stream >> number)
		{
			if (number == 0)
			{
				zeroCount++;
			}
			graphLine.push_back(number);
		}
		if (zeroCount < 1 || zeroCount > 1)
		{
			throw std::invalid_argument("Error: graph is 'incomplete'");
		}
		zeroCount = 0;
		if (graphLine.size() != graphSize)
		{
			throw std::invalid_argument("Error: graph is not built correctly");
		}
		graph.push_back(graphLine);
	}
	if (graph.size() != graphSize)
	{
		throw std::invalid_argument("Error: graph is not built correctly");
	}

	return FindMinCostUnchecked(graph, minPath);
}