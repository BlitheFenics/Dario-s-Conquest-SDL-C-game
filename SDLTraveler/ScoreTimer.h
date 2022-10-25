#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <cstring>
#include <ctime>
class ScoreTimer
{
private:
	const char* timerText = "Time: ";
	const char* timerNum = "000";
	SDL_Renderer* pRenderer = nullptr;
	int startTime =0 ;
	int time = 0;
	std::string newText;
	std::string newTime;
	SDL_Texture* tTextureText = nullptr;
	SDL_Texture* tTextureTime = nullptr;
	SDL_Color white = { 0,0,0 };
	SDL_Surface* tSurface = nullptr;
	SDL_Rect textR = { 500,40,100,50 };
	SDL_Rect textR2 = { 400,50,100,25 };
	TTF_Font* font = nullptr;

	float iMilliseconds = 0;
		
public:
	int GetTime() { return time; }
	ScoreTimer(SDL_Renderer* pRend);
	ScoreTimer();
	void Render(SDL_Renderer* pRend);
	void Reset(SDL_Renderer* pRend);
	void Update(SDL_Renderer* pRend);

	void AddTime();
};

