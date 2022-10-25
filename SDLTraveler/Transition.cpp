#include "Transition.h"

Transition::Transition()
{

}
Transition::~Transition()
{

}
void Transition::Update()
{
	timer++;
	if(timer == 100)
	{
		isActive = false;
		finished = true;
	}
}
void Transition::Render(SDL_Renderer* pRen)
{
	SDL_RenderCopy(pRen, tTexture, NULL, NULL);


}

