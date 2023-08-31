#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>


using namespace std;

/*3.3. [# 50] Для заданного графа, содержащего 𝑣 вершин, найдите количество остовных
деревьев.
Вход. Первая строка исходного файла содержит одно целое число 𝑣 (1 ≤ 𝑣 ≤ 100) –
количество вершин. Вершины пронумерованы от 1 до 𝑛. В последующих 𝑣 строках
содержатся по 𝑣 чисел, разделенных пробелами: вес ребер между вершинами.
Выход. В первой строке должно содержаться одно натуральное число – количество
остовных деревьев.*/

/*
Функция для вычисления определителя матрицы
рекурсивно разбивая матрицу на подматрицы меньшего размера, алгоритм вычисляет определитель матрицы графа,
что позволяет найти количество остовных деревьев в графе.
*/
int determinant(vector<vector<int>>& laplacian, int graphNodeCountMinisOne)
{
    int det = 0;
    //Если размер матрицы graphNodeCountMinisOne равен 1, то это означает, что матрица имеет размер 1x1,
    //и мы просто возвращаем единственный элемент этой матрицы как определитель.
    if (graphNodeCountMinisOne == 1)
        return laplacian[0][0];
    // размер матрицы graphNodeCountMinisOne равен 2. В этом случае мы используем формулу для вычисления определителя матрицы 2x2.
    if (graphNodeCountMinisOne == 2)
        return laplacian[0][0] * laplacian[1][1] - laplacian[0][1] * laplacian[1][0];

    // В остальных случаях (когда размер матрицы больше 2), мы создаем подматрицу submat, которая является матрицей размера (graphNodeCountMinisOne - 1) x (graphNodeCountMinisOne - 1).
    // Мы идем по каждому столбцу матрицы laplacian и рекурсивно вызываем функцию determinant, передавая подматрицу submat, удаляя текущий столбец и первую строку.
    vector<vector<int>> submat(graphNodeCountMinisOne - 1, vector<int>(graphNodeCountMinisOne - 1));
    for (int k = 0; k < graphNodeCountMinisOne; k++)
    {
        int subi = 0;
        for (int i = 1; i < graphNodeCountMinisOne; i++)
        {
            int subj = 0;
            for (int j = 0; j < graphNodeCountMinisOne; j++)
            {
                if (j != k)
                {
                    submat[subi][subj] = laplacian[i][j];
                    subj++;
                }
            }
            subi++;
        }
        // Для каждого столбца k мы вычисляем минор laplacian[0][k] (первый элемент первой строки и k-ый столбец) и умножаем его на соответствующий алгебраический
        // дополнительный знак (k % 2 == 0 ? 1 : -1).
        // Затем рекурсивно вызываем функцию determinant для подматрицы submat, умноженной на минор, и добавляем результат к общему определителю det.
        det += (k % 2 == 0 ? 1 : -1) * laplacian[0][k] * determinant(submat, graphNodeCountMinisOne - 1);
    }

    return det;
}

int main()
{
    int graphNodeCount;
    ifstream in("test.txt");
    in >> graphNodeCount;

    // Создание и инициализация графа
    vector<vector<int>> graph(graphNodeCount, vector<int>(graphNodeCount));
    for (int i = 0; i < graphNodeCount; i++)
    {
        for (int j = 0; j < graphNodeCount; j++)
        {
            in >> graph[i][j];
        }
    }

    // Создание лапласиана (http://www.machinelearning.ru/wiki/images/9/9f/Novikov_SGT_presentation.pdf)
    vector<vector<int>> laplacian(graphNodeCount, vector<int>(graphNodeCount, 0));
    for (int i = 0; i < graphNodeCount; i++)
    {
        for (int j = 0; j < graphNodeCount; j++)
        {
            if (i != j)
            {
                laplacian[i][i] += graph[i][j];
                laplacian[i][j] = -graph[i][j];
            }
        }
    }

    // Вычисление количества остовных деревьев
    int det = determinant(laplacian, graphNodeCount - 1);

    // Вывод количества остовных деревьев
    cout << "Result " << det << endl;
 
    return 0;
}
