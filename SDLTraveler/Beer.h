#pragma once
#include "GameObject.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

enum TypeOfBeer
{
	REGULAR_BEER, // +1 hp
	IRON_BEER, // +1 Hp
	CONFUSION_BEER, // Reverse controls
	POISON_BEER, // -1 hp
	STRENGTH_BEER, // bigger bullets
	SLOW_BEER // makes dario slower?
};

class Beer: public GameObject
{
public:
	Beer(SDL_Renderer* p, int beer)
	{

		if (beer > 5 || beer < 0)
			beer = 0;
		if (beer == 0)
		{
			ToB = REGULAR_BEER;
			BeerSurf = IMG_Load("Beer.png");
			if (BeerSurf == NULL)
				std::cout << "SURFACE FAIL B B\n\n";
			BeerTexture = SDL_CreateTextureFromSurface(p, BeerSurf);
			if (BeerTexture == NULL)
			{
				std::cout << "TEXTURE FAIL B \n\n";
				std::cout << IMG_GetError;
			}
			SDL_FreeSurface(BeerSurf);
		}
		if (beer == 1)
		{
			ToB = IRON_BEER;
			BeerSurf = IMG_Load("armored_heart.png");
			if (BeerSurf == NULL)
				std::cout << "SURFACE FAIL B \n\n";
			BeerTexture = SDL_CreateTextureFromSurface(p, BeerSurf);
			if (BeerTexture == NULL)
			{
				std::cout << "TEXTURE FAIL B \n\n";
				std::cout << IMG_GetError;
			}
			SDL_FreeSurface(BeerSurf);
		}
		if (beer == 2)
		{
			ToB = CONFUSION_BEER;
			BeerSurf = IMG_Load("inverted_controls.png");
			if (BeerSurf == NULL)
				std::cout << "SURFACE FAIL B \n\n";
			BeerTexture = SDL_CreateTextureFromSurface(p, BeerSurf);
			if (BeerTexture == NULL)
			{
				std::cout << "TEXTURE FAIL B \n\n";
				std::cout << IMG_GetError;
			}
			SDL_FreeSurface(BeerSurf);
		}
		if (beer == 3)
		{
			ToB = POISON_BEER;
			BeerSurf = IMG_Load("drunk_vision.png");
			if (BeerSurf == NULL)
				std::cout << "SURFACE FAIL B \n\n";
			BeerTexture = SDL_CreateTextureFromSurface(p, BeerSurf);
			if (BeerTexture == NULL)
			{
				std::cout << "TEXTURE FAIL B \n\n";
				std::cout << IMG_GetError;
			}
			SDL_FreeSurface(BeerSurf);
		}
		if (beer == 4)
		{
			ToB = STRENGTH_BEER;
			BeerSurf = IMG_Load("giant_bullets.png");
			if (BeerSurf == NULL)
				std::cout << "SURFACE FAIL B \n\n";
			BeerTexture = SDL_CreateTextureFromSurface(p, BeerSurf);
			if (BeerTexture == NULL)
			{
				std::cout << "TEXTURE FAIL B \n\n";
				std::cout << IMG_GetError;
			}
			SDL_FreeSurface(BeerSurf);
		}
		if (beer == 5)
		{
			ToB = SLOW_BEER;
			BeerSurf = IMG_Load("increase_score.png");
			if (BeerSurf == NULL)
				std::cout << "SURFACE FAIL B \n\n";
			BeerTexture = SDL_CreateTextureFromSurface(p, BeerSurf);
			if (BeerTexture == NULL)
			{
				std::cout << "TEXTURE FAIL B \n\n";
				std::cout << IMG_GetError;
			}
			SDL_FreeSurface(BeerSurf);
		}
		rSrc = { 0, 0, 32, 32 };
		rDst = { 480, 530, 64, 64 };


		ObjInit();

	}
	
	SDL_Rect GetDst()
	{
		return rDst;
	}
	void SetDst(int x, int y)
	{
		rDst.x = x;
		rDst.y = y;
		ObjInit();
	}

	void Render(SDL_Renderer* p);
	
	void Update();

	int GetType()
	{
		switch(ToB)
		{
			case REGULAR_BEER: // +1 hp
				return 0;
				break;
			case IRON_BEER: // +1 Hp
				return 1;
				break;
			case CONFUSION_BEER: // Reverse controls
				return 2;
				break;
			case POISON_BEER: // -1 hp
				return 3;
				break;
			case STRENGTH_BEER: // bigger bullets
				return 4;
				break;
			case SLOW_BEER: // makes dario slower?
				return 5;
				break;
		
		}
	}

	void Remove()
	{
		rDst.x = -1000;
		rDst.y = -1000;
		ObjInit();
	}
	~Beer(){}
	
private:
	int iteration = 0, cycle = 0;// Animation Loop counter 
	bool animation = false;
	SDL_Surface* BeerSurf = nullptr;
	SDL_Texture* BeerTexture = nullptr;
	SDL_Renderer* p;
	TypeOfBeer ToB;

	//TypeOfBeer GetType() { return ToB; }
	void SetBeer(TypeOfBeer beer) { ToB = beer; }
};

