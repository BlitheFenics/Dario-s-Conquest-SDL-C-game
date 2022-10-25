#include "HighScore.h"
#include <SDL_ttf.h>

HighScore::HighScore(SDL_Renderer* pRend)
{
	textR[0] = { 200,150,100,100 };
	textR[1] = { 200,250, 100, 100 };
	textR[2] = { 200,350, 100, 100 };
	textR[3] = { 200,450, 100, 100 };
	textR[4] = { 200,550, 100, 100 };
	textR[5] = { 200,650, 100, 100 };
	textRect = { 100,50, 300, 100 };
	TTF_Init();
	font = TTF_OpenFont("SuperMario256.ttf", 24);
	if (font == NULL) {
		cout << "FONT FAIL  1 \n\n";

		cout << SDL_GetError() << endl;
	}
	tSurface = TTF_RenderText_Solid(font, textScore, white);
	if (tSurface == NULL) {
		cout << "SURFACE FAIL  2 \n\n";
		cout << SDL_GetError();
	}
	tHighScore = SDL_CreateTextureFromSurface(pRend, tSurface);
	SDL_FreeSurface(tSurface);
	for (int i = 0; i < 5; i++)
	{
		tSurface = TTF_RenderText_Solid(font, textHigh, white);
		tHighScoreNum[i] = SDL_CreateTextureFromSurface(pRend, tSurface);
		SDL_FreeSurface(tSurface);

	}
	/*ifstream inFile;
	inFile.open("highScore.txt", fstream::in);

	inFile >> highScore[0] >> highScore[1] >> highScore[2] >> highScore[3] >> highScore[4];

	inFile.close();*/

	LoadScore();

}

void HighScore::LoadScore()
{
	ifstream inFile;
	inFile.open("highScore.txt", fstream::in);

	inFile >> highScore[0] >> highScore[1] >> highScore[2] >> highScore[3] >> highScore[4];

	inFile.close();
}

void HighScore::Render(SDL_Renderer* pRend)
{

	for (int i = 0; i < 6; i++)
	{
		if (highScore[i] < 999)
		{
			if (highScore[i] < 10)
			{
				newHighScore = "00" + to_string(highScore[i]);
			}
			else if (highScore[i] < 100)
			{
				newHighScore = "0" + to_string(highScore[i]);
			}
			else
			{
				newHighScore = to_string(highScore[i]);
			}
			textHigh = newHighScore.c_str();

			tSurface = TTF_RenderText_Solid(font, textHigh, white);
			if (tSurface == NULL) {
				cout << "SURFACE FAIL  4 \n\n";
				cout << SDL_GetError() << endl;
			}

			tHighScoreNum[i] = SDL_CreateTextureFromSurface(pRend, tSurface);
			if (tHighScore == NULL) {
				cout << "TEXTURE FAIL 5  \n\n";
				cout << SDL_GetError() << endl;
			}
			SDL_RenderCopy(pRend, tHighScore, NULL, &textRect);
			SDL_RenderCopy(pRend, tHighScoreNum[i], NULL, &textR[i]);
		}
	}

	SDL_RenderPresent(pRend);
}