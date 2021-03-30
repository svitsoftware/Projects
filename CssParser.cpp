#include "CssParser.h"

void CssParser::ParseCss(wstring css, CSSOM& cssom)
{
	const wchar_t* cnt = css.c_str();

	string name;
	string prop;

	bool naming = true;
	bool proping = false;

	vector<string> pprs;

	for (int i = 0; i < css.size(); i++)
	{
		switch (cnt[i])
		{
		case '{':
			naming = false;
			proping = true;
			break;
		case '}':
			this->ppar->ParseParams(pprs, *cssom.FindObject(name)->styles);
			pprs.clear();
			name = "";
			proping = false;
			naming = true;
			break;
		case ';':
			if (proping)
			{
				pprs.push_back(prop);
				prop = "";
			}
		default:
			if (naming && cnt[i] != ' ' && cnt[i] != '\n')
			{
				name = name + cnt[i];
			}
			else if (proping && cnt[i] != '\n' && cnt[i] != ';' && cnt[i] != '%')
			{
				prop = prop + cnt[i];
			}
		}
	}
}
