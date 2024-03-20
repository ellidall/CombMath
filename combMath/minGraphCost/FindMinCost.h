#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <windows.h>
#include <limits>

int GetGraphSizeFromFile(std::istream& inputFile);
int FindMinCostUnchecked(const std::vector<std::vector<int>>& graph, std::vector<int>& minPath);
int CopyGraphWithFindingMinCost(const std::string& inputFileName, std::vector<int>& minPath);