#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
// /*
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
using namespace std;

/*
Функция dfs реализует алгоритм глубинного поиска (Depth-First Search). Он используется в данном контексте для поиска максимального паросочетания в двудольном графе.

Алгоритм работает следующим образом:
Если вершина v уже была посещена (visited[v] равно true), возвращается false.
Помечаем вершину v как посещенную (visited[v] = true).
Для каждой смежной вершины to с текущей вершиной v:
Если вершина to еще не имеет пары (match[to] == -1) или можно найти увеличивающую цепь из текущей пары match[to], вызывается рекурсивно dfs для вершины match[to].
Если рекурсивный вызов dfs возвращает true, то текущая вершина v и вершина to образуют пару, и происходит обновление паросочетания: match[to] = v, и функция возвращает true.
Если ни одно из ребер из текущей вершины v не приводит к увеличивающей цепи, функция возвращает false.
*/
/**
 * @param v - текущая вершина, с которой начинается обход
 * @param visited - вектор булевых значений, отражающий посещение вершин графа
 * @param match - вектор, содержащий текущее паросочетание (индексы вершин, связанных ребром)
 * @param graph - двумерный вектор, представляющий граф
 */
bool dfs(int v, vector<bool>& visited, vector<int>& match, const vector<vector<int>>& graph)
{
    if (visited[v])
    {
        return false;
    }
    visited[v] = true;

    for (size_t i = 0; i < graph[v].size(); i++)
    {
        int to = graph[v][i];
        if (match[to] == -1 || dfs(match[to], visited, match, graph))
        {
            match[to] = v;
            return true;
        }
    }
    return false;
}

void ParseTextFile(ifstream& in, vector<vector<int>>& graph, size_t size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            in >> graph[i][j];
        }
    }
    in.close();
}

/**
 *  Функция FindCompleteMatching() используется для поиска максимального паросочетания в двудольном графе.
 * @param arr - двудольный граф в виде матрицы смежности
 * @param size - размер графа
 */
vector<int> FindCompleteMatching(vector<vector<int>>& arr, int size)
{
    //Создается пустой двумерный вектор ribsList, который будет содержать списки смежности для каждой вершины графа. Этот вектор будет представлять граф в виде списков смежности.
    vector<vector<int>> ribsList(size);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            // Для каждой вершины i и каждой вершины j проверяется, есть ли между ними ребро в исходном графе (arr[i][j] == 1).
            if (arr[i][j] == 1)
            {
                //Если ребро есть, то добавляется ребро из вершины i в вершину j в список смежности.
                ribsList[i].push_back(j);
            }
        }
    }

    // Создается вектор matchingList размером size, и каждый его элемент инициализируется значением -1. Этот вектор будет хранить текущее паросочетание.
    vector<int> matchingList(size, -1);
    // Создается вектор visited размером size и заполняется значениями false.
    vector<bool> visited(size, false);

    for (int v = 0; v < size; ++v)
    {
        //oчищаем Used
        visited.assign(size, false);
        //Вызывается функция dfs(v, visited, matchingList, ribsList), которая реализует глубинный поиск для поиска увеличивающих цепей и обновления паросочетания.
        dfs(v, visited, matchingList, ribsList);
    }

    //Возвращается вектор matchingList, содержащий максимальное паросочетание.
    return matchingList;
}

int main()
{
    string fileName = "test.txt";
    ifstream input(fileName);
    if (!input.is_open())
    {
        cout << "File not found";
        return 1;
    }
    int matrixSize, rowSize;
    input >> matrixSize >> rowSize;

    vector<vector<int>> graph(matrixSize, vector<int>(matrixSize, 0));
    ParseTextFile(input, graph, matrixSize);

    vector<int> match = FindCompleteMatching(graph, matrixSize);

    if (find(match.begin(), match.end(), -1) != match.end())
    {
        cout << "No" << endl;
    }
    else
    {
        cout << "Yes" << endl;
        for (int i = 0; i < graph.size(); ++i)
        {
            cout << match[i] + 1 << ", " << i + 1 << endl;
        }
    }

    system("pause");
    return 0;
}