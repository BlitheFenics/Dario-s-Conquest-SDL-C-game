#include "Game.h"
using namespace std;

Game::Game()
{
}

int Game::currentLevel = 0;



void Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_JoystickEventState(SDL_ENABLE);
	SDL_JoystickUpdate();
	cout << SDL_NumJoysticks();

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			controller1 = SDL_GameControllerOpen(i);
			cout << "SUCCESS! HUZZAH!";
		}
		else cout << "FAIL! FUFFAH!";
	}


	pWindow = SDL_CreateWindow("It's Dario's Conquest, motherfucker! Prepare to face your doom! [not affiliated with DOOM.]", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	scoreTimer = new ScoreTimer(pRenderer);
	credit = new Credits(pRenderer);

	highscore = new HighScore(pRenderer);


	levels[0] = new Level(pRenderer, "SunshineStart.png", 0, 0, 0, pfSX0, pfSY0);
	levels[0]->GetPlats(floor);

	ScrollManager::GetScroll()->Reset();
	player.reset();

	ScoreManager::GetInstance(pRenderer)->Render(pRenderer);


	pSurface = IMG_Load("dariosprites.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (pTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);

	//transition.SetTexture(nullptr);
	//transition.SetTexture(pRenderer);

	pSurface = IMG_Load("EyeDeath.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	eTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (eTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);

	pSurface = IMG_Load("Goomba.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	gTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (eTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);

	pSurface = IMG_Load("Goomblast.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	bTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (eTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);

	pSurface = IMG_Load("gameOver.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	goTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (goTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);

	pSurface = IMG_Load("eyeBeam.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	lTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (lTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);

	pSurface = IMG_Load("pauseBG.png");
	if (pSurface == NULL)
		cout << "Surface Fail \n\n";
	pauseBGTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (pauseBGTexture == NULL)
		cout << "Texture fail \n\n";
	SDL_FreeSurface(pSurface);


	pSurface = IMG_Load("pause.png");
	if (pSurface == NULL)
		cout << "Surface Fail \n\n";
	pauseTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (pauseTexture == NULL)
		cout << "Texture fail \n\n";
	SDL_FreeSurface(pSurface);


	pSurface = IMG_Load("tMossy.png");
	if (pSurface == NULL)
		cout << "Surface Fail \n\n";
	tMossy = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (tMossy == NULL)
		cout << "Texture fail \n\n";
	SDL_FreeSurface(pSurface);



	pSurface = IMG_Load("eyeBeam.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	lTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (lTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);



	pSurface = IMG_Load("LogoText.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	ltTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (lTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);


	pSurface = IMG_Load("Logo3.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	sTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (lTexture == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);



	pSurface = IMG_Load("SUCCESS.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	tSuccess = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (tSuccess == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);

	pSurface = IMG_Load("rock_sprite.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	tRock = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	if (tRock == NULL)
		cout << "TEXTURE FAIL \n\n";
	SDL_FreeSurface(pSurface);

	pSurface = IMG_Load("MiniMoss.png");
	if (pSurface == NULL)
		cout << "SURFACE FAIL \n\n";
	MiniMossTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);



	SDL_SetRenderDrawColor(pRenderer, 200, 200, 200, 255);
	SDL_RenderClear(pRenderer);

	// Okay,  now let's try inputs.



	AudioManager::GetInstance()->Music1();


	// Platformer Obj;
	platformer.rDst = { 512, 400, 32, 37 };
	platformer.ObjInit();


	ofstream outFile;
	outFile.open("testFile.txt");
	outFile << "DOES THIS WORK?";
	outFile.close();

	LoadScores();

}

void Game::HandleEvents()
{

	//Bullet count
	/*for (int i = 0; i < 3; i++)
	{

		if (bullet[i] == nullptr)
		{
			bullet[i] = new Bullet;
			bullet[i]->remove();
		}
	}*/


	while (SDL_PollEvent(&event))
	{

		// CONTROLLER CONTROLS ===================================================================================================================
		if(HighScoreOn == true)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				HighScoreOn = false;

			}
		}
		if (CreditsOn == true)
		{

			if (event.type == SDL_KEYDOWN)
			{

				if (event.key.keysym.sym == SDLK_SPACE)
				{
					CreditsOn = false;
					AudioManager::GetInstance()->Music1();
				}
			}
		}

		if (event.type == SDL_CONTROLLERAXISMOTION)
		{
			{
				if (event.caxis.axis == 0)
				{
					if (event.caxis.value > 10000)
					{
						flip = SDL_FLIP_NONE;
						player.moveR();

					}
					else if (event.caxis.value < -10000)
					{
						flip = SDL_FLIP_HORIZONTAL;
						player.moveL();

					}
					else //if (event.caxis.value > -10000 && event.caxis.value < 10000)
					{
						player.stop();
					}
				}
				if (event.caxis.axis == 1)
				{
					if (event.caxis.value > 10000)
					{
						if (currentLevel == 0) // For Pipes in Start screen 
						{
							if (player.getY() < 630 && player.GetGround())
							{
								if (player.getX() < 500 && player.getX() > 300)
								{
									//place highscore screen in here 
									HighScoreOn = true;
								}
								if (player.getX() < 725 && player.getX() > 608)
								{
									levels[0]->StartGame();
									player.reset();
									AudioManager::GetInstance()->Forest();
									cout << "LEVEL LOAD SUCCESS" << (player.getX() < 600 && player.getX() > 300);
								}
								else if (player.getX() < 300)
								{
									AudioManager::GetInstance()->Credits();
									CreditsOn = true;
								}
								else if (player.getX() > 750)
								{
									Exit = true;
									gameOn = false;
									pausing = false;
								}
							}
						}
					}

				}
				if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
				{
					if (event.caxis.value > 8000)
					{
						if (!BulletManager::GetClip()->GetBallistic(0))
						{
							BulletManager::GetClip()->spawn(0, player.getX(), player.getY() + 15, flip);
							//Mix_PlayChannel(1, sFire, 0);

							AudioManager::GetInstance()->Fire();
						}
						else if (!BulletManager::GetClip()->GetBallistic(1))
						{
							BulletManager::GetClip()->spawn(1, player.getX(), player.getY() + 15, flip);
							//Mix_PlayChannel(1, sFire, 0);

							AudioManager::GetInstance()->Fire2();
						}
						else if (!BulletManager::GetClip()->GetBallistic(2))
						{
							BulletManager::GetClip()->spawn(2, player.getX(), player.getY() + 15, flip);
							//Mix_PlayChannel(1, sFire, 0);

							AudioManager::GetInstance()->Fire3();
						}
					}


				}

			}

		}

		if (event.type == SDL_CONTROLLERBUTTONDOWN)
		{

			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
			{
				pauseGame = true;
				gameOn = false;
			}
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
			{
				player.moveL();
				flip = SDL_FLIP_HORIZONTAL;
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
			{
				player.moveR();
				flip = SDL_FLIP_NONE;
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
			{
				player.onSprint();
			}
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
			{
				if (CreditsOn == true)
				{
					AudioManager::GetInstance()->Credits();
					CreditsOn = false;
				}
				if (player.newJump() == true)
				{
					//Mix_PlayChannel(3, sJump, 0);

					AudioManager::GetInstance()->Jump();
				}

			}
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
			{
				if (!BulletManager::GetClip()->GetBallistic(0))
				{
					BulletManager::GetClip()->spawn(0, player.getX(), player.getY() + 15, flip);
					//Mix_PlayChannel(1, sFire, 0);

					AudioManager::GetInstance()->Fire();
				}
				else if (!BulletManager::GetClip()->GetBallistic(1))
				{
					BulletManager::GetClip()->spawn(1, player.getX(), player.getY() + 15, flip);
					//Mix_PlayChannel(1, sFire, 0);

					AudioManager::GetInstance()->Fire2();
				}
				else if (!BulletManager::GetClip()->GetBallistic(2))
				{
					BulletManager::GetClip()->spawn(2, player.getX(), player.getY() + 15, flip);
					//Mix_PlayChannel(1, sFire, 0);

					AudioManager::GetInstance()->Fire3();
				}


			}
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
			{
				if (player.GetSlash() == false)
				{
					//Mix_PlayChannel(1, sSlash, 0);
					int choice = rand() % 2 + 1;
					if (choice == 1 || 0)
					{
						AudioManager::GetInstance()->Slash();
						player.melee();
					}
					if (choice == 2)
					{
						AudioManager::GetInstance()->Slash2();
						player.melee();

					}

				}
			}

		}

		if (event.type == SDL_CONTROLLERBUTTONUP)
		{

			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
			{
				player.Lstop();
			}
			if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
			{
				player.Rstop();
			}
			else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
			{
				player.offSprint();
			}

		}

		// KEYBOARD CONTROLS =====================================================================================================================
		if (event.type == SDL_KEYDOWN)
		{

			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				pauseGame = true;
				gameOn = false;

			}


			if (event.key.keysym.sym == SDLK_a)
			{
				player.moveL();
				flip = SDL_FLIP_HORIZONTAL;
			}
			else if (event.key.keysym.sym == SDLK_d)
			{
				player.moveR();
				flip = SDL_FLIP_NONE;
			}
			else if (event.key.keysym.sym == SDLK_s)
			{
				if (currentLevel == 0) // For Pipes in Start screen 
				{
					if (player.getY() < 630 && player.GetGround())
					{
						if (player.getX() < 500 && player.getX() > 300)
						{
							//place highscore screen in here 
							HighScoreOn = true;
						}
						if (player.getX() < 725 && player.getX() > 608)
						{
							levels[0]->StartGame();
							player.reset();
							cout << "LEVEL LOAD SUCCESS" << (player.getX() < 600 && player.getX() > 300);
						}
						else if (player.getX() < 300)
						{
							AudioManager::GetInstance()->Credits();
							CreditsOn = true;
						}
						else if (player.getX() > 750)
						{
							Exit = true;
							gameOn = false;
							pausing = false;
						}
					}
				}
			}



			/*	if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				gameOn = false;
			}*/

			if (event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_w)
			{
				if (player.newJump() == true)
				{
					//Mix_PlayChannel(3, sJump, 0);

					AudioManager::GetInstance()->Jump();
				}
			}
			if (event.key.keysym.sym == SDLK_j)
			{
				if (!BulletManager::GetClip()->GetBallistic(0))
				{
					BulletManager::GetClip()->spawn(0, player.getX(), player.getY() + 15, flip);
					//Mix_PlayChannel(1, sFire, 0);

					AudioManager::GetInstance()->Fire();
				}
				else if (!BulletManager::GetClip()->GetBallistic(1))
				{
					BulletManager::GetClip()->spawn(1, player.getX(), player.getY() + 15, flip);
					//Mix_PlayChannel(1, sFire, 0);

					AudioManager::GetInstance()->Fire2();
				}
				else if (!BulletManager::GetClip()->GetBallistic(2))
				{
					BulletManager::GetClip()->spawn(2, player.getX(), player.getY() + 15, flip);
					//Mix_PlayChannel(1, sFire, 0);

					AudioManager::GetInstance()->Fire3();
				}


			}
			if (event.key.keysym.sym == SDLK_k)
			{
				if (player.GetSlash() == false)
				{
					//Mix_PlayChannel(1, sSlash, 0);
					int choice = rand() % 2 + 1;
					if (choice == 1 || 0)
					{
						AudioManager::GetInstance()->Slash();
						player.melee();
					}
					if (choice == 2)
					{
						AudioManager::GetInstance()->Slash2();
						player.melee();

					}
				}
			}

			// SPRINT TOGGLE ON/OFF ====================================================

			if (event.key.keysym.sym == SDLK_LSHIFT)
			{
				if (player.GetSprint())
				{
					player.offSprint();
				}
				else if (!player.GetSprint())
				{
					player.onSprint();
				}
			}


		}

		// MOUSE CONTROL ===============================================================

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (!BulletManager::GetClip()->GetBallistic(0))
				{
					BulletManager::GetClip()->spawn(0, player.getX(), player.getY() + 15, flip);
					//Mix_PlayChannel(1, sFire, 0);

					AudioManager::GetInstance()->Fire();
				}
				if (!BulletManager::GetClip()->GetBallistic(1))
				{
					BulletManager::GetClip()->spawn(1, player.getX(), player.getY() + 15, flip);
					//Mix_PlayChannel(1, sFire, 0);

					AudioManager::GetInstance()->Fire2();
				}
				if (!BulletManager::GetClip()->GetBallistic(2))
				{
					BulletManager::GetClip()->spawn(2, player.getX(), player.getY() + 15, flip);
					//Mix_PlayChannel(1, sFire, 0);

					AudioManager::GetInstance()->Fire3();
				}



			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				if (player.GetSlash() == false)
				{
					//Mix_PlayChannel(1, sSlash, 0);
					int choice = rand() % 2 + 1;
					if (choice == 1 || 0)
					{
						AudioManager::GetInstance()->Slash();
						player.melee();
					}
					if (choice == 2)
					{
						AudioManager::GetInstance()->Slash2();
						player.melee();

					}
				}
			}

		}

		// STOPS PLAYER MOVEMENT IF KEY IS LIFTED AFTER BEING PRESSED

		if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_a)
			{
				player.Lstop();
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				player.Rstop();
			}
		}

	}

}

void Game::Update()
{

	if (currentLevel != 0)
	{
		scoreTimer->AddTime();
	}

	//cout << floor[9]->getX() << ", " << floor[9]->getY() << endl;
	int offSetX = 0;
	int offSetY = 0;
	if (currentLevel != 0)
	{
		scoreTimer->Update(pRenderer);
		offSetX = ScrollManager::GetScroll()->OffX();
		offSetY = ScrollManager::GetScroll()->OffY();
		Mix_VolumeMusic(128);
	}
	else
	{
		Mix_VolumeMusic(25);
	}
	//player.Scroll(offSetX, 0);

	if (currentLevel != 0)
	{

		playerHP = levels[currentLevel]->Update(pRenderer, platformer.GetDst(), player.getEdst(), player.GetSlash());
		if (playerHP == 1)
		{
			player.dmg();
			ScrollManager::GetScroll()->SetShake(true);

		}
		else if (playerHP == 3)
		{
			player.addHp();
		}
		// MORE ELSE IFS!!!! HEERERERERERERE!!!!!!!!!
		if (playerHP == 5) // confuse
		{
			player.SetConfused(true);
		}
		else if (playerHP == 6) // slow
		{
			player.SlowDown();
		}

		if (ScrollManager::GetScroll()->GetShake() == true)
		{
			ScrollManager::GetScroll()->ScreenShake();
		}
		/*
					if (levels[currentLevel]->Update(pRenderer, platformer.GetDst(), player.getEdst(), player.GetSlash()) == 1)
					{
					player.dmg();
					}
		*/

		/*if (levels[currentLevel]->Update(pRenderer, platformer, bullet[1]->getDst(), player.getEdst(), player.GetSlash()) == 1)
		{
			player.dmg();
		}
		if (levels[currentLevel]->Update(pRenderer, platformer, bullet[2]->getDst(), player.getEdst(), player.GetSlash()) == 1)
		{
			player.dmg();
		}*/
	}

	for (Platform* p : floor)
	{
		p->Scroll(offSetX, offSetY);

		if (SDL_HasIntersection(&platformer.GetDst(), &p->getDst()))
		{
			if (player.getYvel() > 0 && (p->getY() - player.GetBaseY()) > 20)
			{
				player.fallStop();
				player.setY(p->getTop());
				player.setOnPlat(p);
			}
		}
	}

	grounded = 0;
	for (Platform* p : floor)
	{
		if (SDL_HasIntersection(&platformer.GetDst(), &p->getDst()))
		{
			grounded++;
		}
	}
	if (grounded == 0)
	{
		player.setGround(false);
	}

	player.update(flip, offSetX, offSetY);
	//platformer.Scroll(offSetX, offSetY);
	platformer.rDst.y = player.getY() + 2;
	platformer.rDst.x = player.getX();

	if (player.getHp() == 0)
	{
		if (death == nullptr)
		{
			player.Die();
			death = new Death(player.getX(), player.getY(), pRenderer);

			ScoreManager::GetInstance(pRenderer)->SaveScores();
			//SaveScores();
		}
	}

	if (death != nullptr)
	{
		death->Update();
		if (death->GetY() > 768)
		{
			gameOn = false;
			pausing = false;

			delete(death);
			death = nullptr;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		BulletManager::GetClip()->update(i);

		if (BulletManager::GetClip()->GetEdge(i) == true)
		{
			BulletManager::GetClip()->remove(i);
		}
	}
	if (player.getY() > 760)
	{
		gameOn = false;
		pausing = false;

		ScoreManager::GetInstance(pRenderer)->SaveScores();
	}

	if (currentLevel == 4)
	{
		MossBoss::GetMossy()->ScrollAll(ScrollManager::GetScroll()->OffX(), ScrollManager::GetScroll()->OffY());

		if (SDL_HasIntersection(&platformer.GetDst(), &MossBoss::GetMossy()->GetDst()))
		{
			player.dmg();
			ScrollManager::GetScroll()->SetShake(true);
			if (ScrollManager::GetScroll()->GetShake() == true)
			{
				ScrollManager::GetScroll()->ScreenShake();
			}
		}
		if (SDL_HasIntersection(&platformer.GetDst(), &MossBoss::GetMossy()->GetLeft()))
		{
			player.dmg();

		}
		if (SDL_HasIntersection(&platformer.GetDst(), &MossBoss::GetMossy()->GetRight()))
		{
			player.dmg();

		}

		if (MossBoss::GetMossy()->RockCollide(&platformer.GetDst()))
		{
			player.dmg();

		}

		if (MossBoss::GetMossy()->GetDead() == true)
		{
			gameOn = false;
			pausing = false;
		}
	}

	/*if(transition.GetActive() == true)
	{
		transition.Update();
		transition.Render(pRenderer);
	}*/


	if (levels[currentLevel]->advance())
	{
		/*if (transition.GetActive() == false && transition.GetFinished() == false)
		{
			transition.SetActive(true);
		}*/


		//if (transition.GetFinished() == true)
		//{
		player.reset();
		if (currentLevel < 4)
		{
			delete(levels[currentLevel]);
			levels[currentLevel] = nullptr;
			currentLevel++;
			if (currentLevel == 1)
			{
				ScrollManager::GetScroll()->Reset();
				player.reset();
				
				levels[1] = new Level(pRenderer, "new forest bg (level 1).png", 6, 6, 6, pfX0, pfY0);
				floor[0]->setWidth(1353);
				floor[1]->setWidth(1578);
				floor[8]->setMoving(0, 150);
				floor[9]->setMoving(120, 0);
				floor[10]->setMoving(150, 150);
				floor[14]->setMoving(0, 150);
				levels[1]->GetPlats(floor);
				floor[8]->setMoving(0, 150);
				floor[9]->setMoving(120, 0);
				floor[10]->setMoving(150, 150);
				floor[14]->setMoving(0, 150);
				floor[0]->setWidth(1353);
				floor[1]->setWidth(1578);
				floor[8]->Update();
				floor[9]->Update();
				floor[10]->Update();
				floor[14]->Update();
				AudioManager::GetInstance()->Forest();

			}
			if (currentLevel == 2)
			{
				ScrollManager::GetScroll()->Reset();
				player.reset(60,560);

				levels[2] = new Level(pRenderer, "beer_room.png", 0, 0, 0, pfX1, pfY1);
				if (scoreTimer->GetTime() <= 20)
				{
					ScoreManager::GetInstance(pRenderer)->AddScore(pRenderer, 5);
				}
				floor[0]->setWidth(1024);
				levels[2]->GetPlats(floor);
				floor[0]->setWidth(1024);
				AudioManager::GetInstance()->Music2();
				Mix_HaltChannel(21);

			}
			if (currentLevel == 3)
			{
				player.reset(47, 1400);
				ScrollManager::GetScroll()->SetPrescroll(0, -1000);
				levels[3] = new Level(pRenderer, "level2climb.png", 0, 1, 3, pfX2, pfY2);

				floor[0]->setWidth(1007);
				floor[9]->setMoving(200, 0);
				floor[10]->setMoving(-200, 200);
				floor[11]->setMoving(0, 200);
				floor[12]->setMoving(200, 0);
				floor[13]->setMoving(200, 0);
				floor[14]->setMoving(200, 200);
				floor[15]->setMoving(200, 0);
				floor[16]->setMoving(200, 0);
				floor[17]->setMoving(200, 200);
				floor[18]->setMoving(0, 200);
				levels[3]->GetPlats(floor);
				floor[0]->setWidth(1007);
				floor[9]->setMoving(200, 0);
				floor[10]->setMoving(200, 200);
				floor[11]->setMoving(0, 200);
				floor[12]->setMoving(200, 0);
				floor[13]->setMoving(200, 0);
				floor[14]->setMoving(200, 200);
				floor[15]->setMoving(200, 0);
				floor[16]->setMoving(200, 0);
				floor[17]->setMoving(200, 200);
				floor[18]->setMoving(0, 200);
				floor[9]->Update();
				floor[10]->Update();
				floor[11]->Update();
				floor[12]->Update();
				floor[13]->Update();
				floor[14]->Update();
				floor[15]->Update();
				floor[16]->Update();
				floor[17]->Update();
				floor[18]->Update();



				if (scoreTimer->GetTime() <= 40)
				{
					ScoreManager::GetInstance(pRenderer)->AddScore(pRenderer, 5);
				}
				levels[3]->GetPlats(floor);
				AudioManager::GetInstance()->Alien();
				Mix_HaltChannel(21);
			}
			if (currentLevel == 4)
			{
				ScrollManager::GetScroll()->Reset();
				player.reset(200, 200);
				levels[4] = new Level(pRenderer, "moss_boss_room.png", 0, 1, 0, bpfX, bpfY);

				levels[4]->GetPlats(floor);
				AudioManager::GetInstance()->BossBattle();

			}

			if(currentLevel != 3)
			ScrollManager::GetScroll()->Reset();
		}
		else
		{
			gameOn = false;
			cout << endl << "EVERYTHING SUCKS!!!!" << endl;
			pausing = false;
		}


		//}



	}



	SDL_RenderClear(pRenderer);


}

void Game::Render()
{

	for (int i = 0; i < 20; i++)
	{
		SDL_RenderCopy(pRenderer, pTexture, &floor[i]->getSrc(), &floor[i]->getDst());
	}

	levels[currentLevel]->Render(pRenderer, pTexture, gTexture, eTexture, bTexture, lTexture, MiniMossTexture);

	for (int i = 0; i < 3; i++)
	{
		SDL_RenderCopyEx(pRenderer, pTexture, &BulletManager::GetClip()->GetSrc(i), &BulletManager::GetClip()->GetDest(i), 0, NULL, BulletManager::GetClip()->GetFlip(i));
	}

	// HEARTS 
	if (currentLevel != 0)
	{
		scoreTimer->Render(pRenderer); 
		if (player.getHp() == 3)
		{
			SDL_RenderCopy(pRenderer, pTexture, &hpSR3, &hpDR3);
		}
		else if (player.getHp() == 2)
		{
			SDL_RenderCopy(pRenderer, pTexture, &hpSR2, &hpDR2);
		}
		else if (player.getHp() == 1)
		{
			SDL_RenderCopy(pRenderer, pTexture, &hpSR1, &hpDR1);
		}
	}

	if (player.GetSlash())
	{
		SDL_RenderCopyEx(pRenderer, pTexture, &player.getEsrc(), &player.getEdst(), 0, NULL, flip);
	}

	// SCORE 
	if (currentLevel != 0)
	{
		ScoreManager::GetInstance(pRenderer)->Render(pRenderer);
	}

	if (player.GetAlive() == true)
	{
		if (player.GetFlicker() == false)
		{
			SDL_RenderCopyEx(pRenderer, pTexture, &player.getBsrc(), &player.getBdst(), 0, NULL, flip);

			SDL_RenderCopyEx(pRenderer, pTexture, &player.getSrc(), &player.getDst(), 0, NULL, flip);
		}
	}

	if (death != nullptr)
	{
		death->Render(pRenderer);
	}

	if (CreditsOn == true)
	{
		SDL_RenderClear(pRenderer);
		credit->Render(pRenderer, pTexture, gTexture);
		credit->Update();
	}
	if (HighScoreOn == true)
	{
		SDL_RenderClear(pRenderer);
		highscore->LoadScore();
		highscore->Render(pRenderer);
		
		
		//screen.Render(pRenderer)
	}

	if (currentLevel == 4)
	{
		MossBoss::GetMossy()->Render(pRenderer, tMossy, tRock, player.getX());
	}

	SDL_RenderPresent(pRenderer);
}

bool Game::Start()
{
	Logo logo;
	LogoText logoText;
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	bool choice = false;

	bool playAgain = true;

	ScrollManager::GetScroll()->Reset();

	int LEFT = 220;
	int RIGHT = 650;

	int xVal = 100;
	while (choice == false)
	{
		logo.update();
		logoText.update();

		SDL_RenderClear(pRenderer); //clear the screen to draw color
		SDL_RenderCopy(pRenderer, ltTexture, &logoText.getSrc2(), &logoText.getDst2());
		SDL_RenderCopy(pRenderer, ltTexture, &logoText.getSrc1(), &logoText.getDst1());
		SDL_RenderCopy(pRenderer, sTexture, NULL, &logo.getDst());
		SDL_RenderPresent(pRenderer); // draw anew

		if (logo.getDst().y > 768)
		{
			choice = true;
		}

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
				{
					arrow.SetX(LEFT);
					playAgain = true;
				}
				if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
				{
					arrow.SetX(RIGHT);
					playAgain = false;
				}
				if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE)
				{
					choice = true;
					pausing = true;
				}

			}

			if (event.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
				{
					arrow.SetX(LEFT);
					playAgain = true;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
				{
					arrow.SetX(RIGHT);
					playAgain = false;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
				{
					choice = true;
					pausing = true;
				}

			}

			if (event.type == SDL_CONTROLLERAXISMOTION)
			{
				if (event.caxis.axis == 0)
				{
					if (event.caxis.value < -10000)
					{
						arrow.SetX(LEFT);
						playAgain = true;
					}
					if (event.caxis.value > 10000)
					{
						arrow.SetX(RIGHT);
						playAgain = false;
					}
				}
			}

		}

	}
	return playAgain;

}

//bool Game::HighScores()
//{
//	HighScore screen(pRenderer);
//
//	screen.Render(pRenderer);
//
//	while (SDL_PollEvent(&event))
//	{
//		if (event.type == SDL_KEYDOWN)
//		{
//			return true;
//		}
//	}
//
//
//	return false;
//}

bool Game::Over()
{

	bool choice = false;
	bool playAgain = true;
	int LEFT = 220;
	int RIGHT = 650;
	AudioManager::GetInstance()->Death();
	Mix_HaltChannel(8);
	Mix_HaltChannel(10);
	Mix_HaltChannel(21);
	int xVal = 100;
	while (choice == false)
	{
		arrow.Update();

		SDL_RenderClear(pRenderer);
		SDL_RenderCopy(pRenderer, goTexture, NULL, NULL);

		if (MossBoss::GetMossy()->GetDead() == true)
		{

			SDL_RenderCopy(pRenderer, tSuccess, NULL, NULL);
			SDL_RenderCopy(pRenderer, pTexture, &DarioSrc, &DarioDes);

			cycle++;
			if (cycle % 30 == 0)
			{
				iteration++;
				DarioSrc.x = 32 * (iteration % 4);
			}
			if (cycle == 1500)
			{
				MossBoss::GetMossy()->SetDead();
			}

		}
		else
		{
		SDL_RenderCopy(pRenderer, pTexture, &arrow.GetSrc(), &arrow.GetDst());
		}
		SDL_RenderPresent(pRenderer);

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
				{
					arrow.SetX(LEFT);
					playAgain = true;
				}
				if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
				{
					arrow.SetX(RIGHT);
					playAgain = false;
				}
				if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE)
				{
					choice = true;
					pausing = true;
				}

			}

			if (event.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
				{
					arrow.SetX(LEFT);
					playAgain = true;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
				{
					arrow.SetX(RIGHT);
					playAgain = false;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
				{
					choice = true;
					pausing = true;
				}

			}

			if (event.type == SDL_CONTROLLERAXISMOTION)
			{
				if (event.caxis.axis == 0)
				{
					if (event.caxis.value < -10000)
					{
						arrow.SetX(LEFT);
						playAgain = true;
					}
					if (event.caxis.value > 10000)
					{
						arrow.SetX(RIGHT);
						playAgain = false;
					}
				}
			}

		}

	}
	AudioManager::GetInstance()->Music1();
	return playAgain;

}



void Game::Pause()
{
	bool choice = false;
	int middle = 512;
	Mix_HaltChannel(8);
	Mix_HaltChannel(10);
	Mix_HaltChannel(21);
	Mix_PauseMusic();
	AudioManager::GetInstance()->Pause();

	while (choice == false)
	{
		//std::cout << "Pausing" << std::endl;

		//SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 1);

		SDL_SetTextureAlphaMod(pauseBGTexture, 1);

		SDL_RenderCopy(pRenderer, pauseBGTexture, NULL, NULL);

		SDL_RenderCopy(pRenderer, pauseTexture, NULL, NULL);
		SDL_RenderPresent(pRenderer);


		while (SDL_PollEvent(&event))
		{

			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE)
				{
					pausing = false;
					gameOn = false;
					choice = true;
				}
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					gameOn = true;
					pausing = true;
					pauseGame = false;
					choice = true;

					if (Mix_PauseMusic);
					{
						Mix_ResumeMusic();
						if (currentLevel == 1)
						{
							AudioManager::GetInstance()->Forest();
						}
						if (currentLevel == 2)
						{
							AudioManager::GetInstance()->Music2();
						}

						if (currentLevel == 3)
						{
							AudioManager::GetInstance()->Alien();
						}

						if (currentLevel == 4)
						{
							AudioManager::GetInstance()->BossBattle();
						}
					}
				}
			}
			if (event.type == SDL_CONTROLLERBUTTONDOWN)
			{
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
				{
					pausing = false;
					gameOn = false;
					choice = true;
				}
				if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
				{
					gameOn = true;
					pausing = true;
					pauseGame = false;
					choice = true;
				}
			}
		}
	}
}

void Game::Reset()
{
	ScrollManager::GetScroll()->Reset();
	currentLevel = 0;
	player.reset();
	player.hpReset();
	scoreTimer->Reset(pRenderer);
	levels[0] = new Level(pRenderer, "SunshineStart.png", 0, 0, 0, pfSX0, pfSY0);
	levels[0]->GetPlats(floor);
	//levels[1] = new Level(pRenderer, "stage1.png", 2, 2, pfX0, pfY0);
	//levels[2] = new Level(pRenderer, "level2bg.png", 4, 4, pfX1, pfY1);
	//levels[3] = new Level(pRenderer, "level3bg.png", 6, 6, pfX2, pfY2);
	
	MossBoss::GetMossy()->Reset();

	gameOn = true;

	ScoreManager::GetInstance(pRenderer)->Reset(pRenderer);

}

void Game::Clean()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyTexture(pTexture);
	SDL_DestroyTexture(eTexture);
	SDL_DestroyTexture(gTexture);
	SDL_DestroyTexture(goTexture);
	SDL_DestroyTexture(tTexture);
	SDL_DestroyTexture(tTexture2);
	SDL_DestroyTexture(bTexture);
	SDL_Quit();

}


Game::~Game()
{
}
