#pragma once
#include "SDL.h"
#include "Player.h"
#include "BulletManager.h"
#include "Platform.h"
#include "MiniMoss.h"
#include "Enemy.h"
#include "Goomba.h"
#include "EyeBeam.h"
#include "Eyesplosion.h"
#include "Door.h"
#include "Transition.h"
#include "Bartender.h"
//#include "vine.h"
//#include "Goomblast.h"
#include <string>
#include "SDL_image.h"
#include "ScoreManager.h"
//#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Beer.h"
#include "AudioManager.h"
#include "ScrollManager.h"
#include <ctime>
#include <iostream>
#include "Boo.h"

class Level
{
private:
	SDL_Texture* backGround = nullptr;
	SDL_Texture* pf1 = nullptr;
	SDL_Surface* bgSurface = nullptr;
	SDL_Rect cameraRect = { 0, 0, 1024, 768 }; // The render window where everything gets displayed, is able to move and have things move through it in scrolling section
	Beer* beer = nullptr;
	Beer* pickupBeer[3] = { nullptr };
	Bartender* bartender = nullptr;
	Platform* plat[20];
	Enemy* eye[20] = { nullptr };
	Eyesplosion* eyeBoom[20] = { nullptr };
	//Vine vine;
	SDL_Texture* vTexture;
	int popCount[20];
	EyeBeam* beam[20] = { nullptr };
	Goomba* goom[20] = { nullptr };
	Goomblast* goomBoom[20] = { nullptr };
	Boo* ghost[20] = { nullptr };
	int boomCount[20] = { 0 };
	MiniMoss* moss[20] = { nullptr };

	bool started = false;

	int	currentLevel = 0;

	// Stuff for le door
	Door door;
	SDL_Texture* dTexture;
	int levelWidth, levelHeight; // This gets set to the height and width of whatever level the player is on
	bool levelAdvance = false;
	bool beerTaken = false;

	int startTime;
	int MAXEYES = 0;
	int MAXGOOMS = 0;
	int MAXMOSS = 20;
	int MAXBOOS = 0;

	int endScore = 0;
	int kills = 0;

	int playerDamage = 0;
	bool removeBullet = false;

	const char* num = "000";
	int iNum = 0;
	std::string newNum;

	const char* num2 = "SCORE:";
	int iNum2 = 0;
	std::string newNum2;

	TTF_Font* font1 = nullptr;
	SDL_Color white = { 0,0,0 };
	SDL_Surface* lSurface = nullptr;
	SDL_Texture* tTexture = nullptr;
	SDL_Texture* tTexture2 = nullptr;
	SDL_Texture* booTexture = nullptr;
	//Transition transition;

	//string numberText;

	SDL_Rect textR = { 170, 40 ,100,50 };
	SDL_Rect textR2 = { 64,50,100, 25 };

public:
	void StartGame()
	{
		//kills = 1;
		levelAdvance = true;
	}
	Level();

	void GetCurrLevel();

