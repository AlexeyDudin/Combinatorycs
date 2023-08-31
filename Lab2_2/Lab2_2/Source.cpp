/*
2.2. [# 50] Для заданного ориентированного графа найти компоненты сильной связности
Граф задан матрицей смежности.
Вход. Первая строка исходного файла содержит целое число 𝑣 (1 ≤ 𝑣 ≤ 400) –
количество вершин. В последующих 𝑣 строках содержатся по 𝑣 чисел, разделенных
пробелами: вес ребер между вершинами. Вершины пронумерованы от 1 до 𝑣
Выход. В каждой строчке выходного фала вывести номера вершин, принадлежащих
одной компоненте сильной связности.
*/

#include "MatrixWorker.h"

const int MAX_SIZE = 100;
using namespace std;
string ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid number of argments\n";
		return "";
	}

	return argv[1];
}

int main(int argc, char* argv[])
{
	vector<bool> visited;
	vector<int> topSortVertex;
	int countVertex = 0;
	int countSCC = 0;

	auto args = ParseArgs(argc, argv);
	if (args == "")
	{
		return 1;
	}

	ifstream input(args);
	if (!input.is_open())
	{
		cout << "Failed to open file" << endl;
		return 1;
	}

	input >> countVertex;

	if (countVertex <= 0 || countVertex > MAX_SIZE)
	{
		cout << "Invalid matrix size" << endl;
		return 1;
	}

	Matrix matrix(countVertex, std::vector<int>(countVertex, 0));
	ReadMatrix(input, matrix, countVertex);
	Matrix trMatrix = TransposedMatrix(matrix, countVertex);

	visited.assign(countVertex, false);
	for (int i = 0; i < countVertex; ++i)
	{
		if (!visited[i])
		{
			DepthFirstSearchAndSort(matrix, i, visited, topSortVertex);
		}
	}

	visited.assign(countVertex, false);

	for (int i = 0; i < countVertex; ++i)
	{
		int vertex = topSortVertex[countVertex - 1 - i];
		if (!visited[vertex])
		{
			FindSCC(trMatrix, vertex, visited);
			countSCC++;
		}
	}
	cout << ((countSCC == 1) ? 1 : 0);

	return 0;
}