using Lab3_3C;
using System.IO;
using System.Numerics;
using System.Runtime.Intrinsics;

//Нахождение определителя методом Гаусса
// С++
MyMath.GenerateMatrix("test.txt", 10);

var lines = CReader.FillList("test.txt");
var laplacian = MyMath.CreateLaplasian(lines);

int det = MyMath.Determinant(laplacian, lines.Count() - 1);

Console.WriteLine($"Result {det}");
Console.ReadLine();