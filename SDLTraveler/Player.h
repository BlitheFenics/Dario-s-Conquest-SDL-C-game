#include "SDL.h"
#include "GameObject.h"
#include "ScrollManager.h"
#include "Platform.h"
#include <iostream>

using namespace std;

class Player : public GameObject
{

private:
	int hp;
	int maxHp;
	int frame = 1;
	int frameSkip = 0;
	int dmgCount = 0;
	bool alive = true;

	int speed = 5;

	bool onGround = false;
	bool sprint = false;

	bool slash = false;
	int slashCount = 0;

	double xVel = 0;
	double yVel = 0;

	bool confused = false;
	/*
	SDL_Rect rSrc;
	SDL_Rect rDst;
	*/

	SDL_Rect bSrc;
	SDL_Rect bDst;

	SDL_Rect eSrc;
	SDL_Rect eDst;

	Platform* onPlat = nullptr; // this is for whichever platform dario is on.

public:

	void  addHp()
	{
		if (hp < 3)
			hp++;
	}

	bool GetGround()
	{
		return onGround;
	}

	Player()
	{
		hp = 3;
		maxHp = 3;

		//rSrc = { 0, 25, 32, 39 };
		//rDst = { 510, 300, 32, 39 };

		rSrc = { 0, 25, 32, 29 };
		rDst = { 510, 300, 32, 29 };

		bSrc = { 0, 54, 32, 12 };
		bDst = { 0, 0, 32, 12 };


		eSrc = { 160, 192, 32, 64 };
		eDst = { 0, 0, 40, 64 };

		ObjInit();
	}

	bool GetSlash()
	{
		return slash;
	}

	int GetBaseY()
	{
		return baseY;
	}

	int GetBaseX()
	{
		return baseX;
	}

	SDL_Rect getBsrc()
	{
		return bSrc;
	}

	SDL_Rect getBdst()
	{
		return bDst;
	}

	SDL_Rect getEsrc()
	{
		return eSrc;
	}

	SDL_Rect getEdst()
	{
		return eDst;
	}

	void setOnPlat(Platform* onPlat)
	{
		this->onPlat = onPlat;
	}

	bool GetSprint()
	{
		return sprint;
	}

	void setY(int y)
	{
		//rDst.y = y;
		baseY = y;
	}

	int getYvel()
	{
		return yVel;
	}

	void setGround(bool b)
	{
		onGround = b;
		if (b == false)
		{
			onPlat = nullptr;
		}
	}

