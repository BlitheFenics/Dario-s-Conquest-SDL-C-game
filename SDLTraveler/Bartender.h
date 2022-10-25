#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GameObject.h"
#include <cmath>

class Bartender : public GameObject
{
public:
	int iteration = 0, cycle = 0;
	SDL_Texture* BartenderTexture;
	SDL_Texture* speech = nullptr;
	SDL_Rect speechDst = { 380, 180, 381, 109 };
	Bartender(SDL_Renderer* pRend)
	{
		rSrc = { 0,0, 70, 87 };
		rDst = { 450 - (70 + 200) , 450 - (87 + 80), 140 + 50, 174 + 50 };
		BartenderTexture = IMG_LoadTexture(pRend, "bartenderlu.png");
		speech = IMG_LoadTexture(pRend, "Speech1.png");
	}
	void Update();
	void Render(SDL_Renderer* pRend);
};