#pragma once

#include "Tree.h"
#include "Renderer.h"
#include "ParamParser.h"
#include "Params.h"
#include "CssTree.h"

class HtmlRenderer
{
private:
	ParamParser* par = new ParamParser();
public:
	HtmlRenderer();
	~HtmlRenderer();
	void RenderHtml(Nodes*& tree, Renderer*& renderer, CSSOM& cssom);
};

