#include "HtmlParser.h"

void HtmlParser::ParseHtml(wstring content, Nodes* &tre, CSSOM &cssom)
{
	Nodes* tree = new Nodes("html", "", vector<string>(), vector<string>());
	tree->childs.push_back(new Nodes("body", "", vector<string>(), vector<string>()));

	wstring title;
	wstring elem;
	vector<string> paramname;
	vector<string> param;

	wstring css;

	bool titling = false;
	bool eleming = false;
	bool paramnaming = false;
	bool paraming = false;

	bool cssing = false;

	bool breakline = false;
	bool endtitle = false;

	const wchar_t* cnt = content.c_str();
	for (int i = 0; i < content.size(); i++)
	{
		switch (cnt[i])
		{
		case '<':
			if (eleming && cnt[i + 1] == 'b' && cnt[i + 2] == 'r' && cnt[i + 3] == '>')
				breakline = true;
			else
			{
				eleming = false;
				titling = true;
			}
			break;
		case ' ':
			if (title == L"!DOCTYPE")
				title = title + L" ";
			else
			{
				if (titling)
				{
					paramname.push_back("");
					paramnaming = true;
				}
				else if (eleming)
				{
					elem = elem + cnt[i];
				}
			}
			break;
		case '"':
			if (paramnaming)
			{
				param.push_back("");
				paraming = true;
				paramnaming = false;
			}
			else if (paraming)
			{
				paraming = false;
			}
			break;
		case '>':
			titling = false;
			if (eleming && breakline)
			{
				elem = elem + L'\n';
				breakline = false;
			}
			else if (endtitle == false && title != L"body")
			{
				if (title == L"hr")
				{
					tree->childs[0]->childs.push_back(new Nodes("hr", "", vector<string>(), vector<string>()));
					title = L"";
					elem = L"";
					paramname.clear();
					param.clear();
					eleming = false;
					endtitle = false;
					paramnaming = false;
					paraming = false;
				}
				else if (title == L"style")
				{
					titling = false;
					cssing = true;
				}
				else if (title == L"!DOCTYPE html")
				{
					title = L"";
					elem = L"";
					paramname.clear();
					param.clear();
					eleming = false;
					endtitle = false;
					paramnaming = false;
					paraming = false;
				}
				else
				    eleming = true;
			}
			else
			{
				if (cssing)
				{
					this->cssparser->ParseCss(css, *&cssom);

					css = L"";
					cssing = false;
				}
				else
				{
					eleming = false;
					endtitle = false;
					paramnaming = false;
					paraming = false;
					if (title != L"body" && title != L"")
						tree->childs[0]->childs.push_back(new Nodes(string(title.begin(), title.end()), string(elem.begin(), elem.end()), paramname, param));
					title = L"";
					elem = L"";
					paramname.clear();
					param.clear();
				}
			}			    
			break;
		case '/':
			if (cssing)
			{
				if (paraming)
				{
					char ch;
					wctomb(&ch, cnt[i]);
					param[param.size() - 1] = param[param.size() - 1] + ch;
				}
				else
					endtitle = true;
			} 
			else
			{
				if (titling)
					endtitle = true;
				else
				    css = css + cnt[i];
			}
			break;
		default:
			if (!cssing)
			{
				if (titling && !endtitle)
				{
					if (paramnaming && cnt[i] != '=')
					{
						char ch;
						wctomb(&ch, cnt[i]);
						paramname[paramname.size() - 1] = paramname[paramname.size() - 1] + ch;
					}
					else if (paraming)
					{
						char ch;
						wctomb(&ch, cnt[i]);
						param[param.size() - 1] = param[param.size() - 1] + ch;
					}
					else
					{
						if (cnt[i] != '=')
							title = title + cnt[i];
					}
				}
				else if (eleming && !breakline)
				{
					if (cnt[i] != '\n' && title != L"pre")
						elem = elem + cnt[i];
					else if (title == L"pre")
						elem = elem + cnt[i];
				}
			}
			else
			{
				css = css + cnt[i];
			}
			break;
		}
	}
	
	tre = tree;
}
