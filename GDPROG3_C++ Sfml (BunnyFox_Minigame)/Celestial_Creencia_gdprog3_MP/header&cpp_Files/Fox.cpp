#include <SFML/System.hpp> //SGANW -5 LETTERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Fox.h"
using namespace std;
using namespace sf;

Fox::Fox(Vector2f dimensions, string textureFile, RectangleShape background, vector<vector<int>>& occupied, vector <string>& audioFiles)
{
	while (true)
	{
		foxPos[0] = rand() % 20;
		foxPos[1] = rand() % 20;
		if (occupied[foxPos[0]][foxPos[1]] == 1 || occupied[foxPos[0]][foxPos[1]] == 2)
			continue;
		else
			break;
	}
	occupied[foxPos[0]][foxPos[1]] = 2;
	moveUnits[0] = foxPos[0];
	moveUnits[1] = foxPos[1];
	this->initialPosition[0] = background.getPosition().x - (background.getSize().x / 2) + 4; //60
	this->initialPosition[1] = background.getPosition().y - (background.getSize().y / 2); //47.5
	this->player.setSize(dimensions);
	this->player.setPosition(this->initialPosition[0] + (foxPos[0] * 60), this->initialPosition[1] + (foxPos[1] * 47.5));
	this->playerTexture.loadFromFile(textureFile);
	this->player.setTexture(&this->playerTexture);

	this->currentImage = this->playerTexture.getSize();
	this->uvRect.width = this->currentImage.x / 3;
	this->uvRect.height = this->currentImage.y / 2;
	this->makeAmove = false;

	transferAudioFiles(audioFiles);
}

void Fox::transferAudioFiles(vector <string>& audioFiles)
{
	int x;
	this->buffer.resize(audioFiles.size());
	this->sound.resize(audioFiles.size());
	for (x = 0;x < audioFiles.size();x++)
	{
		if (!this->buffer[x].loadFromFile(audioFiles[x]))
		{
			cout << "Missing Sound File: number " << x;
		}
	}
	for (x = 0;x < audioFiles.size();x++)
	{
		this->sound[x].setBuffer(this->buffer[x]);
	}
}

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

RectangleShape Fox::returnPlayer()
{
	return this->player;
}

bool Fox::playerMovement(vector<vector<int>>& occupied)
{
	++this->time;
	if (Keyboard::isKeyPressed(Keyboard::Left) && this->time >= cooldownTime)//for the left arrow key
	{
		++this->foxMoves;
		occupied[moveUnits[0]][moveUnits[1]] = 0;
		--this->moveUnits[0]; //minus the x index
		if (this->moveUnits[0] < 0)	//clamping
			this->moveUnits[0] = 0;
		this->time = 0;
		this->player.setPosition(this->initialPosition[0] + (this->moveUnits[0] * 60),
			this->initialPosition[1] + (this->moveUnits[1] * 47.5));
		this->makeAmove = true;
		this->idle_pos = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && this->time >= cooldownTime)//for the right arrow key
	{
		++this->foxMoves;
		occupied[moveUnits[0]][moveUnits[1]] = 0;
		++this->moveUnits[0];
		if (this->moveUnits[0] > 19)	//clamping
			this->moveUnits[0] = 19;
		this->time = 0;
		this->player.setPosition(this->initialPosition[0] + (this->moveUnits[0] * 60),
			this->initialPosition[1] + (this->moveUnits[1] * 47.5));
		this->makeAmove = true;
		this->idle_pos = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) && this->time >= cooldownTime)//for the up arrow key
	{
		++this->foxMoves;
		occupied[moveUnits[0]][moveUnits[1]] = 0;
		--this->moveUnits[1];
		if (this->moveUnits[1] < 0)	//clamping
			this->moveUnits[1] = 0;
		this->time = 0;
		this->player.setPosition(this->initialPosition[0] + (this->moveUnits[0] * 60),
			this->initialPosition[1] + (this->moveUnits[1] * 47.5));
		this->makeAmove = true;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) && this->time >= cooldownTime)//for the down arrow key
	{
		++this->foxMoves;
		occupied[moveUnits[0]][moveUnits[1]] = 0;
		++this->moveUnits[1];
		if (this->moveUnits[1] > 19)	//clamping
			this->moveUnits[1] = 19;
		this->time = 0;
		this->player.setPosition(this->initialPosition[0] + (this->moveUnits[0] * 60),
			this->initialPosition[1] + (this->moveUnits[1] * 47.5));
		this->makeAmove = true;
	}
	foxPos[0] = moveUnits[0];
	foxPos[1] = moveUnits[1];
	occupied[moveUnits[0]][moveUnits[1]] = 2;
	return makeAmove;
}

int Fox::getFoxMoves()
{
	return this->foxMoves;
}

void Fox::setFoxMoves(int moves)
{
	this->foxMoves = moves;
}

vector<int> Fox::getFoxPos()
{
	return this->foxPos;
}

void Fox::setMakeAmove(bool condition)
{
	this->makeAmove = condition;
}

int Fox::getIdle_pos()
{
	return this->idle_pos;
}

void Fox:: playSound(int index)
{
	this->sound[0].setVolume(4);
	this->sound[1].setVolume(8);
	this->sound[index].play();
}