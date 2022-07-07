#include <SFML/System.hpp> //SGANW -5 LETTERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Rabbit.h"
using namespace std;
using namespace sf;

Rabbit::Rabbit(Vector2f dimensions, string textureFile, RectangleShape background, vector<vector<int>>& occupied)
{
	while (true)
	{
		this->rabbitPos[0] = rand() % 20; //current index x
		this->rabbitPos[1] = rand() % 20; //current index y
		if (occupied[rabbitPos[0]][rabbitPos[1]] == 1 || occupied[rabbitPos[0]][rabbitPos[1]] == 2)
			continue;
		else
			break;
	}
	occupied[rabbitPos[0]][rabbitPos[1]] = 1;
	this->initialPosition[0] = background.getPosition().x - (background.getSize().x / 2) + 4 + (this->rabbitPos[0] * 60); //60
	this->initialPosition[1] = background.getPosition().y - (background.getSize().y / 2) + (this->rabbitPos[1] * 47.5); //47.5
	this->enemy.setSize(dimensions);
	this->enemy.setPosition(this->initialPosition[0], this->initialPosition[1]);
	this->enemyTexture.loadFromFile(textureFile);
	this->enemy.setTexture(&enemyTexture);

	this->currentImage = this->enemyTexture.getSize();
	this->uvRect.width = this->currentImage.x / 3;
	this->uvRect.height = this->currentImage.y / 2;
}

RectangleShape Rabbit::getEnemy()
{
	return this->enemy;
}

vector<int> Rabbit::getRabbitPos()
{
	return this->rabbitPos;
}

void Rabbit::moveRabbit(vector<vector<int>>& occupied, bool startMove) //bunny will also move everytime the fox moves
{
	srand(time(NULL));
	int x, y;
	vector<bool>banMoves = {false, false, false, false};
	if (rabbitPos[0] + 1 > 19)
		banMoves[0] = true;
	else if (rabbitPos[0] - 1 < 0)
		banMoves[1] = true;
	else if (rabbitPos[1] + 1 > 19)
		banMoves[2] = false;
	else if (rabbitPos[1] - 1 < 0)
		banMoves[3] = false;
	if ((banMoves[0] || (rabbitPos[0]+1 <= 19 && occupied[rabbitPos[0] + 1][rabbitPos[1]] == 1) || (rabbitPos[0] + 1 <= 19 && occupied[rabbitPos[0] + 1][rabbitPos[1]] == 2)) &&
		(banMoves[1] || (rabbitPos[0]-1 >= 0 && occupied[rabbitPos[0] - 1][rabbitPos[1]] == 1) || (rabbitPos[0] - 1 >= 0 && occupied[rabbitPos[0] - 1][rabbitPos[1]] == 2)) &&
		(banMoves[2] || (rabbitPos[1]+1 <= 19 && occupied[rabbitPos[0]][rabbitPos[1] + 1] == 1) || (rabbitPos[1] + 1 <= 19 && occupied[rabbitPos[0]][rabbitPos[1] + 1] == 2)) &&
		(banMoves[3] || (rabbitPos[1] - 1 >= 0 && occupied[rabbitPos[0]][rabbitPos[1] - 1] == 1) || (rabbitPos[1] - 1 >= 0 && occupied[rabbitPos[0]][rabbitPos[1] - 1] == 2)))
	{
		startMove = false;
	}
	//random movement
	while (startMove)
	{
		occupied[this->rabbitPos[0]][this->rabbitPos[1]] = 0;
		x = rand() % 2; // 0 or 1
		y = rand() % 2; // 0 or 1
		if (x == 0)
		{
			//rabbit is going to the right
			if (y == 0)
			{
				++this->rabbitPos[0];
				if (this->rabbitPos[0] > 19 || occupied[this->rabbitPos[0]][this->rabbitPos[1]] == 1 || occupied[this->rabbitPos[0]][this->rabbitPos[1]] == 2)
				{
					--this->rabbitPos[0];
					continue;
				}
				occupied[this->rabbitPos[0]][this->rabbitPos[1]] = 1;
				this->initialPosition[0] += 60;
				this->enemy.setPosition(this->initialPosition[0], this->initialPosition[1]);
				this->idle_pos = 0;
			}
			else if (y == 1)
			{
				--this->rabbitPos[0];
				if (this->rabbitPos[0] < 0 || occupied[this->rabbitPos[0]][this->rabbitPos[1]] == 1 || occupied[this->rabbitPos[0]][this->rabbitPos[1]] == 2)
				{
					++this->rabbitPos[0];
					continue;
				}
				occupied[this->rabbitPos[0]][this->rabbitPos[1]] = 1;
				this->initialPosition[0] -= 60;
				this->enemy.setPosition(this->initialPosition[0], this->initialPosition[1]);
				this->idle_pos = 1;
			}
		}
		else if (x == 1)
		{
			if (y == 0)
			{
				++this->rabbitPos[1];
				if (this->rabbitPos[1] > 19 || occupied[this->rabbitPos[0]][this->rabbitPos[1]] == 1 || occupied[this->rabbitPos[0]][this->rabbitPos[1]] == 2)
				{
					--this->rabbitPos[1];
					continue;
				}
				occupied[this->rabbitPos[0]][this->rabbitPos[1]] = 1;
				this->initialPosition[1] += 47.5;
				this->enemy.setPosition(this->initialPosition[0], this->initialPosition[1]);
			}
			else if (y == 1)
			{
				--this->rabbitPos[1];
				if (this->rabbitPos[1] < 0 || occupied[this->rabbitPos[0]][this->rabbitPos[1]] == 1 || occupied[this->rabbitPos[0]][this->rabbitPos[1]] == 2)
				{
					++this->rabbitPos[1];
					continue;
				}
				occupied[this->rabbitPos[0]][this->rabbitPos[1]] = 1;
				this->initialPosition[1] -= 47.5;
				this->enemy.setPosition(this->initialPosition[0], this->initialPosition[1]);
			}
		}
		startMove = false;
	}

}

void Rabbit::animation(int row, float deltaTime, float switchTime)
{
	this->currentImage.y = row;
	this->totalTime += deltaTime;
	if (this->totalTime >= switchTime)
	{
		this->totalTime -= switchTime;
		++this->currentImage.x;
		if (this->currentImage.x > 2)
			this->currentImage.x = 0;
	}

	this->uvRect.left = this->currentImage.x * this->uvRect.width;
	this->uvRect.top = this->currentImage.y * this->uvRect.height;
	this->enemy.setTextureRect(uvRect);
}

/*
void Fox::animation(int row, float deltaTime, float switchTime)
{
	this->currentImage.y = row;
	this->totalTime += deltaTime;
	if (this->totalTime >= switchTime)
	{
		this->totalTime -= switchTime;
		++this->currentImage.x;
		if (this->currentImage.x > 2)
			this->currentImage.x = 0;
	}

	this->uvRect.left = this->currentImage.x * this->uvRect.width;
	this->uvRect.top = this->currentImage.y * this->uvRect.height;
	this->player.setTextureRect(uvRect);
}
*/

int Rabbit::getIdle_pos()
{
	return this->idle_pos;
}