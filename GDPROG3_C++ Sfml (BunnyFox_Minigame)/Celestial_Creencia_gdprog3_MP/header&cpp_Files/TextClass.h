#ifndef TEXTCLASS
#define TEXTCLASS
#include <SFML/System.hpp> //SGANW -5 LETTERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
using namespace sf;

class TextClass
{
private:
	Font font;
	Text text;
public: //Constructor
	TextClass(string textFont, string textDesc, int textSize, Color color, Vector2f pos);
public:
	Text getText();
	void setTextDesc(string textDesc);
};

#endif