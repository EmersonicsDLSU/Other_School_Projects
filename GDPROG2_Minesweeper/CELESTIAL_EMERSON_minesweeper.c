/*
Programmed by: <Emerson Paul P. Celestial> <S18>

Description: <Describe what this program does briefly>
	In my MP, I really tried to copy all the original features of Minesweeper and also the design of the game.
My program recreates all the mechanics in the game of Minesweeper, and I also add some additional features
like adding a hint feature giving the players hints, a highscore(base on time finished) feature and all the needed 
requirements said in the specifications are all implemented. My favorite feature that I create is the randomBombPlacer 
function because it can givethe player an easy time placing the bombs in the field but the placement would be random.
Another cool feature that I add is the "time" and this feature is correlated to my highscore feature, so the best
player in that levelSet will be determined on how fast the player finsh it. I also program to save every state of 
the player in the game, so whenever he/she accidentally exit the console, the levelSet state of the revealed tiles
will be saved.

Last Modified: <date when last revision was made>	09/30/2020
*/

//Preprocessor directives
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "interface.h"

//specifications for each level
struct MStag{
	int rows;
	int cols;
	int bombs;
	int bombPos[224][2];
	struct MStag *pNext;
};

typedef struct MStag MS;

//specifications for each levelSet
struct MSdataTag{
	MS *levelSet;
	int nLevels;
	int highScores;
	int hints;
	char name[5];
};

typedef struct MSdataTag MSdata;

//function declarations
void initialize(MS **levelSet);
int mainMenu(int *nMenuChoice, MS **levelSet, MSdata **data, char fileName[]);
void mainMenuDisplay(int **nMenuChoice);
void createLevelSet(MS **levelSet, int *rows, int *cols, int *bombs, int bombPos[][2], MSdata **data, char fileName[]);
int specification(MS **levelSet);
void randomBombPlacer(MS **levelSet);
void hintTileReveal(int nMark[][15], int nField[][15], char cPlacedFlag[][15], int nSpot[], int nTileRow, int nTileColumn);
void manualBombLocations(MS **pTemp);
void editLevelMenu(MS **levelSet, MSdata **data, char fileName[], int nAutoSave);
void editLevelMenuDisplay(int *nEditLevelChoice);
void addLevel(MS **levelSet, MSdata **data, char fileName[]);
void editBombLocation1(MS **levelSet, MSdata **data, char fileName[]);
void editBombLocation2(MS **levelSet, MSdata **data, MS **current, int count, char fileName[]); //continuation of editBombLocation1
int deleteBombLocation(MS **current);
int levelSetSpecs(MS **levelSet, MSdata *data, char cField[][15], int *nTileRow, int *nTileColumn, int *nBombSize, int *nBomb, int *nCurrentLevel);
void saveText(MS **saveLevel, MSdata **data, char fileName[], int nLevels);
int loadText1(MS **levelSet, MSdata **data, char fileName[]);
void loadText2(MS **levelSet, MSdata **data, FILE **fptr); //continuation of loadText1
int deleteLevelSet(char deleteFileName[]);
void deleteLevel(MS **levelSet, MSdata **data, char fileName[], int nLevels);
void levelDisplay(MS *display);
void highScoreDisplay(MSdata **data);
void instructions();
void timer(float t);
void bombLocator(char cField[][15], int nField[][15], int nTileRow, int nTileColumn);
int checkBombSize(char cPlacedFlag[][15], int nBombSize, int nBomb, int nTileRow, int nTileColumn);
void adjacentNumberPlacer(char cField[][15], int nField[][15], int x , int y, int nTileRow, int nTileColumn);
void fieldDisplay(int nField[][15], int nMark[][15], char cPlacedFlag[][15], int nTileRow, int nTileColumn);
int tilePicker(MSdata **data, char cField[][15], int nMark[][15], int nField[][15], char cPlacedFlag[][15], int nSpot[], char cFlag[], int *nPick, int nBombSize, int nTileRow, int nTileColumn, int *nLose);
void fill(int nField[][15], int nMark[][15], int mark1, int mark2, int nTileRow, int nTileColumn);
void fillBorders(int nField[][15], int nMark[][15], int nTileRow, int nTileColumn);
int adjacentFlag(int nField[][15], int nMark[][15], char cPlacedFlag[][15], int nSpot[], int nTileRow, int nTileColumn);
void fillAdjacentFlag(char cField[][15], int nField[][15], int nMark[][15], char cPlacedFlag[][15], int nSpot[], int nTileRow, int nTileColumn, int *nLose);
void checkIfBomb(int nField[][15], int nMark[][15], char cPlacedFlag[][15], int nSpot[], int nTileRow, int nTileColumn, int *nLose);
void checkIfWinner(int nField[][15], int nMark[][15], char cPlacedFlag[][15], int nTileRow, int nTileColumn, int *nLose, int *nPick);
void saveFeatures(MSdata *data, char fileName[], int nCurrentLevel);
void loadFeatures(MSdata *data, char fileName[], int *nCurrentLevel);
void saveGame(MS **levelSet, MSdata **data, int nMark[][15], char fileName[], int *nBombSize, int *nBomb);
void loadGame(MS **levelSet, MSdata **data, int nMark[][15], char fileName[], int *nBombSize, int *nBomb);
void deAllocate1(MS *levelSet);
void deAllocate2(MSdata *data);

int main()
{
	char cField[15][15]; //check if its a whitespace(W), a bomb(B), or a number(N)
	int nField[15][15]; //number of adjacent bombs; 9 value is the bomb
	int nBombPlacement[224][2]; //position of all the bombs
	int nMark[15][15]; //value 0 for unrevealed; value of 1 for revealed tile
	char cPlacedFlag[15][15]; //value of 1 if the tile has a flag placed by the use
	int nSpot[2]; //tile chosen by the player
	int nLose = 0, nPick = 0; //variable for the lose event
	int nTileRow = 15, nTileColumn = 15, nBombSize = 224, nBomb = 224; //maximum size of MS field; number of bombs(determines the difficulty)
	char cFlag[10] = "OFF"; //toggle mode for the flag feature
	time_t start, end; //variables for timer
	float t; //variable that holds for the numbers of seconds in the timer
	int nMenuChoice = 0; //variable for mainMenu choice
	int nContinueLevel = 0; //variable for while loop to continue in the level set game
	int nCurrentLevel = 0; //current level in the levelSet being played
	int restart = 0; //turns to 1 if the player wants to restart the levelSet
	int nPLayAgain = 1; //after winning/losing in the game, it will revert to the mainMenu
	char fileName[54]; //txt file currently open
	char deleteSave[58] = "SAVE"; // for the saveGame function
	char name[5]; //player's name
	int save = 0;
	int x=0, y=0, z=0, k=0; //variables for iterations

	//instantiation of objects in structures
	MS *levelSet;
	initialize(&levelSet);
	MSdata *data = NULL;
	MSdata *pCurrent;
	
	while(nPLayAgain==1)
	{
		system("cls");
		nPLayAgain = mainMenu(&nMenuChoice, &levelSet, &data, fileName); //gets the user's choice in the mainMenu
		if(nPLayAgain==10) //if user's picked 10, then the game will deAllocate all the allocation
		{
			if(levelSet!=NULL) //to avoid memory leak
				deAllocate1(levelSet);
			if(data!=NULL) //to avoid memory leak
				deAllocate2(data);
			break;
		}
		restart = 0;
		save = 0;
		while(restart==0) //checks if the player choose to restart the game
		{
			system("cls");
			printf("Player's name(max 4 char): ");
			fflush(stdin);
			gets(name);
			if(strlen(name)>4)
			{
				printf("Invalid character name size\n");
				printf("Press Enter to continue");
				fflush(stdin);
				getchar();
				continue;
			}
			system("cls");
			loadFeatures(data, fileName, &nCurrentLevel); //load the current highscore and the number of hints in the levelSet
			start = time(NULL); //timer starts
			while(nContinueLevel==0 && nLose!=1)
			{
				for(x=0;x<nTileRow;x++) //resets the board
				{	
					for(y=0;y<nTileColumn;y++)
					{
						cField[x][y] = 'W'; //whitespace
						nField[x][y] = 0; 
						nMark[x][y] = 0;
						cPlacedFlag[x][y] = 'N';
					}
				}
				saveFeatures(data, fileName, nCurrentLevel);
				nContinueLevel = levelSetSpecs(&levelSet, data, cField, &nTileRow, &nTileColumn, &nBombSize, &nBomb, &nCurrentLevel); //returns 0 if the player needs to move to the next level
				if(save==0) //checks if the game needs to load the recent saved; whenver the user choose to change its levelSet
				{
					save = 1;
					loadGame(&levelSet, &data, nMark, fileName, &nBombSize, &nBomb);
				}
				saveGame(&levelSet,&data, nMark, fileName, &nBombSize, &nBomb);
				bombLocator(cField, nField, nTileRow, nTileColumn);	//locates the position of the bomb
				while(nLose==0)	//breaks the loop if the player lose
				{
					while(nPick==0)	//pick phase; returns 1 if the player inspect a tile
					{
						system("cls");
						printf("Bombs: %d\t:)\tFlag: %s\n", checkBombSize(cPlacedFlag, nBombSize, nBomb, nTileRow, nTileColumn), cFlag); 
						fieldDisplay(nField, nMark, cPlacedFlag, nTileRow, nTileColumn); //displays the unrevealed and reveled tiles
						restart = tilePicker(&data, cField, nMark, nField, cPlacedFlag, nSpot, cFlag, &nPick, nBombSize, nTileRow, nTileColumn, &nLose); /*user chooses a tile; if user choose to restart, 
						then it returns 1 and restart the levelSet*/
						if(restart==1)
						{
							nLose = 2;
							nPick = 1;
							break; //breaks the loop then restart the levelSet
						}
						checkIfWinner(nField, nMark, cPlacedFlag, nTileRow, nTileColumn, &nLose, &nPick); //check if the player wins
						saveGame(&levelSet,&data, nMark, fileName, &nBombSize, &nBomb);
					}
					if(nLose==2)
						break;
						
					nPick = 0;
					fill(nField, nMark, nSpot[0], nSpot[1], nTileRow, nTileColumn); //check if its a blank space, then fill the neighboring blankspaces
					fillBorders(nField, nMark, nTileRow, nTileColumn); //also fills the adjacent numbers bordering the blankspaces
					checkIfWinner(nField, nMark, cPlacedFlag, nTileRow, nTileColumn, &nLose, &nPick); //check if the player wins
					checkIfBomb(nField, nMark, cPlacedFlag, nSpot, nTileRow, nTileColumn, &nLose); //checks if the player chose a tile bomb
					saveGame(&levelSet,&data, nMark, fileName, &nBombSize, &nBomb);
					nPick=0;
					if(nLose==1) //if the player loses, then all the tiles in the field will be revealed
					{
						for(x=0;x<nTileRow;x++)
						{
							for(y=0;y<nTileColumn;y++)
							{
								nMark[x][y] = 1;
								cPlacedFlag[x][y] = 'N';
							}
						}
						data->hints += 1;
						break;
					}
					saveGame(&levelSet, &data, nMark, fileName, &nBombSize, &nBomb);
					system("cls");
				}
				if(nLose==-1) //if the player wins, then all the tiles in the field will be revealed
				{	
					data->hints += 1;
					for(x=0;x<nTileRow;x++)
					{
						for(y=0;y<nTileColumn;y++)
						{
							nMark[x][y] = 1;
							cPlacedFlag[x][y] = 'N';
						}
					}
					printf("NICE!\n");
					fieldDisplay(nField, nMark, cPlacedFlag, nTileRow, nTileColumn);
					printf("Press Enter to continue.");
					fflush(stdin);
					getchar();
					system("cls");
				}
				if(nContinueLevel==0 && nLose!=1) //if the player won the level
				{
					nPick = 0;
					nLose = 0;
				}
				saveGame(&levelSet, &data, nMark, fileName, &nBombSize, &nBomb);
			}
			end = time(NULL); //stops the timer
			if(nLose!=2)
			{
				t = difftime(end,start);
				system("cls");
				fieldDisplay(nField, nMark, cPlacedFlag, nTileRow, nTileColumn);
			}
			//restart statements
			restart = 0;
			saveGame(&levelSet,&data, nMark, fileName, &nBombSize, &nBomb);
			if(nLose==1) //if the player loses a level
			{
				printf("YOU LOSE!\tTIME: ");
				timer(t);
				restart = 1;
				strcat(deleteSave,fileName);
				remove(deleteSave); //removes the latest save state
			}
			else if(nLose!=1 && nLose!=2)
			{
				if(data->highScores==0)
				{
					strcpy(data->name,name);
					data->highScores = t;
				}	
				else if(t<data->highScores) //if the player gets the highScore
				{
					strcpy(data->name,name);
					data->highScores = t;
				}	
				printf("YOU WIN!\tTIME: ");
				timer(t);
				restart = 1;
				strcat(deleteSave,fileName);
				remove(deleteSave); //removes the latest save state
			}
			if(nLose==1)
				nCurrentLevel = 0;
			saveFeatures(data, fileName, nCurrentLevel); //save highScore and hints
			
			//restart statements; to make the levelSet restart again ":)"
			strcpy(cFlag, "OFF");
			nContinueLevel = 0;
			nCurrentLevel = 0;
			nLose = 0;
			nPick = 0;
			nMenuChoice = 0;
			strcpy(deleteSave, "SAVE");
		
			printf("\nPress Enter to continue.");
			fflush(stdin);
			getchar();
		}
	}
	
	return 0;
}

