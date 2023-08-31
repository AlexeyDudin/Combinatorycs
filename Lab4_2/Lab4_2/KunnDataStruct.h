#pragma once
#include <vector>

struct KunnData
{
	int leftSize = 0;
	int rightSize = 0;
	std::vector<std::vector<int>> edges;
	std::vector<int> matchingPair;
	std::vector<bool> usedPair;
};