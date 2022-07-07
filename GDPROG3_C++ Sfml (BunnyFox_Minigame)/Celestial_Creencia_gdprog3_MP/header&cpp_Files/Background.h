#ifndef BACKGROUND
#define BACKGROUND
#include <SFML/System.hpp> //SGANW -5 LETTERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Background
{
private:
	RectangleShape background;
	Texture backgroundTexture;
public:
	//Constructor
	Background(Vector2f dimensions, string textureFile, RenderWindow& window);
	RectangleShape returnBackground();
};

#endif //BACKGROUND

