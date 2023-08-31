#include "Functions.h"

// Функция для раскраски графа с использованием алгоритма Ершова
vector<int> colorGraph(const vector<vector<int>>& graph)
{
    int v = graph.size();
    vector<int> colors(v, 0); // Вектор цветов вершин
    vector<bool> usedColors(v, false); // Вектор использованных цветов

    // Проходим по всем вершинам графа
    for (int i = 0; i < v; i++) {
        // Обнуляем список использованных цветов для текущей вершины
        for (int j = 0; j < v; j++) {
            usedColors[j] = false;
        }

        // Проходим по всем соседним вершинам и отмечаем использованные цвета
        for (int j = 0; j < v; j++) {
            if (graph[i][j] == 1 && colors[j] != 0) {
                usedColors[colors[j] - 1] = true;
            }
        }

        // Ищем первый доступный цвет для текущей вершины
        int color;
        for (color = 1; color <= v; color++) {
            if (!usedColors[color - 1]) {
                break;
            }
        }

        // Записываем найденный цвет для текущей вершины
        colors[i] = color;
    }

    return colors;
}