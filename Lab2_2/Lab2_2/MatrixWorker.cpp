#include "MatrixWorker.h"

void ReadMatrix(std::ifstream& input, Matrix& field, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			input >> field[i][j];
		}
	}
}

Matrix TransposedMatrix(Matrix& matrix, int n)
{
	Matrix transposedMatrix(n, std::vector<int>(n, 0));

	for (int row = 0; row < n; ++row)
	{
		for (int col = 0; col < n; ++col)
		{
			transposedMatrix[col][row] = matrix[row][col];
		}
	}
	return transposedMatrix;
}

void DepthFirstSearchAndSort(Matrix const& matrix, int vertex, std::vector<bool>& visited, std::vector<int>& topSort)
{
	visited[vertex] = true;
	for (int i = 0; i < visited.size(); ++i)
	{
		int weight = matrix[vertex][i];
		if ((weight != 0) && (!visited[i]))
		{
			DepthFirstSearchAndSort(matrix, i, visited, topSort);
		}
	}
	topSort.push_back(vertex);
}

void FindSCC(Matrix const& matrix, int vertex, std::vector<bool>& visited)
{
	visited[vertex] = true;
	for (int i = 0; i < matrix[vertex].size(); ++i)
	{
		int weight = matrix[vertex][i];
		if ((weight != 0) && (!visited[i]))
		{
			FindSCC(matrix, i, visited);
		}
	}
}