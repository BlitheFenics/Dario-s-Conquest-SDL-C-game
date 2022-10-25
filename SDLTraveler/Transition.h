#pragma once
#include "SDL.h"
#include "SDL_image.h"

class Transition
{
private:
	SDL_Texture* tTexture;
	SDL_Surface* tSurface;
	SDL_Rect* tRect;
	int timer = 0;
	bool isActive = false;
	bool finished = false;

public:

	void SetActive(bool b)
	{
		timer = 0;
		isActive = b;
		finished = false;
	}
	void SetRect(SDL_Rect* rect)
	{
		tRect = rect;
	}
	void SetTexture(SDL_Renderer* ren)
	{
		tSurface = IMG_Load("transitionIMG.png");
		tTexture = SDL_CreateTextureFromSurface(ren, tSurface);
		SDL_FreeSurface(tSurface);
	}
	bool GetFinished()
	{
		return finished;
	}
	bool GetActive()
	{
		return isActive;
	}
	SDL_Rect* GetRect()
	{
		return tRect;
	}
	SDL_Texture* GetTexture()
	{
		return tTexture;
	}
	SDL_Surface* GetSurface()
	{
		return tSurface;
	}
	void Update();
	void Render(SDL_Renderer* pRen);



	Transition();
	~Transition();

};

