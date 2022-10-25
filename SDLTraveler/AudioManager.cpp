#pragma once
#include "SDL_mixer.h"
class AudioManager
{
private:
	AudioManager();

	static AudioManager* AudioMan;

	Mix_Music* sMusic = nullptr;
	Mix_Music* sForest = nullptr;
	Mix_Music* sCombat = nullptr;
	Mix_Music* sDeath = nullptr;
	Mix_Music* sAlien = nullptr;
	Mix_Music* sCredits = nullptr;
	Mix_Music* sBoss = nullptr;
	Mix_Music* sPause = nullptr;
	Mix_Music* sWinState = nullptr;
	Mix_Music* sScores = nullptr;
	Mix_Chunk* sPortal = nullptr;
	Mix_Chunk* sPortal2 = nullptr;
	Mix_Chunk* sOw = nullptr;
	Mix_Chunk* sDying = nullptr;
	Mix_Chunk* sFireball = nullptr;
	Mix_Chunk* sThrow = nullptr;
	Mix_Chunk* sAvalanche = nullptr;
	Mix_Chunk* sBeer = nullptr;
	Mix_Chunk* sBossDeath = nullptr;
	Mix_Chunk* sBossHit = nullptr;
	Mix_Chunk* sBossHit2 = nullptr;
	Mix_Chunk* sGroundHit = nullptr;
	Mix_Chunk* sClang = nullptr;
	Mix_Chunk* sBurn = nullptr;
	Mix_Chunk* sPunch = nullptr;
	Mix_Chunk* sLaser = nullptr;
	Mix_Chunk* sJump = nullptr;
	Mix_Chunk* sFire = nullptr;
	Mix_Chunk* sFire2 = nullptr;
	Mix_Chunk* sfire3 = nullptr;
	Mix_Chunk* sPlat = nullptr;
	Mix_Chunk* sBoom = nullptr;
	Mix_Chunk* sCrackle = nullptr;
	Mix_Chunk* sSlash = nullptr;
	Mix_Chunk* sSlash2 = nullptr;


public:
	static AudioManager* GetInstance();
	/*{
		if (AudioMan == nullptr)
		{
			AudioMan = new AudioManager;

		}
		return AudioMan;
	}
*/


	void Music1();

	void Music2();

	void Scores();

	void WinState();

	void BossBattle();

	void BossDeath();

	void GroundHit();

	void BossHit();

	void BossHit2();

	void Alien();

	void Forest();

	void Death();

	void Credits();

	void Pause();

	void Jump();

	void Fire();

	void Fire2();

	void Fire3();

	void Fireball();

	void Laser();

	void Burn();

	void Beer();

	void Clang();

	void Splat();

	void Boom();

	void Punch();

	void Crackle();

	void Slash();

	void Slash2();

	void Avalanche();

	void Throw();

	void Ow();

	void Portal();

	void Portal2();
	void Dying();

	~AudioManager();
};

