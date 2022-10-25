#pragma once
#include "GameObject.h"
#include "SDL.h"
#include "SDL_image.h"

class Death : public GameObject
{
private:
	SDL_Texture* tDeath = nullptr;
	SDL_Surface* pSurface = nullptr;
	int homeY = 0;
	int phase = 0;
	int yVel = -30;
	int iteration = 0;

public:
	Death(int x, int y, SDL_Renderer* pRend)
	{
		rSrc = { 0, 0, 26, 36 };
		rDst = { x, y, 26, 36 };

		pSurface = IMG_Load("DarioDeath.png");
		tDeath = SDL_CreateTextureFromSurface(pRend, pSurface);
		SDL_FreeSurface(pSurface);

		//rDst.x = x;
		//rDst.y = y;

		ObjInit();

		homeY = y;

	}

	void Render(SDL_Renderer* pRend)
	{
		SDL_RenderCopy(pRend, tDeath, &rSrc, &rDst);
	}

	void Update()
	{
		iteration++;
		if (iteration % 2 == 0)
		{
			baseY += yVel;
			yVel++;
		}

		Scroll(0, 0);
	}

	int GetY()
	{
		return rDst.y;
	}


};

