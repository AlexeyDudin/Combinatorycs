#pragma once
#include "KunnDataStruct.h"
#include "types.h"
#include <fstream>
#include <iostream>

KunnData ReadKunnDataFromMatrix(Matrix& matrix, int sizeX, int sizeY);
void ReadMatrix(std::ifstream& input, Matrix& field, int sizeX, int sizeY);
void PrintMatrix(Matrix& field, int sizeX, int sizeY, std::ostream& output);
bool UseKunn(KunnData& data, int vertex);
void SolveKunn(KunnData& data);
void PrintKunnResult(KunnData data);