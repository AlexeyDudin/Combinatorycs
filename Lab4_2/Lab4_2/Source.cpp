#include "KunnDataWorker.h"
#include <string>

// 4.2. [# 50] Задан двудольный граф 𝐺 = 𝐺(𝑋, 𝐸, 𝑌), где 𝑋, 𝑌 – множество вершин, |𝑋| = |𝑌| = 𝑛; 𝐸 – множество ребер.
// В заданном двудольном графе найти полное паросочетание, воспользовавшись алгоритмом Куна.
// Вход. Двудольный граф 𝐺 = 𝐺(𝑋, 𝐸, 𝑌) задается матрицей 𝐴[1. . 𝑝, 1. . 𝑞], 𝑝 = |𝑋|, 𝑞 =
// |𝑌|, в которой 𝐴[𝑥, 𝑦] = 1, если есть ребро (𝑥, 𝑦) и 𝐴[𝑥, 𝑦] = 0, если такого ребра нет.
// Первая строка входного файла содержит два числа 𝑝, 𝑞 (1 ≤ 𝑝, 𝑞 ≤ 100) – количество
// вершин в каждой доле. В последующих 𝑝 строках содержатся по 𝑞 чисел матрицы 𝐴.
// Вершины в каждой доле пронумерованы от 1.
// Выход. В первой строчке Yes либо No, в зависимости от того есть максимальное
// паросочетание или нет. Во втором случае, следующих 𝑛 строчках по два числа –
// вершины, соединенные ребром (первое число – первая доля, второе – вторая).
// */

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
	string args = ParseArgs(argc, argv);
	if (args == "")
	{
		return 1;
	}

	ifstream input(args);
	if (!input.is_open())
	{
		cout << "Failed to open file\n";
		return 1;
	}

	int p = 0, q = 0;
	input >> p >> q;

	if (p <= 0 || p > MAX_SIZE || q <= 0 || q > MAX_SIZE)
	{
		cout << "Invalid matrix attributes\n";
		return 1;
	}

	Matrix matrix(p, vector<int>(q, 0));
	ReadMatrix(input, matrix, q, p);

	KunnData kunnData = ReadKunnDataFromMatrix(matrix, q, p);

	SolveKunn(kunnData);

	PrintKunnResult(kunnData);

	return 0;
}