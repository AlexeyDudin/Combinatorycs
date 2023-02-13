#pragma once
#include "Country.h"

typedef struct _pair
{
	GraphElem destCity;
	unsigned long length;
	vector<PPath> paths;
} Pair, * PPair;