#pragma once
#include "Command.h"
#include <vector>
#include <iostream>
using namespace std;

struct Thing
{
    size_t weight; // вес
    size_t price; // цена 
};

const string configFile = "Config.txt";

void ParseCommandFile(Command& command, vector<Thing>& thing);
void GetResultItems(vector<vector<size_t>>& array, size_t k, size_t s, vector<Thing>& w, vector<Thing>& resultArray);