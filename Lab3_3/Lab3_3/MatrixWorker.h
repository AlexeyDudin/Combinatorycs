#pragma once
#include "types.h"
#include <fstream>
#include <iostream>

void ReadMatrix(std::ifstream& input, Matrix& field, int size);
bool FillMatrix(Matrix& inputMatrix, Matrix& kirghofMatrix, int size);
double GetDeterminant(Matrix matrix, int size);