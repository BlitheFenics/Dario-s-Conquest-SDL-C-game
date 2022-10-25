#pragma once
#pragma once
#include "SDL.h"
//#include "Game.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include "GameObject.h"
#include "BulletManager.h"
#include "AudioManager.h"

using namespace std;

const int NUMROCKS = 10;

class Rock : public GameObject
{
private:

	int cycle = 0;
	int iteration = 0;

	int angle = 0;
	int orientation = 0;

	int spinDir = 0;

	SDL_Point spawn = { -100,-100 };
	SDL_Point vel = { 0,0 };

	bool up = true;


public:
	Rock()
	{
		rSrc = { 0,0,0,0 };
		rDst = { -100, -100, 50, 50 };

		ObjInit();
	}
	Rock(int x, int y)
	{
		rSrc = { 0,0,0,0 };
		rDst = { -100, -100, 50, 50 };

		spawn.x = x;
		spawn.y = y;


		vel.y = 0;
		vel.x = 0;
	}


	void Spawn()
	{
		rDst.x = spawn.x;
		rDst.y = (spawn.y - 100) + (rand() % 200);

		vel.y = -10;
		vel.x = -3 + (rand() % 7);

		spinDir = 1 - (rand() % 2) * 2;

		std::cout << "SPAWNING ROCK" << endl;
		AudioManager::GetInstance()->Throw();
	}

	void Render(SDL_Renderer* pRend, SDL_Texture* mText)
	{
		Update();
		SDL_RenderCopyEx(pRend, mText, NULL, &rDst, orientation, NULL, SDL_FLIP_NONE);
	}

	void Update()
	{
		orientation += spinDir;
		
		rDst.y += vel.y;
		rDst.x += vel.x;

		if (rDst.y <= -860)
		{
			vel.x = 0;
			vel.y = 8;
		}
	}

};


class MossHand : public GameObject
{
private:

	int homeX;
	int homeY;
	int cycle = 0;
	int iteration = 0;

	SDL_Point targetPlat = { 512, 200 };
	SDL_Point hoverPlat = { 0,0 };

	enum phases { IDLE, SEEKTARGET, HOVER, STRIKE, LAND, RETURN };

	int phase = IDLE;

	int hoverTime = 0;

	SDL_RendererFlip handFlip = SDL_FLIP_NONE;


public:
	MossHand(int x, int y, SDL_RendererFlip f)
	{
		rSrc = { 0,48,68,68 };
		rDst = { 250, 500, 68, 68 };

		homeX = x;
		homeY = y;
		rDst.x = x;
		rDst.y = y;

		ObjInit();

		handFlip = f;
	}

	int GetPhase()
	{
		return phase;
	}

	void AttackPlat(int x, int y)
	{
		targetPlat.x = x;
		targetPlat.y = y;

		hoverPlat.x = x + 32;
		hoverPlat.y = y - 200;

		phase = SEEKTARGET;
	}

	void Render(SDL_Renderer* pRend, SDL_Texture* pText)
	{
		Update();
		SDL_RenderCopyEx(pRend, pText, &rSrc, &rDst, 0, NULL, handFlip);
	}

	void Update()
	{

		switch (phase)
		{
		case IDLE:
		{
			cycle++;
			if (cycle % 5 == 0)
			{
				iteration++;
				if (iteration >= 360)
				{
					iteration = 0;
				}
				baseY = homeY + (10 * cos(iteration));
			}
			break;
		}
		case SEEKTARGET:
		{
			if (baseX > hoverPlat.x)
				baseX--;
			if (baseX < hoverPlat.x)
				baseX++;

			if (baseY > hoverPlat.y)
				baseY--;
			if (baseY < hoverPlat.y)
				baseY++;


			if (baseY == hoverPlat.y && baseX == hoverPlat.x)
			{
				hoverTime = 0;
				phase = HOVER;
			}
			break;
		}
		case HOVER:
		{
			hoverTime++;
			baseY = hoverPlat.y + (5 * cos(hoverTime));

			if (hoverTime == 200)
			{
				phase = STRIKE;
			}

			break;
		}
		case STRIKE:
		{
			baseY += 32;

			if (baseY >= (targetPlat.y - 50))
			{
				phase = LAND;
				hoverTime = 0;
				AudioManager::GetInstance()->GroundHit();
			}

			break;
		}
		case LAND:
		{
			rDst.x = baseX - 40;
			rDst.y = baseY + 20;
			rDst.w = 128;
			rDst.h = 32;
			hoverTime++;

			if (hoverTime == 40)
			{
				phase = RETURN;
				
				rDst.w = 68;
				rDst.h = 68;
			}
			break;
		}
		case RETURN:
		{
			if (baseX > homeX)
				baseX--;
			if (baseX < homeX)
				baseX++;

			if (baseY > homeY)
				baseY--;
			if (baseY < homeY)
				baseY++;


			if (baseY == homeY && baseX == homeX)
			{
				hoverTime = 0;
				phase = IDLE;
			}
		}


		}

	}

};




class MossBoss : public GameObject
{
private:
	MossBoss()
	{

		rSrc = { 0,0,43,39 };
		rDst = { 370, 370, 270, 250 };


		ObjInit();

		for (int i = 0; i < NUMROCKS; i++)//(Rock r : rocks)
		{
			Rock rock(rDst.x + 125, rDst.y + 125);
			rocks[i] = rock;

		}

	}

	static MossBoss* mossy;

	bool dead = false;

	MossHand lefty = { (310), (490), SDL_FLIP_NONE };
	MossHand righty = { (650), (490), SDL_FLIP_HORIZONTAL };

	Rock rocks[NUMROCKS];

	int iteration = 0;

	int hp = 20;

	bool removeBullet = false;
	int bulletCount = 0;

