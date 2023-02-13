#include "FileWorker.h"

using namespace std;

bool VectorContains(vector<PGraphElem> v, string name)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i]->name == name)
			return true;
	}
	return false;
}

PGraphElem GetElemByName(std::vector<PGraphElem> v, string name)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i]->name == name)
			return v[i];
	}
	return NULL;
}

PCountry ReadGraph(string fileName)
{
	PCountry result = new Country;
	memset(result, 0, sizeof(Country));
	ifstream file;
	file.open(fileName);
	if (!file.good())
	{
		cout << "Ошибка открытия файла " << fileName << endl;
		return result;
	}

	int cityFrom = 1;
	while (!file.eof())
	{
		string line;
		int cityDest = 1;
		while (getline(file, line, ' ')) {
			if (result->capital == NULL)
			{
				result->capital = new GraphElem;
				result->capital->name = to_string(cityFrom);
			}
			if (!VectorContains(result->cityes, to_string(cityDest)))
			{
				PGraphElem graphElem = new GraphElem;
				graphElem->isReturned = false;
				graphElem->name = to_string(cityDest);
				result->cityes.push_back(graphElem);
			}

			if (line != "0")
			{
				PGraphElem fromCity = GetElemByName(result->cityes, to_string(cityFrom));
				PGraphElem destCity = GetElemByName(result->cityes, to_string(cityDest));

				PPath path = new Path;
				path->left = fromCity;
				path->right = destCity;
				path->size = stoi(line);

				result->paths.push_back(path);
				//TODO fill path
			}
			cityDest++;
		}
		cityFrom++;
	}

    return result;
}
