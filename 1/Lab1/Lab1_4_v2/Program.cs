﻿using System;

namespace Lab1_4_v2
{
    public class Program
    {
        public static void Main(string[] args)
        {
            FileWorker fileWorker = new FileWorker();
            Country country = fileWorker.ReadFromFile("Input.txt");
            country.PrintAllPaths();
            country.PrintPathsToCityes();
        }
    }
}
