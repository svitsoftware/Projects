#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include "CssTree.h"
#include "ParamParser.h"

class CssParser
{
private:
	ParamParser* ppar = new ParamParser();
public:
	void ParseCss(wstring css, CSSOM& cssom);
};

