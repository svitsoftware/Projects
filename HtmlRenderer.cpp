#include "HtmlRenderer.h"

HtmlRenderer::HtmlRenderer()
{

}

HtmlRenderer::~HtmlRenderer()
{
    delete this;
}

void HtmlRenderer::RenderHtml(Nodes*& tree, Renderer*& renderer, CSSOM &cssom)
{
    Object* obj;
    for (int i = 0; i < tree->childs[0]->childs.size(); i++)
    {
        obj = cssom.FindObject(tree->childs[0]->childs[i]->name);
        switch (tree->childs[0]->childs[i]->name.c_str()[0])
        {
        case 'h':
            if (tree->childs[0]->childs[i]->name != "hr")
                renderer->DrawString(10, renderer->GetNextLoc(), tree->childs[0]->childs[i]->data, obj->styles->fontstyle, obj->styles->charsize, obj->styles->forecolor);
            else
            {
                renderer->DrawRectangle(10, renderer->GetNextLoc(), renderer->winrect.right - renderer->winrect.left - 40, 3, obj->styles->backcolor);
            }
            break;
        case 'p':
            renderer->DrawString(10, renderer->GetNextLoc(), tree->childs[0]->childs[i]->data, obj->styles->fontstyle, obj->styles->charsize, obj->styles->forecolor);
            delete obj;
            break;
        case 'a':
            renderer->DrawString(10, renderer->GetNextLoc(), tree->childs[0]->childs[i]->data, obj->styles->fontstyle, obj->styles->charsize, obj->styles->forecolor);
            break;
        case 'b':
            if (tree->childs[0]->childs[i]->name != "button")
                renderer->DrawString(10, renderer->GetNextLoc(), tree->childs[0]->childs[i]->data, obj->styles->fontstyle, obj->styles->charsize, obj->styles->forecolor);
            else
            {
               // par->ParseParams(tree->childs[0]->childs[i]->paramnames, tree->childs[0]->childs[i]->params, *&this->dfparams);
                renderer->DrawButton(10, renderer->GetNextLoc(), tree->childs[0]->childs[i]->data, obj->styles->fontstyle, obj->styles->charsize, obj->styles->forecolor, obj->styles->backcolor);
            }
            break;
        case 'i':
            renderer->DrawString(10, renderer->GetNextLoc(), tree->childs[0]->childs[i]->data, obj->styles->fontstyle, obj->styles->fontstyle, obj->styles->forecolor);
            break;
        default:
            
            break;
        }
    }
}
