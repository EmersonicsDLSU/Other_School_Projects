#ifndef RABBIT
#define RABBIT
#include <SFML/System.hpp> //SGANW -5 LETTERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Rabbit
{
private:
	RectangleShape enemy;
	Texture enemyTexture;
	float initialPosition[2];
	vector<int> rabbitPos = { 0, 0 }; //current position of the fox

private: //for animation
	IntRect uvRect;
	Vector2u currentImage;
	float totalTime = 0;
	int idle_pos = 0;

public:
	//Constructor
	Rabbit(Vector2f dimensions, string textureFile, RectangleShape background, vector<vector<int>>& occupied);

public:
	RectangleShape getEnemy();
	vector<int> getRabbitPos();
	void moveRabbit(vector<vector<int>>& occupied, bool startMove);
	void animation(int col, float deltaTime, float switchTime);
	int getIdle_pos();
};

#endif // !FOX