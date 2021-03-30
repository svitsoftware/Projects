#pragma once

#include <iostream>
using namespace std;

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
using namespace sf;

class SWidgets
{
	class Button
	{
		RectangleShape bt1;
		CircleShape bt2;
		CircleShape bt3;
		Text text;

		Button(int x, int y, int width, int height, string text, int charsize)
		{
			this->bt1.setPosition(x + height / 2, y);
			this->bt1.setSize(Vector2f(width - height, height));
			this->bt1.setFillColor(Color(200, 210, 200));
			this->bt1.setScale(1.f, 1.f);

			this->bt2.setPosition(x + height / 2, y + height / 2);
			this->bt2.setRadius(height / 2);
			this->bt2.setFillColor(Color(200, 210, 200));
			this->bt2.setScale(1.f, 1.f);

			this->bt3.setPosition(width - height / 2, y);
			this->bt3.setRadius(height / 2);
			this->bt3.setFillColor(Color(200, 210, 200));
			this->bt3.setScale(1.f, 1.f);

			this->text.setPosition(x + height / 2, y + (height - charsize) / 2);
			this->text.setString(text);
			this->text.setFillColor(Color(50, 60, 50));
			this->text.setCharacterSize(charsize);
		}

		void Render(RenderWindow*& target)
		{
			target->draw(this->bt2);
			target->draw(this->bt3);
			target->draw(this->bt1);
			target->draw(this->text);
		}
	};
};

