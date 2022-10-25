#include "vine.h"

Vine::Vine()
{
	rSrc = { 0, 0,  60, 120 };
	rDst = { 1638, 716, 150, 400 };

	ObjInit();
}

Vine::~Vine()
{

}

Vine::Vine(int x, int y)
{
	rDst.x = x;
	rDst.y = y;
	ObjInit();
}

SDL_Rect Vine::GetSrc()
{
	return rSrc;
}

void Vine::SetSrc(SDL_Rect v)
{
	rSrc = v;
}

SDL_Rect Vine::GetDst()
{
	return rDst;
}

void Vine::SetDst(int x, int y)
{
	rDst.x = x;
	rDst.y = y;
}