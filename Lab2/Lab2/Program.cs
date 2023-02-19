using System;
using System.Collections.Generic;
using System.Data.OleDb;

namespace Lab2
{
    class Alg1
    {
        private bool NextPermutation<T>(IList<T> a) where T : IComparable
        {
            if (a.Count < 2) return false;
            var k = a.Count - 2;

            while (k >= 0 && a[k].CompareTo(a[k + 1]) >= 0) k--;
            if (k < 0) return false;

            var l = a.Count - 1;
            while (l > k && a[l].CompareTo(a[k]) <= 0) l--;

            var tmp = a[k];
            a[k] = a[l];
            a[l] = tmp;

            var i = k + 1;
            var j = a.Count - 1;
            while (i < j)
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
                i++;
                j--;
            }

            return true;
        }

        public void PrintArray(int m, int[] a)
        {
            Console.WriteLine(string.Join(" ", a));
        }

        public void PrintArray(int m, List<int> a)
        {
            Console.WriteLine(string.Join(" ", a));
        }

        public void Generate(int n, int m, int t, int[] valuesArray, bool[] r)
        {
            int j;
            if (t > (m - 1))
            {
                if (IsAscending(valuesArray))
                {
                    List<int> cloneValuesArray = new List<int>(valuesArray);
                    do
                    {
                        PrintArray(m, cloneValuesArray);
                    } while (NextPermutation(cloneValuesArray));
                }
            }
            else
            {
                for (j = 1; j <= n; j++)
                {
                    if (!r[j - 1])
                    {
                        r[j - 1] = true;
                        valuesArray[t] = j;
                        Generate(n, m, t + 1, valuesArray, r);
                        r[j - 1] = false;
                    }
                }

            }
        }

        private bool IsAscending(int[] a)
        {
            int? prevElem = null;
            foreach(var elem in a)
            {
                if (prevElem != null)
                {
                    if (prevElem.Value > elem)
                        return false;
                }
                prevElem = elem;
            }
            return true;
        }

        public int ControlInt1()
        {
            int n = 0;
            Console.Write("Введите количество элементов последовательности: ");
            while (!int.TryParse(Console.ReadLine(), out n) || (n < 1))
            {
                Console.WriteLine("Некорректный ввод данных для элементов последовательности!");
                Console.Write("Повторите ввод n: ");
            }
            return n;
        }
        public int ControlInt(int countN)
        {
            int m = 0;
            Console.Write("Введите количество элементов массива m: ");
            while (!int.TryParse(Console.ReadLine(), out m) || (m < 1) || (m > countN))
            {
                Console.WriteLine("Некорректный ввод данных для количества элементов массива!");
                Console.Write("Повторите ввод m: ");
            }
            return m;
        }
    }
    public class Program
    {
        public static void Main(string[] args)
        {
            Alg1 rec = new Alg1();
            int t = 0;

            int n = rec.ControlInt1();
            int m = rec.ControlInt(n);
            int[] a = new int[m];
            bool[] r = new bool[n];
            rec.Generate(n, m, t, a, r);
            Console.ReadKey();
        }
    }
}