/*identifies the location of the bomb in the field
cField(char**) the character vaulue 'W'(whitespace), 'B'(bomb), and 'N'(number) contain in a tile
nField(int**) the integer value 0(whitespace), 9(bomb), and n(number) contain in a tile
nTileRow(int) number of rows in the field
nTileColumn(int) number of columns in the field
doesn't return anything(void)
*/
void bombLocator(char cField[][15], int nField[][15], int nTileRow, int nTileColumn)
{
	int x=0, y=0, z=0, k=0; //for iterations
	for(x=0;x<nTileRow;x++) //identifies the tile containing the bomb
	{
		for(y=0;y<nTileColumn;y++)
		{
			if(cField[x][y]=='B')
			{
				adjacentNumberPlacer(cField, nField, x , y, nTileRow, nTileColumn); //call this function to add number to the tiles adjacent to the bomb
			}
		}
	}
}

/*places a number in a tile basing on the number of adjacent bombs around it
cField(char**) the character vaulue 'W'(whitespace), 'B'(bomb), and 'N'(number) contain in a tile
nField(int**) the integer value 0(whitespace), 9(bomb), and n(number) contain in a tile
x(int) the current x value of the "bombLocator" function;
y(int) the current y value of the "bombLocator" function;
nTileRow(int) number of rows in the field
nTileColumn(int) number of columns in the field
doesn't return anything(void)
*/
void adjacentNumberPlacer(char cField[][15], int nField[][15], int x , int y, int nTileRow, int nTileColumn)
{
	//place a number in the tile adjaccent to a bomb; checks all the 8 tiles surrounding the bomb
	nField[x][y] = 9;
	if(!(x-1<0) && !(y-1<0) && cField[x-1][y-1]!='B')
	{
		++nField[x-1][y-1];
		cField[x-1][y-1] = 'N';
	}
	if(!(x-1<0) &&  cField[x-1][y]!='B')
	{
		++nField[x-1][y];
		cField[x-1][y] = 'N';
	}
	if(!(x-1<0) && !(y+1>=nTileColumn) && cField[x-1][y+1]!='B')
	{
		++nField[x-1][y+1];
		cField[x-1][y+1] = 'N';
	}
	if(!(y-1<0) && cField[x][y-1]!='B')
	{
		++nField[x][y-1];
		cField[x][y-1] = 'N';
	}
	if(!(y+1>=nTileColumn) && cField[x][y+1]!='B')
	{
		++nField[x][y+1];
		cField[x][y+1] = 'N';
	}
	if(!(x+1>=nTileRow) && !(y-1<0) && cField[x+1][y-1]!='B')
	{
		++nField[x+1][y-1];
		cField[x+1][y-1] = 'N';
	}
	if(!(x+1>=nTileRow) && cField[x+1][y]!='B')
	{
		++nField[x+1][y];
		cField[x+1][y] = 'N';
	}
	if(!(x+1>=nTileRow) && !(y+1>=nTileColumn) && cField[x+1][y+1]!='B')
	{
		++nField[x+1][y+1];
		cField[x+1][y+1] = 'N';
	}
	
}

/*this function is for getting the input of the user for opening a tile; toggling of the flag mechanic
data(MSdata **) address of structiure pointer "data"
cField(char**) the character vaulue 'W'(whitespace), 'B'(bomb), and 'N'(number) contain in a tile
nMark(int**) the integer value of 0(unrevealed tile) and 1(revealed tile) of the tile
nField(int**) the integer value 0(whitespace), 9(bomb), and n(number) contain in a tile
cPlacedFlag(char**) the character vaulue 'F'(placed flag) and 'N'(no placed flag) contain in a tile
nSpot(int*) the index of the user picked tile; [0] is the row index while [1] is the column index
cFlag(char*) a string for the display of flag feature status; the string "ON" and "OFF
nPick(int*) integer pointer that receives the address of nPick that is used in the while loop condition for the pick phase; 0 for continuous pick
of tile index while 1 for the closing of the pick phase
nBombSize(int) number of bombs in the field
nTileRow(int) number of rows in the field
nTileColumn(int) number of columns in the field
nLose(int*) integer pointer that receives the address of nLose that is used in the while loop condition for the whole mineSweeper field mechanic 
phase; 0 for continuos gameplay, 1 for win status and -1 for lose status
returns 1 if the players wants to restart in playing the levelSet(int)
*/
int tilePicker(MSdata **data, char cField[][15], int nMark[][15], int nField[][15], char cPlacedFlag[][15], int nSpot[], char cFlag[], int *nPick, int nBombSize, int nTileRow, int nTileColumn, int *nLose)
{
	int x=0, y=0, z=0, k=0; //for iterations
	char respond[21];
	
	printf("Choose the tile index to open (put one space between) \n");
	printf("Type \"flag\" to toggle the Flag feature\n");
	printf("Type \":)\" to restart the game\n");
	printf("Type \"hint\" to randomnly reveal a tile(Available Hints: %d)\n", (*data)->hints);
	printf("row and column(i.e. \"7 0\"): ");
	fflush(stdin);
	gets(respond);
	strlwr(respond);
	//if the user chose to restart the game
	if(strcmp(respond,":)")==0)
	{
		system("cls");
		printf(":(\nRestarting the Level Set\n");
		return 1;
	}
	//if the "flag" feature is called
	if(strcmp(respond,"flag")==0)
	{
		if(strcmp(cFlag,"OFF")==0)
			strcpy(cFlag, "ON");
		else
			strcpy(cFlag, "OFF");
		system("cls");
		return 0;
	}
	//if the user wants to use a hint
	if(strcmp(respond,"hint")==0 && (*data)->hints>0) //hint
	{
		--((*data)->hints);
		hintTileReveal(nMark, nField, cPlacedFlag, nSpot, nTileRow, nTileColumn);
		if(nField[nSpot[0]][nSpot[1]]!=0)
		{
			nMark[nSpot[0]][nSpot[1]] = 1;
		}
      	*nPick = 1;
		return 0;
	}
	//if the user wants to use a hint but hint has no value
	else if(strcmp(respond,"hint")==0 && (*data)->hints<=0)
	{
		return 0;
	}
	//if the input is a tile index
	sscanf(respond, "%d %d", &nSpot[0], &nSpot[1]);
	//if the "flag" feature is on
	if(strcmp(cFlag,"ON")==0)
	{
		if(nField[nSpot[0]][nSpot[1]]!=0 && nMark[nSpot[0]][nSpot[1]]==1 && adjacentFlag(nField, nMark, cPlacedFlag, nSpot, nTileRow, nTileColumn))
		{
			fillAdjacentFlag(cField, nField, nMark, cPlacedFlag, nSpot, nTileRow, nTileColumn, nLose);
			if(*nLose==1)
				*nPick = 1;
		}
		if(nBombSize!=0 && nMark[nSpot[0]][nSpot[1]]!=1)
		{
			if(cPlacedFlag[nSpot[0]][nSpot[1]]=='N')
				cPlacedFlag[nSpot[0]][nSpot[1]]='F';
			else
				cPlacedFlag[nSpot[0]][nSpot[1]]='N';
		}
		if(nBombSize==0 && nMark[nSpot[0]][nSpot[1]]!=1)
		{
			if(cPlacedFlag[nSpot[0]][nSpot[1]]=='F')
				cPlacedFlag[nSpot[0]][nSpot[1]]='N';
		}
		system("cls");
		return 0;
	}
	if(cPlacedFlag[nSpot[0]][nSpot[1]]=='F') //return whenever they click the flag with an OFF toggle flag
	{
		system("cls");
		return 0;
	}
	if(nField[nSpot[0]][nSpot[1]]!=0 && nMark[nSpot[0]][nSpot[1]]==1 && adjacentFlag(nField, nMark, cPlacedFlag, nSpot, nTileRow, nTileColumn))
		fillAdjacentFlag(cField, nField, nMark, cPlacedFlag, nSpot, nTileRow, nTileColumn, nLose);
	if(nField[nSpot[0]][nSpot[1]]!=0 && nMark[nSpot[0]][nSpot[1]]==0) //reveal the tile chosen by the user, except for chosen bomb
		nMark[nSpot[0]][nSpot[1]] = 1;
	*nPick = 1;
	return 0;
} 

/*Displays the image of the field, the tileNumbers, flag icon, bomb, blankspace, unrevealed and revealed tiles
nField(int**) the integer value 0(whitespace), 9(bomb), and n(number) contain in a tile
nMark(int**) the integer value of 0(unrevealed tile) and 1(revealed tile) of the tile
cPlacedFlag(char**) the character vaulue 'F'(placed flag) and 'N'(no placed flag) contain in a tile
nTileRow(int) number of rows in the field
nTileColumn(int) number of columns in the field
doesn't return anything(void)
*/
void fieldDisplay(int nField[][15], int nMark[][15], char cPlacedFlag[][15], int nTileRow, int nTileColumn)
{
	int x=0, y=0, z=0, k=0; //for iterations
	
	// displays the entire MS field
	iSetColor(I_COLOR_RED);
	printf("   ");
	for(x=0;x<nTileColumn;x++)
	{
		if(x>9)
			printf("%d ", x-10);
		else
			printf("%d ", x);
	}
	printf("\n");
	for(x=0;x<nTileRow;x++)
	{
		if(x>9)
			printf("%d", x);
		else
			printf("%d ", x);
		for(y=0;y<nTileColumn;y++)
		{
			iSetColor(I_COLOR_YELLOW);
			if(y==0)
				iSetColor(I_COLOR_RED);
			if(cPlacedFlag[x][y]=='F' && (nMark[x][y]==0 || nMark[x][y]!=0))
			{
				nMark[x][y]=0;
				printf("|");
				iSetColor(I_COLOR_YELLOW);
				printf("F");
				continue;
			}
			if(nMark[x][y]!=0 && cPlacedFlag[x][y]!='F')
			{
				if(nField[x][y]==9)
				{
					printf("|");
					iSetColor(I_COLOR_RED);
					printf("0");
				}
				else if(nField[x][y]==0)
				{
					printf("|");
					iSetColor(I_COLOR_YELLOW);
					printf("#");
				}
				else
				{
					printf("|", nField[x][y]);
					if(nField[x][y]==1)
						iSetColor(I_COLOR_CYAN);
					if(nField[x][y]==2)
						iSetColor(I_COLOR_GREEN);
					if(nField[x][y]==3)
						iSetColor(I_COLOR_RED);
					if(nField[x][y]==4)
						iSetColor(I_COLOR_BLUE);
					if(nField[x][y]==5)
						iSetColor(I_COLOR_PURPLE);	
					if(nField[x][y]==6)
						iSetColor(I_COLOR_CYAN);
					if(nField[x][y]==7)
						iSetColor(I_COLOR_GREEN);
					if(nField[x][y]==8)
						iSetColor(I_COLOR_RED);
					printf("%d", nField[x][y]);
					iSetColor(I_COLOR_WHITE);
				}
			}
			else
				printf("| ");
		}
		iSetColor(I_COLOR_RED);
		printf("|\n");
	}
	iSetColor(I_COLOR_WHITE);
}

