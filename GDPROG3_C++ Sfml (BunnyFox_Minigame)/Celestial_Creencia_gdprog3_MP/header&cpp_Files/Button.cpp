#include <SFML/System.hpp> //SGANW -5 LETTERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <string.h>
#include "Button.h"
using namespace std;
using namespace sf;

Button::Button(Vector2f buttonDimension, Vector2f pos, string texture)
{
	this->buttonShape.setSize(buttonDimension);
	this->buttonTexture.loadFromFile(texture);
	this->buttonShape.setTexture(&this->buttonTexture);
	this->buttonShape.setOutlineThickness(2);
	this->buttonShape.setOutlineColor(Color::Black);
	this->buttonShape.setOrigin(buttonShape.getSize().x / 2, buttonShape.getSize().y / 2);
	this->buttonShape.setPosition(pos);
	this->buttonShape.setOrigin(0, 0);
	this->buttonPos1.x = this->buttonShape.getPosition().x;
	this->buttonPos1.y = this->buttonShape.getPosition().y;
	this->buttonPos2.x = this->buttonShape.getPosition().x + this->buttonShape.getSize().x;
	this->buttonPos2.y = this->buttonShape.getPosition().y + this->buttonShape.getSize().y;
}

bool Button::checkIfButtonClicked(RenderWindow& window)
{
	this->mousePos.x = Mouse::getPosition(window).x;
	this->mousePos.y = Mouse::getPosition(window).y;
	//checks if the cursor is inside the button
	if (this->mousePos.x >= this->buttonPos1.x && this->mousePos.x <= this->buttonPos2.x && 
		this->mousePos.y <= this->buttonPos2.y && this->mousePos.y >= this->buttonPos1.y &&
		Mouse::isButtonPressed(Mouse::Left))
	{
		return false;
	}
	return true;
}

RectangleShape Button::getButton()
{
	return this->buttonShape;
}