using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab3_3C
{
    public static class MyMath
    {
        public static void GenerateMatrix(string fileName, int size)
        {
            Random rnd = new Random((int)DateTime.Now.Ticks);
            List<List<int>> matrix = new List<List<int>>();
            for (int i = 0; i < size; i++)
            {
                matrix.Add(new List<int>());
                for (int j = 0; j < size; j++)
                {
                    matrix[i].Add(0);
                }
            }
            for (int i = 0; i < size; i++)
            {
                for (int j = i; j < size; j++)
                {
                    matrix[i][j] = (int)rnd.Next(2);
                    matrix[j][i] = matrix[i][j];
                }
            }
            File.Delete(fileName);
            File.AppendAllText(fileName, $"{size}\n");

            foreach (var line in matrix)
            {
                File.AppendAllText(fileName, string.Join(' ', line) + "\n");
            }
        }

        public static int Determinant(List<List<int>> laplacian, int graphNodeCountMinisOne)
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
            List<List<int>> submat = new List<List<int>>();
            for (int i = 0; i < graphNodeCountMinisOne - 1; i++)
            {
                var tmp = new List<int>();
                for (int j = 0; j < graphNodeCountMinisOne - 1; j++)
                {
                    tmp.Add(0);
                }
                submat.Add(tmp);
            }
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
                det += (k % 2 == 0 ? 1 : -1) * laplacian[0][k] * Determinant(submat, graphNodeCountMinisOne - 1);
            }

            return det;
        }

        public static List<List<int>> CreateLaplasian(List<List<int>> graph)
        {
            int graphNodeCount = graph.Count;
            List<List<int>> result = new List<List<int>>();
            for (int i = 0; i < graphNodeCount; i++)
            {
                var tmp = new List<int>();
                for (int j = 0; j < graphNodeCount; j++)
                {
                    tmp.Add(0);
                }
                result.Add(tmp);
            }

            for (int i = 0; i < graphNodeCount; i++)
            {
                for (int j = 0; j < graphNodeCount; j++)
                {
                    if (i != j)
                    {
                        result[i][i] += graph[i][j];
                        result[i][j] = -graph[i][j];
                    }
                }
            }

            return result;
        }
    }
}