/*recursive function to check the eight tiles surrounding the specified tile if it's a part of the conjoint blankspace area
nField(int**) the integer value 0(whitespace), 9(bomb), and n(number) contain in a tile
nMark(int**) the integer value of 0(unrevealed tile) and 1(revealed tile) of the tile
mark1(int) receives the value of nSpot[0] for the user picked input for the row index
mark2(int) receives the value of nSpot[0] for the user picked input for the row index
nTileRow(int) number of rows in the field
nTileColumn(int) number of columns in the field
doesn't return anything(void)
*/
void fill(int nField[][15], int nMark[][15], int mark1, int mark2, int nTileRow, int nTileColumn)
{
	//flood fill algorithm - checks every tile if its a blankspace, if not then it return that condition
	if(mark1<0 || mark2<0 || mark1>=nTileRow || mark2>=nTileColumn || nMark[mark1][mark2]==1 || nField[mark1][mark2]!=0)
	{
		return;
	}
	nMark[mark1][mark2] = 1;
	fill(nField, nMark, mark1-1, mark2, nTileRow, nTileColumn);
	fill(nField, nMark, mark1+1, mark2, nTileRow, nTileColumn);
	fill(nField, nMark, mark1, mark2-1, nTileRow, nTileColumn);
	fill(nField, nMark, mark1, mark2+1, nTileRow, nTileColumn);
	fill(nField, nMark, mark1-1, mark2-1, nTileRow, nTileColumn);
	fill(nField, nMark, mark1-1, mark2+1, nTileRow, nTileColumn);
	fill(nField, nMark, mark1+1, mark2-1, nTileRow, nTileColumn);
	fill(nField, nMark, mark1+1, mark2+1, nTileRow, nTileColumn);
}

/*fills the border of adjacent numbers surrounding the blankspace area
nField(int**) the integer value 0(whitespace), 9(bomb), and n(number) contain in a tile
nMark(int**) the integer value of 0(unrevealed tile) and 1(revealed tile) of the tile
nTileRow(int) number of rows in the field
nTileColumn(int) number of columns in the field
doesn't return anything(void)
*/
void fillBorders(int nField[][15], int nMark[][15], int nTileRow, int nTileColumn)
{
	int x=0, y=0, z=0, k=0; //for iterations
	//reveals the tile beside the blankspace; border numbers for the cascading effect 
	for(x=0;x<nTileRow;x++)
	{
		for(y=0;y<nTileColumn;y++)
		{
			if(nField[x][y]==0 && nMark[x][y]==1)
			{
				if(!(x-1<0) && !(y-1<0) && nField[x-1][y-1]!=9)
					nMark[x-1][y-1] = 1;
				if(!(x-1<0) && nField[x-1][y]!=9)
					nMark[x-1][y] = 1;
				if(!(x-1<0) && !(y+1>=nTileColumn) && nField[x-1][y+1]!=9)
					nMark[x-1][y+1] = 1;
				if(!(y-1<0) && nField[x][y-1]!=9)
					nMark[x][y-1] = 1;
				if(!(y+1>=nTileColumn) && nField[x][y+1]!=9)
					nMark[x][y+1] = 1;
				if(!(x+1>=nTileRow) && !(y-1<0) && nField[x+1][y-1]!=9)
					nMark[x+1][y-1] = 1;
				if(!(x+1>=nTileRow) && nField[x+1][y]!=9)
					nMark[x+1][y] = 1;
				if(!(x+1>=nTileRow) && !(y+1>=nTileColumn) && nField[x+1][y+1]!=9)
					nMark[x+1][y+1] = 1;
			}
		}
	}
}

//returns 1 if the user's pick tile is surrounded by a tile with a flag in it
/*this function is for getting the input of the user for opening a tile; toggling of the flag mechanic
nField(int**) the integer value 0(whitespace), 9(bomb), and n(number) contain in a tile
nMark(int**) the integer value of 0(unrevealed tile) and 1(revealed tile) of the tile
cPlacedFlag(char**) the character vaulue 'F'(placed flag) and 'N'(no placed flag) contain in a tile
nSpot(int*) the index of the user picked tile; [0] is the row index while [1] is the column index
nTileRow(int) number of rows in the field
nTileColumn(int) number of columns in the field
@return (void) return 1 if there's a flag surrounding the picked tile while returning 0 means there are no flags
*/
int adjacentFlag(int nField[][15], int nMark[][15], char cPlacedFlag[][15], int nSpot[], int nTileRow, int nTileColumn)
{
	int num = nField[nSpot[0]][nSpot[1]];
	int count = 0;
	//check if the "tile number" corresponds with the nubmer of flags around the chosen tile
	if(cPlacedFlag[nSpot[0]-1][nSpot[1]-1]=='F' && nSpot[0]-1>=0 && nSpot[1]-1>=0)
	{
		++count;
		if(num==count && !(num<count))
			return 1;
	}
	if(cPlacedFlag[nSpot[0]-1][nSpot[1]]=='F' && nSpot[0]-1>=0)
	{
		++count;
		if(num==count && !(num<count))
			return 1;
	}
	if(cPlacedFlag[nSpot[0]-1][nSpot[1]+1]=='F' && nSpot[0]-1>=0 && nSpot[1]+1<nTileColumn)
	{
		++count;
		if(num==count && !(num<count))
			return 1;
	}
	if(cPlacedFlag[nSpot[0]][nSpot[1]-1]=='F' && nSpot[1]-1>=0)
	{
		++count;
		if(num==count && !(num<count))
			return 1;
	}
	if(cPlacedFlag[nSpot[0]][nSpot[1]+1]=='F' && nSpot[1]+1<nTileColumn)
	{
		++count;
		if(num==count && !(num<count))
			return 1;
	}
	if(cPlacedFlag[nSpot[0]+1][nSpot[1]-1]=='F' && nSpot[0]+1<nTileRow && nSpot[1]-1>=0)
	{
		++count;
		if(num==count && !(num<count))
			return 1;
	}
	if(cPlacedFlag[nSpot[0]+1][nSpot[1]]=='F' && nSpot[0]+1<nTileRow)
	{
		++count;
		if(num==count && !(num<count))
			return 1;
	}
	if(cPlacedFlag[nSpot[0]+1][nSpot[1]+1]=='F' && nSpot[0]+1<nTileRow && nSpot[1]+1<nTileColumn)
	{
		++count;
		if(num==count && !(num<count))
			return 1;
	}
	return 0;
}

//reveals the tiles surronding the tile open by the user with the tile having the required number of adjacent flags
/*this function is for getting the input of the user for opening a tile; toggling of the flag mechanic
cField(char**) the character vaulue 'W'(whitespace), 'B'(bomb), and 'N'(number) contain in a tile
nField(int**) the integer value 0(whitespace), 9(bomb), and n(number) contain in a tile
nMark(int**) the integer value of 0(unrevealed tile) and 1(revealed tile) of the tile
cPlacedFlag(char**) the character vaulue 'F'(placed flag) and 'N'(no placed flag) contain in a tile
nSpot(int*) the index of the user picked tile; [0] is the row index while [1] is the column index
nTileRow(int) number of rows in the field
nTileColumn(int) number of columns in the field
nLose(int*) integer pointer that receives the address of nLose that is used in the while loop condition for the whole mineSweeper field mechanic 
phase; 0 for continuos gameplay, 1 for win status and -1 for lose status
doesn't return anything(void)
*/
void fillAdjacentFlag(char cField[][15], int nField[][15], int nMark[][15], char cPlacedFlag[][15], int nSpot[], int nTileRow, int nTileColumn, int *nLose)
{
	//reveal the tile adjacent to it if "the tile is unrevealed, the tile index is not out of bound, and there is no placed flag"
	if(nMark[nSpot[0]-1][nSpot[1]-1]==0 && nSpot[0]-1>=0 && nSpot[1]-1>=0 && cPlacedFlag[nSpot[0]-1][nSpot[1]-1]!='F')
	{
		if(cField[nSpot[0]-1][nSpot[1]-1]=='B')
		{
			*nLose = 1;
			return;
		}
		if(cField[nSpot[0]-1][nSpot[1]-1] == 'W' && nMark[nSpot[0]-1][nSpot[1]-1]==0)
		{
			fill(nField, nMark, nSpot[0]-1, nSpot[1]-1, nTileRow, nTileColumn);
			fillBorders(nField, nMark, nTileRow, nTileColumn);
		}
		nMark[nSpot[0]-1][nSpot[1]-1] = 1;
	}
	if(nMark[nSpot[0]-1][nSpot[1]]==0 && nSpot[0]-1>=0 && cPlacedFlag[nSpot[0]-1][nSpot[1]]!='F')
	{
		if(cField[nSpot[0]-1][nSpot[1]]=='B')
		{
			*nLose = 1;
			return;
		}
		if(cField[nSpot[0]-1][nSpot[1]] == 'W' && nMark[nSpot[0]-1][nSpot[1]]==0)
		{
			fill(nField, nMark, nSpot[0]-1, nSpot[1], nTileRow, nTileColumn);
			fillBorders(nField, nMark, nTileRow, nTileColumn);
		}
		nMark[nSpot[0]-1][nSpot[1]] = 1;
	}
	if(nMark[nSpot[0]-1][nSpot[1]+1]==0 && nSpot[0]-1>=0 && nSpot[1]+1<nTileColumn && cPlacedFlag[nSpot[0]-1][nSpot[1]+1]!='F')
	{
		if(cField[nSpot[0]-1][nSpot[1]+1]=='B')
		{
			*nLose = 1;
			return;
		}
		if(cField[nSpot[0]-1][nSpot[1]+1] == 'W' && nMark[nSpot[0]-1][nSpot[1]+1]==0)
		{
			fill(nField, nMark, nSpot[0]-1, nSpot[1]+1, nTileRow, nTileColumn);
			fillBorders(nField, nMark, nTileRow, nTileColumn);
		}
		nMark[nSpot[0]-1][nSpot[1]+1] = 1;
	}
	if(nMark[nSpot[0]][nSpot[1]-1]==0 && nSpot[1]-1>=0 && cPlacedFlag[nSpot[0]][nSpot[1]-1]!='F')
	{
		if(cField[nSpot[0]][nSpot[1]-1]=='B')
		{
			*nLose = 1;
			return;
		}
		if(cField[nSpot[0]][nSpot[1]-1] == 'W' && nMark[nSpot[0]][nSpot[1]-1]==0)
		{
			fill(nField, nMark, nSpot[0], nSpot[1]-1, nTileRow, nTileColumn);
			fillBorders(nField, nMark, nTileRow, nTileColumn);
		}
		nMark[nSpot[0]][nSpot[1]-1] = 1;
	}
	if(nMark[nSpot[0]][nSpot[1]+1]==0 && nSpot[1]+1<nTileColumn && cPlacedFlag[nSpot[0]][nSpot[1]+1]!='F')
	{
		if(cField[nSpot[0]][nSpot[1]+1]=='B')
		{
			*nLose = 1;
			return;
		}
		if(cField[nSpot[0]][nSpot[1]+1] == 'W' && nMark[nSpot[0]][nSpot[1]+1]==0)
		{
			fill(nField, nMark, nSpot[0], nSpot[1]+1, nTileRow, nTileColumn);
			fillBorders(nField, nMark, nTileRow, nTileColumn);
		}
		nMark[nSpot[0]][nSpot[1]+1] = 1;
	}
	if(nMark[nSpot[0]+1][nSpot[1]-1]==0 && nSpot[0]+1<nTileRow && nSpot[1]-1>=0 && cPlacedFlag[nSpot[0]+1][nSpot[1]-1]!='F')
	{
		if(cField[nSpot[0]+1][nSpot[1]-1]=='B')
		{
			*nLose = 1;
			return;
		}
		if(cField[nSpot[0]+1][nSpot[1]-1] == 'W' && nMark[nSpot[0]+1][nSpot[1]-1]==0)
		{
			fill(nField, nMark, nSpot[0]+1, nSpot[1]-1, nTileRow, nTileColumn);
			fillBorders(nField, nMark, nTileRow, nTileColumn);
		}
		nMark[nSpot[0]+1][nSpot[1]-1] = 1;
	}
	if(nMark[nSpot[0]+1][nSpot[1]]==0 && nSpot[0]+1<nTileRow && cPlacedFlag[nSpot[0]+1][nSpot[1]]!='F')
	{
		if(cField[nSpot[0]+1][nSpot[1]]=='B')
		{
			*nLose = 1;
			return;
		}
		if(cField[nSpot[0]+1][nSpot[1]] == 'W' && nMark[nSpot[0]+1][nSpot[1]]==0)
		{
			fill(nField, nMark, nSpot[0]+1, nSpot[1], nTileRow, nTileColumn);
			fillBorders(nField, nMark, nTileRow, nTileColumn);
		}
		nMark[nSpot[0]+1][nSpot[1]] = 1;
	}
	if(nMark[nSpot[0]+1][nSpot[1]+1]==0 && nSpot[0]+1<nTileRow && nSpot[1]+1<nTileColumn && cPlacedFlag[nSpot[0]+1][nSpot[1]+1]!='F')
	{
		if(cField[nSpot[0]+1][nSpot[1]+1]=='B')
		{
			*nLose = 1;
			return;
		}
		if(cField[nSpot[0]+1][nSpot[1]+1] == 'W' && nMark[nSpot[0]+1][nSpot[1]+1]==0)
		{
			fill(nField, nMark, nSpot[0]+1, nSpot[1]+1, nTileRow, nTileColumn);
			fillBorders(nField, nMark, nTileRow, nTileColumn);
		}
		nMark[nSpot[0]+1][nSpot[1]+1] = 1;
	}
}

