#pragma once
#include "GameObject.h"
#include <cmath>

class Vine : public GameObject
{
private:
	int iteration = 0;
public:
	Vine();
	~Vine();
	Vine(int x, int y);

	SDL_Rect GetSrc();
	void SetSrc(SDL_Rect v);
	SDL_Rect GetDst();
	void SetDst(int x, int y);

	void Update(int offX, int offY)
	{
		iteration += 3;

		if (iteration == 361)
		{
			iteration = 0;
		}

		rDst.h = 120 + (10 * sin(iteration * M_PI / 180));
		baseY = 500 - (10 * sin(iteration * M_PI / 180));

		Scroll(offX, offY);
	}
};