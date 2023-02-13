#include "GraphWorker.h"
#include "Pairs.h"
#include <iostream>

using namespace std;

vector<PPath> AllPathsFromCity(Country country, PGraphElem city)
{
    vector<PPath> result;
    for (int i = 0; i < country.paths.size(); i++)
    {
        if (country.paths[i]->left == city)
            result.push_back(country.paths[i]);
    }
    return result;
}

vector<vector<PPath>> FindPaths(Country country, PGraphElem from, PGraphElem to)
{
    vector<vector<PPath>> result;
    vector<PPath> fromCityPaths = AllPathsFromCity(country, from);
    from->isReturned = true;
    for (int i = 0; i < fromCityPaths.size(); i++)
    {
        if (!fromCityPaths[i]->right->isReturned)
        {
            if (fromCityPaths[i]->right == to)
            {
                vector<PPath> tmp;
                tmp.push_back(fromCityPaths[i]);
                result.push_back(tmp);
            }
            else
            {
                vector<vector<PPath>> tmp1 = FindPaths(country, fromCityPaths[i]->right, to);
                for (int j = 0; j < tmp1.size(); j++)
                {
                    vector<PPath> tmp;
                    tmp.push_back(fromCityPaths[i]);
                    for (int k = 0; k < tmp1[j].size(); k++)
                    {
                        tmp.push_back(tmp1[j][k]);
                    }

                    result.push_back(tmp);
                }
            }
        }
    }
    from->isReturned = false;
    return result;
}

vector<PPair> SortPairs(vector<PPair> pairs)
{
    vector<PPair> result = pairs;
    for (int i = 0; i < result.size(); i++)
    {
        for (int j = i; j < result.size(); j++)
        {
            if (result[i]->length > result[j]->length)
            {
                PPair tmp = result[i];
                result[i] = result[j];
                result[j] = tmp;
            }
        }
    }
    return result;
}

void PrintPath(PPair pair)
{
    cout << pair->paths[0]->left->name;
    for (int i = 0; i < pair->paths.size(); i++)
    {
        cout << " -(" << pair->paths[i]->size << ")-> " << pair->paths[i]->right->name;
    }
    cout << " = (" << pair->length << ")" << endl;
}

void PrintAllPaths(Country country)
{
    for (int i = 0; i < country.cityes.size(); i++)
    {
        if (country.cityes[i] != country.capital)
        { 
            cout << "Пути " << country.capital->name << " -> " << country.cityes[i]->name << ":" << endl;
            vector<vector<PPath>> paths = FindPaths(country, country.capital, country.cityes[i]);
            if (paths.size() == 0)
                cout << "Из города " << country.capital->name << " в город " << country.cityes[i]->name << " нет путей" << endl;
            else
            {
                vector<PPair> pairs;
                for (int j = 0; j < paths.size(); j++)
                {
                    PPair pair = new Pair;
                    pair->length = 0;
                    for (int k = 0; k < paths[j].size(); k++)
                    {
                        pair->paths.push_back(paths[j][k]);
                        pair->length += paths[j][k]->size;
                    }
                    pairs.push_back(pair);
                }
                pairs = SortPairs(pairs);
                for (int j = 0; j < pairs.size(); j++)
                {
                    PrintPath(pairs[j]);
                }
                cout << endl;
            }
        }
    }
}