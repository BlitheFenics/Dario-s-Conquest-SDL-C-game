#pragma once
#include "SDL.h"
#include "GameObject.h"
#include <ctime>
#include <iostream>
#include "Platform.h"

class Goomba : public GameObject
{
private:
	

	int frame = 0;
	int frameCount = 0;
	int m_moveSpeed = 1;
	//int direction = 1;

	SDL_RendererFlip m_Flip = SDL_FLIP_NONE;
	Platform* m_onPlat = nullptr;
	int hp = 18;

	bool m_Alive = false;

public:
	Goomba()
	{
		rSrc = { 0,0, 49, 67 };
		rDst = { 0,0, 49,67 };
		rDst.x = -100;
		rDst.y = -100;

		ObjInit();
	}

	Goomba(int x, int y)
	{
		rSrc = { 0,0, 49, 67 };
		rDst = { 0,0, 49,67 };

		rDst.x = x;
		rDst.y = y;

		ObjInit();
	}

	void Spawn(int x, int y, Platform* platform)
	{
		m_Alive = true;
		rDst = { x, y, 49, 67 };
		m_onPlat = platform;
		ObjInit();
	}

	void Remove()
	{
		m_Alive = false;
		rDst.x = -100;
		rDst.y = -100;
	}

	bool GetAlive()
	{
		return m_Alive;
	}

	void update(int offsetX, int offsetY)
	{
		if (m_Alive) 
		{
			frameCount++;
			//baseX += direction;
			if (frameCount % 2 == 0)
			{
				if (frame < 9)
				{
					frame++;
				}
				else
				{
					frame = 0;
				}
			}
			rSrc.x = frame * 64;

			/*
			if (baseX >= 1024) //3028
			{
				direction = -1;
			}

			if (baseX <= 0)
			{
				direction = 1;
			}
			*/

			if (rDst.x >= m_onPlat->getDst().w + m_onPlat->getDst().x - rDst.w)
			{
				m_Flip = SDL_FLIP_NONE;
				m_moveSpeed = -1;
			}

			if (rDst.x <= m_onPlat->getDst().x)
			{
				m_Flip = SDL_FLIP_HORIZONTAL;
				m_moveSpeed = 1;
			}
			baseX += m_moveSpeed;
			Scroll(offsetX, offsetY);

			if (m_onPlat != nullptr)
			{
				if (m_onPlat->getXMoving() == true)
				{
					if (m_onPlat->getDirectionX() == true)
					{
						baseX++;
					}
					else
					{
						baseX--;
					}
				}
				if (m_onPlat->getYMoving() == true)
				{
					if (m_onPlat->getDirectionY() == true)
					{
						baseY++;
					}
					else
					{
						baseY--;
					}
				}
			}
		}
/*
		if (hp <= 0)
		{
			Remove();
		}
*/
	}

	int GetMove() { return m_moveSpeed; }

	void OnPlat(Platform* platform)
	{
		m_onPlat = platform;
	}

	int getX()
	{
		return baseX;
	}
	int getY()
	{
		return baseY;
	}
	int GetHP()
	{
		return hp;
	}

	SDL_RendererFlip getFlip()
	{
		return m_Flip;
	}

	SDL_Rect getSrc()
	{
		return rSrc;
	}

	SDL_Rect getDst()
	{
		return rDst;
	}

	void damage(int dmg)
	{
		hp -= dmg;
	}

};

#pragma once
#include "SDL.h"


class Goomblast : public GameObject
{
private:
	
	int frame = 0;
	int frameSkip = 0;

public:

	Goomblast(int x, int y)
	{
		rSrc = { 0,0,192,192 };
		rDst = { 0,0,192,192 };


		baseX = x - 73;
		baseY = y - 130;

		rDst.x = baseX;
		rDst.y = baseY;

		ObjInit();
	}

	SDL_Rect getSrc()
	{
		return rSrc;
	}
	SDL_Rect getDst()
	{
		return rDst;
	}


	void update()
	{
		frameSkip++;

		if (frameSkip % 3 == 0)
		{
			frame++;
			rSrc.x = frame * 192;
		}

	}

};

