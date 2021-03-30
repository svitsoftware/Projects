#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include "SFML/Graphics.hpp"
using namespace sf;

#include "Params.h"

class ParamParser
{
public:
	Color ParseColor(string color);
	void ParseParams(vector<string> params, Params& pars);
};