/*checks if the user chose a tile with a bomb in it and makes the player lose the game
nField(int**) the integer value 0(whitespace), 9(bomb), and n(number) contain in a tile
nMark(int**) the integer value of 0(unrevealed tile) and 1(revealed tile) of the tile
cPlacedFlag(char**) the character vaulue 'F'(placed flag) and 'N'(no placed flag) contain in a tile
nSpot(int*) the index of the user picked tile; [0] is the row index while [1] is the column index
nTileRow(int) number of rows in the field
nTileColumn(int) number of columns in the field
nLose(int*) integer pointer that receives the address of nLose that is used in the while loop condition for the whole mineSweeper field mechanic 
phase; 0 for continuos gameplay, 1 for win status and -1 for lose status
doesn't return anything(void)
*/
void checkIfBomb(int nField[][15], int nMark[][15], char cPlacedFlag[][15], int nSpot[], int nTileRow, int nTileColumn, int *nLose)
{
	int x=0, y=0, z=0, k=0; //for iterations
	//checks all the tile
	if(nField[nSpot[0]][nSpot[1]] == 9)
	{
		for(x=0;x<nTileRow;x++)
		{
			for(y=0;y<nTileColumn;y++)
			{
				nMark[x][y] = 1;
				cPlacedFlag[x][y] = 'N';
			}
		}
		*nLose = 1; //pass 1 if it's a bomb(stoping the while loop)
	}
		
}

/*return the number of Bombs in the field; this is relied by the "Bombs Remaining" display
cPlacedFlag(char**) the character vaulue 'F'(placed flag) and 'N'(no placed flag) contain in a tile
nBombSize(int) number of bombs in the field
nBomb(int) number of bombs in the field
nTileRow(int) number of rows in the field
nTileColumn(int) number of columns in the field
@return (int) returns the remaining marked bombs
*/
int checkBombSize(char cPlacedFlag[][15], int nBombSize, int nBomb, int nTileRow, int nTileColumn)
{
	int x=0, y=0; //for iterations
	int nFlags = 0;
	//check the current number of bombs in the field; use for HUD
	for(x=0;x<nTileRow;x++)
		{
			for(y=0;y<nTileColumn;y++)
			{
				if(cPlacedFlag[x][y]=='F')
					++nFlags;
			}
		}
	nBombSize = nBomb - nFlags;
	return nBombSize;
}

/*a function to check if the player already won
nField(int**) the integer value 0(whitespace), 9(bomb), and n(number) contain in a tile
nMark(int**) the integer value of 0(unrevealed tile) and 1(revealed tile) of the tile
cPlacedFlag(char**) the character vaulue 'F'(placed flag) and 'N'(no placed flag) contain in a tile
nTileRow(int) number of rows in the field
nTileColumn(int) number of columns in the field
nLose(int*) integer pointer that receives the address of nLose that is used in the while loop condition for the whole mineSweeper field mechanic 
phase; 0 for continuos gameplay, 1 for win status and -1 for lose status
nPick(int*) integer pointer that receives the address of nPick that is used in the while loop condition for the pick phase; 0 for continuous pick
doesn't return anything(void)
*/
void checkIfWinner(int nField[][15], int nMark[][15], char cPlacedFlag[][15], int nTileRow, int nTileColumn, int *nLose, int *nPick)
{
	int x=0, y=0, win=0; //for iterations
	for(x=0;x<nTileRow;x++) //checks every tile except a tile bomb, if it's all revealed
	{
		for(y=0;y<nTileColumn;y++)
		{
			if(nField[x][y]==9)
				continue;
			if(nField[x][y]!=9 && cPlacedFlag[x][y]!='F' && nMark[x][y]==0)
			{
				win = 0;
				return;
			}
			if(nField[x][y]!=9 && cPlacedFlag[x][y]!='F' && nMark[x][y]==1)
				win = 1;
		}
	}
	//pass the valid value for the win condition
	if(win==1)
	{
		*nPick = 1;
		*nLose = -1;
	}
}


/*saves the highscore and hints for the levelSet
data(MSdata *) address of structiure pointer "data"
fileName(char*) holds the address of the fileName for the txt file
nCurrentLevel(int) holds the value for the currentLevel of the levelSet
doesn't return anything(void)
*/
void saveFeatures(MSdata *data, char fileName[], int nCurrentLevel)
{
	char newFileName[57] = "REC";
	//create new a name for the record file
	strcat(newFileName, fileName);
	
	FILE *fptr;
	fptr = fopen(newFileName, "w");
	
	//-1 means that the user didn't restart the game
	if(nCurrentLevel!=-1)
		fprintf(fptr, "%d\n", nCurrentLevel);
	else
		fprintf(fptr, "%d\n", 0);
	fprintf(fptr, "%d\n", data->highScores);
	fprintf(fptr, "%d\n", data->hints);
	fprintf(fptr, "%s", data->name);
	
	fclose(fptr);
}

/*loads the highscore and hints for the levelSet
data(MSdata *) address of structiure pointer "data"
fileName(char*) holds the address of the fileName for the txt file
nCurrentLevel(int*) holds the address of the current level of the levelSet
doesn't return anything(void)
*/
void loadFeatures(MSdata *data, char fileName[], int *nCurrentLevel)
{
	char newFileName[57] = "REC";
	char dummy;
	//create new a name for the record file
	strcat(newFileName, fileName);
	
	FILE *fptr;
	fptr = fopen(newFileName, "r");
	if(fptr==NULL)
	{
		fclose(fptr);
		return;
	}
	
	fscanf(fptr, "%d", nCurrentLevel);
	fscanf(fptr, "%c", &dummy);		
	fscanf(fptr, "%d", &(data->highScores));
	fscanf(fptr, "%c", &dummy);
	fscanf(fptr, "%d", &(data->hints));
	fscanf(fptr, "%c", &dummy);
	fscanf(fptr, "%s", data->name);
	
	fclose(fptr);
}

/*saves the last situation of the player in the game
levelSet(MS **) address of structiure pointer "levelSet"
data(MSdata **) address of structiure pointer "levelSet"
nMark(int**) the integer value of 0(unrevealed tile) and 1(revealed tile) of the tile
fileName(char*) holds the address of the fileName for the txt file
nBombSize(int*) number of bombs in the field
nBomb(int*) number of bombs in the field
doesn't return anything(void)
*/
void saveGame(MS **levelSet, MSdata **data, int nMark[][15], char fileName[], int *nBombSize, int *nBomb)
{
	char saveName[58] = "SAVE";
	int x,y,z;
	MS *pRun = *levelSet;
	//create new a name for the save state file
	strcat(saveName, fileName);
	
	FILE *fptr;
	fptr = fopen(saveName, "w");
	if(fptr==NULL)
	{
		fclose(fptr);
		perror("Error in saving game");
		exit(1);
	}
	
	for(x=0;x<(*data)->nLevels;x++)
	{
		fprintf(fptr, "%d\n", pRun->bombs);
		for(y=0;y<pRun->rows;y++)
		{
			for(z=0;z<pRun->cols;z++)
			{
				fprintf(fptr, "%d ", nMark[y][z]);
			}
			fprintf(fptr, "\n");
		}
		fprintf(fptr, "\n");
		pRun = pRun->pNext;
	}
	
	fclose(fptr);
}

/*loads the last situation of the player in the game
levelSet(MS **) address of structiure pointer "levelSet"
data(MSdata **) address of structiure pointer "levelSet"
nMark(int**) the integer value of 0(unrevealed tile) and 1(revealed tile) of the tile
fileName(char*) holds the address of the fileName for the txt file
nBombSize(int*) number of bombs in the field
nBomb(int*) number of bombs in the field
doesn't return anything(void)
*/
void loadGame(MS **levelSet, MSdata **data, int nMark[][15], char fileName[], int *nBombSize, int *nBomb)
{
	char saveName[58] = "SAVE";
	char dummy;
	int value;
	int x,y,z;
	MS *pRun = *levelSet;
	//create new a name for the save state file
	strcat(saveName, fileName);
	
	FILE *fptr;
	fptr = fopen(saveName, "r");
	if(fptr==NULL)
	{
		fclose(fptr);
		return;
	}
	
	for(x=0;x<(*data)->nLevels;x++)
	{
		fscanf(fptr, "%d", nBombSize);
		*nBomb = *nBombSize;
		fscanf(fptr, "%c", &dummy);
		for(y=0;y<pRun->rows;y++)
		{
			for(z=0;z<pRun->cols;z++)
			{
				fscanf(fptr, "%d", &value);
				fscanf(fptr, "%c", &dummy);
				nMark[y][z] = value;
			}
			fscanf(fptr, "%c", &dummy);
		}
		fscanf(fptr, "%c", &dummy);
	}
	
	fclose(fptr);
}

