#include "ScoreTimer.h"


ScoreTimer::ScoreTimer(SDL_Renderer* pRend)
{
	
	TTF_Init();
	font = TTF_OpenFont("SuperMario256.ttf", 24);
	if (font == NULL) {
		std::cout << "FONT FAIL  1 \n\n";

		std::cout << SDL_GetError() << std::endl;
	}
	tSurface = TTF_RenderText_Solid(font, timerText, white);
	if (tSurface == NULL) {
		std::cout << "SURFACE FAIL  2 \n\n";
		std::cout << SDL_GetError();
	}
	tTextureText = SDL_CreateTextureFromSurface(pRend, tSurface);
	if (tTextureText == NULL) {
		std::cout << "TEXTURE FAIL  3  \n\n";
		std::cout << SDL_GetError() << std::endl;
	}
	startTime = SDL_GetTicks();
	SDL_FreeSurface(tSurface);


	tSurface = TTF_RenderText_Solid(font, timerNum, white);
	if (tSurface == NULL) {
		std::cout << "SURFACE FAIL  4 \n\n";
		std::cout << SDL_GetError() << std::endl;
	}
	tTextureTime = SDL_CreateTextureFromSurface(pRend, tSurface);
	if (tTextureTime == NULL) {
		std::cout << "TEXTURE FAIL 5  \n\n";
	}
	SDL_FreeSurface(tSurface);
}

ScoreTimer::ScoreTimer()
{
}

void ScoreTimer::Render(SDL_Renderer* pRend)
{
	SDL_RenderCopy(pRend, tTextureText, NULL, &textR2);
	SDL_RenderCopy(pRend, tTextureTime, NULL, &textR);
}

void ScoreTimer::Reset(SDL_Renderer* pRend)
{
	startTime = SDL_GetTicks();
	time = 0;
	iMilliseconds = 0;
	if (time < 10)
	{
		newTime = "000" + std::to_string(time);
	}
	else if (time < 100)
	{
		newTime = "00" + std::to_string(time);

	}
	else if (time < 1000)
	{
		newTime = "0" + std::to_string(time);
	}
	else
	{
		newTime = std::to_string(time);
	}
	timerNum = newTime.c_str();
	tSurface = TTF_RenderText_Solid(font, timerNum, white);
	if (tSurface == NULL) {
		std::cout << "SURFACE FAIL  4 \n\n";
		std::cout << SDL_GetError() << std::endl;
	}
	tTextureTime = SDL_CreateTextureFromSurface(pRend, tSurface);
	if (tTextureTime == NULL) {
		std::cout << "TEXTURE FAIL 5  \n\n";
		std::cout << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(tSurface);
}

void ScoreTimer::Update(SDL_Renderer* pRend)
{	
	time = iMilliseconds/1000;

	//std::cout << time << std::endl;
	if (time < 10)
	{
		newTime = "000" + std::to_string(time);
	}
	else if (time < 100)
	{
		newTime = "00" + std::to_string(time);

	}
	else if (time < 1000)
	{
		newTime = "0" + std::to_string(time);
	}
	else
	{
		newTime = std::to_string(time);
	}
	timerNum = newTime.c_str();
	tSurface = TTF_RenderText_Solid(font, timerNum, white);
	if (tSurface == NULL) {
		std::cout << "SURFACE FAIL  4 \n\n";
		std::cout << SDL_GetError() << std::endl;
	}
	tTextureTime = SDL_CreateTextureFromSurface(pRend, tSurface);
	if (tTextureTime == NULL) {
		std::cout << "TEXTURE FAIL 5  \n\n";
		std::cout << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(tSurface);
}

void ScoreTimer::AddTime()
{
	iMilliseconds += 16.6666667;

}

