#pragma once

#include <Windows.h>

#include <iostream>
#include <vector>
using namespace std;

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
using namespace sf;

#include "SWidgets.h"

enum Decoration
{
	none = 0,
	overline = 1,
	linetrough = 2,
	underline = 3
};
class Renderer
{
private:
	RenderWindow* view;

	Font font;

	vector<RectangleShape> HomeRects;
	vector<Text> HomeTexts;

	vector<Texture> Textures;

	vector<Sprite> ImageControls;
	vector<RectangleShape> RectControls;
	vector<CircleShape> CircleControls;
	vector<Text> TextControls;

	int nextloc = 40;
	bool lowrefresh = false;
	int rtimer = 0;
public:
	Renderer(HWND hwnd);
	~Renderer();

	void DrawImageFromUrl(int x, int y, string url);
	void DrawImageFromFIle(int x, int y, string path, Vector2f = Vector2f(1.f, 1.f));

	void DrawRectangle(int x, int y, int width, int height, Color col, Color = Color::Black, int = 0, bool = false);
	void HideRectangle(int index);

	void DrawCircle(int x, int y, int radius, Color col);
	void HideCircle(int index);

	void DrawString(int x, int y, string text, UINT32 style, int charsize, Color col, Decoration = Decoration::none ,bool = false);
	void HideString();

	void DrawButton(int x, int y, string text, UINT32 style, int charsize, Color col1, Color col2);
	void HideButton();

	void Render();

	void CheckClick(POINT* point);
public:
	void Scroll(short direction);
public:
	RECT winrect;
	int GetNextLoc();
	void higherRefresh();
	void lowerRefresh();
private:
	friend class SWidgets;
};
