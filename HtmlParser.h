#pragma once
#include <iostream>
#include <sstream>
using namespace std;

#include "Tree.h"
#include "CssParser.h"

class HtmlParser
{
private:
	CssParser* cssparser = new CssParser();
public:
	void ParseHtml(wstring content, Nodes* &tre, CSSOM &cssom);
};

