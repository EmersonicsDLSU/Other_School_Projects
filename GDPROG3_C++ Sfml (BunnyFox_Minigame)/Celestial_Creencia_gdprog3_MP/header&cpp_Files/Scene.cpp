#include <SFML/System.hpp> //SGANW -5 LETTERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <string.h>
#include "Scene.h"
using namespace std;
using namespace sf;

Scene::Scene(string backgroundPic)
{
	this->sceneFrame.setSize(Vector2f(1500.0f, 1000.0f));
	this->backgroundTex.loadFromFile(backgroundPic);
	this->sceneFrame.setTexture(&this->backgroundTex);
}

void Scene::runScene(RenderWindow& window)
{
	window.draw(sceneFrame);
}