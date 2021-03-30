#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <iostream>
#include <sstream>
using namespace std;

#include "Tree.h"
#include "Http.h"
#include "Renderer.h"
#include "HtmlParser.h"
#include "HtmlRenderer.h"
#include "CssTree.h"

class App
{
private:
	HttpReq* http = new HttpReq();
	Renderer* ren;
	HtmlParser* parser = new HtmlParser();
	HtmlRenderer* htmlren = new HtmlRenderer();

	vector<Object*> dfobjects;
	CSSOM cssom = CSSOM(vector<Object*>());

	POINT movingMousePoint;
	POINT downMousePoint;
	bool mousePressed = false;

	int WIDTH;
	int HEIGHT;

	void checkClick(RECT* rect);

	void initHome();
	void initDefaultStyles();
public:
	App(HWND &hwnd, int width, int height);
	~App();

	void update(HWND& hwnd);

	void mouseDown(POINT p);
	void mouseMove(HWND& hwnd);
	void mouseUp(POINT p);

	void mouseWheel(short delta);

	void Navigate(string url);
};