#ifndef BUTTON
#define BUTTON
#include <SFML/System.hpp> //SGANW -5 LETTERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <string.h>
using namespace std;
using namespace sf;

class Button
{
private:
	RectangleShape buttonShape;
	Texture buttonTexture;
	Vector2f mousePos;
	Vector2f buttonPos1; //left side
	Vector2f buttonPos2; //right side
public: //constructor
	Button(Vector2f buttonDimension, Vector2f pos, string texture);
public:
	bool checkIfButtonClicked(RenderWindow& window);
	RectangleShape getButton();
};

#endif //BUTTON

