#pragma once
#include "SDL.h"


class Logo
{
private:
	SDL_Rect src = { 0,0,1024,768 };
	SDL_Rect dst = { 275,-768,500,400 };
	int count = 0;
public:
	SDL_Rect getSrc() { return src; }
	SDL_Rect getDst() { return dst; }

	void update()
	{
		count++;
		if (count % 2 == 0)//modulus slows down the speed of image movement. slow frame rate
		{
			dst.y += 1; //moves image on screen 
		}
		if (dst.y == 200)/*delays screen for 1 sec and continues moving image*/
		{
			SDL_Delay(1000);
		}
	}
};

class LogoText
{
private:
	SDL_Rect src1 = { 0,0,562,350 };
	SDL_Rect src2 = { 600,0,562,350 };
	SDL_Rect dst1 = { 425, 8 ,562,350 };
	SDL_Rect dst2 = { 416, 11 ,562,350 };
	int count = 0;
public:
	SDL_Rect getSrc1() { return src1; }
	SDL_Rect getSrc2() { return src2; }
	SDL_Rect getDst1() { return dst1; }
	SDL_Rect getDst2() { return dst2; }

	void update()
	{

		count++;

		if (count % 4 == 0)//modulus slows down the speed of image movement. slow frame rate
		{
			src1.y += 1;
			dst1.y += 1; //moves image on screen 
		}
	}
};
