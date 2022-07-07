#ifndef SCENE
#define SCENE
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

class Scene
{
private:
	RectangleShape sceneFrame;
	Texture backgroundTex;
public: //constructor
	Scene(string backgroundPic);
public:
	void runScene(RenderWindow& window);
};

#endif //SCENE
