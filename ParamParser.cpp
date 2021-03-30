#include "ParamParser.h"

Color ParamParser::ParseColor(string color)
{
	if (color == "black")
		return Color(0, 0, 0);
	else if (color == "white")
		return Color(255, 255, 255);
	else if (color == "royalblue")
		return Color(36, 96, 222);
	else if (color == "yellowgreen")
		return Color(82, 208, 23);
	else if (color == "lightblue")
		return Color(173, 223, 255);
	else if (color == "aquamarine")
		return Color(127, 255, 212);
	else if (color == "seagreen")
		return Color(78, 137, 117);
	else if (color == "green")
		return Color(0, 255, 0);
	else if (color == "yellow")
		return Color(255, 255, 0);
	else if (color == "goldenbrown")
		return Color(234, 193, 23);
		
}

void ParamParser::ParseParams(vector<string> params, Params& pars)
{
	for (int i = 0; i < params.size(); i++)
	{
		string mod = params[i].substr(0, params[i].find(':'));
		string val = params[i].substr(params[i].find(':') + 1);
		if (mod == "background-color")
		{
			pars.backcolor = ParseColor(val);
		}
		else if (mod == "color")
		{
			pars.forecolor = ParseColor(val);
		}
		else if (mod == "font-size")
		{
			double size = pars.charsize * stoi(val) / 100;
			pars.charsize = size;
		}
	}
}