	Level(SDL_Renderer* pRend, const char* bgName, int MAXEYES, int MAXGOOMS, int MAXBOOS, int platX[], int platY[])
	{
		GetCurrLevel();
		std::cout << endl << "COMMENCING LEVEL" << endl;

		srand(time(NULL));
		startTime = SDL_GetTicks();
		bgSurface = IMG_Load(bgName);

		if (bgSurface == nullptr)
		{
			std::cout << "BACKGROUND SURFACE FAIL!" << std::endl << std::endl;
		}
		backGround = SDL_CreateTextureFromSurface(pRend, bgSurface); // converts the background from an sdl surface to an sdl texture
		if (backGround == nullptr)
		{
			std::cout << "BACKGROUND TEXTURE FAIL!" << std::endl << std::endl;
			std::cout << SDL_GetError();
		}

		bgSurface = IMG_Load("Tree_Platform.png");
		if (bgSurface == nullptr)
		{
			std::cout << "PLATFORM SURFACE FAIL!" << std::endl << std::endl;
		}
		pf1 = SDL_CreateTextureFromSurface(pRend, bgSurface);
		if (pf1 == nullptr)
		{
			std::cout << "PLATFORM TEXTURE FAIL!" << std::endl << std::endl;
			std::cout << SDL_GetError();
		}
		// Door stuff
		bgSurface = IMG_Load("Door_Sprite.png");
		if (bgSurface == nullptr)
		{
			std::cout << "PLATFORM SURFACE FAIL!" << std::endl << std::endl;
		}
		dTexture = SDL_CreateTextureFromSurface(pRend, bgSurface);
		if (dTexture == nullptr)
		{
			std::cout << "PLATFORM TEXTURE FAIL!" << std::endl << std::endl;
			std::cout << SDL_GetError();
		}
		// Vine stuff
		bgSurface = IMG_Load("Vine4.png");
		if (bgSurface == nullptr)
		{
			std::cout << "PLATFORM SURFACE FAIL!" << std::endl << std::endl;
		}
		vTexture = SDL_CreateTextureFromSurface(pRend, bgSurface);
		if (vTexture == nullptr)
		{
			std::cout << "PLATFORM TEXTURE FAIL!" << std::endl << std::endl;
			std::cout << SDL_GetError();
		}

		for (int i = 0; i < 20; i++)
		{
			plat[i] = new Platform;
			plat[i]->setPlatform(platX[i], platY[i]);
		}
		// Boo texture
		bgSurface = IMG_Load("Boo.png");
		if (bgSurface == nullptr)
		{
			std::cout << "PLATFORM SURFACE FAIL!" << std::endl << std::endl;
		}
		booTexture = SDL_CreateTextureFromSurface(pRend, bgSurface);
		if (booTexture == nullptr)
		{
			std::cout << "PLATFORM TEXTURE FAIL!" << std::endl << std::endl;
			std::cout << SDL_GetError();
		}
		SDL_FreeSurface(bgSurface);

		

		for (int i = 0; i < 20; i++)
		{
			plat[i] = new Platform;
			plat[i]->setPlatform(platX[i], platY[i]);
		}

		//SDL_FreeSurface(transition.GetSurface());

		this->MAXEYES = MAXEYES;
		this->MAXGOOMS = MAXGOOMS;
		this->MAXBOOS = MAXBOOS;

		endScore = MAXEYES + MAXGOOMS;

		SDL_QueryTexture(backGround, NULL, NULL, &levelWidth, &levelHeight); // gets the height and width of the texture

		ScrollManager::GetScroll()->SetLimits(levelWidth, levelHeight);

		ScrollManager::GetScroll()->CheckBoundary();
	}

	void GetPlats(Platform* pf[])
	{
		for (int i = 0; i < 20; i++)
		{
			pf[i] = plat[i];
		}
	}

