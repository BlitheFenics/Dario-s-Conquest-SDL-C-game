#pragma once
#include "SDL.h"
#include "GameObject.h"

class Platform : public GameObject
{	

private:
	bool isMoving = false; // determines whether it moves or not.
	bool directionX = false, directionY = false;
	int homeX = 0, homeY = 0; // this is for the home position, where is starts.
	int amplitudeX = 0, amplitudeY = 0; // amplitude is how wide it moves, how far in direction.
	int cycle = 0;

public:
	

	Platform()
	{
		rSrc = { 0, 0, 143, 71};
		rDst = {-100, -100, 128, 30 };

		ObjInit();
	}
	Platform(int x, int y)
	{
		rSrc = { 0, 0, 580, 103 };
		rDst = { x, y, 128, 32 };

		ObjInit();
	}
	void setPlatform(int x, int y)
	{
		rDst.x = x;
		rDst.y = y;

		ObjInit();
	}
	void setMoving(int ampX, int ampY)
	{
		isMoving = true;
		amplitudeX = ampX;
		amplitudeY = ampY;
		homeX = baseX;
		homeY = baseY;
	}

	int getTop()
	{
		//return (rDst.y - 37);
		return (baseY - 37);
	}

	int getX()
	{
		return baseX;
	}

	int getY()
	{
		return baseY;
	}

	SDL_Rect getSrc()
	{
		return rSrc;
	}
	SDL_Rect getDst()
	{
		return rDst;
	}

	void Update()
	{
		if (isMoving == true)
		{
			//cycle++;
			if (directionX == true) // true is right. false is left.
			{
				baseX++;
				if (baseX - homeX >= amplitudeX)
				{
					directionX = false;
				}
			}
			if (directionX == false) 
			{
				baseX--;
				if (homeX - baseX >= amplitudeX)
				{
					directionX = true;
				}
			}
			if (directionY == true) // true is down, false is up.
			{
				baseY++;
				if (baseY - homeY >= amplitudeY)
				{
					directionY = false;
				}
			}
			if (directionY == false) 
			{
				baseY--;
				if (homeY - baseY >= amplitudeY)
				{
					directionY = true;
				}
			}
		}
	};

	void setWidth(int x)
	{
		rDst.w = x;
	}	

	bool getDirectionX()
	{
		return directionX;
	}
	bool getDirectionY()
	{
		return directionY;
	}


	bool getXMoving()
	{
		if (amplitudeX > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool getYMoving()
	{
		if (amplitudeY > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};