/*displays the time of the player in finishing one level set; starts counting when the player start to play the set
t(float) the value of the time it takes the player to finish a level set
doesn't return anything(void)
*/
void timer(float t)
{
	int x = (int)t;
	//displays the time in seconds value to a format of "hour:minute:seconds"
	if((x/3600)>9)
		printf("%d:", x/3600);
	else
		printf("0%d:", x/3600);
	if(((x%3600)/60)>9)
		printf("%d:", (x%3600)/60);
	else
		printf("0%d:", (x%3600)/60);
	if((x%60)>9)
		printf("%d", x%60);
	else
		printf("0%d", x%60);	
}

/*initializes a structure to NULL.
levelSet(MS **) address of structiure pointer "levelSet"
doesn't return anything(void)
*/
void initialize(MS **levelSet)
{
	*levelSet = NULL;
}

/*function for the main menu that holds several other functions like "Create levelSet", "Edit levelSet", "Highscore", "Instructions"
nMenuChoice(int*) the chosen option number of the user in the main menu
levelSet(MS **) address of structiure pointer "levelSet"
data(MSdata **) address of structiure pointer "data"
fileName(char*) holds the address of the fileName for the txt file
returns 8 and the program quits and deallocates(int)
*/
int mainMenu(int *nMenuChoice, MS **levelSet, MSdata **data, char fileName[])
{
	int rows, cols, bombs, bombPos[224][2];
	int back = 0, create = 0, nToggle = 0, nDummy, nDelete;
	static int nAutoSave = 0;
	char deleteFileName[54];
	char recFileName[57] = "REC";
	char saveFileName[58] = "SAVE";
	MSdata *features;
	
	while(*nMenuChoice==0)
	{
		system("cls");
		mainMenuDisplay(&nMenuChoice);
		if(*nMenuChoice==1 && (*levelSet==NULL || *data==NULL)) //Deny to Play the LevelSet
		{
			system("cls");
			printf("Create/Load a levelSet first.\n");
			printf("Press enter to continue.\n");
			fflush(stdin);
			getchar();
			*nMenuChoice = 0;
		}
		if(*nMenuChoice==2) //Create a new LevelSet
		{
			system("cls");
			printf("Creating a new Level Set will overwrite the current Level Set.\nMake sure to save your current level Set.\n");
			printf("[1]Continue\t[2]Go back\n: ");
			scanf("%d", &create);
			if(create!=1)
			{
				*nMenuChoice = 0;
				continue;
			}
			*levelSet = NULL;
			*data = NULL;
			createLevelSet(levelSet, &rows, &cols, &bombs, bombPos, data, fileName);
			*nMenuChoice = 0;
		}
		if(*nMenuChoice==3 && *levelSet!=NULL && *data!=NULL) //edit the current loaded LevelSet
		{
			editLevelMenu(levelSet, data, fileName, nAutoSave);
			*nMenuChoice = 0;
		}
		else if(*nMenuChoice==3 && (*levelSet==NULL || *data==NULL)) //no loaded levelSet in the mainMenu
		{
			system("cls");
			printf("Create/Load a levelSet first.\n");
			printf("Press enter to continue.\n");
			fflush(stdin);
			getchar();
			*nMenuChoice = 0;
		}
		if(*nMenuChoice==4) //delete a LevelSet
		{
			nDelete = deleteLevelSet(deleteFileName);
			if(nDelete!=1)
			{
				strcpy(recFileName, "REC");
				strcpy(saveFileName, "SAVE");
				remove(deleteFileName);
				strcat(recFileName, deleteFileName);
				remove(recFileName);
				strcat(saveFileName,deleteFileName);
				remove(saveFileName);
				*levelSet = NULL;
				*data = NULL;
			}
			*nMenuChoice = 0;
		}
		if(*nMenuChoice==5) //load a levelSet in the folder
		{
			*levelSet = NULL;
			*data = NULL;
			back = loadText1(levelSet, data, fileName);
			if(back==0)
				(*data)->levelSet = *levelSet;
			*nMenuChoice = 0;
		}
		if(*nMenuChoice==6 && *levelSet!=NULL && *data!=NULL) //save the levelSet
		{
			system("cls");
			printf("Save Level Set successful!\nPress enter to continue.");
			fflush(stdin);
			getchar();
			saveText(levelSet, data, fileName, (*data)->nLevels);
			*nMenuChoice = 0;
		}
		else if(*nMenuChoice==6 && (*levelSet==NULL || *data==NULL))  //no loaded levelSet in the mainMenu
		{
			system("cls");
			printf("Create/Load a levelSet first.\n");
			printf("Press enter to continue.\n");
			fflush(stdin);
			getchar();
			*nMenuChoice = 0;
		}
		if(*nMenuChoice==7) //settings ; for the autoSave feature
		{
			system("cls");
			if(nAutoSave==0)
				printf("Auto Save [ ]\n");
			else if(nAutoSave==1)
				printf("Auto Save [X]\n");
			printf("[1]Toggle\t[2]Back\n: ");
			scanf("%d", &nToggle);
			if(nToggle==1)
			{
				nAutoSave = !nAutoSave;
			}
			*nMenuChoice = 0;
		}
		if(*nMenuChoice==8 && *levelSet!=NULL && *data!=NULL) //access the highScore display feature
		{
			features = *data;
			loadFeatures(features, fileName, &nDummy);
			highScoreDisplay(data);
			*nMenuChoice = 0;
		}
		else if(*nMenuChoice==8 && (*levelSet==NULL || *data==NULL))  //no loaded levelSet in the mainMenu
		{
			system("cls");
			printf("Create/Load a levelSet first.\n");
			printf("Press enter to continue.\n");
			fflush(stdin);
			getchar();
			*nMenuChoice = 0;
		}
		if(*nMenuChoice==9) //shows instructions for mineSweeper
		{
			instructions();
			*nMenuChoice = 0;
		}
		if(*nMenuChoice==10) //exit the game
			return 10;
	}	
}

/*this function shows the highscore of the current levelSet
data(MSdata **) address of structiure pointer "data"
doesn't return anything(void)
*/
void highScoreDisplay(MSdata **data)
{
	system("cls");
	iSetColor(I_COLOR_GREEN);
	printf("======================\n");
	printf("||");
	iSetColor(I_COLOR_WHITE);
	printf("    HIGHSCORE:    ");
	iSetColor(I_COLOR_GREEN);
	printf("||\n");
	printf("||");
	iSetColor(I_COLOR_WHITE);
	if(strlen((*data)->name)==1)
		printf("\t  %s\t    ", (*data)->name);
	else if(strlen((*data)->name)==2)
		printf("\t  %s\t    ", (*data)->name);
	else if(strlen((*data)->name)==3)
		printf("\t  %s\t    ", (*data)->name);
	else if(strlen((*data)->name)==4)
		printf("\t %s\t    ", (*data)->name);
	iSetColor(I_COLOR_GREEN);
	printf("||\n");
	printf("||     ");
	iSetColor(I_COLOR_WHITE);
	timer((*data)->highScores);
	printf("     ");
	iSetColor(I_COLOR_GREEN);
	printf("||\n");
	printf("======================\n");
	iSetColor(I_COLOR_WHITE);
	printf("Press Enter to return.");
	fflush(stdin);
	getchar();
	system("cls");
}

/*this function is accessible in the "mainMenu" function where the player has the option to add more levels in the levelSet,
levelSet(MS **) address of structiure pointer "levelSet"
data(MSdata **) address of structiure pointer "data"
fileName(char*) holds the address of the fileName for the txt file
nAutoSave(int) checks if the user enable the autoSave function
doesn't return anything(void)
*/
void editLevelMenu(MS **levelSet, MSdata **data, char fileName[], int nAutoSave)
{
	int nEditLevelChoice = 0;
	//each options direct to a certain function
	while(nEditLevelChoice==0)
	{
		system("cls");
		editLevelMenuDisplay(&nEditLevelChoice);
		if(nEditLevelChoice==1)
		{
			addLevel(levelSet, data, fileName);
			nEditLevelChoice = 0;
			if(nAutoSave==1)
				saveText(levelSet, data, fileName, (*data)->nLevels);
		}
		if(nEditLevelChoice==2 && *levelSet!=NULL)
		{
			deleteLevel(levelSet, data, fileName, (*data)->nLevels);
			nEditLevelChoice = 0;
			if(nAutoSave==1)
				saveText(levelSet, data, fileName, (*data)->nLevels);
		}
		else if(nEditLevelChoice==2 && *levelSet==NULL)
		{
			printf("No level to delete.\n");
			printf("Press enter to continue.");
			fflush(stdin);
			getchar();
			nEditLevelChoice = 0;
		}
		if(nEditLevelChoice==3 && *levelSet!=NULL)
		{
			editBombLocation1(levelSet, data, fileName);
			nEditLevelChoice = 0;
			if(nAutoSave==1)
				saveText(levelSet, data, fileName, (*data)->nLevels);
		}
		else if(nEditLevelChoice==3 && *levelSet==NULL)
		{
			printf("No level to edit.\n");
			printf("Press enter to continue.");
			fflush(stdin);
			getchar();
			nEditLevelChoice = 0;
		}
		if(nEditLevelChoice==4 && *levelSet==NULL)
		{
			printf("You can't proceed without levels in your LevelSet\n");
			printf("Press enter to continue.");
			fflush(stdin);
			getchar();
			nEditLevelChoice = 0;
		}
	}	
}

/*this is accessible in the "editLevelMenu" function where the player can add more levels in the current levelSet
levelSet(MS **) address of structiure pointer "levelSet"
data(MSdata **) address of structiure pointer "data"
fileName(char*) holds the address of the fileName for the txt file
doesn't return anything(void)
returns nothing(void)
*/
void addLevel(MS **levelSet, MSdata **data, char fileName[])
{
	int x;
	int respond = 1, respond2 = 0,valid = 0;
	int count = 0;
	MS *pTemp;
	
	//resets the number of hints
	(*data)->hints = 0;
	(*data)->highScores = 0;
	
	MSdata *save = *data;
	saveFeatures(save, fileName, -1); //save highScore and hints
	
	//add levels to the current loaded levelSet until the user stop adding a level
	while(respond==1)
	{
		valid = 0;
		if (*levelSet == NULL)
		{
			++count;
			*levelSet = malloc(sizeof(MS));
			if (pTemp == NULL)
			{
				perror("addLevel Error");
				exit(1);
			}
			
			respond2 = specification(levelSet);
			if(respond2==1)
				randomBombPlacer(levelSet);
			(*levelSet)->pNext = NULL;
			
			do
			{
				printf("Add more levels?[1]Yes [2]No): ");
				scanf("%d", &respond);
				system("cls");
			}
			while(respond!=1 && respond!=2);
			
			if(respond==1)
			{
				continue;
			}
			else if(respond==2)
			{
				(*data)->nLevels += count;
				system("cls");
				return;
			}
		}
		else
		{
			++count;
			MS *pRun = *levelSet;
			while (pRun->pNext != NULL)
			{
				pRun = pRun->pNext;
			}
			pTemp = malloc(sizeof(MS));
			if (pTemp == NULL)
			{
				perror("addLevel Error");
				exit(1);
			}
			
			respond2 = specification(&pTemp);
			if(respond2==1)
				randomBombPlacer(&pTemp);
			pTemp->pNext = NULL;
			pRun->pNext = pTemp;
			
			do
			{
				printf("Add more levels?[1]Yes [2]No): ");
				scanf("%d", &respond);
				system("cls");
			}
			while(respond!=1 && respond!=2);
			
			if(respond==1)
			{
				continue;
			}
			else if(respond==2)
			{
				(*data)->nLevels += count;
				system("cls");
				return;
			}	
		}	
	}
}

