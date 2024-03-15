#pragma once

#include "StandartInputs.h"

int GetGraphSizeFromFile(std::istream& inputFile);

int FindMinCostUnchecked(const std::vector<std::vector<int>>& graph, std::vector<int>& minPath);

int CopyGraphWithFindingMinCost(const std::string& inputFileName, std::vector<int>& minPath);