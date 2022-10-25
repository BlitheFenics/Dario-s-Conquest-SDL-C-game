#include "Bartender.h"

void Bartender::Update()
{
	cycle++;
	if (cycle % 10 == 0) {
		iteration++;
		rSrc.x = 70 * (iteration % 4);
	}


	speechDst.y = 175 + (10 * sin(iteration * M_PI/180));
}

void Bartender::Render(SDL_Renderer* pRend)
{
	SDL_RenderCopy(pRend, BartenderTexture, &rSrc, &rDst);
	SDL_RenderCopy(pRend, speech, NULL, &speechDst);
}
