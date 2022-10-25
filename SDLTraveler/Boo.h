#pragma once
#include "GameObject.h"
#include "AudioManager.h"
#include <cmath>
#include <ctime>
#include <SDL.h>




class FireBall : public GameObject
{
private:
	int iteration = 0;
	int angle = 0;
	int yVel = 5;
	int xVel = 0;
	SDL_Point center = { 11, 18 };

public:
	FireBall(int x, int y)
	{
		rSrc = { 192, 0, 18, 25 };
		baseX = x;
		baseY = y;
		rDst = { baseX, baseY, 18, 25 };

		xVel = ((rand() % 2) * 2) - 1;


		ObjInit();
	}

	void ReSpawn(int x, int y)
	{
		baseX = x;
		baseY = y + 32;

		xVel = ((rand() % 2) * 2) - 1;

	}

	void Update()
	{
		iteration -= 10;
		angle = iteration;

		if (iteration > 360)
		{
			iteration = 0;
		}

		baseX += xVel;
		baseY += yVel;
	}

	void Render(SDL_Renderer* pRen, SDL_Texture* pText)
	{
		SDL_RenderCopyEx(pRen, pText, &rSrc, &rDst, angle, &center, SDL_FLIP_NONE);
	}

	int GetY()
	{
		return baseY;
	}

};



class Boo : public GameObject
{
private:
	int direction = 1;
	int homeX = 0;
	int homeY = 0;
	int iteration = 0;
	int frame = 0;
	int bottom = 0;
	bool alive = false;

	FireBall* flame = nullptr;

	SDL_RendererFlip flip = SDL_FLIP_NONE;

public:
	Boo(int x, int y, int bottom)
	{
		rSrc = { 0,0,37, 68 };
		rDst = { x,y,37, 68 };
		homeX = x;
		homeY = y;
		this->bottom = bottom;
		ObjInit();
		alive = true;
	}

	void Remove()
	{
		alive = false;
		rSrc = { 0, 0, 0, 0 };
		rDst = { 0, 0, 0, 0 };
	}

	bool GetAlive()
	{
		return alive;
	}



	SDL_Rect* GetFlameBox()
	{
		return &flame->GetDst();
	}

	void Update(int OffSetX, int OffSetY)
	{
		if (alive == true)
		{
			iteration += 2;
			frame++;

			// The y coordinate of the boo is a sine wave
			baseY = homeY + 50 * sin(iteration * M_PI / 180);


			// These ifs control the horizontal movement. He moves 200 pixels to the right of the homeX position, then turns left.
			// Then he heads 200 to the left of it and turns right again. And so on, and so forth, et cetera, etc, and all the rest.
			if (direction == 1)
			{
				baseX++;
				if (baseX == (homeX + 200))
				{
					direction = -1;
					flip = SDL_FLIP_HORIZONTAL;
				}
			}
			if (direction == -1)
			{
				baseX--;
				if (baseX == (homeX - 200))
				{
					direction = +1;
					flip = SDL_FLIP_NONE;
				}
			}

			rSrc.x = (frame % 4) * 48;

			Scroll(OffSetX, OffSetY);

			if (flame == nullptr)
			{
				flame = new FireBall(baseX, baseY);
			}
			else
			{
				flame->Update();
				if (flame->GetY() > bottom)
				{
					flame->ReSpawn(baseX, baseY);
					AudioManager::GetInstance()->Fireball();
				}

				flame->Scroll(OffSetX, OffSetY);

			}
		}

	}


	void Render(SDL_Renderer* pRen, SDL_Texture* pTex)
	{
		if (alive == true)
		{
			SDL_RenderCopyEx(pRen, pTex, &rSrc, &rDst, 0, NULL, flip);
			if (flame != nullptr)
			{
				flame->Render(pRen, pTex);
			}
		}

	}

};
