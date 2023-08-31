#include "MatrixWorker.h"

void ReadMatrix(std::ifstream& input, Matrix& field, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            input >> field[i][j];
        }
    }
}

bool FillMatrix(Matrix& inputMatrix, Matrix& kirghofMatrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        float relations = 0.0f;
        for (int j = 0; j < size; j++)
        {
            if (inputMatrix[i][j] > 0)
            {
                relations++;
                kirghofMatrix[i][j] = -1.0;
            }
            else
            {
                kirghofMatrix[i][j] = 0.0;
            }
        }
        if (relations > 0)
        {
            kirghofMatrix[i][i] = relations;
        }
        else
        {
            return false;
        }
    }
    return true;
}

double GetDeterminant(Matrix matrix, int size)
{
    double determinant = 1;

    for (int i = 0; i < size; i++)
    {
        int pivot_index = -1;
        double pivot_value = 0;

        for (int j = i; j < size; j++)
        {
            if (fabs(matrix[j][i]) > pivot_value)
            {
                pivot_index = j;
                pivot_value = fabs(matrix[j][i]);
            }
        }
        if (pivot_value == 0)
        {
            return 0;
        }

        if (pivot_index != i)
        {
            swap(matrix[i], matrix[pivot_index]);
            determinant *= -1;
        }

        for (int j = i + 1; j < size; j++)
        {
            if (matrix[j][i] != 0)
            {
                float multiplier = 1 / matrix[i][i] * matrix[j][i];

                for (int k = i; k < size; k++)
                {
                    matrix[j][k] -= matrix[i][k] * multiplier;
                }
            }
        }

        determinant *= matrix[i][i];
    }

    return determinant;
}