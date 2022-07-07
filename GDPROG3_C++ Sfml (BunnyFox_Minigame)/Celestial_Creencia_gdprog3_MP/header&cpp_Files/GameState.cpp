#include <SFML/System.hpp> //SGANW -5 LETTERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "GameState.h"
using namespace std;
using namespace sf;


GameState::GameState(vector <string> &audioFiles)
{
	int x;
	this->occcupied.resize(20);
	for (x = 0;x < this->occcupied.size();x++)
	{
		this->occcupied[x].resize(20);
	}
	
	transferAudioFiles(audioFiles);
}

void GameState:: transferAudioFiles(vector <string>& audioFiles)
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

int GameState::getRabbitSize()
{
	return this->numberOfRabbits;
}

void GameState::setRabbitSize(int size)
{
	this->numberOfRabbits = size;
}

int GameState::getScore()
{
	return this->score;
}

void GameState::setScore(int score)
{
	this->score = score;
}

int GameState::getWinCondition()
{
	return this->winCondition;
}

void GameState::setWinCondition(int condition)
{
	this->winCondition = condition;
}
vector<vector<int>>& GameState::getOccupied()
{
	return this->occcupied;
}

bool GameState::getFoxMakesAMove()
{
	return this->foxMakesAMove;
}

void GameState::setFoxMakesAMove(bool condition)
{
	this->foxMakesAMove = condition;
}

void GameState::playSound(int index, bool stop)
{
	sound[0].setVolume(2);
	sound[1].setVolume(2);
	sound[2].setVolume(5);
	sound[3].setVolume(5);
	if (stop == true)
	{
		this->sound[index].stop();
		return;
	}
	this->sound[index].play();
	this->sound[index].setLoop(true);
}
