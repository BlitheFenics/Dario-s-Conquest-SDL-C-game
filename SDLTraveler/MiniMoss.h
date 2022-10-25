#pragma once
#include "SDL.h"
#include "GameObject.h"
#include "Platform.h"

class MiniMoss : public GameObject
{
private:
	int m_moveSpeed = 1;

	SDL_RendererFlip m_Flip = SDL_FLIP_NONE;

	bool m_Alive = false;
	int frame = 0, framecount = 0;
	Platform* m_onPlat = nullptr;

public:
	MiniMoss();
	~MiniMoss();
	//The Getters
	SDL_Rect GetDest() { return rDst; }
	SDL_Rect GetSrc() { return rSrc; }
	int GetMove() { return m_moveSpeed; }
	SDL_RendererFlip GetFlip() { return m_Flip; }
	bool GetAlive() { return m_Alive; }


	void Update(int offsetX, int offsetY);
	void Render();
	void Clean();
	void DeSpawn();
	void Spawn(int x, int y, Platform* platform);
	void OnPlat(Platform* platform);
};