	int attackingPlatform = 0;

	int rightIdle = 0;
	int leftIdle = 0;

	int hurting = 0;

	SDL_RendererFlip flip = SDL_FLIP_NONE;

public:
	static MossBoss* GetMossy();

	~MossBoss() {}

	void RockThrow()
	{
		for (int i = 0; i < NUMROCKS; i++)
		{
			rocks[i].Spawn();
			AudioManager::GetInstance()->Avalanche();
		}

		std::cout << "THROWING ROCKS" << endl;
		/*for (Rock r : rocks)
		{
			r.Spawn();
		}*/
	}

	bool RockCollide(SDL_Rect* p)
	{
		bool collide = false;
		for (Rock r : rocks)
		{
			if (SDL_HasIntersection(p, &r.GetDst()))
			{
				collide = true;
			}
		}
		return collide;
	}

	SDL_Rect GetLeft()
	{
		return lefty.GetDst();
	}
	SDL_Rect GetRight()
	{
		return righty.GetDst();
	}


	void ScrollAll(int x, int y)
	{
		Scroll(x, y);
		lefty.Scroll(x, y);
		righty.Scroll(x, y);

		for (Rock r : rocks)
		{
			r.Scroll(x, y);
		}

	}

	void TakeDamage()
	{
		hp--;
		removeBullet = true;
		bulletCount++;
		int choice = rand() % 2 + 1;
		if (choice == 1 || 0)
		{
			AudioManager::GetInstance()->BossHit();
		}
		if (choice == 2)
		{
			AudioManager::GetInstance()->BossHit2();
		}
	}

	void Update()
	{
		iteration++;
		//cout << iteration << endl;


		if (iteration % 400 == 0)
		{
			RockThrow();
		}

		if (lefty.GetPhase() == 0)
		{
			leftIdle++;
		}

		if (righty.GetPhase() == 0)
		{
			rightIdle++;
		}
		
		if (leftIdle >= 100)
		{

			leftIdle = 0;
			int t = (rand() % 6);


			switch (t)
			{
			case 0:
				lefty.AttackPlat(50, 350);
				AudioManager::GetInstance()->GroundHit();
				break;
			case 1:
				lefty.AttackPlat(150, 450);
				AudioManager::GetInstance()->GroundHit();
				break;
			case 2:
				lefty.AttackPlat(360, 300);
				AudioManager::GetInstance()->GroundHit();
				break;
			case 3:
				lefty.AttackPlat(550, 280);
				AudioManager::GetInstance()->GroundHit();
				break;
			case 4:
				lefty.AttackPlat(700, 450);
				AudioManager::GetInstance()->GroundHit();
				break;
			case 5:
				lefty.AttackPlat(870, 300);
				AudioManager::GetInstance()->GroundHit();
				break;

			}
		}

		if (rightIdle >= 105)
		{
			rightIdle = 0;
			int t = (rand() % 6);


			switch (t)
			{
			case 0:
				righty.AttackPlat(50, 350);
				AudioManager::GetInstance()->GroundHit();
				break;
			case 1:
				righty.AttackPlat(150, 450);
				AudioManager::GetInstance()->GroundHit();
				break;
			case 2:
				righty.AttackPlat(360, 300);
				AudioManager::GetInstance()->GroundHit();
				break;
			case 3:
				righty.AttackPlat(550, 280);
				AudioManager::GetInstance()->GroundHit();
				break;
			case 4:
				righty.AttackPlat(700, 450);
				AudioManager::GetInstance()->GroundHit();
				break;
			case 5:
				righty.AttackPlat(870, 300);
				AudioManager::GetInstance()->GroundHit();
				break;

			}
			
		}


		//cout << "UPDATING BOSS" << endl;

		rDst.h = 240 + (10 * sin(iteration * M_PI / 180));
		//rDst.y = baseY - (10 * sin(iteration * M_PI / 180));
		baseY = 370 - (10 * sin(iteration * M_PI / 180));
	}

	bool GetRemoveBullet()
	{
		return removeBullet;
	}

	void Reset()
	{
		delete(mossy);
		mossy = nullptr;
	}

	void Render(SDL_Renderer* pRend, SDL_Texture* mText, SDL_Texture* mTexture, int playerPos)
	{
		if (hp > 0) 
		{
			Update();
			

			for (int i = 0; i < 3; i++) 
			{
				if (SDL_HasIntersection(&rDst, &BulletManager::GetClip()->GetDest(i)))
				{
					hurting++;
					TakeDamage();
					BulletManager::GetClip()->remove(i);
				}
				
			}

			if (hurting > 0)
			{
				rSrc.x = 48;
				hurting++;
			}

			if (hurting > 10)
			{
				rSrc.x = 0;
				hurting = 0;
			}


			if (playerPos > 512)
			{
				flip = SDL_FLIP_HORIZONTAL;
			}
			else
			{
				flip = SDL_FLIP_NONE;
			}

			SDL_RenderCopyEx(pRend, mText, &rSrc, &rDst, 0, NULL, flip);

			lefty.Render(pRend, mText);
			righty.Render(pRend, mText);
			SDL_SetRenderDrawColor(pRend, 0, 0, 255, 255);

			for (int i = 0; i < NUMROCKS; i++)
			{
				rocks[i].Render(pRend, mTexture);

			}


			if (removeBullet == true)
			{
				bulletCount++;
				if (bulletCount >= 4)
				{
					removeBullet = false;
					bulletCount = 0;
				}
			}

			if (hp == 0)
			{
				AudioManager::GetInstance()->BossDeath();
				
			}

		}
		else
		{
			removeBullet = false;
			dead = true;
		}

	}

	bool GetDead()
	{
		return dead;
	}
	void SetDead()
	{
		dead = false;
	}
};
