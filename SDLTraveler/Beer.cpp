#include "Beer.h"

void Beer::Render(SDL_Renderer* p)
{
	//SDL_RenderCopy(p, BeerTexture, NULL, NULL);
	SDL_RenderCopy(p, BeerTexture, &rSrc, &rDst);
}

void Beer::Update()
{
	
		cycle++;
		if (cycle % 5 == 0) {
			iteration++;
			rSrc.x = 32 * (iteration % 20);
		}
	
}
