#pragma once
#include "bullet.h"
#include "Enemy.h"
#include "Platform.h"
//#include "Player.h"
#include "Eyesplosion.h"
#include "Goomba.h"
//#include "Goomblast.h"
#include "Health.h"
#include "Arrow.h"
#include "Eyebeam.h"
#include "Logo.h"
#include "AudioManager.h"
#include "Level.h"
#include "ScoreManager.h"
#include "Credits.h"
#include "MossBoss.h"
#include "ScoreTimer.h"
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Death.h"

#include "HighScore.h"

#include "SDL_ttf.h"
#include <string>


#include <fstream>

using namespace std;

class Game
{
private:
	Player player;
	Bullet* bullet[3] = { nullptr };
	Credits* credit;
	HighScore* highscore;
	bool CreditsOn = false;
	bool HighScoreOn = false;
	ScoreTimer* scoreTimer;
	Level* levels[5] = {nullptr};
	static int currentLevel;

	Death* death = nullptr;

	Arrow arrow;

	Transition transition;
	SDL_Rect hpSR1 = { 32, 0, 22, 22 };
	SDL_Rect hpSR2 = { 32, 0, 50, 22 };
	SDL_Rect hpSR3 = { 32, 0, 80, 22 };

	SDL_Rect hpDR1 = { 64, 80, 44, 44 };
	SDL_Rect hpDR2 = { 64, 80, 100, 44 };
	SDL_Rect hpDR3 = { 64, 80, 160, 44 };

	int iteration = 0, cycle = 0;
	SDL_Rect DarioSrc = { 0, 283, 32, 37 };
	SDL_Rect DarioDes = { 600, 580, 64, 74 };

	//SDL_Rect platformer = { 512, 400, 32, 37 };
	GameObject platformer;

	SDL_Rect i = { 0,0,0,0 };

	int grounded = 0;

	bool gameOn = true;

	// SDL stuff

	SDL_Window* pWindow = nullptr;
	SDL_Renderer* pRenderer = nullptr;
	SDL_Texture* pTexture = nullptr;
	SDL_Texture* eTexture = nullptr;
	SDL_Texture* gTexture = nullptr;
	SDL_Texture* bTexture = nullptr;
	SDL_Texture* goTexture = nullptr;
	SDL_Texture* lTexture = nullptr;
	SDL_Texture* sTexture = nullptr;
	SDL_Texture* ltTexture = nullptr;
	SDL_Texture* pauseTexture = nullptr;
	SDL_Texture* pauseBGTexture = nullptr;
	SDL_Texture* MiniMossTexture = nullptr;
	SDL_Texture* tMossy = nullptr;
	SDL_Texture* tSuccess = nullptr;
	SDL_Texture* tRock = nullptr;

	SDL_Surface* pSurface = nullptr;

	Platform* floor[20];

	const char* num;
	int iNum = 0;
	string newNum;

	const char* num2;
	int iNum2 = 0;
	string newNum2;

	TTF_Font* font1 = nullptr;
	SDL_Color white = { 0,0,0 };
	SDL_Surface* tSurface = nullptr;
	SDL_Texture* tTexture = nullptr;
	SDL_Texture* tTexture2 = nullptr;

	//string numberText;

	SDL_Rect textR = { 500, 40 ,100,50 };
	SDL_Rect textR2 = { 390,50,100, 25 };
	
	SDL_GameController* controller1 = nullptr;
	SDL_Event event;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	//Mix_Music* sMusic = nullptr;

	//Mix_Chunk* sJump = nullptr;
	//Mix_Chunk* sFire = nullptr;
	//Mix_Chunk* sPlat = nullptr;
	//Mix_Chunk* sBoom = nullptr;
	//Mix_Chunk* sCrackle = nullptr;
	//Mix_Chunk* sSlash = nullptr;


	//BOSSPLATS. 128 is how long the platform is, then you times it to add a new plat. ex. 128 * 2.
	int bpfX[20] = { -100, -100, -100, -100, -100, -100, -100, -100, 50, 150, 360, -100, -100, -100, -100, -100, -100, -100, -100, -100 }; // -100 means that it puts them off into a corner, and not on screen.
	int bpfY[20] = { -100, -100, -100, -100, -100, -100, -100, -100, 350, 450, 300, -100, -100, -100, -100, -100, -100, -100, -100, -100 }; 


	int pfSX0[20] = { 0, 128, 128 * 2, 128 * 3, 128 * 4, 128 * 5, 128 * 6, 128 * 7, 87, 362, 608, 835, -100, -100, -100, -100, -100, -100, -100, -100 };
	int pfSY0[20] = { 768,768,768,768,768,768,768,768, 619, 619, 619, 619, 200, -100, -100, -100, -100, -100, -100, -100 };


	int pfX0[20] = { 0, 2422, 128 * 2, 128 * 3, 128 * 4, 128 * 5, 128 * 6, 128 * 7, 1350, 1630, 2059, 3874, 3754, 3634, 3362, -100, -100, -100, -100, };
	int pfY0[20] = { 594, 594, -100, -100, -100, -100, -100, -100, 400, 191, 256, 126, 126, 126, 353, -100, -100, -100, -100, -100, };

	int pfX1[20] = { 0, 80, 336, 598, 853, 1022, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100 };
	int pfY1[20] = { 733, 558, 558, 558, 558, 495, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100, -100 };

	int pfX2[20] = { 16, -100, -100, -100, -100, -100, -100, -100,  47,   667,  227,  617,  876,  86,   472,  172, 496, 425, 446,  151 };
	int pfY2[20] = { 113, -100, -100, -100, -100, -100, -100, -100, 1544, 1493, 1350, 1161, 1281, 1166, 1016, 911, 774, 546, 331,  401 };

	int playerHP = 0;


	int highScore[5] = { 0,0,0,0,0 };


public:
	Game();

	bool Exit = false;

	bool pauseGame = false;
	
	bool pausing = true;

	void Init();

	void HandleEvents();

	void Update();

	void Render();

	void Clean();

	bool Over();

	bool Start();
	
	/*bool HighScores();
*/
	void Pause();

	void Reset();

	static int GetCurrentLevel()
	{
		return currentLevel;
	}

	bool endGame()
	{
		if (gameOn == true)
		{
			return false;
		}
		else
		{
			return true;
		}
	}


	bool GetAlive()
	{
		return player.GetAlive();
	}

	void LoadScores()
	{

		ifstream inFile;
		inFile.open("highScore.txt", fstream::in);

		inFile >> highScore[0] >> highScore[1] >> highScore[2] >> highScore[3] >> highScore[4];

		inFile.close();
	}

	void SaveScores()
	{
		int score = ScoreManager::GetInstance(pRenderer)->GetScore();

		if (score > highScore[0])
		{
			highScore[4] = highScore[3];
			highScore[3] = highScore[2];
			highScore[2] = highScore[1];
			highScore[1] = highScore[0];
			highScore[0] = score;
		}
		else if (score > highScore[1])
		{
			highScore[4] = highScore[3];
			highScore[3] = highScore[2];
			highScore[2] = highScore[1];
			highScore[1] = score;
		}
		else if (score > highScore[2])
		{
			highScore[4] = highScore[3];
			highScore[3] = highScore[2];
			highScore[2] = score;
		}
		else if (score > highScore[3])
		{
			highScore[4] = highScore[3];
			highScore[3] = score;
		}
		else if (score > highScore[4])
		{
			highScore[4] = score;
		}

		ofstream outFile;
		outFile.open("highScore.txt", fstream::out);

		for (int i : highScore)
		{
			outFile << i << endl;
		}

		outFile.close();

	}
	~Game();
};