/*displays the UI and display for the editLevelMenu options.
nEditLevelChoice(int *) holds the address of "nEditLevelChoice" int variable in the "editLevelMenu" function.
doesn't return anything(void)
*/
void editLevelMenuDisplay(int *nEditLevelChoice)
{
	system("cls");
	while(*nEditLevelChoice<1 || *nEditLevelChoice>4)
	{
		iSetColor(I_COLOR_GREEN);
		printf("===============================\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [1]Add Level           ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [2]Delete Levels       ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [3]Edit bomb Locations ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [4]Back\t\t     ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("===============================\n");
		iSetColor(I_COLOR_WHITE);
		printf("After editing, the highscore and hints will reset.\n");
		printf("Input number choice: ");
		scanf("%d", nEditLevelChoice);
		system("cls");
	}
}

/*displays the instruction of the mineSweeper game.
doesn't return anything(void)
*/
void instructions()
{
	printf("\t\t\t\t\tINSTRUCTIONS\n");
	iSetColor(I_COLOR_GREEN);
	printf("===================================================================================================\n");
	printf("||");
	iSetColor(I_COLOR_WHITE);
	printf("1.A squares \"neighbours\" are the squares adjacent above,(below,left,right,and all 4 diagonals.)");
	iSetColor(I_COLOR_GREEN);
	printf("||\n");
	printf("||");
	iSetColor(I_COLOR_WHITE);
	printf("Squares on the sides of the board or in a corner have fewer neighbors.\t\t\t ");
	iSetColor(I_COLOR_GREEN);
	printf("||\n");
	printf("||");
	iSetColor(I_COLOR_WHITE);
	printf("The board does not wrap around the edges.\t\t\t\t\t\t\t ");
	iSetColor(I_COLOR_GREEN);
	printf("||\n");
	printf("||");
	iSetColor(I_COLOR_WHITE);
	printf("2.If you open a square with 0 neighboring bombs, all its neighbors will automatically open.\t ");
	iSetColor(I_COLOR_GREEN);
	printf("||\n");
	printf("||");
	iSetColor(I_COLOR_WHITE);
	printf("This can cause a large area to automatically open.\t\t\t\t\t\t ");
	iSetColor(I_COLOR_GREEN);
	printf("||\n");
	printf("||");
	iSetColor(I_COLOR_WHITE);
	printf("3.To remove a bomb marker from a square, \"ON\" the flag marker then click on that tile again.   ");
	iSetColor(I_COLOR_GREEN);
	printf("||\n");
	printf("||");
	iSetColor(I_COLOR_WHITE);
	printf("4.If you mark a bomb incorrectly, you will have to correct the mistake before you can win.\t ");
	iSetColor(I_COLOR_GREEN);
	printf("||\n");
	printf("||");
	iSetColor(I_COLOR_WHITE);
	printf("Incorrect bomb marking doesn't kill you, but it can lead to mistakes which do.\t\t ");
	iSetColor(I_COLOR_GREEN);
	printf("||\n");
	printf("||");
	iSetColor(I_COLOR_WHITE);
	printf("5.You don't have to mark all the bombs to win; you just need to open all non-bomb squares.\t ");
	iSetColor(I_COLOR_GREEN);
	printf("||\n");
	printf("===================================================================================================\n");
	iSetColor(I_COLOR_WHITE);
	printf("Press enter to go back.\n");
	fflush(stdin);
	getchar();
	return;
}

/*displays the interface for the mainMenu; shows the play, create level set, edit level set, highscore, instrucitons, and quit options.
nMenuChoice(int**) the integer value for the user's choice of option in the mainMenu
doesn't return anything(void)
*/
void mainMenuDisplay(int **nMenuChoice)
{
	system("cls");
	while(**nMenuChoice<1 || **nMenuChoice>10)
	{
		iSetColor(I_COLOR_GREEN);
		printf("===============================\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [1]New Game            ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [2]Create Level Set    ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [3]Edit Level Set      ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [4]Delete Level Set    ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [5]Load Level Set      ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [6]Save Level Set      ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [7]Settings            ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [8]High Score          ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [9]Instructions        ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("||");
		iSetColor(I_COLOR_WHITE);
		printf("    [10]Quit               ");
		iSetColor(I_COLOR_GREEN);
		printf("||\n");
		printf("===============================\n");
		iSetColor(I_COLOR_WHITE);
		printf("Input number choice: ");
		scanf("%d", *nMenuChoice);
		system("cls");
	}
}

/*this function let the player create a new levelSet in the game
levelSet(MS **) address of structiure pointer "levelSet"
rows(int*) holds the address of integer variables "rows" inside the "mainMenu" function and also hold the value for the row 
of the created MS level
cols(int*) holds the address of integer variables "cols" inside the "mainMenu" function and also hold the value for the cols 
of the created MS level
bombs(int*) holds the address of integer variables "bombs" inside the "mainMenu" function and also hold the value for the bombs 
of the created MS level
bombPos(int**) holds the address of integer variables "bombPos" inside the "mainMenu" function and also hold the value for the 
bombsPositions of the created MS level
data(MSdata **) address of structiure pointer "data"
fileName(char*) holds the address of the fileName for the txt file
doesn't return anything(void)
*/
void createLevelSet(MS **levelSet, int *rows, int *cols, int *bombs, int bombPos[][2], MSdata **data, char fileOfName[])
{
	int x, y, z;
	int valid = 0;
	int respond = 0, respond1=0, respond2 = 0, nLevels = 0;
	char name[51], fileName[54];
	MS *pRun;
	MS *pTemp;
	
	//gets the name for the levelSet to be created
	while(valid!=1)
	{
		system("cls");
		printf("Input levelSet file name(max 50 char)\n(Accessing exisitng file will overwrtie it): ");
		scanf("%s", name);
		if(strlen(name)<1 || strlen(name)>50)
		{
			system("cls");
			printf("Invalid name size\n");
			printf("Press enter to retry");
			fflush(stdin);
			getchar();
			continue;
		}
		sprintf(fileName, "%s.txt", name);
		strcpy(fileOfName, fileName);
		valid = 1;
	}	
	//add levels to the recently created levelSet until the user stop adding a level
	while(respond1==0)
	{
		system("cls");
		if(*levelSet==NULL)
		{
			*levelSet = malloc(sizeof(MS));
			if(*levelSet==NULL)
			{
				exit(1);
			}
			
			respond = specification(levelSet);
			if(respond==1)
				randomBombPlacer(levelSet);
			(*levelSet)->pNext = NULL;
		}
		else
		{
			pRun = *levelSet;
			while(pRun->pNext!=NULL)
			{
				pRun = pRun->pNext;
			}
			pTemp = malloc(sizeof(MS));
			if(pTemp==NULL)
			{
				exit(1);
			}
			
			respond = specification(&pTemp);
			if(respond==1)
				randomBombPlacer(&pTemp);
			(pTemp)->pNext = NULL;
			pRun->pNext = pTemp;	
		}
		++nLevels;
		
		while(respond2==0)
		{
			system("cls");
			printf("[1]Add more levels\n");
			printf("[2]Save Level Set\n");
			scanf("%d", &respond1);
			if(respond1==1)
			{
				respond1 = 0;
				respond2 = 1;
			}
			if(respond1==2 && *levelSet==NULL)
			{
				printf("You can't proceed without levels in your LevelSet\n");
				printf("Press enter to continue.");
				fflush(stdin);
				getchar();
				system("cls");
				respond1 = 0;
				respond2 = 0;
			}
			else if(respond1==2 && *levelSet!=NULL)
			{
				saveText(levelSet, data, fileName, nLevels);
				respond2 = 1;
			}
		}
		respond2 = 0;	
	}
	system("cls");
}

/*this function saves the levelSet on a specified fileName
saveLevel(MS **) address of structiure pointer "levelSet"
data(MSdata **) address of structiure pointer "data"
fileName(char*) holds the address of the fileName for the txt file
nLevels(int) holds the value of the number of levels in the created levelSet
doesn't return anything(void)
*/
void saveText(MS **saveLevel, MSdata **data, char fileName[], int nLevels)
{
	//allocating
	if(*data==NULL)
	{
		*data = malloc(sizeof(MSdata));
		if (data == NULL)
		{
			exit(1);
		}
		(*data)->highScores = 0;
		(*data)->hints = 0;
		(*data)->levelSet = *saveLevel;
		(*data)->nLevels = nLevels;
	}
	else
	{
		(*data)->highScores = 0;
		(*data)->hints = 0;
		(*data)->levelSet = *saveLevel;
		(*data)->nLevels = nLevels;
	}
	
	FILE *fptr;
	fptr = fopen(fileName, "w");
	if(fptr==NULL)
	{
		perror("Error1");
		exit(1);
	}
	
	int level, bombs;
	int x,y,z;
	int valid = 0;
	
	level = (*data)->nLevels;
	fprintf(fptr, "%d\n", level);
	while(level!=0)
	{
		bombs = 0;
		--level;
		fprintf(fptr, "%d\n", (*data)->levelSet->rows);
		fprintf(fptr, "%d\n", (*data)->levelSet->cols);
		for(x=0;x<(*data)->levelSet->rows;x++)
		{
			bombs = 0;
			for(y=0;y<(*data)->levelSet->cols;y++)
			{
				bombs = 0;
				while(bombs!=(*data)->levelSet->bombs)
				{
					if((*data)->levelSet->bombPos[bombs][0]==x && (*data)->levelSet->bombPos[bombs][1]==y)
					{
						fprintf(fptr, "X ");
						valid = 1;
						break;
					}
					++bombs;
				}
				if(valid==0)
				{
					fprintf(fptr, "_ ");
				}
				valid = 0;
			}	
			fprintf(fptr, "\n");
		}
			(*data)->levelSet = (*data)->levelSet->pNext;
	}
	
	fclose(fptr);	
}

/*this function loads the levelSet on a specified fileName
levelSet(MS **) address of structiure pointer "levelSet"
data(MSdata **) address of structiure pointer "data"
fileName(char*) holds the address of the fileName for the txt file
returns 1 if the user decide to go back to the mainMenu(int)
*/
int loadText1(MS **levelSet, MSdata **data, char fileName[])
{
	int valid = 0;
	char name[51];
	
	FILE *fptr;
	while(valid!=1)
	{
		system("cls");
		printf("Input levelSet file name to load(input \"back\" to go back): ");
		scanf("%s", name);
		if(strcmp(name,"back")==0)
		{
			fclose(fptr);
			return 1;
		}
		sprintf(fileName, "%s.txt", name);
		fptr = fopen(fileName, "r");
		if(fptr==NULL)
		{
			printf("File not found\n");
			printf("Press enter to retry");
			fflush(stdin);
			getchar();
			continue;
		}
		valid = 1;
	}
	
	int bombs=0;
	int x,y,z;
	static int nBombs = 0;
	char dummy, tile;
	
	*data = malloc(sizeof(MSdata));
	if(*data==NULL)
	{
		perror("Error Load:");
		exit(1);
	}
	
	fscanf(fptr, "%d", &((*data)->nLevels));
	fscanf(fptr, "%c", &dummy);
	for(x=0;x<(*data)->nLevels;x++)
	{
		if(*levelSet==NULL)
		{
			*levelSet = malloc(sizeof(MS));
			if (*levelSet == NULL)
			{
				perror("Error allocation");
				exit(1);
			}
			fscanf(fptr, "%d", &((*levelSet)->rows));
			fscanf(fptr, "%c", &dummy);
			fscanf(fptr, "%d", &((*levelSet)->cols));
			fscanf(fptr, "%c", &dummy);
			bombs = 0;
			nBombs = 0;
			for(y=0;y<((*levelSet)->rows);y++)
			{
				for(z=0;z<((*levelSet)->cols);z++)
				{
					fscanf(fptr, "%c", &tile);
					if(tile=='X')
					{
						++bombs;
						(*levelSet)->bombPos[nBombs][0] = y;
						(*levelSet)->bombPos[nBombs][1] = z;
						++nBombs;
					}
					fscanf(fptr, "%c", &dummy);
				}
				fscanf(fptr, "%c", &dummy);
			}
			(*levelSet)->bombs = bombs;
			(*levelSet)->pNext = NULL;
			continue;
		}
		else
			loadText2(levelSet, data, &fptr);
	}

	fclose(fptr);
	return 0;
}

/*this function loads the levelSet on a specified fileName; this function loads the corresponding levels in the file
saveLevel(MS **) address of structiure pointer "levelSet"
data(MSdata **) address of structiure pointer "data"
fptr(FILE**) holds the address of the file that is currently opened
doesn't return anything(void)
*/
void loadText2(MS **levelSet, MSdata **data, FILE **fptr)
{
	int bombs=0;
	int x,y,z;
	static int nBombs = 0;
	char dummy, tile;
	
	MS *pRun = *levelSet;
	MS *pTemp;
	
	while (pRun->pNext != NULL)
	{
		pRun = pRun->pNext;
	}
		
	pTemp = malloc(sizeof(MS));
	if(pTemp==NULL)
	{
		perror("Error Load:");
		exit(1);
	}
	fscanf(*fptr, "%d", &(pTemp->rows));
	fscanf(*fptr, "%c", &dummy);
	fscanf(*fptr, "%d", &(pTemp->cols));
	fscanf(*fptr, "%c", &dummy);
	bombs = 0;
	nBombs = 0;
	for(y=0;y<(pTemp->rows);y++)
	{
		for(z=0;z<(pTemp->cols);z++)
		{
			fscanf(*fptr, "%c", &tile);
			if(tile=='X')
			{
				++bombs;
				pTemp->bombPos[nBombs][0] = y;
				pTemp->bombPos[nBombs][1] = z;
				++nBombs;
			}
			fscanf(*fptr, "%c", &dummy);
		}
		fscanf(*fptr, "%c", &dummy);
	}
	pTemp->bombs = bombs;
	pTemp->pNext = NULL;
	pRun->pNext = pTemp;
}

/*this function deletes the levelSet on a specified fileName
deleteFileName(char*) holds the address of the fileName for the txt file to be deleted
returns 1 if the user wants to return to the main menu(int)
*/
int deleteLevelSet(char deleteFileName[])
{
	char fileName[54], name[51];
	int valid = 0;
	FILE *fptr;
	
	//checks if the entered name for file deletion exist in the folder
	while(valid==0)
	{	
		system("cls");
		printf("Input the levelSet name to delete(input \"back\" to return): ");
		scanf("%s", name);
		if(strcmp(name,"back")==0)
			return 1;
		sprintf(fileName, "%s.txt", name);
		printf("%s\n", fileName);
		fptr = fopen(fileName, "r");
		if(fptr==NULL)
		{
			printf("File deletion unsuccessful.\n");
			printf("Press Enter to Continue.");
			fflush(stdin);
			getchar();
			continue;
		}
		printf("File deletion successful.\n");
		printf("Press Enter to Continue.");
		fflush(stdin);
		getchar();
		valid = 1;
	}
	
	strcpy(deleteFileName, fileName);
	
	fclose(fptr);
	return 0;
}


/*a function to randomly place the bombs in the field
levelSet(MS **) address of structiure pointer "levelSet"
doesn't return anything(void)
*/
void randomBombPlacer(MS **levelSet)
{
	int x=0, y=0; //for iterations
	srand(time(NULL)); //resets the random number to create another one whenever the program was exited
	
	for(x=0;x<(*levelSet)->bombs;x++)
	{
		(*levelSet)->bombPos[x][0] = rand()%(*levelSet)->rows; //if tileRow is 15, then it will randomnly get from the range 0-14
		(*levelSet)->bombPos[x][1] = rand()%(*levelSet)->cols; //if tileColumn is 15, then it will randomnly get from the range 0-14
		//checks if the randomnly generated value has already been chosen
		for(y=x-1;y>=0;y--)
		{
			if((*levelSet)->bombPos[y][0]==(*levelSet)->bombPos[x][0] && (*levelSet)->bombPos[y][1]==(*levelSet)->bombPos[x][1])
			{
				--x;
				break;
			}
		}
	}
}

/*this function is for the hint mechanic that reveals an unreveal tile that is not a bomb
nMark(int**) the integer value of 0(unrevealed tile) and 1(revealed tile) of the tile
nField(int**) the integer value 0(whitespace), 9(bomb), and n(number) contain in a tile
cPlacedFlag(char**) the character vaulue 'F'(placed flag) and 'N'(no placed flag) contain in a tile
nSpot(int*) the index of the user picked tile; [0] is the row index while [1] is the column index
nTileRow(int) number of rows in the field
nTileColumn(int) number of columns in the field
returns nothing(void)
*/
void hintTileReveal(int nMark[][15], int nField[][15], char cPlacedFlag[][15], int nSpot[], int nTileRow, int nTileColumn)
{
	int valid = 0;
	srand(time(NULL)); //resets the random number to create another one whenever the program was exited
	
	//loop until the tile chosen is not bomb tile
	while(valid==0)
	{
		nSpot[0] = rand()%nTileRow; //if tileRow is 15, then it will randomnly get from the range 0-14
		nSpot[1] = rand()%nTileColumn; //if tileColumn is 15, then it will randomnly get from the range 0-14
		//checks if the randomly generated location is not a bomb tile
		if(nField[nSpot[0]][nSpot[1]]!=9 && nMark[nSpot[0]][nSpot[1]]!=1)
		{
			valid = 1;
		}
	}
}

/*this function let the players pick their desired specification of each levels in the levelSet
levelSet(MS **) address of structiure pointer "levelSet"
returns 0 if the player wants the bombs to be placed manually and returns 1 if the player want the bomb to be randomnly generated(int)
*/
int specification(MS **levelSet)
{
	int x;
	int invalid = 0;
	int choice = 0;
	MS *specs = *levelSet;
	
	//loop until all specifications for rows, cols and bombSize are correct
	while(invalid == 0)
	{
		system("cls");
		printf("Number of rows(min=5, max=15): ");
		scanf("%d", &specs->rows);
		if(specs->rows<5 || specs->rows>15)
		{
			printf("Invalid Input.\n");
			printf("Press enter to continue.\n");
			fflush(stdin);
			getchar();
			continue;	
		}

		printf("Number of cols(min=5, max=15): ");
		scanf("%d", &specs->cols);
		if(specs->cols<5 || specs->cols>15)
		{
			printf("Invalid Input.\n");
			printf("Press enter to continue.\n");
			fflush(stdin);
			getchar();
			continue;		
		}
		
		printf("Randomly generate bomb?[1]Yes[2]No: ");
		scanf("%d", &choice);
		system("cls");
		if(choice==1)
		{
			printf("Number of bombs(min=1, max=%d): ", (specs->rows)*(specs->cols)-1);
			scanf("%d", &specs->bombs);
			if(specs->bombs<1 || specs->bombs>(specs->rows)*(specs->cols)-1)
			{
				printf("Invalid Input.\n");
				printf("Press enter to continue.\n");
				fflush(stdin);
				getchar();
				continue;	
			}
			return 1;
		}
		
		else if(choice==2)
			manualBombLocations(levelSet);
			
		else
			continue;
		invalid = 1;
	}
	
	return 0;
}

/*this function let the player manually place the bombs in the field
pTemp(MS **) address of structiure pointer "levelSet"
doesn't return anything(void)
*/
void manualBombLocations(MS **pTemp)
{
	int x = 0;
	int rowLoc, colLoc, valid = 0, valid2 = 0;
	char loc[10];
	MS *display = *pTemp;
	
	display->bombs = 0;
	
	//loop until the user stop adding bombs in the field; updates the display of the field
	while(valid==0)
	{
		system("cls");
		levelDisplay(display); //function to displays the image of the field
		printf("Bombs Placed: %d\n", x);
		printf("Location of Bomb %d(row and col 0-15)\n(Input \"stop\" to stop adding)\n(Input \"delete\" to delete bombs): ", x+1);
		fflush(stdin);
		gets(loc);
		strlwr(loc);
		if(strcmp(loc, "stop")==0)
		{
			if(display->bombs<1 || display->bombs>(display->rows)*(display->cols)-1)
			{
				printf("Invalid BombSize.\n");
				printf("Press enter to continue.\n");
				fflush(stdin);
				getchar();
				continue;
			}
			break;
		}
		if(strcmp(loc, "delete")==0 && display->bombs!=0)
		{
			valid2 = deleteBombLocation(&display);
			if(valid2!=1)
				--x;
			continue;
		}
		else if(strcmp(loc, "delete")==0 && display->bombs==0)
		{
			printf("No bombs to delete.\n");
			printf("Press enter to continue.\n");
			fflush(stdin);
			getchar();
			continue;
		}
		
		sscanf(loc, "%d %d", &rowLoc, &colLoc);
		if(rowLoc>=display->rows || rowLoc<0 || colLoc>=display->cols || colLoc<0)
		{
			printf("Invalid Input.\n");
			printf("Press enter to continue.\n");
			fflush(stdin);
			getchar();
			continue;
		}
		display->bombPos[x][0] = rowLoc;
		display->bombPos[x][1] = colLoc;
		++x;
		++(display->bombs);
	}
}

/*this function let the players edit the bombs location again to all created levels
levelSet(MS **) address of structiure pointer "levelSet"
data(MSdata **) address of structiure pointer "data"
fileName(char*) holds the address of the fileName for the txt file
doesn't return anything(void)
*/
void editBombLocation1(MS **levelSet, MSdata **data, char fileName[])
{
	int x, y, z;
	int respond = 0, count = 1;
	MS *display;
	MS *current;
	MS *back;
	
	current = *levelSet;
	
	system("cls");
	do
	{
		printf("Level %d\n", count);
		display = current;
		levelDisplay(display);
		
		if(current->pNext!=NULL)
		{
			printf("[1]Next\n");
		}
		
		printf("[2]Finish\n");
		printf("[3]Edit Bomb Locations\n");
		scanf("%d", &respond);
		
		if(respond==1)
		{
			current = current->pNext;
			++count;
		}
		if(respond==2)
		{
			printf("Press enter to continue.");
			fflush(stdin);
			getchar();
			system("cls");
			break;
		}
		if(respond==3)
		{
			editBombLocation2(levelSet, data, &current, count, fileName);
		}
		
		respond = 0;
		system("cls");
	}
	while(current!=NULL);
}

/*this function let the players edit the bombs location again to all created levels
levelSet(MS **) address of structiure pointer "levelSet"
data(MSdata **) address of structiure pointer "data"
current(MS **) address of structiure pointer "levelSet"; this is the structure of the current level being edited
count(int) index of the selected level to be edited with its bombLocations
fileName(char*) holds the address of the fileName for the txt file
doesn't return anything(void)
*/
void editBombLocation2(MS **levelSet, MSdata **data, MS **current, int count, char fileName[])
{
	int respond = 0, del1, del2, add1, add2, valid = 0;
	int x = 0, y = 0,z = 0;
	int nField[15][15] = {0};
	char cAdd[10];
	MS *display = *current;
	MS *saveLevel = *levelSet;
	MSdata *save = *data;
	
	for(x=0;x<(*current)->rows;x++)
	{
		for(y=0;y<(*current)->cols;y++)
		{
			nField[x][y] = 0;
		}
	}
	for(x=0;x<(*current)->bombs;x++)
	{
		nField[(*current)->bombPos[x][0]][(*current)->bombPos[x][1]] = 1;
	}
	
	while(respond==0)
	{
		system("cls");
		levelDisplay(display);
		printf("Existing Bomb in the Field: %d\t Max bombs: %d/%d\n", (*current)->bombs, (*current)->bombs, (*current)->rows*(*current)->cols-1);
		printf("[1]Delete a bomb tile\n");
		printf("[2]Add a bomb tile\n");
		printf("[3]Back\n");
		scanf("%d", &respond);
		
		if(respond==1 && (*current)->bombs!=0)
		{
			valid = deleteBombLocation(current);
			//resets the number of hints
			(*data)->hints = 0;
			saveFeatures(save, fileName, -1); //save highScore and hints
			respond = 0;
		}
		else if(respond==1 && (*current)->bombs==0)
		{
			printf("No bombs in the field.\n");
			printf("Press enter to retry.\n");
			fflush(stdin);
			getchar();
			respond = 0;
		}
		
		if(respond==2 && (*current)->bombs<(*current)->rows*(*current)->cols)
		{
			printf("Select a tile to add bomb(row & column index): ");
			fflush(stdin);
			gets(cAdd);
			sscanf(cAdd, "%d %d", &add1, &add2);
			if(add1<0 || add1>=(*current)->rows || add2<0 || add2>=(*current)->cols)
			{
				printf("Invalid Input.\n");
				printf("Press enter to continue.");
			    fflush(stdin);
				getchar();
				continue;
			}
			if((*current)->bombs==0)
			{
				nField[add1][add2] = 1;
				(*current)->bombPos[(*current)->bombs][0] = add1;
				(*current)->bombPos[(*current)->bombs][1] = add2;
				(*current)->bombs+=1; 
			}
			else
			{
				for(x=0;x<(*current)->bombs;x++)
				{
					if(((*current)->bombPos[x][0]!=add1 || (*current)->bombPos[x][1]!=add2) && nField[add1][add2]==0)
					{
						nField[add1][add2] = 1;
						(*current)->bombPos[(*current)->bombs][0] = add1;
						(*current)->bombPos[(*current)->bombs][1] = add2;
						(*current)->bombs+=1; 
						break;
					}
					else
					{
						printf("The tile already has a bomb.\n");
						printf("Press enter to retry.\n");
						fflush(stdin);
						getchar();
						break;
					}
				}
			}
			respond = 0;
			//resets the number of hints
			(*data)->hints = 0;
			saveFeatures(save, fileName, -1); //save highScore and hints
		}
		else if(respond==2 && (*current)->bombs>=(*current)->rows*(*current)->cols)
		{
			printf("No more bombs remaining.\n");
			printf("Press enter to retry.\n");
			fflush(stdin);
			getchar();
			respond = 0;
		}
		if(respond==3 && (*current)->bombs==0)
		{
			printf("You can't leave with no bombs in the field.\n");
			printf("Press enter to retry.\n");
			fflush(stdin);
			getchar();
			respond = 0;
		}
	}
	while(count!=1)
	{
		--count;
		saveLevel = saveLevel->pNext;
	}
	saveLevel = *current;
}

/*this function let the players delete the bombs location again to all created levels
current(MS **) address of structiure pointer "levelSet"; this is the structure of the current level being edited
doesn't return anything(void)
*/
int deleteBombLocation(MS **current)
{
	int del1, del2, valid = 0;
	char cDelete[10];
	int nField[15][15] = {0};
	int x = 0, y = 0,z = 0;
	MS *display = *current;
	
	for(x=0;x<(*current)->bombs;x++)
	{
		nField[(*current)->bombPos[x][0]][(*current)->bombPos[x][1]] = 1;
	}
	
	//checks if there are still bombs in the field to be deleted
	while(valid==0 && (*current)->bombs!=0)
	{
		printf("Select a tile to delete(row & column index): ");
		fflush(stdin);
		gets(cDelete);
		sscanf(cDelete, "%d %d", &del1, &del2);
		if(del1<0 || del1>=(*current)->rows || del2<0 || del2>=(*current)->cols)
		{
			printf("Invalid Input.\n");
			printf("Press enter to continue.");
			fflush(stdin);
			getchar();
			return 1;
		}
		for(x=0;x<(*current)->bombs;x++)
		{
			z=x;
			if((*current)->bombPos[x][0]==del1 && (*current)->bombPos[x][1]==del2 && nField[del1][del2]==1)
			{
				nField[del1][del2] = 0;
				for(y=x+1;y<(*current)->bombs;y++)
				{
					(*current)->bombPos[z][0] = (*current)->bombPos[y][0];
					(*current)->bombPos[z][1] = (*current)->bombPos[y][1];
					++z;
				}
				(*current)->bombs-=1;
				return 0;
			}
			else if(x==(*current)->bombs-1)
			{
				system("cls");
				printf("No bomb tile seen.\n");
				printf("Press enter to retry.\n");
				fflush(stdin);
				getchar();
				system("cls");
				levelDisplay(display);
				return 1;
			}
		}
		valid = 1;
	}
	
}

/*this function gets the specifications of all the levels in the levelSet one by one; this function is responsible for the
transpose of specification information of each levels to be played by the player
levelSet(MS **) address of structiure pointer "levelSet"
data(MSdata **) address of structiure pointer "data"
cField(char**) holds the address for the character vaulue 'W'(whitespace), 'B'(bomb), and 'N'(number) contain in a tile
nTileRow(int*) holds the address for number of rows in the field
nTileColumn(int*) holds the address for number of columns in the field
nBombSize(int*) holds the address for number of bombs in the field
nBomb(int*) holds the address for number of bombs in the field
nCurrentLevel(int*) holds the address for the current level in the game
returns 1 if the current level played is the last level; returns 0 if the level is not the last level(int)
*/
int levelSetSpecs(MS **levelSet, MSdata *data, char cField[][15], int *nTileRow, int *nTileColumn, int *nBombSize, int *nBomb, int *nCurrentLevel)
{
	int x;
	MS *current;
	initialize(&current);
	current = *levelSet;
	
	for(x=0;x<*nCurrentLevel && current->pNext!=NULL;x++)
	{
		current = current->pNext;
	}
	++(*nCurrentLevel);
	for(x=0;x<current->bombs;x++)
	{
		cField[current->bombPos[x][0]][current->bombPos[x][1]] = 'B';
	}
	*nTileRow = current->rows;
	*nTileColumn = current->cols;
	*nBombSize = current->bombs;
	*nBomb = current->bombs;
	
	if(*nCurrentLevel==data->nLevels)
		*nCurrentLevel = 0;
	if(current->pNext==NULL)
		return 1;
	return 0;
}

/*this function let the players delete an existing level in the current levelSet
levelSet(MS **) address of structiure pointer "levelSet"
data(MSdata **) address of structiure pointer "data"
fileName(char*) holds the address of the fileName for the txt file
nLevels(int) holds the value of the number of levels in the created levelSet
doesn't return anything(void)
*/
void deleteLevel(MS **levelSet, MSdata **data, char fileName[], int nLevels)
{
	int x, y, z;
	int respond = 0, respond1 = 1, count = 0, nBack = 0, nDelete, count1 = 0;
	MS *display;
	MS *current;
	MS *back;
	
	current = *levelSet;
	
	//resets the number of hints
	(*data)->hints = 0;
	MSdata *save = *data;
	saveFeatures(save, fileName, -1); //save highScore and hints
	
	system("cls");
	
	//displays the image of the levels in the levelSet
	while(current!=NULL)
	{
		printf("Level %d\n", count+1);
		display = current;
		levelDisplay(display);
		
		if(current->pNext!=NULL)
		{
			printf("[1]Next\n");
		}
		
		if(current->pNext==NULL)
		{
			printf("[2]Finish\n");
		}
		scanf("%d", &respond);
		
		if(respond==1)
		{
			current = current->pNext;
		}
		++count;
		if(current->pNext==NULL && respond==2)
		{
			printf("Press enter to continue.");
			fflush(stdin);
			getchar();
			system("cls");
			break;
		}
		respond = 0;
		system("cls");
	}
	
	MS *pDelete;
	MS *pRun;
	int levelDelete = 0;
	
	//loop until all level are deleted or the user chose to end the deletion of levels
	while(count!=0 && respond1==1)
	{
		printf("Level number to delete: ");
		scanf("%d", &nDelete);
		
		if (nDelete == 1)
		{
			pDelete = *levelSet;
			*levelSet = pDelete->pNext;
			free(pDelete);
			++levelDelete;
		}
		else
		{
			pRun = *levelSet;
			while (pRun->pNext!=NULL && count1 != nDelete-2)
			{
				pRun = pRun->pNext;
				++count1;
			}
			if (pRun->pNext != NULL)
			{
				pDelete = pRun->pNext;
				pRun->pNext = pDelete->pNext;
				free(pDelete);
			}
			++levelDelete;
		}
		--count;
		if(count>0)
		{
			printf("Delete more?(1-yes, 2-no): ");
			scanf("%d", &respond1);
		}
	}
	
	//save to the levelSet
	(*data)->nLevels -= levelDelete;
	
}

/*displays the level image and the specification of the level(this serves as a UI for the levels display); this function is used for the
"editBombLocation" function and "deleteLevel" function because this can be helpful for the player while editing a level or deciding what
level to delete.
display(MS *) address of structiure pointer "display"; the structure for the current level being displayed
doesn't return anything(void)
*/
void levelDisplay(MS *display)
{
	int x, y, z;
	char cDisplay[15][15];
	
	for(x=0;x<display->rows;x++)
	{
		for(y=0;y<display->cols;y++)
		{
			cDisplay[x][y] = 'W'; 
		}
	}
	for(x=0;x<display->bombs;x++)
	{
		cDisplay[display->bombPos[x][0]][display->bombPos[x][1]] = 'B';
	}
	
	printf("   ");
	for(x=0;x<display->cols;x++)
	{
		printf("%d ", x);
	}
	printf("\n");
	for(x=0;x<display->rows;x++)
	{
		if(x>9)
			printf("%d", x);
		else
			printf("%d ", x);
		for(y=0;y<display->cols;y++)
		{
			if(cDisplay[x][y]=='W')
			{
				printf("| ");
			}
			else
			{
				printf("|X");
			}
		}
		printf("|\n");
	}
}

/*this function frees all the memory allocated in the structure pointer of "levelSet"
levelSet(MS *) address of structiure pointer "levelSet"
doesn't return anything(void)
*/
void deAllocate1(MS *levelSet)
{
	MS *pRun;
	MS *pTerminator;
	
	pTerminator = levelSet;
	while (pTerminator != NULL)
	{
		pRun = pTerminator->pNext;
		free(pTerminator);
		pTerminator = pRun;
	}
}	

/*this function frees all the memory allocated in the structure pointer of "data"
data(MSdata *) address of structiure pointer "data"
doesn't return anything(void)
*/
void deAllocate2(MSdata *data)
{
	free(data);
}	

//Programmed by: Emerson Celestial
