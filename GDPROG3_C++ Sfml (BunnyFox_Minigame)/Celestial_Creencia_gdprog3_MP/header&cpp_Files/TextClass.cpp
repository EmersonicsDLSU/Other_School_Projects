#include <SFML/System.hpp> //SGANW -5 LETTERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <string.h>
#include "TextClass.h"
using namespace std;
using namespace sf;

TextClass:: TextClass(string textFont, string textDesc, int textSize, Color color, Vector2f pos)
{
	this->font.loadFromFile(textFont);
	this->text.setFont(this->font);
	this->text.setCharacterSize(textSize);
	this->text.setFillColor(color);
	this->text.setStyle(Text::Bold);
	this->text.setString(textDesc);

	Vector2f textDimension = { this->text.getScale().x,this->text.getScale().y };
	this->text.setOrigin(textDimension.x / 2, textDimension.y / 2);
	text.setPosition(pos);
}

Text TextClass::getText()
{
	return this->text;
}

void TextClass::setTextDesc(string textDesc)
{
	this->text.setString(textDesc);
}
