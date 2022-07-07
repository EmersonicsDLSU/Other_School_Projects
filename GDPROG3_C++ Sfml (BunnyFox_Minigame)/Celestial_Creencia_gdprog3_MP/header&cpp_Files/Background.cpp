#include <SFML/System.hpp> //SGANW -5 LETTERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Background.h"
using namespace std;
using namespace sf;

Background::Background(Vector2f dimensions, string textureFile, RenderWindow& window)
{
	this->background.setSize(dimensions);
	this->background.setOrigin(dimensions.x / 2, dimensions.y / 2);
	this->background.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	this->backgroundTexture.loadFromFile(textureFile);
	this->background.setTexture(&backgroundTexture);
}

RectangleShape Background::returnBackground()
{
	return this->background;
}