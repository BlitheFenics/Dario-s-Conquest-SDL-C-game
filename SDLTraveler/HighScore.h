#pragma once
#include <iostream>
#include "SDL_ttf.h"
#include <string>
#include <fstream>

using namespace std;

class HighScore
{
private:
	SDL_Renderer* pRend = nullptr;
	SDL_Surface* tSurface = nullptr;
	SDL_Texture* tHighScore = nullptr;
	SDL_Texture* tHighScoreNum[5] = { nullptr };
	SDL_Rect textR[6];
	SDL_Rect textRect;
	const char* textScore = "High Scores";
	const char* textHigh = "000";
	std::string newHighScore;
	int highScore[5] = { 0,0,0,0,0 };
	
	TTF_Font* font = nullptr;

	SDL_Color white = { 255,255,255 };

public:
	HighScore(SDL_Renderer* pRend);
	void SaveScore();
	void LoadScore();
	void Render(SDL_Renderer* pRend);

	~HighScore();
	
};