	void update(SDL_RendererFlip f, int x, int y)
	{

		baseX += xVel;
		baseY += yVel;

		Scroll(x, y);

		if (sprint)
		{
			rDst.x += xVel;
			//rDst.y += yVel;
		}

		bDst.x = rDst.x;
		bDst.y = rDst.y + 27;

		eDst.y = rDst.y - 16;
		if (f == SDL_FLIP_NONE)
		{
			eDst.x = rDst.x + 10;
		}
		else
		{
			eDst.x = rDst.x - 20;
		}

		frameSkip++;

		if (alive == true)
		{
			if (onGround == false)
			{
				yVel += 0.5;
			}
		}
		//else
		//{
		//	yVel = 0;
		//}

		if (yVel < 0)
		{
			frame = 5;
			//rSrc.h = 41;
			//rDst.h = 41;
		}
		else
		{
			//rSrc.h = 39;
			//rDst.h = 39;
			if (xVel == 0)
			{
				frame = 0;
			}
			else if (xVel != 0)
			{
				if (frameSkip % (sprint ? 1 : 3) == 0)
				{
					if (frame < 4)
					{
						frame++;
					}
					else
					{
						frame = 1;
					}
				}

			}
		}

		if (slashCount < 4)
		{
			if (frameSkip % 4 == 0)
			{
				slashCount++;
			}
		}
		else
		{
			slash = false;
		}
		//if (!slash)
		//{
			//rSrc.x = 32 * frame;
			//bSrc.x = 32 * frame;
		//}
		if (slash)
		{
			rSrc.x = 224 + slashCount * 32;
			eSrc.x = 32 * slashCount;
		}

		bSrc.x = 32 * frame;


		if (dmgCount > 1 && dmgCount < 50)
		{
			dmgCount++;
		}
		else
		{
			dmgCount = 1;
		}

		if (yVel > 10)
		{
			yVel = 10;
		}

		if (alive == true)
		{

			if (rDst.x > 600 && xVel > 0)
			{
				if (baseX < ScrollManager::GetScroll()->GetLimitR())
					ScrollManager::GetScroll()->Scroll(-5, 0);
			}
			if (rDst.x < 400 && xVel < 0)
			{
				if (baseX > 400)
					ScrollManager::GetScroll()->Scroll(5, 0);
			}




			if (rDst.y > 560 && yVel > 0)
			{
				if (baseY < ScrollManager::GetScroll()->GetLimitB())
					ScrollManager::GetScroll()->Scroll(0, -yVel);
			}
			if (rDst.y < 600 && yVel < 0)
			{
				if (baseY > 600)
					ScrollManager::GetScroll()->Scroll(0, -yVel);
			}






		}

		if (onPlat != nullptr)
		{
			if (onPlat->getXMoving() == true)
			{
				if (onPlat->getDirectionX() == true)
				{
					baseX++;
				}
				else
				{
					baseX--;
				}
			}
			if (onPlat->getYMoving() == true)
			{
				if (onPlat->getDirectionY() == true)
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

	int getHp()
	{
		return hp;
	}

	int getMaxHp()
	{
		return maxHp;
	}

	int getX()
	{
		return rDst.x;
	}

	int getY()
	{
		return rDst.y;
	}

	SDL_Rect getSrc()
	{
		return rSrc;
	}

	SDL_Rect getDst()
	{
		return rDst;
	}

	void moveL()
	{
		xVel = -speed;
	}

	void moveR()
	{
		xVel = speed;
	}

	void moveUp()
	{
		rDst.y -= 5;
	}

	void moveDown()
	{

		rDst.y += 5;
	}

	void stop()
	{
		xVel = 0;
	}

	void Lstop()
	{
		if (xVel < 0)
		{
			xVel = 0;
		}
	}

	void Rstop()
	{
		if (xVel > 0)
		{
			xVel = 0;
		}
	}

	void onSprint()
	{
		//if (onGround)
		{
			sprint = true;
		}
	}

	void offSprint()
	{
		sprint = false;
	}

	bool newJump()
	{
		if (onGround == true)
		{
			onGround = false;
			yVel = -13;

			return true;
		}
		else
		{
			return false;
		}
	}

	void fallStop()
	{
		yVel = 0;
		onGround = true;
	}

	void dmg()
	{
		if (dmgCount == 1)
		{
			hp--;
			dmgCount++;
		}

		//cout << endl << "PLAYER'S CURRENT HP:  " << getHp() << endl;


	}

	bool GetFlicker()
	{
		if (dmgCount != 1)
		{
			if (dmgCount % 2 == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else return false;
	}

	void Die()
	{
		alive = false;
	}

	bool GetAlive()
	{
		return alive;
	}

	void melee()
	{
		slash = true;
		slashCount = 0;
	}

	void hpReset()
	{
		hp = 3;
	}
	void reset(int x = 510, int y = 300)
	{
		//hp = 3;
		alive = true;
		

		yVel = 0;

		baseX - x;
		baseY = y;

		

		Scroll(ScrollManager::GetScroll()->OffX(), ScrollManager::GetScroll()->OffY());

		rSrc = { 0, 25, 32, 29 };
		rDst = { x, y, 32, 29 };

		
		
		ObjInit();
		
		//bSrc = { 0, 54, 32, 12 };
		//bDst = { 0, 0, 32, 12 };


		eSrc = { 160, 192, 32, 64 };
		eDst = { 0, 0, 40, 64 };

		stop();

		ObjInit();
	}

	void SlowDown()
	{
		speed = 3;
	}


	bool GetConfused() { return confused; }
	void SetConfused(bool confuse) { confused = confuse; }

};
