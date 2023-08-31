#include "Thing.h"
#include <fstream>

void ParseCommandFile(Command& command, vector<Thing>& thingVector)
{
    ifstream in(configFile);
    if (in.is_open())
    {
        in >> command.numberOfThings >> command.countOfThings >> command.priceOfThings;
        Thing thing;
        thingVector.push_back({ 0,0 }); // КОСТЫЛЬ побороть чтение с 1 элемента
        while (!in.eof())
        {
            in >> thing.weight >> thing.price;
            thingVector.push_back(thing);
        }
    }
}

void GetResultItems(vector<vector<size_t>>& array, size_t k, size_t s, vector<Thing>& w, vector<Thing>& resultArray)
{
    if (array[k][s] == 0)
        return;
    if (array[k - 1][s] == array[k][s])
        GetResultItems(array, k - 1, s, w, resultArray);
    else
    {
        GetResultItems(array, k - 1, s - w[k].weight, w, resultArray);
        resultArray.push_back({ w[k].weight,w[k].price });
    }
}
