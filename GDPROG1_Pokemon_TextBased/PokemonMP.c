#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>

//determine the winner of the game
int gameWinner(int nWinner,char *c1stName,char *c2ndName,char *cPokemonName1,char *cPokemonName2,float fP1hp,float fP2hp,float fP1Uhp,float fP2Uhp)
{

	system("cls");
	//presents this statement if the nWinner value is equal to 1
	if(nWinner==1)
	{
		printf("\n\n\n\t %0.5s's Pokemon  \t\t\t\t\t\t\t %0.5s's Pokemon \n", c1stName,c2ndName); // displays the match
    	printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
    	printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
    	printf("\t||   %s     ||\t\t\t\t\t\t\t||   %s     || \n",cPokemonName1, cPokemonName2 );
    	printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
    	printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
    	printf("\t    %0.01f/%0.01f        \t\t\t\t\t\t\t     0/%0.01f     \n\n", fP1Uhp,fP1hp,fP2hp);
    	printf("\n%s Wins!!! \n", c1stName);
	}
	//presents this statement if the nWinner value is equal to 2
	if(nWinner==2)
	{
		printf("\n\n\n\t %0.5s's Pokemon  \t\t\t\t\t\t\t %0.5s's Pokemon \n", c1stName,c2ndName); // displays the match
    	printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
    	printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
    	printf("\t||   %s     ||\t\t\t\t\t\t\t||   %s     || \n",cPokemonName1, cPokemonName2 );
    	printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
    	printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
    	printf("\t     0/%0.01f        \t\t\t\t\t\t\t     %0.01f/%0.01f     \n\n", fP1hp,fP2Uhp,fP2hp);
    	printf("\n%s Wins!!! \n", c2ndName);
	}

}

//displays the healthbar feature for player2
void healthBarP2(float fP2Uhp,float fP2hp)
{
	float fRatio;
	int nBar,x,y;
	fRatio = fP2Uhp/fP2hp;
	// determines the length of the healthbar
	if(0.1<fRatio && fRatio<=0.2)
		nBar = 1;
	if(0.2<fRatio && fRatio<=0.3)
		nBar = 2;
	if(0.3<fRatio && fRatio<=0.4)
		nBar = 3;
	if(0.4<fRatio && fRatio<=0.5)
		nBar = 4;
	if(0.5<fRatio && fRatio<=0.6)
		nBar = 5;
	if(0.6<fRatio && fRatio<=0.7)
		nBar = 6;
	if(0.7<fRatio && fRatio<=0.8)
		nBar = 8;
	if(0.8<fRatio && fRatio<=0.9)
		nBar = 9;
	if(0.9<fRatio && fRatio<=0.99)
		nBar = 10;
	if(fRatio==1)
		nBar = 11;
	//displays the healthbar
	printf("|");
	for(x=1;x<=nBar;x++)
	{
		printf("=");
	}
	for(y=1;y<=11-nBar;y++)
	{
		printf(" ");
	}
	printf("|");
}
//displays the healthbar feature for player1
void healthBarP1(float fP1Uhp,float fP1hp)
{
	float fRatio;
	int nBar,x,y;
	fRatio = fP1Uhp/fP1hp;
	// determines the length of the healthbar
	if(0.1<fRatio && fRatio<=0.2)
		nBar = 1;
	if(0.2<fRatio && fRatio<=0.3)
		nBar = 2;
	if(0.3<fRatio && fRatio<=0.4)
		nBar = 3;
	if(0.4<fRatio && fRatio<=0.5)
		nBar = 4;
	if(0.5<fRatio && fRatio<=0.6)
		nBar = 5;
	if(0.6<fRatio && fRatio<=0.7)
		nBar = 6;
	if(0.7<fRatio && fRatio<=0.8)
		nBar = 8;
	if(0.8<fRatio && fRatio<=0.9)
		nBar = 9;
	if(0.9<fRatio && fRatio<=0.99)
		nBar = 10;
	if(fRatio==1)
		nBar = 11;
	//displays the healthbar
	printf("|");
	for(x=1;x<=nBar;x++)
	{
		printf("=");
	}
	for(y=1;y<=11-nBar;y++)
	{
		printf(" ");
	}
	printf("|");
}

// pickMove1 function returns the move of each player per turn
char pickMove1(char *cPokemonName1,char *cPokemonName2,char *c1stName,char *c2ndName,
char *sAttack1,char *sAttack2,char *sAttack3,char *sAttack4,
float fAbp1, int nApp1,float fAbp2, int nApp2, int nApp3, int nApp4,
float fP1Uhp,float fP2Uhp,float fP1hp,float fP2hp)
{
	char cChoice1;
	// displays the live match
	//a loop for the picking of move process if the user insist to pick an invalid move
    while(!(cChoice1=='a' ||  cChoice1=='b' || cChoice1=='c'  ||  cChoice1=='d'))
	{
    	system("cls");
    	printf("\n\n\n\t %0.5s's Pokemon  \t\t\t\t\t\t\t %0.5s's Pokemon \n", c1stName,c2ndName); // displays the match
    	printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
    	printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
    	printf("\t||   %s     ||\t\t\t\t\t\t\t||   %s     || \n",cPokemonName1, cPokemonName2 );
    	printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
    	printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
    	printf("\t   %0.1f/%0.1f         \t\t\t\t\t\t\t   %0.1f/%0.1f\n", fP1Uhp,fP1hp,fP2Uhp, fP2hp);
    	printf("\t  ");healthBarP1(fP1Uhp,fP1hp);printf("\t\t\t\t\t\t\t\t  "); healthBarP2(fP2Uhp,fP2hp);
    	printf("\nPlayer 1:\n");
    	printf("%s\n", cPokemonName1);
    	printf("Choose your move:\n");
    	printf("%s--BP:%0.1f--PP:%d  [A]\n", sAttack1,fAbp1,nApp1);
    	printf("%s--BP:%0.1f--PP:%d  [B]\n", sAttack2,fAbp2,nApp2);
    	printf("%s--BP:00--PP:%d  [C]\n", sAttack3,nApp3);
    	printf("%s--BP:00--PP:%d  [D]\n", sAttack4,nApp4);
    	scanf("%c", &cChoice1);
    	cChoice1 = tolower(cChoice1);
    	fflush(stdin);
    	
    	if(!(cChoice1=='a' ||  cChoice1=='b' || cChoice1=='c'  ||  cChoice1=='d'))
		{
    		printf("Wrong Input\n");
    		printf("Press Enter key to continue\n");
    		getchar();
    		fflush(stdin);
		}
	}
	
    return cChoice1;
}

