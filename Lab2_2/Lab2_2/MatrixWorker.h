#pragma once
#include <iostream>
#include <fstream>
#include "types.h"
#include <string>

void ReadMatrix(std::ifstream& input, Matrix& field, int size);
Matrix TransposedMatrix(Matrix& matrix, int n);
void DepthFirstSearchAndSort(Matrix const& matrix, int vertex, std::vector<bool>& visited, std::vector<int>& topSort);
void FindSCC(Matrix const& matrix, int vertex, std::vector<bool>& visited);