#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include "Params.h"

struct Object
{
	string objname;
	Params* styles;

	Object(string nobjname, Params* nstyles)
	{
		objname = nobjname;
		styles = nstyles;
	}
};

struct CSSOM
{
	vector<Object*> objects;

	CSSOM(vector<Object*> nobjects)
	{
		objects = nobjects;
	}

	Object* FindObject(string nobjname)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->objname == nobjname)
				return objects[i];
		}
		return nullptr;
	}
};

