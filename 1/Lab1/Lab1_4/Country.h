#pragma once
#include <string>
#include <vector>

using namespace std;

typedef struct _graphElement
{
	string name;
	bool isReturned;
} GraphElem, * PGraphElem;

typedef struct _path
{
	PGraphElem left, right;
	unsigned long size;
} Path, * PPath;

typedef struct _country
{
	PGraphElem capital;
	vector<PPath> paths;
	vector<PGraphElem> cityes;
} Country, * PCountry;