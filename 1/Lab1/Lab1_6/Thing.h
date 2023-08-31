#pragma once
#include "Command.h"
#include <vector>
#include <iostream>
using namespace std;

struct Thing
{
    size_t weight; // ���
    size_t price; // ���� 
};

const string configFile = "Config.txt";

void ParseCommandFile(Command& command, vector<Thing>& thing);
void GetResultItems(vector<vector<size_t>>& array, size_t k, size_t s, vector<Thing>& w, vector<Thing>& resultArray);