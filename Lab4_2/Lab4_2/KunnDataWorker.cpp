#include "KunnDataWorker.h"

KunnData ReadKunnDataFromMatrix(Matrix& matrix, int sizeX, int sizeY)
{
	KunnData data;

	data.edges.resize(sizeY);

	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			if (matrix[i][j])
			{
				data.edges[i].push_back(j);
			}
		}
	}

	data.leftSize = sizeY;
	data.rightSize = sizeX;

	return data;
}

void ReadMatrix(std::ifstream& input, Matrix& field, int sizeX, int sizeY)
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			input >> field[i][j];
		}
	}
}

void PrintMatrix(Matrix& field, int sizeX, int sizeY, std::ostream& output)
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			output << field[i][j] << ' ';
		}
		output << std::endl;
	}
	output << std::endl;
}


bool UseKunn(KunnData& data, int vertex)
{
	if (data.usedPair[vertex])
	{
		return false;
	}

	data.usedPair[vertex] = true;
	for (size_t i = 0; i < data.edges[vertex].size(); ++i)
	{
		int to = data.edges[vertex][i];
		if (data.matchingPair[to] == -1 || UseKunn(data, data.matchingPair[to]))
		{
			data.matchingPair[to] = vertex;
			return true;
		}
	}
	return false;
}

void SolveKunn(KunnData& data)
{
	data.matchingPair.assign(data.rightSize, -1);
	for (int vertexNumber = 0; vertexNumber < data.leftSize; vertexNumber++)
	{
		data.usedPair.assign(data.leftSize, false);
		UseKunn(data, vertexNumber);
	}
}

void PrintKunnResult(KunnData data)
{
	bool isHaveSolution = true;
	for (int vertex = 0; vertex < data.rightSize; vertex++)
	{
		if (isHaveSolution && data.matchingPair[vertex] == -1)
		{
			isHaveSolution = false;
		}
	}

	if (!isHaveSolution)
	{
		std::cout << "No\n";
		return;
	}
	else
	{
		std::cout << "Yes\n";
		for (int vertex = 0; vertex < data.rightSize; vertex++)
		{
			std::cout << data.matchingPair[vertex] + 1 << ' ' << vertex + 1 << "\n";
		}
	}

}