// pickMove2 function returns the move of each player per turn
char pickMove2(char *cPokemonName1,char *cPokemonName2,char *c1stName,char *c2ndName,char *s2Attack1,char *s2Attack2,char *s2Attack3,char *s2Attack4,
 float f2Abp1, int n2App1, float f2Abp2, int n2App2, int n2App3, int n2App4,float fP1Uhp,float fP2Uhp,float fP1hp,float fP2hp)
 {
	char cChoice2;
	// displays the match
	//a loop for the picking of move process if the user insist to pick an invalid move
    while(!(cChoice2=='a' ||  cChoice2=='b' || cChoice2=='c'  ||  cChoice2=='d'))
	{
    	system("cls");
     	printf("\n\n\n\t %0.5s's Pokemon  \t\t\t\t\t\t\t %0.5s's Pokemon \n", c1stName,c2ndName); // displays the match
   		printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
   		printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
   		printf("\t||   %s     ||\t\t\t\t\t\t\t||   %s     || \n",cPokemonName1, cPokemonName2 );
   		printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
  	    printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
  	  	printf("\t   %0.1f/%0.1f         \t\t\t\t\t\t\t   %0.1f/%0.1f\n", fP1Uhp,fP1hp,fP2Uhp, fP2hp);
   	 	printf("\t  ");healthBarP1(fP1Uhp,fP1hp);printf("\t\t\t\t\t\t\t\t  "); healthBarP2(fP2Uhp,fP2hp);
  	    printf("\nPlayer 2:\n");
  	    printf("%s\n", cPokemonName2);
  	    printf("Choose your move:\n");
  	    printf("%s--BP:%0.1f--PP:%d  [A]\n", s2Attack1,f2Abp1,n2App1);
    	printf("%s--BP:%0.1f--PP:%d  [B]\n", s2Attack2,f2Abp2,n2App2);
   	 	printf("%s--BP:00--PP:%d  [C]\n", s2Attack3,n2App3);
   		 printf("%s--BP:00--PP:%d  [D]\n", s2Attack4,n2App4);
  		scanf("%c", &cChoice2);
   	 	cChoice2 = tolower(cChoice2);
    	fflush(stdin);
    	
    	if(!(cChoice2=='a' ||  cChoice2=='b' || cChoice2=='c'  ||  cChoice2=='d'))
		{
    		printf("Wrong Input\n");
    		printf("Press Enter key to continue\n");
    		getchar();
    		fflush(stdin);
		}
	}
	
    return cChoice2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mainGame(char cPokemon1,char cPokemon2, char *cPokemonName1,char *cPokemonName2,char *c1stName,char *c2ndName)
{
	char *sAttack1,*sAttack2,*sAttack3,*sAttack4,*s2Attack1,*s2Attack2,*s2Attack3,*s2Attack4; //pokemon's moves
	char *sPhrase1,*sPhrase2,*sPhrase3,*sPhrase4,*s2Phrase1,*s2Phrase2,*s2Phrase3,*s2Phrase4;
	char sType1,sType2, s2Type1,s2Type2; // pokemon types
	char cAT1, cAT2, c2AT1, c2AT2; // pokemon's attack types
	float fAbp1,fAbp2,f2Abp1,f2Abp2;  // pokemon's bp
	int nApp1, nApp2, nApp3, nApp4, n2App1, n2App2, n2App3, n2App4; // pokemon's pp
	float fP1hp, fP2hp; // pokemon's hp
	float fP1Uhp, fP2Uhp; // pokemon's updated hp
	int nCharge1 = 0,nCharge2 = 0,nProtect1 = 0,nProtect2 = 0;
    char cChoice1, cChoice2;
    float fAbpr1, fAbpr2, f2Abpr1, f2Abpr2; // brings back the orignal power after using charge up
    int nWinner; // determines the winner, if 1 player1 wins and if 2 then pl2 wins
    /*lets the user to pick again if ever the chosen move doesn't have pp or 
	if the player repeats the move for protect and charge up twice after picking it previously*/
    static int nRetry1 = 1; 
    static int nRetry2 = 1;
    // in order for the protect not to be use twice in a row
    static int nProtectTurn1 = 0;
    static int nProtectTurn2 = 0;
    
    // gets the choice of player 1's pokemon then identify its stats
	switch(cPokemon1)
	{ 
		case 'e':
			sType1 = 'F';
			sType2 = 'N';
			fP1hp = 150.0;
			fP1Uhp = 150.0;
			sAttack1 = "Fire Blast";
			cAT1 = 'f';
			fAbp1 = 30.0;
			nApp1 = 5;
			sAttack2 = "Earthquake";
			cAT2 = 'g';
			fAbp2 = 30.0;
			nApp2 = 5;
			sAttack3 = "Protect";
			nApp3 = 5;
			sAttack4 = "Charge Up";
			nApp4 = 5;
			sPhrase1 = "Entei, burn him with your fire blast!";
			sPhrase2 = "Entei, use earthquake now!";
			sPhrase3 = "Entei, use your protect!";
			sPhrase4 = "Entei, use charged up!";
		break;
		case 'm':
			sType1 = 'W';
			sType2 = 'N';
			fP1hp = 200.0;
			fP1Uhp = 200.0;
			sAttack1 = "Scald";
			cAT1 = 'w';
			fAbp1 = 20.0;
			nApp1 = 7;
			sAttack2 = "Ice Beam";
			cAT2 = 'i';
			fAbp2 = 20.0;
			nApp2 = 7;
			sAttack3 = "Protect";
			nApp3 = 5;
			sAttack4 = "Charge Up";
			nApp4 = 5;
			sPhrase1 = "Milotic, scald attack now!";
			sPhrase2 = "Alright now Milotic, hit him with ice beam!";
			sPhrase3 = "Milotic, use your protect!";
			sPhrase4 = "Milotic, use charged up!";
		break;
		case 't':
			sType1 = 'L';
			sType2 = 'G';
			fP1hp = 220.0;
			fP1Uhp = 220.0;
			sAttack1 = "Dig";
			cAT1 = 'g';
			fAbp1 = 20.0;
			nApp1 = 7;
			sAttack2 = "Leaf Storm";
			cAT2 = 'l';
			fAbp2 = 40.0;
			nApp2 = 5;
			sAttack3 = "Protect";
			nApp3 = 5;
			sAttack4 = "Charge Up";
			nApp4 = 5;
			sPhrase1 = "Torterra go, use dig!";
			sPhrase2 = "Torterra, leaf storm now!";
			sPhrase3 = "Torterra, use your protect!";
			sPhrase4 = "Torterra, use charged up!";
		break;
		case 'p':
			sType1 = 'E';
			sType2 = 'N';
			fP1hp = 120.0;
			fP1Uhp = 120.0;
			sAttack1 = "Thunderbolt";
			cAT1 = 'e';
			fAbp1 = 10.0;
			nApp1 = 10;
			sAttack2 = "Dig";
			cAT2 = 'g';
			fAbp2 = 20.0;
			nApp2 = 7;
			sAttack3 = "Protect";
			nApp3 = 5;
			sAttack4 = "Charge Up";
			nApp4 = 5;
			sPhrase1 = "Pikachu, thunderbolt now!";
			sPhrase2 = "Pikachu go, use dig!";
			sPhrase3 = "Pikachu, use your protect!";
			sPhrase4 = "Pikachu, use charged up!";
		break;
		case 'g':
			sType1 = 'G';
			sType2 = 'N';
			fP1hp = 150.0;
			fP1Uhp = 150.0;
			sAttack1 = "Fissure";
			cAT1 = 'g';
			fAbp1 = 40.0;
			nApp1 = 5;
			sAttack2 = "Fire Blast";
			cAT2 = 'f';
			fAbp2 = 30.0;
			nApp2 = 5;
			sAttack3 = "Protect";
			nApp3 = 5;
			sAttack4 = "Charge Up";
			nApp4 = 5;
			sPhrase1 = "Groudon, fissure attack!";
			sPhrase2 = "Let's go, Groudon fire blast!";
			sPhrase3 = "Groudon, use your protect!";
			sPhrase4 = "Groudon, use charged up!";
		break;
		case 'l':
			sType1 = 'I';
			sType2 = 'W';
			fP1hp = 190.0;
			fP1Uhp = 190.0;
			sAttack1 = "Ice Beam";
			cAT1 = 'i';
			fAbp1 = 20.0;
			nApp1 = 7;
			sAttack2 = "Scald";
			cAT2 = 'w';
			fAbp2 = 20.0;
			nApp2 = 7;
			sAttack3 = "Protect";
			nApp3 = 5;
			sAttack4 = "Charge Up";
			nApp4 = 5;
			sPhrase1 = "Alright now Lapras, hit him with ice beam!";
			sPhrase2 = "Lapras, scald attack now!";
			sPhrase3 = "Lapras, use your protect!";
			sPhrase4 = "Lapras, use charged up!";
		break;
		case 's':
			sType1 = 'G';
			sType2 = 'E';
			fP1hp = 130.0;
			fP1Uhp = 130.0;
			sAttack1 = "Water Gun";
			cAT1 = 'w';
			fAbp1 = 10.0;
			nApp1 = 10;
			sAttack2 = "Earthquake";
			cAT2 = 'g';
			fAbp2 = 30.0;
			nApp2 = 5;
			sAttack3 = "Protect";
			nApp3 = 5;
			sAttack4 = "Charge Up";
			nApp4 = 5;
			sPhrase1 = "Stunfisk, water gun attack now!";
			sPhrase2 = "Stunfisk, use earthquake now!";
			sPhrase3 = "Stunfisk, use your protect!";
			sPhrase4 = "Stunfisk, use charged up!";
		break;
	}
	
	// gets the choice of player 2's pokemon then identify its stats
	switch(cPokemon2)
	{ 
		case 'e':
			s2Type1 = 'F';
			s2Type2 = 'N';
			fP2hp = 150.0;
			fP2Uhp = 150.0;
			s2Attack1 = "Fire Blast";
			c2AT1 = 'f';
			f2Abp1 = 30.0;
			n2App1 = 5;
			s2Attack2 = "Earthquake";
			c2AT2 = 'g';
			f2Abp2 = 30.0;
			n2App2 = 5;
			s2Attack3 = "Protect";
			n2App3 = 5;
			s2Attack4 = "Charge Up";
			n2App4 = 5;
			s2Phrase1 = "Entei, burn him with your fire blast!";
			s2Phrase2 = "Entei, use earthquake now!";
			s2Phrase3 = "Entei, use your protect!";
			s2Phrase4 = "Entei, use charged up!";
		break;
		case 'm':
			s2Type1 = 'W';
			s2Type2 = 'N';
			fP2hp = 200.0;
			fP2Uhp = 200.0;
			s2Attack1 = "Scald";
			c2AT1 = 'w';
			f2Abp1 = 20.0;
			n2App1 = 7;
			s2Attack2 = "Ice Beam";
			c2AT2 = 'i';
			f2Abp2 = 20.0;
			n2App2 = 7;
			s2Attack3 = "Protect";
			n2App3 = 5;
			s2Attack4 = "Charge Up";
			n2App4 = 5;
			s2Phrase1 = "Milotic, scald attack now!";
			s2Phrase2 = "Alright now Milotic, hit him with ice beam!";
			s2Phrase3 = "Milotic, use your protect!";
			s2Phrase4 = "Milotic, use charged up!";
		break;
		case 't':
			s2Type1 = 'L';
			s2Type2 = 'G';
			fP2hp = 220.0;
			fP2Uhp = 220.0;
			s2Attack1 = "Dig";
			c2AT1 = 'g';
			f2Abp1 = 20.0;
			n2App1 = 7;
			s2Attack2 = "Leaf Storm";
			c2AT2 = 'l';
			f2Abp2 = 40.0;
			n2App2 = 5;
			s2Attack3 = "Protect";
			n2App3 = 5;
			s2Attack4 = "Charge Up";
			n2App4 = 5;
			s2Phrase1 = "Torterra go, use dig!";
			s2Phrase2 = "Torterra, leaf storm now!";
			s2Phrase3 = "Torterra, use your protect!";
			s2Phrase4 = "Torterra, use charged up!";
		break;
		case 'p':
			s2Type1 = 'E';
			s2Type2 = 'N';
			fP2hp = 120.0;
			fP2Uhp = 120.0;
			s2Attack1 = "Thunderbolt";
			c2AT1 = 'e';
			f2Abp1 = 10.0;
			n2App1 = 10;
			s2Attack2 = "Dig";
			c2AT2 = 'g';
			f2Abp2 = 20.0;
			n2App2 = 7;
			s2Attack3 = "Protect";
			n2App3 = 5;
			s2Attack4 = "Charge Up";
			n2App4 = 5;
			s2Phrase1 = "Pikachu, thunderbolt now!";
			s2Phrase2 = "Pikachu go, use dig!";
			s2Phrase3 = "Pikachu, use your protect!";
			s2Phrase4 = "Pikachu, use charged up!";
		break;
		case 'g':
			s2Type1 = 'G';
			s2Type2 = 'N';
			fP2hp = 150.0;
			fP2Uhp = 150.0;
			s2Attack1 = "Fissure";
			c2AT1 = 'g';
			f2Abp1 = 40.0;
			n2App1 = 5;
			s2Attack2 = "Fire Blast";
			c2AT2 = 'f';
			f2Abp2 = 30.0;
			n2App2 = 5;
			s2Attack3 = "Protect";
			n2App3 = 5;
			s2Attack4 = "Charge Up";
			n2App4 = 5;
			s2Phrase1 = "Groudon, fissure attack!";
			s2Phrase2 = "Let's go, Groudon fire blast!";
			s2Phrase3 = "Groudon, use your protect!";
			s2Phrase4 = "Groudon, use charged up!";
		break;
		case 'l':
			s2Type1 = 'I';
			s2Type2 = 'W';
			fP2hp = 190.0;
			fP2Uhp = 190.0;
			s2Attack1 = "Ice Beam";
			c2AT1 = 'i';
			f2Abp1 = 20.0;
			n2App1 = 7;
			s2Attack2 = "Scald";
			c2AT2 = 'w';
			f2Abp2 = 20.0;
			n2App2 = 7;
			s2Attack3 = "Protect";
			n2App3 = 5;
			s2Attack4 = "Charge Up";
			n2App4 = 5;
			s2Phrase1 = "Alright now Lapras, hit him with ice beam!";
			s2Phrase2 = "Lapras, scald attack now!";
			s2Phrase3 = "Lapras, use your protect!";
			s2Phrase4 = "Lapras, use charged up!";
		break;
		case 's':
			s2Type1 = 'G';
			s2Type2 = 'E';
			fP2hp = 130.0;
			fP2Uhp = 130.0;
			s2Attack1 = "Water Gun";
			c2AT1 = 'w';
			f2Abp1 = 10.0;
			n2App1 = 10;
			s2Attack2 = "Earthquake";
			c2AT2 = 'g';
			f2Abp2 = 30.0;
			n2App2 = 5;
			s2Attack3 = "Protect";
			n2App3 = 5;
			s2Attack4 = "Charge Up";
			n2App4 = 5;
			s2Phrase1 = "Stunfisk, water gun attack now!";
			s2Phrase2 = "Stunfisk, use earthquake now!";
			s2Phrase3 = "Stunfisk, use your protect!";
			s2Phrase4 = "Stunfisk, use charged up!";
		break;
	}
	
	/* fAbpr1 and fAbpr2 will reset the basepower to the orignal after attacking with the charge up boost,
	in order to bring back the original basepower of the pokemon after the usage of charge up
	*/
	fAbpr1 = fAbp1; 
	fAbpr2 = fAbp2; 
	f2Abpr1 = f2Abp1;
	f2Abpr2 = f2Abp2;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// a loop for the battle phasing for both players, will only stop if one had already make its opponent hp to 0
	while(fP1Uhp>0 && fP2Uhp>0)
	{
		nRetry1=1;	
		nRetry2=1;	
		
		if(nCharge1==0)
		{
			fAbp1 = fAbpr1;
			fAbp2 = fAbpr2;
		}
	
		if(nCharge2==0)
		{
			f2Abp1 = f2Abpr1;
			f2Abp2 = f2Abpr2;
		}
	//phase for player 1
	while(nRetry1==1)
	{
		system("cls");
		
		// if there's no more pp for move1&2; auto attack will happen
		if((nApp1==0)&&(nApp2==0))
		{
			fP1Uhp = fP1Uhp-5;
			fP2Uhp = fP2Uhp-10;
			// displays the match
			printf("\n\n\n\t %0.5s's Pokemon  \t\t\t\t\t\t\t %0.5s's Pokemon \n", c1stName,c2ndName);
    		printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
    		printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
    		printf("\t||   %s     ||\t\t\t\t\t\t\t||   %s       || \n",cPokemonName1, cPokemonName2 );
    		printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
    		printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
    		printf("\t   %0.1f/%0.1f         \t\t\t\t\t\t\t   %0.1f/%0.1f\n\n", fP1Uhp,fP1hp,fP2Uhp, fP2hp);
			printf("No more attack moves. %s uses self-attack. \n(PLayer1 deals 10 damage but takes 5 damage in return)\n", cPokemonName1);
			printf("Press enter to continue");
			getchar();
    		fflush(stdin);
			break;
		}
		nRetry1 = 0;
		
		if((nApp1!=0)||(nApp2!=0))
		{	
			cChoice1 = pickMove1(cPokemonName1,cPokemonName2,c1stName,c2ndName,sAttack1,sAttack2,sAttack3,sAttack4,fAbp1,nApp1,fAbp2,nApp2,nApp3,nApp4,fP1Uhp,fP2Uhp,fP1hp,fP2hp);
		
		switch (cChoice1)
		{
		//first line in case a, move 1
        case 'a':
        	//displays the trainers phrase
        	printf("%s\n", sPhrase1);
        	printf("Press enter key to continue.");
        	getchar();
        	fflush(stdin);
        	// if the move1 has no more PP
            if(nApp1==0)
			{
                printf("No more pp.\n");
                printf("Press enter to continue\n");
                getchar();
    		 	fflush(stdin);
                nRetry1=1;
            }
            
        	if (nApp1!=0)
			{
            	if(cAT1=='w' && (sType1=='G'&& sType2 == 'E'))
				{
                    if(nProtect2==1)
					{
                    	fP2Uhp;
                    	nApp1 = nApp1 -1;
                    }
                    
                    else if(nProtect2!=1)
					{
                        if((s2Type1=='F'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='E'))
						{
                        	fP2Uhp = fP2Uhp-fAbp1*2.0;
                        	nApp1 = nApp1 -1;
                        }
                        
                        if((s2Type1=='L'&&s2Type2=='G')||(s2Type1=='E'&&s2Type2=='N'))
						{ 
                        	fP2Uhp = fP2Uhp-fAbp1;
                        	nApp1 = nApp1 -1;
                        }
                        
                        if((s2Type1=='I'&&s2Type2=='W')||(s2Type1=='W'&&s2Type2=='N'))
						{ 
                        	fP2Uhp = fP2Uhp-fAbp1*0.5;
                        	nApp1 = nApp1 -1;
                        }
                        nCharge1=0;
                    }
 
						nProtect2=0;  
                }
                
                // STAB section
                if(cAT1=='f')
				{
                    if(nProtect2==1)
					{
                   	 	fP2Uhp;
                        nApp1 = nApp1 -1;
                    }
                    
                    else if(nProtect2!=1)
					{
                        if((s2Type1=='L'&&s2Type2=='G')||(s2Type1=='E'&&s2Type2=='N')||(s2Type1=='I'&&s2Type2=='W'))
						{
                        	fAbp1 = fAbp1 * 1.5; 
                        	fP2Uhp = fP2Uhp-fAbp1;
                        	nApp1 = nApp1 -1;
						}
						
                        if((s2Type1=='F'&&s2Type2=='N')||(s2Type1=='W'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='E'))
						{
                        	fAbp1 = fAbp1 * 1.5;
                        	fP2Uhp = fP2Uhp-fAbp1*0.5;
                        	nApp1 = nApp1 -1;
                        }
                        nCharge1=0;
                    }
                    
						nProtect2=0;  
                }
                
                if(cAT1=='w' && (!(sType1=='G'&& sType2 == 'E')))
				{
                    if(nProtect2==1)
					{
                        fP2Uhp;
                        nApp1 = nApp1 -1;
                    }
                    
                    else if(nProtect2!=1)
					{
                        if((s2Type1=='F'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='E'))
						{
                        	fAbp1 = fAbp1 * 1.5; 
                        	fP2Uhp = fP2Uhp-fAbp1*2.0;
                        	nApp1 = nApp1 -1;
                    	}
                    	
                        if((s2Type1=='L'&&s2Type2=='G')||(s2Type1=='E'&&s2Type2=='N'))
						{
							fAbp1 = fAbp1 * 1.5;  
                        	fP2Uhp = fP2Uhp-fAbp1;
                        	nApp1 = nApp1 -1;
                        }
                        
                        if((s2Type1=='I'&&s2Type2=='W')||(s2Type1=='W'&&s2Type2=='N'))
						{ 
                        	fAbp1 = fAbp1 * 1.5; 
                        	fP2Uhp = fP2Uhp-fAbp1*0.5;
                        	nApp1 = nApp1 -1;
                        }
                        nCharge1=0;
                    }
                    
						nProtect2=0;  
                    }
                    
                    if(cAT1=='g')
					{
                        if(nProtect2==1)
						{
                        	fP2Uhp;
                        	nApp1 = nApp1 -1;
                        }
                        
                        else if(nProtect2!=1)
						{
                        	if((s2Type1=='F'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='E')||(s2Type1=='E'&&s2Type2=='N'))
							{
                        		fAbp1 = fAbp1 * 1.5; 
                        		fP2Uhp = fP2Uhp-fAbp1*2.0;
                        		nApp1 = nApp1 -1;
							}
							
							if(s2Type1=='G'&&s2Type2=='N')
							{
                        		fAbp1 = fAbp1 * 1.5; 
                        		fP2Uhp = fP2Uhp-fAbp1*1.0;
                        		nApp1 = nApp1 -1;
							}
							
                        	if((s2Type1=='W'&&s2Type2=='N')||(s2Type1=='L'&&s2Type2=='G'))
							{
                        		fAbp1 = fAbp1 * 1.5; 
                        		fP2Uhp = fP2Uhp-fAbp1*0.5;
                        		nApp1 = nApp1 -1;
							}
							
                        	if((s2Type1=='I'&&s2Type2=='W'))
							{
                        		fAbp1 = fAbp1 * 1.5;
                        		fP2Uhp = fP2Uhp-fAbp1*0.25;
                        		nApp1 = nApp1 -1;
                        	}
                        	nCharge1=0;
                        }

						nProtect2=0;  
                    }
                    
                    if(cAT1=='e')
					{
                        if(nProtect2==1)
						{
                        	fP2Uhp;
                        	nApp1 = nApp1 -1;
                        }
                        else if(nProtect2!=1)
						{
                        	if((s2Type1=='W'&&s2Type2=='N')||(s2Type1=='I'&&s2Type2=='W'))
							{
                        		fAbp1 = fAbp1 * 1.5; 
                       	 		fP2Uhp = fP2Uhp-fAbp1*2.0;
                        		nApp1 = nApp1 -1;
							}
							
                        	if((s2Type1=='F'&&s2Type2=='N')||(s2Type1=='E'&&s2Type2=='N'))
							{
                        		fAbp1 = fAbp1 * 1.5; 
                        		fP2Uhp = fP2Uhp-fAbp1;
                        		nApp1 = nApp1 -1;
							}
							
                       	 	if((s2Type1=='G'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='E')||(s2Type1=='L'&&s2Type2=='G'))	
							{
                        		fAbp1 = fAbp1 * 1.5;
                        		fP2Uhp = fP2Uhp-fAbp1*0.0;
                        		nApp1 = nApp1 -1;
                        	}
                        	nCharge1=0;
                        }
                       
						nProtect2=0;  
                    }
                    
                    if(cAT1=='i')
					{
                        if(nProtect2==1)
						{
                        	fP2Uhp;
                        	nApp1 = nApp1 -1;
                        }
                        
                        else if(nProtect2!=1)
						{
                        	if((s2Type1=='L'&&s2Type2=='G'))
							{
                        		fAbp1 = fAbp1 * 1.5; 
                        		fP2Uhp = fP2Uhp-fAbp1*4.0;
                        		nApp1 = nApp1 -1;
							}
							
                        	if((s2Type1=='W'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='E')||(s2Type1=='I'&&s2Type2=='W'))
							{
                        		fAbp1 = fAbp1 * 1.5; 
                        		fP2Uhp = fP2Uhp-fAbp1*2.0;
                        		nApp1 = nApp1 -1;
							}
							
                        	if((s2Type1=='E'&&s2Type2=='N'))
							{
                        		fAbp1 = fAbp1 * 1.5; 
                        		fP2Uhp = fP2Uhp-fAbp1;
                        		nApp1 = nApp1 -1;
							}
							
                        	if((s2Type1=='F'&&s2Type2=='N'))
							{
                        		fAbp1 = fAbp1 * 1.5;
                        		fP2Uhp = fP2Uhp-fAbp1*0.5;
                        		nApp1 = nApp1 -1;
                        	}
                        	nCharge1=0;
                        }
                        
						nProtect2=0;   
                    }
            }
            break;
            //last line in case a
            
        //first line in case b, move 2
        case 'b':
        	//displays the trainers phrase
        	printf("%s\n", sPhrase2);
        	printf("Press enter key to continue.");
        	getchar();
        	fflush(stdin);
        	// if the move2 has no more PP
            if(nApp2==0)
			{
				printf("No more pp.\n");
                printf("Press enter to continue\n");
                getchar();
    		    fflush(stdin);
                nRetry1=1;
            }
        	
            if (nApp2!=0)
			{
                if(cAT2=='g' && (!(sType1=='G'&&sType2=='E')))
				{
                    if(nProtect2==1)
					{
                    	fP2Uhp = fP2Uhp;
                    	nApp2 = nApp2 -1;
                	}
                	
                    else if(nProtect2!=1)
					{
                        if((s2Type1=='F'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='E')||(s2Type1=='E'&&s2Type2=='N'))
						{
                        	fP2Uhp = fP2Uhp-fAbp2*2.0;
                        	nApp2 = nApp2 -1;
                        }
                        
                        if(s2Type1=='G'&&s2Type2=='N')
						{ 
                        fP2Uhp = fP2Uhp-fAbp2*1.0;
                        nApp2 = nApp2 -1;
                        }
                        
                        if((s2Type1=='W'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='N')||(s2Type1=='L'&&s2Type2=='G'))
						{ 
                        fP2Uhp = fP2Uhp-fAbp2*0.5;
                        nApp2 = nApp2 -1;
                        }
                        
                        if((s2Type1=='I'&&s2Type2=='W'))
						{ 
                        fP2Uhp = fP2Uhp-fAbp2*0.25;
                        nApp2 = nApp2 -1;
                        }
                        nCharge1=0;
                    }
                    
						nProtect2=0;  
                    }
                    
                    if(cAT2=='i')
					{
                        if(nProtect2==1)
						{
                        	fP2Uhp = fP2Uhp;
                        	nApp2 = nApp2 -1;
                        }
                        
                        else if(nProtect2!=1)
						{
                        	if((s2Type1=='L'&&s2Type2=='G'))
							{
                        		fP2Uhp = fP2Uhp-fAbp2*4.0;
                        		nApp2 = nApp2 -1;
                        	}
                        	
                        	if((s2Type1=='W'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='E')||(s2Type1=='I'&&s2Type2=='W'))
							{ 
                        		fP2Uhp = fP2Uhp-fAbp2*2.0;
                       			 nApp2 = nApp2 -1;
                        	}
                        	
                        	if((s2Type1=='E'&&s2Type2=='N'))
							{ 
                        		fP2Uhp = fP2Uhp-fAbp2;
                        		nApp2 = nApp2 -1;
                            }
                            
                        	if((s2Type1=='F'&&s2Type2=='N'))
							{ 
                        		fP2Uhp = fP2Uhp-fAbp2*0.5;
                        		nApp2 = nApp2 -1;
                            }
                            nCharge1=0;
                        }
                       
						nProtect2=0;  
                    }
                    
                    if(cAT2=='f')
					{
                        if(nProtect2==1)
						{
                        	fP2Uhp = fP2Uhp;
                        	nApp2 = nApp2 -1;
                        }
                        
                        else if(nProtect2!=1)
						{
                        	if((s2Type1=='L'&&s2Type2=='G')||(s2Type1=='E'&&s2Type2=='N')||(s2Type1=='I'&&s2Type2=='W'))
							{
                        		fP2Uhp = fP2Uhp-fAbp2;
                        		nApp2 = nApp2 -1;
                        	}
                        	
                       	 	if((s2Type1=='F'&&s2Type2=='N')||(s2Type1=='W'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='E'))
							{ 
                        		fP2Uhp = fP2Uhp-fAbp2*0.5;
                        		nApp2 = nApp2 -1;
                        	}
                        	nCharge1=0;
                        }
                        
						nProtect2=0;   
                    }
                    
            		// STAB section
            		if(cAT2=='g' && (sType1=='G'&&sType2=='E'))
					{
                		if(nProtect2==1)
						{
                    		fP2Uhp = fP2Uhp;
                    		nApp2 = nApp2 -1;
                		}
                
                		else if(nProtect2!=1)
						{
                    		if((s2Type1=='F'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='E')||(s2Type1=='E'&&s2Type2=='N'))
							{
                       			fAbp2 = fAbp2 * 1.5;
                        		fP2Uhp = fP2Uhp-fAbp2*2.0;
                        		nApp2 = nApp2 -1;
                    		}
                    
                    		if((s2Type1=='W'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='N')||(s2Type1=='L'&&s2Type2=='G'))
							{
								fAbp2 = fAbp2 * 1.5; 
                        		fP2Uhp = fP2Uhp-fAbp2*0.5;
                        		nApp2 = nApp2 -1;
                    		}
                    
                    		if((s2Type1=='I'&&s2Type2=='W'))
							{
								fAbp2 = fAbp2 * 1.5; 
            	            	fP2Uhp = fP2Uhp-fAbp2*0.25;
                	        	nApp2 = nApp2 -1;
                    		}
                    		nCharge1=0;
                		}
                
						nProtect2=0;	  
                	}
                
                	if(cAT2=='l')
					{
                    	if(nProtect2==1)
						{
                        fP2Uhp = fP2Uhp;
                        nApp2 = nApp2 -1;
                    	}
                    
                    	else if(nProtect2!=1)
						{
                        	if((s2Type1=='W'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='N'))
							{
                        		fAbp2 = fAbp2 * 1.5;
                        		fP2Uhp = fP2Uhp-fAbp2*2.0;
                        		nApp2 = nApp2 -1;
                        	}
                        	
                        	if((s2Type1=='L'&&s2Type2=='G'))
							{
								fAbp2 = fAbp2 * 1.5; 
                     	   		fP2Uhp = fP2Uhp-fAbp2;
                        		nApp2 = nApp2 -1;
                        	}
                        	
                        	if((s2Type1=='F'&&s2Type2=='N'))
							{
								fAbp2 = fAbp2 * 1.5; 
                        		fP2Uhp = fP2Uhp-fAbp2*0.5;
                        		nApp2 = nApp2 -1;
                        	}
                        	
                        	if((s2Type1=='I'&&s2Type2=='W')||(s2Type1=='G'&&s2Type2=='E')||(s2Type1=='E'&&s2Type2=='N'))
							{
								fAbp2 = fAbp2 * 1.5; 
                        		fP2Uhp = fP2Uhp-fAbp2*0.0;
                        		nApp2 = nApp2 -1;
                            }
                            nCharge1=0;
                        }
                        
						nProtect2=0;  
                    }
                    
                    if(cAT2=='w')
					{
                        if(nProtect2==1)
						{
                        	fP2Uhp = fP2Uhp;
                        	nApp2 = nApp2 -1;
                        }
                        
                        else if(nProtect2!=1)
						{
                        	if((s2Type1=='F'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='N')||(s2Type1=='G'&&s2Type2=='E'))
							{
                        		fAbp2 = fAbp2 * 1.5;
                        		fP2Uhp = fP2Uhp-fAbp2*2.0;
                        		nApp2 = nApp2 -1;
                        	}
                        	
                        	if((s2Type1=='L'&&s2Type2=='G')||(s2Type1=='E'&&s2Type2=='N'))
							{
								fAbp2 = fAbp2 * 1.5; 
                        		fP2Uhp = fP2Uhp-fAbp2;
                        		nApp2 = nApp2 -1;
                        	}
                        	
                        	if((s2Type1=='W'&&s2Type2=='N')||(s2Type1=='I'&&s2Type2=='W'))
							{
								fAbp2 = fAbp2 * 1.5; 
                        		fP2Uhp = fP2Uhp-fAbp2*0.5;
                        		nApp2 = nApp2 -1;
                        	}     
							nCharge1=0;         	
                        }
                        
						nProtect2=0; 
                    }
            }
            break;
            //last line in case b
            
            //first line in case c
            case 'c':
            	//displays the trainers phrase
            	printf("%s\n", sPhrase3);
        		printf("Press enter key to continue.");
        		getchar();
        		fflush(stdin);
            	// no more pp
            	if(nApp3==0)
				{
                    printf("No more pp.\n");
                   	printf("Press enter to continue\n");
                   	getchar();
    		        fflush(stdin);
                   	nRetry1=1;
                } 
            	// tells the user that the protect effect is still in used
            	if(nProtect1==1)
					{
						printf("Protect is still in effect. You can't use it again.\n");
						printf("Press enter to continue\n");
                    	getchar();
    		            fflush(stdin);
						nRetry1=1;
                	}
                // tells the user that protect can't be used twice in a row	
            	if(nProtectTurn1>0)
				{
					printf("You can't use protect twice in a row\n");
					printf("Press enter to continue\n");
                    getchar();
    		        fflush(stdin);
					nRetry1=1;
				}  
				
            	if(nProtectTurn1<=0)
				{
                	// uses protect
                	if(!(nProtect1==1))
					{
                		if(nApp3!=0)
						{
							nProtect1 = 1;
                    		nApp3 = nApp3-1;
                    		nProtectTurn1=3;
                		}
            		}
            	}
                break;
            //last line in case c
            
            //first line in case d
            case 'd':
            	//displays the trainers phrase
        		printf("%s\n", sPhrase4);
        		printf("Press enter key to continue.");
        		getchar();
        		fflush(stdin);
            	// no more pp
            	if(nApp4==0)
				{
                    printf("No more pp.\n");
                    printf("Press enter to continue\n");
                    getchar();
    		        fflush(stdin);
                    nRetry1=1;
                }
                // tells the user that the charge up effect is still in used
            	if(nCharge1==1)
				{
					printf("Charge up is still in effect. You can't use it again.\n");
					printf("Press enter to continue\n");
                    getchar();
    		        fflush(stdin);
					nRetry1=1;
            	}
            	
                if(nCharge1==0)
				{	
					// uses charge up
                	if(nApp4!=0)
					{
						nRetry1==0;
                    	nApp4 = nApp4-1;
                    	fAbp1 = fAbp1*2;
                    	fAbp2 = fAbp2*2;
                    	nCharge1=1;
                	}
            	}
            	
            break;
            //last line in case d
    	}
    }
    }
	//checks if the current player already beats the opponent
	if(fP2Uhp<=0)
		{
			nRetry1=0;
			nWinner = 1;
			gameWinner(nWinner,c1stName,c2ndName,cPokemonName1,cPokemonName2,fP1hp,fP2hp,fP1Uhp,fP2Uhp);
			break;
		}
		
	nProtectTurn1--;
	
	//phase for player 2	
	while(nRetry2==1)
	{
		system("cls");
		
		if((n2App1==0)&&(n2App2==0))
		{
			fP1Uhp = fP1Uhp-10;
			fP2Uhp = fP2Uhp-5;
			// displays the match
			printf("\n\n\n\t %0.5s's Pokemon  \t\t\t\t\t\t\t %0.5s's Pokemon \n", c1stName,c2ndName);
    		printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
    		printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
    		printf("\t||   %s     ||\t\t\t\t\t\t\t||   %s   || \n",cPokemonName1, cPokemonName2 );
    		printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
    		printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
    		printf("\t   %0.1f/%0.1f         \t\t\t\t\t\t\t   %0.1f/%0.1f\n\n", fP1Uhp,fP1hp,fP2Uhp, fP2hp);
			printf("No more attack moves. %s uses self-attack. \n(PLayer2 deals 10 damage but takes 5 damage in return)\n", cPokemonName2);
			printf("Press enter to continue");
			getchar();
    		fflush(stdin);
			break;
		}
		
		nRetry2 = 0;
		
		if((n2App1!=0)||(n2App2!=0))
		{	
    		cChoice2 = pickMove2(cPokemonName1,cPokemonName2,c1stName,c2ndName,s2Attack1,s2Attack2,s2Attack3,s2Attack4,f2Abp1,n2App1,f2Abp2,n2App2,n2App3,n2App4,fP1Uhp,fP2Uhp,fP1hp,fP2hp);
    
		switch (cChoice2)
		{
			//first line of case a
            case 'a':
            	//displays the trainers phrase
        		printf("%s\n", s2Phrase1);
        		printf("Press enter key to continue.");
        		getchar();
        		fflush(stdin);
            	// no more pp for move1
            	if(n2App1==0)
				{
                 	printf("No more pp.\n");
                    printf("Press enter to continue\n");
                    getchar();
    		        fflush(stdin);
                    nRetry2=1;
                }    
            	
                if (n2App1!=0)
				{					
            		if(c2AT1=='w' && (s2Type1=='G'&& s2Type2 == 'E'))
					{
                    	if(nProtect1==1)
						{
                        	fP1Uhp;
                        	n2App1 = n2App1 -1;
                    	}
                    
                    	else if(nProtect1!=1)
						{
                        	if((sType1=='F'&&sType2=='N')||(sType1=='G'&&sType2=='N')||(sType1=='G'&&sType2=='E'))
							{
                        	fP1Uhp = fP1Uhp-f2Abp1*2.0;
                        	n2App1 = n2App1 -1;
                        	}
                        
                        	if((sType1=='L'&&sType2=='G')||(sType1=='E'&&sType2=='N'))
							{ 
                        		fP1Uhp = fP1Uhp-f2Abp1;
                        		n2App1 = n2App1 -1;
                        	}
                        
                        	if((sType1=='I'&&sType2=='W')||(sType1=='W'&&sType2=='N'))
							{ 
                        		fP1Uhp = fP1Uhp-f2Abp1*0.5;
                        		n2App1 = n2App1 -1;
                        	}
                        	nCharge2=0;
                    	}
                    
						nProtect1=0;  
                	}
                
                    // STAB section
                    if(c2AT1=='f')
					{
                        if(nProtect1==1)
						{
                        	fP1Uhp;
                        	n2App1 = n2App1 -1;
                        }
                        
                        else if(nProtect1!=1)
						{
                        	if((sType1=='L'&&sType2=='G')||(sType1=='E'&&sType2=='N')||(sType1=='I'&&sType2=='W'))
							{
                        		f2Abp1 = f2Abp1 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp1;
                       			n2App1 = n2App1 -1;
							}
							
                        	if((sType1=='F'&&sType2=='N')||(sType1=='W'&&sType2=='N')||(sType1=='G'&&sType2=='N')||(sType1=='G'&&sType2=='E'))
							{
                        		f2Abp1 = f2Abp1 * 1.5;
                        		fP1Uhp = fP1Uhp-f2Abp1*0.5;
                        		n2App1 = n2App1 -1;
                        	}
                        	nCharge2=0;
                        }
                        
						nProtect1=0;  
                    }
                    
                    if(c2AT1=='w' && (!(s2Type1=='G'&& s2Type2 == 'E')))
					{
                        if(nProtect1==1)
						{
                        	fP1Uhp;
                        	n2App1 = n2App1 -1;
                        }
                        
                        else if(nProtect1!=1)
						{
                        	if((sType1=='F'&&sType2=='N')||(sType1=='G'&&sType2=='N')||(sType1=='G'&&sType2=='E'))
							{
                        		f2Abp1 = f2Abp1 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp1*2.0;
                        		n2App1 = n2App1 -1;
                        	}
                        	
                        	if((sType1=='L'&&sType2=='G')||(sType1=='E'&&sType2=='N'))
							{
								f2Abp1 = f2Abp1 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp1;
                        		n2App1 = n2App1 -1;
                        	}
                        	
                        	if((sType1=='I'&&sType2=='W')||(sType1=='W'&&sType2=='N'))
							{
								f2Abp1 = f2Abp1 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp1*0.5;
                        		n2App1 = n2App1 -1;
                            }
                            nCharge2=0;
                        }
                        
						nProtect1=0;  
                    }
                    
                    if(c2AT1=='g')
					{
                        if(nProtect1==1)
						{
                        	fP1Uhp;
                        	n2App1 = n2App1 -1;
                        }
                        
                        else if(nProtect1!=1)
						{
                        	if((sType1=='F'&&sType2=='N')||(sType1=='G'&&sType2=='E')||(sType1=='E'&&sType2=='N'))
							{
                        		f2Abp1 = f2Abp1 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp1*2.0;
                        		n2App1 = n2App1 -1;
							}
							
							if(sType1=='G'&&sType2=='N')
							{
                        		f2Abp1 = f2Abp1 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp1*1.0;
                        		n2App1 = n2App1 -1;
							}
                        	if((sType1=='W'&&sType2=='N')||(sType1=='G'&&sType2=='N')||(sType1=='L'&&sType2=='G'))
							{
                        		f2Abp1 = f2Abp1 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp1*0.5;
                        		n2App1 = n2App1 -1;
							}
							
                        	if((sType1=='I'&&sType2=='W'))
							{
                        		f2Abp1 = f2Abp1 * 1.5;
		                        fP1Uhp = fP1Uhp-f2Abp1*0.25;
                        		n2App1 = n2App1 -1;
                        	}
                        	nCharge2=0;
                        }
                        
						nProtect1=0;  
                    }
                    
                    if(c2AT1=='e')
					{
                        if(nProtect1==1)
						{
                        	fP1Uhp;
                        	n2App1 = n2App1 -1;
                        }
                        
                        else if(nProtect1!=1)
						{
                        	if((sType1=='W'&&sType2=='N')||(sType1=='I'&&sType2=='W'))
							{
                        		f2Abp1 = f2Abp1 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp1*2.0;
                        		n2App1 = n2App1 -1;
							}
							
                        	if((sType1=='F'&&sType2=='N')||(sType1=='E'&&sType2=='N'))
							{
                        		f2Abp1 = f2Abp1 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp1;
                        		n2App1 = n2App1 -1;
							}
							
                        	if((sType1=='G'&&sType2=='N')||(sType1=='G'&&sType2=='E')||(sType1=='L'&&sType2=='G'))
							{
                        		f2Abp1 = f2Abp1 * 1.5;
                        		fP1Uhp = fP1Uhp-f2Abp1*0.0;
                        		n2App1 = n2App1 -1;
                        	}
                        	nCharge2=0;
                        }
                        
						nProtect1=0;  
                    }
                    
                    if(c2AT1=='i')
					{
                        if(nProtect1==1)
						{
                        	fP1Uhp;
                        	n2App1 = n2App1 -1;
                        }
                        
                        else if(nProtect1!=1)
						{
                        	if((sType1=='L'&&sType2=='G'))
							{
                        		f2Abp1 = f2Abp1 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp1*4.0;
                        		n2App1 = n2App1 -1;
							}
							
                        	if((sType1=='W'&&sType2=='N')||(sType1=='G'&&sType2=='N')||(sType1=='G'&&sType2=='E')||(sType1=='I'&&sType2=='W'))
							{
                       			f2Abp1 = f2Abp1 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp1*2.0;
                       	 		n2App1 = n2App1 -1;
							}
							
                        	if((sType1=='E'&&sType2=='N'))
							{
                        		f2Abp1 = f2Abp1 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp1;
                        		n2App1 = n2App1 -1;
							}
							
                        	if((sType1=='F'&&sType2=='N'))
							{
                        		f2Abp1 = f2Abp1 * 1.5;
                        		fP1Uhp = fP1Uhp-f2Abp1*0.5;
                        		n2App1 = n2App1 -1;
                        	}
                        	nCharge2=0;
                        }
                        
						nProtect1=0;  
                    }   
                }      
            break;
            //last line of case a
            
            //first line of case b
            case 'b':
            	//displays the trainers phrase
        		printf("%s\n", s2Phrase2);
        		printf("Press enter key to continue.");
        		getchar();
        		fflush(stdin);
            	//no more pp for move 1
            	if(n2App2==0)
				{
                   	printf("No more pp.\n");
                    printf("Press enter to continue\n");
                    getchar();
    		        fflush(stdin);
                    nRetry2=1;
                }
            	
                if (n2App2!=0)
				{
                	if(c2AT2=='g' && (!(s2Type1=='G'&&s2Type2=='E')))
					{
                        if(cChoice2=='c')
						{
                        	fP1Uhp = fP1Uhp;
                        	n2App2 = n2App2 -1;
                        }
                        
                        else if(cChoice2!='c')
						{
                        	if((sType1=='F'&&sType2=='N')||(sType1=='G'&&sType2=='E')||(sType1=='E'&&sType2=='N'))
							{
                        		fP1Uhp = fP1Uhp-f2Abp2*2.0;
                        		n2App2 = n2App2 -1;
                        	}
                        	
                        	if((sType1=='W'&&sType2=='N')||(sType1=='G'&&sType2=='N')||(sType1=='L'&&sType2=='G'))
							{ 
                        		fP1Uhp = fP1Uhp-f2Abp2*0.5;
                       	 		n2App2 = n2App2 -1;
	                        }
	                        
                        	if((sType1=='I'&&sType2=='W'))
							{ 
                        		fP1Uhp = fP1Uhp-f2Abp2*0.25;
                        		n2App2 = n2App2 -1;
                            }
                            nCharge2=0;
                        }
                        
						nProtect1=0;  
                    }
                    
                    if(c2AT2=='i')
					{
                        if(nProtect1==1)
						{
                        	fP1Uhp = fP1Uhp;
                        	n2App2 = n2App2 -1;
                        }
                        
                        else if(nProtect1!=1)
						{
                        	if((sType1=='L'&&sType2=='G'))
							{
                        		fP1Uhp = fP1Uhp-f2Abp2*4.0;
                        		n2App2 = n2App2 -1;
                        	}
                        	
                        	if((sType1=='W'&&sType2=='N')||(sType1=='G'&&sType2=='N')||(sType1=='G'&&sType2=='E')||(sType1=='I'&&sType2=='W'))
							{ 
                        		fP1Uhp = fP1Uhp-f2Abp2*2.0;
                        		n2App2 = n2App2 -1;
                        	}
                        	
                        	if((sType1=='E'&&sType2=='N'))
							{ 
                        		fP1Uhp = fP1Uhp-f2Abp2;
                        		n2App2 = n2App2 -1;
                            }
                            
                        	if((sType1=='F'&&sType2=='N'))
							{ 
                        		fP1Uhp = fP1Uhp-f2Abp2*0.5;
                        		n2App2 = n2App2 -1;
                            }
                            nCharge2=0;
                        }
                        
						nProtect1=0;  
                    }
                    
                    if(c2AT2=='f')
					{
                        if(nProtect1==1)
						{
                        	fP1Uhp = fP1Uhp;
                        	n2App2 = n2App2 -1;
                        }
                        
                        else if(nProtect1!=1)
						{
                        	if((sType1=='L'&&sType2=='G')||(sType1=='E'&&sType2=='N')||(sType1=='I'&&sType2=='W'))
							{
                        		fP1Uhp = fP1Uhp-f2Abp2;
                        		n2App2 = n2App2 -1;
                        	}
                        	
                        	if((sType1=='F'&&sType2=='N')||(sType1=='W'&&sType2=='N')||(sType1=='G'&&sType2=='N')||(sType1=='G'&&sType2=='E'))
							{ 
                        		fP1Uhp = fP1Uhp-f2Abp2*0.5;
                        		n2App2 = n2App2 -1;
                        	}
                        	nCharge2=0;
                        }
                        
						nProtect1=0;  
                    }
                    
                    // STAB section
                    if(c2AT2=='g' && (s2Type1=='G'&&s2Type2=='E'))
					{
                        if(nProtect1==1)
						{
                        	fP1Uhp = fP1Uhp;
                        	n2App2 = n2App2 -1;
                        }
                        
                        else if(nProtect1!=1)
						{
                        	if((sType1=='F'&&sType2=='N')||(sType1=='G'&&sType2=='E')||(sType1=='E'&&sType2=='N'))
							{
                        		f2Abp2 = f2Abp2 * 1.5;
                        		fP1Uhp = fP1Uhp-f2Abp2*2.0;
                        		n2App2 = n2App2 -1;
                        	}
                        	
                        	if((sType1=='W'&&sType2=='N')||(sType1=='G'&&sType2=='N')||(sType1=='L'&&sType2=='G'))
							{
								f2Abp2 = f2Abp2 * 1.5; 
                        		fP1Uhp = fP1Uhp-fAbp2*0.5;
                        		n2App2 = n2App2 -1;
                        	}
                        	
                        	if((sType1=='I'&&sType2=='W'))
							{
								f2Abp2 = f2Abp2 * 1.5; 
                        		fP1Uhp = fP1Uhp-fAbp2*0.25;
                        		n2App2 = n2App2 -1;
                            }
                            nCharge2=0;
                        }
                        
						nProtect1=0;  
                    }
                    
                    if(c2AT2=='l')
					{
                        if(nProtect1==1)
						{
                        	fP1Uhp = fP1Uhp;
                        	n2App2 = n2App2 -1;
                        }
                        
                        else if(nProtect1!=1)
						{
                        	if((sType1=='W'&&sType2=='N')||(sType1=='G'&&sType2=='N'))
							{
                        		f2Abp2 = f2Abp2 * 1.5;
                        		fP1Uhp = fP1Uhp-f2Abp2*2.0;
                        		n2App2 = n2App2 -1;
                        	}
                        	
                        	if((sType1=='L'&&sType2=='G'))
							{
								f2Abp2 = f2Abp2 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp2;
                        		n2App2 = n2App2 -1;
                        	}
                        	
                        	if((sType1=='F'&&sType2=='N'))
							{
								f2Abp2 = f2Abp2 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp2*0.5;
                        		n2App2 = n2App2 -1;
                        	}
                        	
                        	if((sType1=='I'&&sType2=='W')||(sType1=='G'&&sType2=='E')||(sType1=='E'&&sType2=='N'))
							{
								f2Abp2 = f2Abp2 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp2*0.0;
                        		n2App2 = n2App2 -1;
                            }
                            nCharge2=0;
                        }
                        
						nProtect1=0;  
                    }
                    
                    if(c2AT2=='w')
					{
                        if(nProtect1==1)
						{
                        	fP1Uhp = fP1Uhp;
                        	n2App2 = n2App2 -1;
                        }
                        
                        else if(nProtect1!=1)
						{
                        	if((sType1=='F'&&sType2=='N')||(sType1=='G'&&sType2=='N')||(sType1=='G'&&sType2=='E'))
							{
                        		f2Abp2 = f2Abp2 * 1.5;
                        		fP1Uhp = fP1Uhp-f2Abp2*2.0;
                        		n2App2 = n2App2 -1;
                        	}
                        	
                        	if((sType1=='L'&&sType2=='G')||(sType1=='E'&&sType2=='N'))
							{
								f2Abp2 = f2Abp2 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp2;
                        		n2App2 = n2App2 -1;
                        	}
                        	
                        	if((sType1=='W'&&sType2=='N')||(sType1=='I'&&sType2=='W'))
							{
								f2Abp2 = f2Abp2 * 1.5; 
                        		fP1Uhp = fP1Uhp-f2Abp2*0.5;
                        		n2App2 = n2App2 -1;
                        	}
                        	nCharge2=0;
                        }
                        
						nProtect1=0;  
                    }
             	}
            break;
            //last line of case b
            
            //first line in case c
            case 'c':
            	//displays the trainers phrase
        		printf("%s\n", s2Phrase3);
        		printf("Press enter key to continue.");
        		getchar();
        		fflush(stdin);
            	//no more pp for move3
            	if(n2App3==0)
				{
                    printf("No more pp.\n");
                    printf("Press enter to continue\n");
                    getchar();
    		        fflush(stdin);
                   	nRetry2=1;
               	} 
            	// tells the user that the protect effect is still in used
            	if(nProtect2==1)
					{
						printf("Protect is still in effect. You can't use it again.\n");
						printf("Press enter to continue\n");
                    	getchar();
    		            fflush(stdin);
						nRetry2=1;
                	}
                	
            	if(nProtectTurn2>0)
				{
					printf("You can't use protect twice in a row\n");
					printf("Press enter to continue\n");
                    getchar();
    		        fflush(stdin);
					nRetry2=1;
				}
				
            	if(nProtectTurn2<=0)
				{
                	if(!(nProtect2==1))
					{
                		if(nApp3!=0)
						{
							nProtect2 = 1;
                    		n2App3 = n2App3-1;
                    		nProtectTurn2=3;
                		}
            		}
            	}
            	
                break;
            //last line in case c
            
            //first line in case d
            case 'd':
            	//displays the trainers phrase
        		printf("%s\n", s2Phrase4);
        		printf("Press enter key to continue.");
        		getchar();
        		fflush(stdin);
            	if(n2App4==0)
				{
                    printf("No more pp.\n");
                    printf("Press enter to continue\n");
                    getchar();
    		        fflush(stdin);
                    nRetry2=0;
                }
                
                if(nCharge2==1)
				{
					printf("Charge up is still in effect. You can't use it again.\n");
					printf("Press enter to continue\n");
                    getchar();
    		        fflush(stdin);
					nRetry2=0;
            	}
            	
                if(nCharge2==0)
				{
                	if(nApp4!=0)
					{
						nRetry2==0;
                    	n2App4 = n2App4-1;
                    	f2Abp1 = f2Abp1*2;
                    	f2Abp2 = f2Abp2*2;
                    	nCharge2=1;
                	}
            	}
            	
            break;
            //last line in case d  
        }
    }
            system("cls");    
		
	}
	//checks if the current player already beats the opponent
	if(fP1Uhp<=0)
		{
			nRetry2=0;
			nWinner=2;
    		gameWinner(nWinner,c1stName,c2ndName,cPokemonName1,cPokemonName2,fP1hp,fP2hp,fP1Uhp,fP2Uhp);
    		break;
		}
	
	nProtectTurn2--;
	}
	
}

//shows the instruction of the game before heading to the battle
void instruction(char cPokemon1,char cPokemon2,char *cPokemonName1,char *cPokemonName2,char *c1stName,char *c2ndName)
{
	
	
	// displays the trainer matchup
	printf("\n\n\n\t %0.5s's Pokemon  \t\t\t\t\t\t\t %0.5s's Pokemon \n", c1stName,c2ndName);
	printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
	printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
	printf("\t||   %s     ||\t\t\t VS\t\t\t\t||   %s     || \n",cPokemonName1, cPokemonName2 );
	printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
	printf("\t  =============  \t\t\t\t\t\t\t  =============\n\n\n");
	printf("\t\t\t\t\t\t\t\t  ==============================================\n");
	printf("\t\t\t\t\t\t\t\t||                 INSTRUCTION                  ||\n");
	printf("\t\t\t\t\t\t\t\t||                                              ||\n");
	printf("\t\t\t\t\t\t\t\t||     Player 1 will make the first attack,     ||\n");
	printf("\t\t\t\t\t\t\t\t||     then Player 2. Each Player will take     ||\n");
	printf("\t\t\t\t\t\t\t\t||     turns selecting moves their Pokemon      ||\n");
	printf("\t\t\t\t\t\t\t\t||     will use. The objective is to defeat     ||\n");
	printf("\t\t\t\t\t\t\t\t||       your opponent's pokemon and win.       ||\n");
	printf("\t\t\t\t\t\t\t\t||                                              ||\n");
	printf("\t\t\t\t\t\t\t\t  ==============================================\n\n");
	printf("Press enter key to continue");
	getchar();
    fflush(stdin);
	system("cls");
	
	mainGame(cPokemon1, cPokemon2, cPokemonName1,cPokemonName2,c1stName,c2ndName);
}
// shows the list of pokemon to be chosen
void pokemonList(char *c1stName,char *c2ndName){
	
	printf("\n\t %0.5s's Pokemon  \t\t\t\t\t\t\t %0.5s's Pokemon \n", c1stName,c2ndName);
	printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
	printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
	printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
	printf("\t||             ||\t\t\t\t\t\t\t||             || \n");
	printf("\t  =============  \t\t\t\t\t\t\t  =============\n");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("||          |         |         |      |                 Unique Move 1                   |                   Unique Move 2                 ||\n");
	printf("||----------|---------|---------|------|-------------------------------------------------|-------------------------------------------------||\n");
	printf("||   Name   |  Type1  |  Type2  |  HP  |    Name    | Base Power | Power Points |  Type  |    Name    | Base Power | Power Points |  Type  || \n");
	printf("||----------|-------------------|------|------------|------------|--------------|--------|------------|------------|--------------|--------||\n");
	printf("||  -Entei  |  -Fire  |  -None  | -150 | Fire Blast | -30 damage |      5pp     |  Fire  | Earthquake | -30 damage |      5pp     | Ground || [E]\n");
	printf("|| -Milotic |  Water  |  -None  | -200 |   -Scald   | -20 damage |      7pp     | -Water |  Ice Beam  | -20 damage |      7pp     |  -Ice  || [M]\n");
	printf("|| Torterra |  Grass  | -Ground | -220 |    -Dig    | -20 damage |      7pp     | Ground | Leaf Storm | -40 damage |      5pp     | -Grass || [T]\n");
	printf("|| -Pikachu |-Electric|  -None  | -120 |-Thunderbolt| -10 damage |     10pp     |Electric|    -Dig    | -20 damage |      7pp     | Ground || [P]\n");
	printf("|| -Groudon | -Ground |  -None  | -150 |  -Fissure  | -40 damage |      5pp     | Ground | Fire Blast | -30 damage |      5pp     |  Fire  || [G]\n");
	printf("||  Lapras  |   Ice   |  Water  | -190 |  Ice Beam  | -20 damage |      7pp     |Electric|   -Scald   | -20 damage |      7pp     |  Water || [L]\n");
	printf("|| Stunfisk | -Ground |-Electric| -130 | -Water Gun | -10 damage |     10pp     | -Water | Earthquake | -30 damage |      5pp     | Ground || [S]\n");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
}
//both players will have to choose their pokemon
void pokemonSelection(char *c1stName,char *c2ndName)
{
	char cPokemon1, cPokemon2;
	char *cPokemonName1, *cPokemonName2;
	
	pokemonList(c1stName,c2ndName);
	
	// pokemon selection phase
	printf("\n\tProfessor Oak: Trainer %0.5s, please select your pokemon.", c1stName); 
	scanf("%c", &cPokemon1);
	cPokemon1 = tolower(cPokemon1);
	fflush(stdin);
	
	if(!(cPokemon1=='e' ||  cPokemon1=='m' || cPokemon1=='t'  ||  cPokemon1=='p' ||  cPokemon1=='g' ||  cPokemon1=='l' ||  cPokemon1=='s'))
	{	
		printf("\nWrong Input\n");
		printf("Press enter to continue.\n");
		getchar();
    	fflush(stdin);
	}

	while(!(cPokemon1=='e' ||  cPokemon1=='m' || cPokemon1=='t'  ||  cPokemon1=='p' ||  cPokemon1=='g' ||  cPokemon1=='l' ||  cPokemon1=='s'))
	{
		system("cls");
		pokemonList(c1stName,c2ndName);
		// pokemon selection phase
		printf("\n\tProfessor Oak: Trainer %0.5s, please select your pokemon.", c1stName);
		scanf("%c", &cPokemon1);
		cPokemon1 = tolower(cPokemon1);
		fflush(stdin);
	
		if(!(cPokemon1=='e' ||  cPokemon1=='m' || cPokemon1=='t'  ||  cPokemon1=='p' ||  cPokemon1=='g' ||  cPokemon1=='l' ||  cPokemon1=='s'))
		{
			printf("\nWrong Input\n");
			printf("Press enter to continue.\n");
			getchar();
    		fflush(stdin);
		}
	}
	
	system("cls");
	pokemonList(c1stName,c2ndName);
	
	printf("\n\tProfessor Oak: Trainer %0.5s, please select your pokemon.", c2ndName);
	scanf("%c", &cPokemon2);
	cPokemon2 = tolower(cPokemon2);
	fflush(stdin);
	
	if(!(cPokemon2=='e' ||  cPokemon2=='m' || cPokemon2=='t'  ||  cPokemon2=='p' ||  cPokemon2=='g' ||  cPokemon2=='l' ||  cPokemon2=='s'))
	{
		printf("\nWrong Input\n");
		printf("Press enter to continue.\n");
		getchar();
    	fflush(stdin);
	}

	while(!(cPokemon2=='e' ||  cPokemon2=='m' || cPokemon2=='t'  ||  cPokemon2=='p' ||  cPokemon2=='g' ||  cPokemon2=='l' ||  cPokemon2=='s'))
	{
		system("cls");
		pokemonList(c1stName,c2ndName);
		// pokemon selection phase
		printf("\n\tProfessor Oak: Trainer %0.5s, please select your pokemon.", c2ndName);
		scanf("%c", &cPokemon2);
		cPokemon2 = tolower(cPokemon2);
		fflush(stdin);
		
		if(!(cPokemon2=='e' ||  cPokemon2=='m' || cPokemon2=='t'  ||  cPokemon2=='p' ||  cPokemon2=='g' ||  cPokemon2=='l' ||  cPokemon2=='s'))
		{
			printf("\nWrong Input\n");
			printf("Press enter to continue.\n");
			getchar();
    		fflush(stdin);
		}
	}
	
	//displays the chosen pokemon Name
	switch(cPokemon1)
	{ 
		case 'e': cPokemonName1 = "Entei";
		break;
		case 'm': cPokemonName1 = "Milotic";
		break;
		case 't': cPokemonName1 = "Torterra";
		break;
		case 'p': cPokemonName1 = "Pikachu";
		break;
		case 'g': cPokemonName1 = "Groudon";
		break;
		case 'l': cPokemonName1 = "Lapras";
		break;
		case 's': cPokemonName1 = "Stunfisk";
		break;
	}
	
	switch(cPokemon2)
	{
		case 'e': cPokemonName2 = "Entei";
		break;
		case 'm': cPokemonName2 = "Milotic";
		break;
		case 't': cPokemonName2 = "Torterra";
		break;
		case 'p': cPokemonName2 = "Pikachu";
		break;
		case 'g': cPokemonName2 = "Groudon";
		break;
		case 'l': cPokemonName2 = "Lapras";
		break;
		case 's': cPokemonName2 = "Stunfisk";
		break;
	}
	
	system("cls");
	instruction(cPokemon1, cPokemon2,cPokemonName1,cPokemonName2,c1stName, c2ndName);
}
// gets the names of the players
void playersNames()
{
	char c1stName[5],c2ndName[5];
	/* gets the names of the two
	players */
	printf("(5characters only)\n");
	printf("Professor Oak: What's your name kiddo?\n");
	printf("Player 1 NAME:"); 
	gets(c1stName);
	fflush(stdin);
	printf("\nProfessor Oak: What's your name kiddo?\n");
	printf("Player 2 NAME:");
	gets(c2ndName);
	fflush(stdin);
	system("cls");
	pokemonSelection(c1stName, c2ndName);
}
// the opening menu; transfer the user to the game 
void startMenu()
{ 
	char cChoice;
	
	printf("\t\t\t\t\t\t\t\t\t\t       Enter:"); 
	scanf("%c", &cChoice);
	fflush(stdin);
	printf("\n");
	cChoice = tolower(cChoice); // to make the reply valid for lower and uppercase input
	
	if (cChoice == 'a' )// proceed to the main game
	{ 
		system("cls");
		playersNames();
	}
	
	else if (cChoice == 'b')// exits the program
	{ 
		printf("\t\t\t\t\t       THANK YOU FOR PLAYING");
	}
	
	else// invalid output
	{
		system("cls");
		printf("\t\t\t\t\t\t\t\t  ==============================================\n");
		printf("\t\t\t\t\t\t\t\t||                                              ||\n");
		printf("\t\t\t\t\t\t\t\t||                                              ||\n");
		printf("\t\t\t\t\t\t\t\t||                    1 V 1                     ||\n");
		printf("\t\t\t\t\t\t\t\t||                                              ||\n");
		printf("\t\t\t\t\t\t\t\t||          POKEMON  BATTLE  SIMULATOR          ||\n");
		printf("\t\t\t\t\t\t\t\t||                                              ||\n");
		printf("\t\t\t\t\t\t\t\t||                                              ||\n");
		printf("\t\t\t\t\t\t\t\t||                                              ||\n");
		printf("\t\t\t\t\t\t\t\t  ==============================================\n\n");
		printf("\t\t\t\t\t\t\t\t             [A]                   [B]                   \n");
		printf("\t\t\t\t\t\t\t\t            START                  END                  \n");
		printf("\t\t\t\t\t\t     Wrong Input.\n");
		
		startMenu();
	}	
}


int main()
{
	printf("\t\t\t\t\t\t\t\t  ==============================================\n");
	printf("\t\t\t\t\t\t\t\t||                                              ||\n");
	printf("\t\t\t\t\t\t\t\t||                                              ||\n");
	printf("\t\t\t\t\t\t\t\t||                    1 V 1                     ||\n");
	printf("\t\t\t\t\t\t\t\t||                                              ||\n");
	printf("\t\t\t\t\t\t\t\t||          POKEMON  BATTLE  SIMULATOR          ||\n");
	printf("\t\t\t\t\t\t\t\t||                                              ||\n");
	printf("\t\t\t\t\t\t\t\t||                                              ||\n");
	printf("\t\t\t\t\t\t\t\t||                                              ||\n");
	printf("\t\t\t\t\t\t\t\t  ==============================================\n\n");
	printf("\t\t\t\t\t\t\t\t             [A]                   [B]                   \n");
	printf("\t\t\t\t\t\t\t\t            START                  END                  \n");
	
	startMenu();
	
	 return 0;
}
