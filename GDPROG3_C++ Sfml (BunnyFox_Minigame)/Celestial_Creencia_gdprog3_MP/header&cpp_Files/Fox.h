#ifndef FOX
#define FOX
#include <SFML/System.hpp> //SGANW -5 LETTERS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace std;
using namespace sf;


class Fox
{
private:
	RectangleShape player;
	Texture playerTexture;
	float initialPosition[2];
	int moveUnits[2] = { 0, 0 };
	vector<int> foxPos = { 0, 0 }; //current position of the fox
	float time = 0; //total time of the current time elapsed
	float cooldownTime = 15.0f; //time interval before the player can move again
	int foxMoves = 0; //checks if the fox moves 3 turns
	bool tempOccupied[20][20];
	bool makeAmove = false;
	vector<SoundBuffer> buffer;
	vector<Sound> sound;

private: //for animation
	IntRect uvRect;
	Vector2u currentImage;
	float totalTime = 0;
	int idle_pos = 0;

public://Constructor
	Fox(Vector2f dimensions, string textureFile, RectangleShape background, vector<vector<int>>& occupied, vector <string>& audioFiles);

public:
	RectangleShape returnPlayer();
	bool playerMovement(vector<vector<int>>& occupied); //add movements to the player
	int getFoxMoves();
	void setFoxMoves(int moves);
	vector<int> getFoxPos();
	void setMakeAmove(bool condition);
	void animation(int col, float deltaTime, float switchTime);
	int getIdle_pos();
	void playSound(int index);

private:
	void transferAudioFiles(vector <string>& audioFiles);
};

#endif // !FOX