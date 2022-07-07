#ifndef GAMESTATE
#define GAMESTATE
#include <vector>
#include <iostream>
using namespace std;
using namespace sf;

class GameState
{
private:
	int numberOfRabbits = 3;
	vector<vector<int>> occcupied;
	bool foxMakesAMove = false;
	int score = 0;
	int winCondition = 0;
	vector<SoundBuffer> buffer;
	vector<Sound> sound;
public:
	//constructor
	GameState(vector <string>& audioFiles);

public:
	int getRabbitSize();
	void setRabbitSize(int size);
	int getScore();
	void setScore(int score);
	int getWinCondition();
	void setWinCondition(int condition);
	vector<vector<int>>& getOccupied();
	bool getFoxMakesAMove();
	void setFoxMakesAMove(bool condition);
	void playSound(int index, bool stop);

private:
	void transferAudioFiles(vector <string>& audioFiles);
};

#endif //GAMESTATE