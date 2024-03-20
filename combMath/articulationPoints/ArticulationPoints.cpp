#include "FindArticulationPoints.h"

void dfs(int u, int parent, Graph& graph)
{
	static int time;
	int children = 0;
	graph.vertices[u].visited = true;
	graph.vertices[u].low = graph.vertices[u].disc = ++time;

	for (const Edge& edge : graph.adjList[u])
	{
		int v = edge.dest;
		if (!graph.vertices[v].visited)
		{
			children++;
			dfs(v, u, graph);
			graph.vertices[u].low = std::min(graph.vertices[u].low, graph.vertices[v].low);

			if (parent != -1 && graph.vertices[v].low >= graph.vertices[u].disc)
				graph.vertices[u].articulationPoint = true;
		}
		else if (v != parent)
			graph.vertices[u].low = std::min(graph.vertices[u].low, graph.vertices[v].disc);
	}

	if (parent == -1 && children > 1)
		graph.vertices[u].articulationPoint = true;
}

void FindArticulationPoints(Graph& graph)
{
	for (size_t i = 0; i < graph.vertices.size(); ++i)
	{
		if (!graph.vertices[i].visited)
		{
			dfs(i, -1, graph);
		}
	}

	std::cout << "Articulation Points: ";
	for (size_t i = 0; i < graph.vertices.size(); ++i)
	{
		if (graph.vertices[i].articulationPoint)
			std::cout << i << " ";
	}
	std::cout << std::endl;
}

Graph InitializeGraph()
{
	//Graph graph(6);

	/*graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(1, 2);
	graph.addEdge(1, 3);
	graph.addEdge(1, 4);
	graph.addEdge(3, 5);*/
	Graph graph(4);
	graph.addEdge(0, 1);
	graph.addEdge(1, 2);
	graph.addEdge(1, 3);
	graph.addEdge(2, 3);

	return graph;
}

int main()
{
	try
	{
		Graph graph = InitializeGraph();
		FindArticulationPoints(graph);
	} 
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	

	return 0;
}