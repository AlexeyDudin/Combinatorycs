#include "Functions.h"

// ������� ��� ��������� ����� � �������������� ��������� ������
vector<int> colorGraph(const vector<vector<int>>& graph)
{
    int v = graph.size();
    vector<int> colors(v, 0); // ������ ������ ������
    vector<bool> usedColors(v, false); // ������ �������������� ������

    // �������� �� ���� �������� �����
    for (int i = 0; i < v; i++) {
        // �������� ������ �������������� ������ ��� ������� �������
        for (int j = 0; j < v; j++) {
            usedColors[j] = false;
        }

        // �������� �� ���� �������� �������� � �������� �������������� �����
        for (int j = 0; j < v; j++) {
            if (graph[i][j] == 1 && colors[j] != 0) {
                usedColors[colors[j] - 1] = true;
            }
        }

        // ���� ������ ��������� ���� ��� ������� �������
        int color;
        for (color = 1; color <= v; color++) {
            if (!usedColors[color - 1]) {
                break;
            }
        }

        // ���������� ��������� ���� ��� ������� �������
        colors[i] = color;
    }

    return colors;
}