#include "Renderer.h"


Renderer::Renderer(HWND hwnd)
{
	this->view = new RenderWindow(hwnd);
	this->view->setFramerateLimit(60);

	GetWindowRect(hwnd, &this->winrect);

	this->font.loadFromFile("font.ttf");
}

Renderer::~Renderer()
{
	delete this;
}

void Renderer::DrawImageFromUrl(int x, int y, string url)
{

}

void Renderer::DrawImageFromFIle(int x, int y, string path, Vector2f scale)
{
	Texture tx;
	tx.loadFromFile(path);
	tx.setSmooth(true);
	this->Textures.push_back(tx);

	Sprite sp;
	sp.setTexture(this->Textures[this->Textures.size() - 1]);
	sp.setScale(scale);
	sp.setPosition(x, y);
	this->ImageControls.push_back(sp);
}

void Renderer::DrawRectangle(int x, int y, int width, int height, Color col, Color outlinecol, int outlinethick, bool homepart)
{
	RectangleShape shape;
	shape.setPosition(x, y);
	shape.setSize(Vector2f(width, height));
	shape.setScale(1.f, 1.f);
	shape.setFillColor(col);
	shape.setOutlineThickness(outlinethick);
	shape.setOutlineColor(outlinecol);
	if (!homepart)
	{
		this->RectControls.push_back(shape);
		this->nextloc = this->nextloc + height + 10;
	}
	else
	{
		this->HomeRects.push_back(shape);
	}
}

void Renderer::HideRectangle(int index)
{
	this->RectControls.erase(this->RectControls.begin() + index);
}

void Renderer::DrawCircle(int x, int y, int radius, Color col)
{
	CircleShape shape;
	shape.setPosition(x, y);
	shape.setRadius(radius);
	shape.setFillColor(col);
	this->CircleControls.push_back(shape);
	this->nextloc = this->nextloc + radius * 2 + 10;
}

void Renderer::HideCircle(int index)
{

}

void Renderer::DrawString(int x, int y, string text, UINT32 style, int charsize, Color col, Decoration decor, bool homepart)
{
	Text shape;
	shape.setFont(this->font);
	shape.setCharacterSize(charsize);
	shape.setStyle(style);
	shape.setPosition(x, y);
	shape.setString(text);
	shape.setFillColor(col);
	if (homepart)
	{
		this->HomeTexts.push_back(shape);
	}
	else
	{
		this->TextControls.push_back(shape);
		this->nextloc = this->nextloc + charsize * (count(text.begin(), text.end(), '\n') + 1) + 10;
	}
}

void Renderer::HideString()
{

}

void Renderer::DrawButton(int x, int y, string text, UINT32 style, int charsize, Color col1, Color col2)
{
	Text shapet;
	shapet.setFont(this->font);
	shapet.setCharacterSize(charsize);
	shapet.setStyle(style);
	shapet.setPosition(x + 5, y + 2);
	shapet.setString(text);
	shapet.setFillColor(col1);
	this->TextControls.push_back(shapet);

	RectangleShape shape;
	shape.setPosition(x, y);
	shape.setSize(Vector2f(shapet.getLocalBounds().width + 10, (count(text.begin(), text.end(), '\n') + 1) * charsize + 10));
	shape.setScale(1.f, 1.f);
	shape.setFillColor(col2);
	this->RectControls.push_back(shape);
	this->nextloc = this->nextloc + (count(text.begin(), text.end(), '\n') + 1) * charsize + 10;
}

void Renderer::HideButton()
{
}

void Renderer::Render()
{
	this->view->clear(Color::White);

	for (auto& e : this->RectControls)
	{
		if (e.getPosition().y < this->winrect.bottom - this->winrect.top)
	    	this->view->draw(e);
	}

	for (auto& e : this->CircleControls)
	{
		if (e.getPosition().y < this->winrect.bottom - this->winrect.top)
			this->view->draw(e);
	}

	for (auto& e : this->TextControls)
	{
		if (e.getPosition().y < this->winrect.bottom - this->winrect.top)
			this->view->draw(e);
	}

	for (auto& e : this->HomeRects)
	{
		if (e.getPosition().y < this->winrect.bottom - this->winrect.top)
			this->view->draw(e);
	}

	for (auto& e : this->ImageControls)
	{
		if (e.getPosition().y < this->winrect.bottom - this->winrect.top)
			this->view->draw(e);
	}

	for (auto& e : this->HomeTexts)
	{
		if (e.getPosition().y < this->winrect.bottom - this->winrect.top)
			this->view->draw(e);
	}

	this->view->display();

	if (!lowrefresh)
	{
		this->rtimer = this->rtimer + 1;
		if (this->rtimer == 180)
		{
			this->view->setFramerateLimit(10);
			this->lowrefresh = true;
			this->rtimer = 0;
		}
	}
}

void Renderer::CheckClick(POINT* point)
{
	RECT* rc = new RECT();
	rc->left = this->ImageControls[0].getGlobalBounds().left;
	rc->top = this->ImageControls[0].getGlobalBounds().top;
	rc->right = rc->left + this->ImageControls[0].getGlobalBounds().width;
	rc->bottom = rc->top + this->ImageControls[0].getGlobalBounds().height;
	cout << rc->left << endl << rc->top << endl << rc->right << endl << rc->bottom << endl << point->x << endl << point->y << endl;
	if (point->x < rc->right && point->x > rc->left && point->y < rc->bottom && point->y > rc->top)
	{
		PostQuitMessage(0);
	}
}

void Renderer::Scroll(short direction)
{
	for (int i = 0; i < this->TextControls.size() || i < this->RectControls.size() || i < this->CircleControls.size(); i++)
	{
		if (i < this->TextControls.size())
			this->TextControls[i].move(0, direction);
		if (i < this->RectControls.size())
			this->RectControls[i].move(0, direction);
		if (i < this->CircleControls.size())
			this->CircleControls[i].move(0, direction);

		this->rtimer = 0;
		this->view->setFramerateLimit(60);
		this->lowrefresh = false;
	}
}

int Renderer::GetNextLoc()
{
	return this->nextloc;
}

void Renderer::higherRefresh()
{
	this->lowrefresh = true;
	this->rtimer = 0;
	this->view->setFramerateLimit(60);
}

void Renderer::lowerRefresh()
{
	this->lowrefresh = false;
	this->rtimer = 0;
}