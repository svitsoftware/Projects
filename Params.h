#pragma once

#include <iostream>
using namespace std;

#include "SFML/Graphics.hpp"
using namespace sf;

struct Params
{
	Color backcolor;
	Color forecolor;
	int charsize;
	int fontstyle;

	Params(Color bc, Color fc, int ncharsize, int nfontstyle)
	{
		backcolor = bc;
		forecolor = fc;
		charsize = ncharsize;
		fontstyle = nfontstyle;
	}
};