	int Update(SDL_Renderer* pRend, SDL_Rect p, SDL_Rect s, bool slash)
	{
		

		playerDamage = 0;
		removeBullet = false;

		// SCROLLING:
		// Allows for scrolling based off dario

		int offSetX = ScrollManager::GetScroll()->OffX();
		int offSetY = ScrollManager::GetScroll()->OffY();
		
		
		cameraRect.x = 0 - offSetX;
		cameraRect.y = 0 - offSetY;
		if (kills == endScore)
		{
			door.SetOpen(true);
			if (beer == nullptr && beerTaken == false)
			{
				beer = new Beer(pRend, 0);
				if (currentLevel == 1)
					beer->SetDst(3750, 66);
				if (currentLevel == 2)
					beer->SetDst(-100, -100);
				if (currentLevel == 3)
					beer->SetDst(450, 100);

			}

		}
		if (door.GetOpen() == true)
		{
			// Selecting random plat and spawns door on it
			
			 //////////// NEEDS FIXING BUT WORKS ATM ////////////////////////
			//door.Update(offSetX, offSetY);
			//SDL_RenderCopy(pRend, dTexture, &door.GetSrc(), &door.GetDst());
			if (SDL_HasIntersection(&door.GetDst(), &p))
			{
				levelAdvance = true;
				AudioManager::GetInstance()->Portal2();
			}
		}
		if (currentLevel == 1)
		{
			door.SetDst(3900, 25);
		}
		if (currentLevel == 2)
		{
			if (started == false)
			{
				door.SetDst(100, 450);
				for (int i = 0; i < 3; i++)
				{
					if (pickupBeer[i] == nullptr)
						pickupBeer[i] = new Beer(pRend, rand() % 5);
				}
				pickupBeer[0]->SetDst(350, 430);
				pickupBeer[1]->SetDst(550, 430);
				pickupBeer[2]->SetDst(750, 430);

				if (bartender == nullptr)
					bartender = new Bartender(pRend);

				started = true;
			}

			if (bartender != nullptr)
				bartender->Update();

			for(Beer* b :pickupBeer)
			{
				b->Update();

				if(SDL_HasIntersection(&b->GetDst(), &p))
				{
					switch(b->GetType())
					{
						case 0: // regular
							playerDamage = 3;
							break;
						case 1: // iron
							break;
						case 2: // confuse
							playerDamage = 5;
							break;
						case 3: // poison
							playerDamage = 1;
							break;
						case 4: // strength
							playerDamage = 7;
							break;
						case 5: // slow
							playerDamage = 6;
							break;
					}
					pickupBeer[0]->Remove();
					pickupBeer[1]->Remove();
					pickupBeer[2]->Remove();
				}
			}
		}
		if (currentLevel == 3)
		{
			door.SetDst(300, 10);
		}

		// Keeps the camera from scrolling past the level


		if (cameraRect.x < 0)
		{
			cameraRect.x = 0;
		}
		if (cameraRect.y < 0)
		{
			cameraRect.y = 0;
		}





		// Stops the camera from scrolling once it reaches the edge of the level

		if (cameraRect.x + cameraRect.w >= levelWidth)
		{
			cameraRect.x = levelWidth - 1024;

		}
		if (cameraRect.y + cameraRect.h >= levelHeight)
		{
			cameraRect.y = levelHeight - 768;
		}

		// Door scroll

		door.Scroll(offSetX, offSetY);
		/*
				if (p.x > 600)
				{
					offSetX = 600 - p.x;
				}
		*/
		// "SCROLLING" her

		// SCROLLING PLATFORMS
		for (Platform* pf : plat)
		{
			pf->Scroll(offSetX, offSetY);
		}

		//SCROLLING GOOMBAS
		for (int i = 0; i < MAXGOOMS; i++)
		{
			if (goom[i] != nullptr)
			{
				goom[i]->Scroll(offSetX, offSetY);
			}
			if (goomBoom[i] != nullptr)
			{
				goomBoom[i]->Scroll(offSetX, offSetY);
			}
		}

		//SCROLLING EYES
		for (int i = 0; i < MAXEYES; i++)
		{
			if (eye[i] != nullptr)
			{
				eye[i]->Scroll(offSetX, offSetY);
			}
			if (eyeBoom[i] != nullptr)
			{
				eyeBoom[i]->Scroll(offSetX, offSetY);
			}
			if (beam[i] != nullptr)
			{
				beam[i]->Scroll(offSetX, offSetY);
			}
		}

		//SCROLLING MOSSES
		for (int i = 0; i < MAXMOSS; i++)
		{
			if (moss[i] != nullptr)
			{
				moss[i]->Scroll(offSetX, offSetY);
			}
		}

		if (beer)
		{
			beer->Scroll(offSetX, offSetY);
		}

		//vine.Update(offSetX, offSetY);

		// END SCROLL STUFF

		// Delayed spawn for eyes 
		for (int i = 0; i < MAXEYES; i++)
		{
			if (eye[i] == nullptr)
			{
				if (SDL_GetTicks() > startTime + (i * 3000))
				{
					eye[i] = new Enemy;
					eye[i]->Spawn();
				}
			}
		}
		// Update for Eye
		for (int i = 0; i < MAXEYES; i++)
		{
			if (eye[i] != nullptr)
			{
				eye[i]->update(p.x, p.y);
			}
		}
		// Delayed Goomba spawn
		for (int i = 0; i < MAXGOOMS; i++)
		{
			if (goom[i] == nullptr)
			{
				//if (SDL_GetTicks() > startTime + (i * 3000))
				{
					goom[i] = new Goomba(/*-100, -100*/);
					//goom[i]->Spawn();
					if (plat[i] != nullptr)
					{
						int ground = (8 + rand() % 12);
						goom[i]->Spawn(plat[ground]->rDst.x -67, plat[ground]->rDst.y -67, plat[ground]); // To be changed
					}
				}
			}
		}

		// Delayed Boo spawn
		for (int i = 0; i < MAXBOOS; i++)
		{
			if (ghost[i] == nullptr)
			{
				if (SDL_GetTicks() > startTime + (i * 3000))
				{
					ghost[i] = new Boo(rand() % levelWidth, 300, levelHeight);
					//ghost[i]->ReSpawn();
				} 
			}
		}

		// Update for Boos
		for (int i = 0; i < MAXBOOS; i++)
		{
			if (ghost[i] != nullptr)
			{
			

				ghost[i]->Update(offSetX,offSetY);

				if (SDL_HasIntersection(&p, ghost[i]->GetFlameBox()))
				{
					playerDamage = 1;
					AudioManager::GetInstance()->Punch();
					AudioManager::GetInstance()->Ow();
				}

				if (SDL_HasIntersection(&p, &ghost[i]->GetDst()))
				{
					playerDamage = 1;
					AudioManager::GetInstance()->Punch();
					AudioManager::GetInstance()->Ow();
				}

			}
		}

		// Update for Gooms
		for (int i = 0; i < MAXGOOMS; i++)
		{
			if (goom[i] != nullptr)
			{
				if (goom[i]->GetAlive())
				{
					goom[i]->update(offSetX, offSetY);

					if (SDL_HasIntersection(&p, &goom[i]->getDst()))
					{
						playerDamage = 1;
						AudioManager::GetInstance()->Punch();
						AudioManager::GetInstance()->Ow();
					}
				}
			}
		}
		
		// Delayed moss spawn
		if (levelHeight > 1050)
		{
			for (int i = 0; i < MAXMOSS; i++)
			{
				if (moss[i] == nullptr && i % 2)
				{
					moss[i] = new MiniMoss();
					if (plat[i] != nullptr && i % 2)
					{
						moss[i]->Spawn(plat[i]->rDst.x - 32, plat[i]->rDst.y - 32, plat[i]); // To be changed
					}
				}
			}
			// Update for mosses
			for (int i = 0; i < MAXMOSS; i++)
			{
				if (moss[i] != nullptr)
				{
					if (moss[i]->GetAlive())
					{
						moss[i]->Update(offSetX, offSetY);

						if (SDL_HasIntersection(&p, &moss[i]->GetDest()))
						{
							playerDamage = 1;
							//AudioManager::GetInstance()->Punch();
						}
					}
				}
			}
		}

		for (int i = 0; i < MAXEYES; i++)
		{
			if (eye[i] != nullptr)
			{
				if (eye[i]->GetAlive())
				{
					eye[i]->update(p.x, p.y);

					if (SDL_HasIntersection(&p, &eye[i]->getDst()))
					{
						playerDamage = 1;
						AudioManager::GetInstance()->Burn();
					}

					if (eye[i]->GetOnTarget() == 1 && eye[i]->GetOnScreen())
					{
						if (!beam[i])
						{
							beam[i] = new EyeBeam(eye[i]->GetDX(), eye[i]->GetDY(), eye[i]->getFlip());
							AudioManager::GetInstance()->Laser();
							AudioManager::GetInstance()->Ow();
						}
					}

				}
			}
		}

		if (slash)
		{
			for (int i = 0; i < MAXGOOMS; i++)
			{
				if (goom[i] != nullptr)
				{
					if (goom[i]->GetAlive())
					{
						if (SDL_HasIntersection(&goom[i]->getDst(), &s))
						{
							int chance;
							chance = rand() % 2 + 1;
							//cout << chance << endl;

							if (chance == 1 || 0)
							{
								goom[i]->damage(0);
								Mix_HaltChannel(4);
								AudioManager::GetInstance()->Clang();
							}

							else if (chance == 2);
							{
								goom[i]->damage(1);
								AudioManager::GetInstance()->Crackle();
								//GoombaHP--;
								//delete(bullet);
								//bullet = nullptr;
							}

							//Mix_PlayChannel(4, sCrackle, 0);

							if (goom[i]->GetHP() == 0)
							{
								goomBoom[i] = new Goomblast(goom[i]->getX(), goom[i]->getY());
								boomCount[i] = 0;

								goom[i]->Remove();
								kills++;
								ScoreManager::GetInstance(pRend)->AddScore(pRend, 1);
								//bullet = nullptr;

							}
						}
					}
				}

				if (ghost[i] != nullptr)
				{
					if (SDL_HasIntersection(&ghost[i]->GetDst(), &s))
					{
						ghost[i]->Remove();
						kills++;

						ScoreManager::GetInstance(pRend)->AddScore(pRend, 2);
					}
				}

				if (eye[i] != nullptr)
				{
					if (eye[i]->GetAlive())
					{
						if (SDL_HasIntersection(&eye[i]->getDst(), &s))
						{
							eyeBoom[i] = new Eyesplosion(eye[i]->getX(), eye[i]->getY(), eye[i]->getFlip());
							popCount[i] = 0;

							//Mix_PlayChannel(2, sBoom, 0);

							AudioManager::GetInstance()->Boom();

							eye[i]->Remove();

							kills++;
							ScoreManager::GetInstance(pRend)->AddScore(pRend, 2);
							//delete(bullet);
							//bullet = nullptr;


							if (iNum < 999)
							{
								iNum++;
								if (iNum < 10)
								{
									newNum = "00" + std::to_string(iNum);
								}
								else if (iNum < 100)
								{
									newNum = "0" + std::to_string(iNum);
								}
								else
								{
									newNum = std::to_string(iNum);
								}
								num = newNum.c_str();

								
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < MAXBOOS; i++)
		{
			if (ghost[i] != nullptr)
			{

				for (int b = 0; b < 3; b++)
				{

					if (SDL_HasIntersection(&BulletManager::GetClip()->GetDest(b), &ghost[i]->GetDst()))
					{
						ghost[i]->Remove();

						kills++;
						BulletManager::GetClip()->remove(b);


						ScoreManager::GetInstance(pRend)->AddScore(pRend, 2);
					}
				}
			}
		}

		for (int i = 0; i < MAXEYES; i++)
		{
			for (int b = 0; b < 3; b++)
			{


				if (eye[i] != nullptr)
				{
					if (eye[i]->GetAlive())
					{
						if (SDL_HasIntersection(&BulletManager::GetClip()->GetDest(b), &eye[i]->getDst()))
						{
							eyeBoom[i] = new Eyesplosion(eye[i]->getX(), eye[i]->getY(), eye[i]->getFlip());
							popCount[i] = 0;

							//Mix_PlayChannel(2, sBoom, 0);

							AudioManager::GetInstance()->Boom();

							eye[i]->Remove();
							kills++;
							BulletManager::GetClip()->remove(b);
							//removeBullet = true;

							ScoreManager::GetInstance(pRend)->AddScore(pRend, 2);
							if (iNum < 999)
							{
								iNum++;
								if (iNum < 10)
								{
									newNum = "00" + std::to_string(iNum);
								}
								else if (iNum < 100)
								{
									newNum = "0" + std::to_string(iNum);
								}
								else
								{
									newNum = std::to_string(iNum);
								}
								num = newNum.c_str();

								
							}

						}
					}
				}
			}
		}


		for (int i = 0; i < MAXGOOMS; i++)
		{
			for (int b = 0; b < 3; b++)
			{
				if (goom[i] != nullptr)
				{
					if (goom[i]->GetAlive())
					{
						if (SDL_HasIntersection(&BulletManager::GetClip()->GetDest(b), &goom[i]->getDst()))
						{
							goom[i]->damage(6);

							BulletManager::GetClip()->remove(b);
							//removeBullet = true;

							//Mix_PlayChannel(4, sCrackle, 0);

							AudioManager::GetInstance()->Crackle();

							if (goom[i]->GetHP() <= 0)
							{
								goomBoom[i] = new Goomblast(goom[i]->getX(), goom[i]->getY());
								boomCount[i] = 0;

								goom[i]->Remove();
								kills++;
								ScoreManager::GetInstance(pRend)->AddScore(pRend, 1);
								//bullet = nullptr;

								if (iNum < 999)
								{
									iNum++;
									if (iNum < 10)
									{
										newNum = "00" + std::to_string(iNum);
									}
									else if (iNum < 100)
									{
										newNum = "0" + std::to_string(iNum);
									}
									else
									{
										newNum = std::to_string(iNum);
									}
									num = newNum.c_str();

									
								}


							}
						}
					}
				}
			}
		}

		for (int i = 0; i < MAXGOOMS; i++) {
			if (goomBoom[i])
			{
				goomBoom[i]->update();
				boomCount[i]++;

				if (boomCount[i] == 30)
				{
					//Mix_PlayChannel(5, sPlat, 0);

					AudioManager::GetInstance()->Splat();

				}
				if (boomCount[i] == 60)
				{
					delete(goomBoom[i]);
					goomBoom[i] = nullptr;

				}

			}
		}

		for (int i = 0; i < MAXEYES; i++)
		{
			if (eyeBoom[i])
			{
				eyeBoom[i]->update();
				popCount[i]++;

				if (popCount[i] == 24)
				{
					delete(eyeBoom[i]);
					eyeBoom[i] = nullptr;

				}

			}
		}

		/*
		if (player.getY() >= -37 + floor[0].getTop())
		{
			player.fallStop();
			player.setY(-37 + floor[0].getTop());
		}
		*/
		for (int i = 0; i < MAXEYES; i++)
		{
			if (beam[i])
			{
				if (eye[i] != nullptr)
				{
					if (eye[i]->GetAlive())
					{
						if (beam[i]->Update(eye[i]->GetDX(), eye[i]->GetDY(), eye[i]->getFlip()) == 1)
						{
							if (SDL_HasIntersection(&beam[i]->GetbDst(), &p))
							{
								playerDamage = 1;
							}
						}
						if (beam[i]->GetStatus() == 2)
						{
							delete(beam[i]);
							beam[i] = nullptr;
						}
					}
					else
					{
						delete(beam[i]);
						beam[i] = nullptr;
						Mix_HaltChannel(8);
					}
				}
			}
		}


		if (beer)
		{
			beer->Update();
			if (SDL_HasIntersection(&p, &beer->GetDst()))
			{
				playerDamage = 3;
				AudioManager::GetInstance()->Beer();
				delete(beer);
				beer = nullptr;
				beerTaken = true;
			}
		}
		/*plat[9]->Update();
		plat[12]->Update();
		plat[16]->Update();
		plat[15]->Update();*/

		for (int i = 0; i < 20; i++)
		{
			plat[i]->Update();
			plat[i]->Scroll(offSetX, offSetY);
		}

		return playerDamage;
	}

	void Render(SDL_Renderer * pRen, SDL_Texture * eyeText, SDL_Texture * goomText, SDL_Texture * eyePopText,
		SDL_Texture * goomBlastText, SDL_Texture * eyeBeamText, SDL_Texture * minimoss)
	{
		SDL_RenderCopy(pRen, backGround, &cameraRect, NULL);
		//SDL_RenderCopy(pRen, vTexture, &vine.GetSrc(), &vine.GetDst());
		if (MAXGOOMS > 0)
		{
			for (int i = 8; i < 20; i++)
			{
				SDL_RenderCopy(pRen, pf1, &plat[i]->getSrc(), &plat[i]->getDst());
			}
		}
		for (int i = 0; i < MAXEYES; i++)
		{
			if (eyeBoom[i])
			{
				SDL_RenderCopyEx(pRen, eyePopText, &eyeBoom[i]->getSrc(), &eyeBoom[i]->getDst(), 0, NULL, eyeBoom[i]->getFlip());
			}
		}
		for (int i = 0; i < MAXGOOMS; i++)
		{
			if (goomBoom[i])
			{
				SDL_RenderCopyEx(pRen, goomBlastText, &goomBoom[i]->getSrc(), &goomBoom[i]->getDst(), 0, NULL, SDL_FLIP_NONE);
			}
		}
		for (int i = 0; i < MAXGOOMS; i++)
		{
			if (goom[i] != nullptr)
			{
				if (goom[i]->GetAlive())
				{
					SDL_RenderCopyEx(pRen, goomText, &goom[i]->getSrc(), &goom[i]->getDst(), 0, NULL, goom[i]->getFlip());
				}
			}
		}
		for (int i = 0; i < MAXEYES; i++)
		{
			if (eye[i] != nullptr)
			{
				if (eye[i]->GetAlive())
				{
					SDL_RenderCopyEx(pRen, eyeText, &eye[i]->getSrc(), &eye[i]->getDst(), 0, NULL, eye[i]->getFlip());
				}
			}
		}
		for (int i = 0; i < MAXEYES; i++)
		{
			if (beam[i])
			{
				SDL_RenderCopyEx(pRen, eyeBeamText, &beam[i]->GeteSrc(), &beam[i]->GeteDst(), 0, NULL, beam[i]->GetFlip());

				if (beam[i]->GetStatus() == 1)
				{
					SDL_RenderCopyEx(pRen, eyeBeamText, &beam[i]->GetbSrc(), &beam[i]->GetbDst(), 0, NULL, beam[i]->GetFlip());
				}
			}
		}
		for (int i = 0; i < MAXMOSS; i++)
		{
			if (moss[i] != nullptr)
			{
				SDL_RenderCopyEx(pRen, minimoss, &moss[i]->GetSrc(), &moss[i]->GetDest(), 0, NULL, moss[i]->GetFlip());
			}
		}
		
		for (int i = 0; i < MAXBOOS; i++)
		{
			if (ghost[i] != nullptr)
			{
				ghost[i]->Render(pRen, booTexture);
			}
		}

		if (bartender != nullptr)
			bartender->Render(pRen);


		if (beer)
		{
			beer->Render(pRen);
		}
		// here
		if (pickupBeer[0] != nullptr && pickupBeer[1] != nullptr && pickupBeer[2] != nullptr)
		{
			for (int i = 0; i < 3; i++)
			{
				pickupBeer[i]->Render(pRen);
			}
		}

		SDL_RenderCopy(pRen, tTexture, NULL, &textR);
		SDL_RenderCopy(pRen, tTexture2, NULL, &textR2);
		if (door.GetOpen() == true)
		{
			SDL_RenderCopy(pRen, dTexture, &door.GetSrc(), &door.GetDst());
			AudioManager::GetInstance()->Portal();
		}
		door.animate();

	}

	bool advance()
	{
		return levelAdvance;
	}

	int GetRemoveBullet()
	{
		return removeBullet;
	}

	~Level();
};

