/*
* 3.3. [# 50] ��� ��������� �����, ����������� ?? ������, ������� ���������� ��������
��������.
����. ������ ������ ��������� ����� �������� ���� ����� ����� ?? (1 ? ?? ? 100) �
���������� ������. ������� ������������� �� 1 �� ??. � ����������� ?? �������
���������� �� ?? �����, ����������� ���������: ��� ����� ����� ���������.
�����. � ������ ������ ������ ����������� ���� ����������� ����� � ����������
�������� ��������

*/

#include "types.h"
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
    string args = ParseArgs(argc, argv);
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

    int v = 0;
    input >> v;

    if (v <= 0 || v > MAX_SIZE)
    {
        cout << "Invalid matrix size" << endl;
        return 1;
    }

    Matrix matrix(v, std::vector<float>(v, 0));
    ReadMatrix(input, matrix, v);


    Matrix kirghoffMatrix(v, std::vector<float>(v, 0));
    if (FillMatrix(matrix, kirghoffMatrix, v))
    {
        cout << GetDeterminant(kirghoffMatrix, v - 1) << endl;
    }
    else
    {
        cout << "Incorrect input!" << endl;
        return 1;
    }

    return 0;
}