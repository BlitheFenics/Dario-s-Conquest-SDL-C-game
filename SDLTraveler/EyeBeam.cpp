#include "EyeBeam.h"


EyeBeam::EyeBeam(int x, int y, SDL_RendererFlip f)
{

	rSrc = { 0,0,64,64 };
	rDst = { x,y,64,64 };

	rDst.y = y - 32;


	bDst.y = y - 16;

	if (f == SDL_FLIP_NONE)
	{
		flip = SDL_FLIP_HORIZONTAL;
		rDst.x = x;
		bDst.x = x;
	}
	else
	{
		flip = SDL_FLIP_NONE;
		rDst.x = x - 64;
		bDst.x = x - 1024;

	}

}

int EyeBeam::Update(int x, int y, SDL_RendererFlip f)
{
	iteration++;

	//baseX = x;
	//baseY = y - 9;

	bDst.x = x;
	bDst.y = y + 6;



	if (f == SDL_FLIP_NONE)
	{
		flip = SDL_FLIP_HORIZONTAL;
		//baseX = x - 16;
		bDst.x = x - 1020;
		bDst.y = y + 6;


		rDst.y = y - 9;
		rDst.x = x - 13;

	}
	else
	{
		flip = SDL_FLIP_NONE;
		//baseX = x - 5;
		bDst.x = x + 38;
		bDst.y = y + 6;


		rDst.y = y - 9;
		rDst.x = x - 9;
	}

	if (iteration % 3 == 0)
	{

		if (chargeCount < 6)
		{
			chargeCount++;
			rSrc.x = chargeCount * 64;
		}
		else
		{
			rSrc.y = 64;
			rSrc.x = 64 * waveCount;
			if (waveCount < 6)
			{
				waveCount++;
			}
			else
			{
				waveCount = 0;
			}


			if (flicker < 3)
			{
				flicker++;
			}
			else
			{
				flicker = 0;
			}
		}

	}

	bSrc.y = 160 + (64 * flicker);

	if (waveCount == 6)
	{
		loopCount++;
	}

	if (loopCount < 1)
	{
		return 0;
	}
	else if (loopCount < 20)
	{
		status = 1;
		return 1;
	}
	else
	{
		status = 2;
		return 2;
	}
}

EyeBeam::~EyeBeam()
{
}
