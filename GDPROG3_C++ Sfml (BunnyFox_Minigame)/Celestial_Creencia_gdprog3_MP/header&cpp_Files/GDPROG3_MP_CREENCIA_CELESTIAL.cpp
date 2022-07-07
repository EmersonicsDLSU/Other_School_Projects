/* GDPROG3 MP - "Fox and Rabbit"
Members:
Emerson Paul P. Celestial
Alain Creencia

Date created: 01/24/2021
*/

//library declarations
#include <SFML/System.hpp> //SGANW -5 LETTERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <fstream>
#include <time.h>
#include "Fox.h"
#include "Rabbit.h"
#include "Background.h"
#include "GameState.h"
#include "TextClass.h"
#include "Scene.h"
#include "Button.h"
using namespace std;
using namespace sf;

//typedef declarations
typedef vector<Rabbit> enemyList;
//function declarations
void foxEats(GameState& game, Fox& player, enemyList& rabbitList, TextClass& scoreValueText, TextClass& currentRabbit);
void rabbitRandomMovement(GameState& game, Fox& player, enemyList& rabbitList);
void rabbitSizeDouble(GameState& game, Fox& player, enemyList& rabbitList, Background& background);
void gameCondition(RenderWindow &window, GameState& game, Fox& player, enemyList& rabbitList, Background& winCondition, Background& loseCondition);

int main()
{
	srand(time(NULL));
	RenderWindow window(VideoMode(1500, 1000), "FOX AND RABBIT", Style::Default);
	window.setFramerateLimit(30);

	//Awake  values
	int x, temp, y, z;
	enemyList rabbitList;
	float deltaTime = 0.0f;
	Clock clock;
	bool scene1 = true;
	vector <string> gameStateAudios = {"sounds/title_screen.wav", "sounds/ingame_sound.wav", "sounds/lose.wav", "sounds/win.wav"};
	vector <string> playerAudios = {"sounds/walk_fox.wav","sounds/eat_fox.wav" };
	bool musicOn = false;

	//Awake objects
	GameState game(gameStateAudios);
	TextClass scoreText("fonts/Cuddle-Bunny.ttf", "Score:", 40, Color::White, Vector2f(10, 100));
	TextClass scoreValueText("fonts/Cuddle-Bunny.ttf", to_string(game.getScore()), 40, Color::White, Vector2f(60, 150));
	TextClass totalRabbit("fonts/Cuddle-Bunny.ttf", "Total\nRabbit:", 40, Color::White, Vector2f(10, 250));
	TextClass currentRabbit("fonts/Cuddle-Bunny.ttf", to_string(game.getRabbitSize()), 40, Color::White, Vector2f(60, 350));
	Scene titleScreen("arts/titleScreen.png");

	Background background(Vector2f(1200.0f, 950.0f), "arts/border.png", window);  //background object
	Background background2(Vector2f(1500.0f, 1000.0f), "arts/inGameScreen.png", window); //background background
	Background winCondition(Vector2f(600.0f, 400.0f), "arts/win.png", window);  //background object
	Background loseCondition(Vector2f(600.0f, 400.0f), "arts/lose.png", window);  //background object

	Button playButton(Vector2f(500.0f,250.0f), Vector2f(window.getSize().x/2 - 250, window.getSize().y / 2 - 200), "arts/play.png");

	Fox player(Vector2f(55.0f, 50.0f), "arts/player_idle.png", background.returnBackground(), game.getOccupied(), playerAudios); //fox object

	for (x = 0;x < game.getRabbitSize();x++)
	{
		Rabbit* enemy = new Rabbit(Vector2f(55.0f, 50.0f), "arts/enemy_idle.png", background.returnBackground(), game.getOccupied()); //rabbit object
		rabbitList.push_back(*enemy);
	}

	//window loop
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		//title screen
		if (scene1)
		{
			if (musicOn == false)
			{
				game.playSound(0, false);
				musicOn = true;
			}
			if (!playButton.checkIfButtonClicked(window))
			{
				game.playSound(0, true);
				scene1 = false;
				musicOn = false;
			}
			titleScreen.runScene(window);
			window.draw(playButton.getButton());
			window.display();
			continue;
		}
		//Update
		//plays the ingame background music
		if (musicOn == false) 
		{
			game.playSound(1, false);
			musicOn = true;
		}
		//player moving
		game.setFoxMakesAMove(player.playerMovement(game.getOccupied())); 
		//player animation
		player.animation(player.getIdle_pos(), deltaTime, 0.2f);
		//enemy animation
		for (x = 0;x < game.getRabbitSize();x++)
		{
			rabbitList[x].animation(rabbitList[x].getIdle_pos(), deltaTime, 0.2f);
		}
		//if fox eats a rabbit
		if (game.getFoxMakesAMove())
		{
			player.playSound(0);
			foxEats(game, player, rabbitList, scoreValueText, currentRabbit);
		}
		//rabbit random movement
		if (game.getFoxMakesAMove())
			rabbitRandomMovement(game, player, rabbitList);  
		//doubles the rabbit if the fox moves 3 moves
		if (player.getFoxMoves() == 3)
			rabbitSizeDouble(game, player, rabbitList, background);
		//background of the game
		window.draw(background2.returnBackground());
		//display/draw objects
		window.draw(background.returnBackground());
		window.draw(player.returnPlayer()); //fox
		for (x = 0;x < game.getRabbitSize();x++)
		{
			window.draw(rabbitList[x].getEnemy()); //rabbit
		}
		//Displays the text
		window.draw(scoreText.getText());
		window.draw(scoreValueText.getText());
		window.draw(totalRabbit.getText());
		window.draw(currentRabbit.getText());
		//displays the conditions
		gameCondition(window, game, player, rabbitList, winCondition, loseCondition);
		//displays all the drawn objects
		window.display();
		//clear
		window.clear(Color::Green);
	}

	return 0;
}

