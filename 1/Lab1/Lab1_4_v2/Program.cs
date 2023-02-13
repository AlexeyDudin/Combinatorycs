using System;

namespace Lab1_4_v2
{
    public class Program
    {
        public static void Main(string[] args)
        {
            FileWorker fileWorker = new FileWorker();
            Country country = fileWorker.ReadFromFile("Input.txt");
            country.PrintAllPaths();
            DateTime startTime = DateTime.Now;
            country.PrintPathsToCityes();
            DateTime endTime = DateTime.Now;
            Console.WriteLine((endTime - startTime).TotalMilliseconds + " ms.");
            Console.ReadKey();
        }
    }
}
