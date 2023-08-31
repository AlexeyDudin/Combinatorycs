using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab3_3C
{
    public static class CReader
    {
        public static List<List<int>> FillList(string path)
        {
            var lines = File.ReadAllLines(path);
            int graphNodeCount = Int32.Parse(lines[0]);
            List<List<int>> graph = new List<List<int>>();
            for(int i = 0; i < graphNodeCount; i++)
            {
                List<int> tmp = new List<int>();
                var arr = lines[i + 1].Split();
                for (int j = 0; j < graphNodeCount; j++)
                {
                    tmp.Add(Int32.Parse(arr[j]));
                }
                graph.Add(tmp);
            }
            return graph;
        }
    }
}