/*
Function Definitions:
Total functions = 4
*/
void foxEats(GameState &game,Fox &player, enemyList &rabbitList, TextClass &scoreValueText, TextClass& currentRabbit)
{
	int x;
	for (x = 0;x < rabbitList.size();x++)
	{
		if (player.getFoxPos()[0] == rabbitList[x].getRabbitPos()[0] && player.getFoxPos()[1] == rabbitList[x].getRabbitPos()[1])
		{
			player.playSound(1);
			game.setScore(game.getScore()+1);
			scoreValueText.setTextDesc(to_string(game.getScore()));
			rabbitList.erase(rabbitList.begin() + x);
			game.setRabbitSize(game.getRabbitSize() - 1);
		}
	}
	currentRabbit.setTextDesc(to_string(game.getRabbitSize()));
}

void rabbitRandomMovement(GameState& game, Fox& player, enemyList& rabbitList)
{
	int x;
	if (game.getFoxMakesAMove())
	{
		for (x = 0;x < rabbitList.size();x++)
		{
			rabbitList[x].moveRabbit(game.getOccupied(), true);
		}
		game.setFoxMakesAMove(false);
		player.setMakeAmove(false);
	}
}

void rabbitSizeDouble(GameState& game, Fox& player, enemyList& rabbitList, Background &background)
{
	int x, y,z,temp;
	if (player.getFoxMoves() == 3)
	{
		temp = game.getRabbitSize();
		game.setRabbitSize(game.getRabbitSize() * 2);
		for (x = temp;x < game.getRabbitSize();x++)
		{
			Rabbit* enemy = new Rabbit(Vector2f(55.0f, 50.0f), "arts/enemy_idle.png", background.returnBackground(), game.getOccupied()); //rabbit object
			rabbitList.push_back(*enemy);
		}
		player.setFoxMoves(0);
	}
}


void gameCondition(RenderWindow& window, GameState& game, Fox& player, enemyList& rabbitList, Background& winCondition, Background& loseCondition)
{
	if (game.getRabbitSize() >= 50 && game.getWinCondition() == 0) //LOSE THE GAME
	{
		game.playSound(2, false);
		game.playSound(1, true);
		rabbitList.clear();
		game.setRabbitSize(0);
		game.setWinCondition(-1);
	}
	else if (game.getRabbitSize() == 0 && game.getWinCondition() == 0) //WIN THE GAME
	{
		game.playSound(3, false);
		game.playSound(1, true);
		rabbitList.clear();
		game.setRabbitSize(0);
		game.setWinCondition(1);
	}
	if (game.getWinCondition() == 1)
		window.draw(winCondition.returnBackground());
	else if (game.getWinCondition() == -1)
		window.draw(loseCondition.returnBackground());
}