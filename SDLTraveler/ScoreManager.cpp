#include "ScoreManager.h"
using namespace std;
ScoreManager* ScoreManager::instance;


ScoreManager* ScoreManager::GetInstance(SDL_Renderer* pRend)
{
	if (instance == nullptr)
	{
		instance = new ScoreManager(pRend);
	}
	return instance;
}

void ScoreManager::Render(SDL_Renderer* pRend)
{
	SDL_RenderCopy(pRend, tTextureText, NULL, &textR2);
	SDL_RenderCopy(pRend, tTextureScore, NULL, &textR);
}
ScoreManager::ScoreManager(SDL_Renderer* pRend)
{
	TTF_Init();
	font = TTF_OpenFont("SuperMario256.ttf", 24);
	if (font == NULL) {
		cout << "FONT FAIL  1 \n\n";

		cout << SDL_GetError()<<endl;
	}
	tSurface = TTF_RenderText_Solid(font, textScore, white);
	if (tSurface == NULL) {
		cout << "SURFACE FAIL  2 \n\n";
		cout << SDL_GetError();
	}
	tTextureText = SDL_CreateTextureFromSurface(pRend, tSurface);
	if (tTextureText == NULL) {
		cout << "TEXTURE FAIL  3  \n\n";
		cout << SDL_GetError() << endl;
	}
	SDL_FreeSurface(tSurface);


	tSurface = TTF_RenderText_Solid(font, textNum, white);
	if (tSurface == NULL) {
		cout << "SURFACE FAIL  4 \n\n";
		cout << SDL_GetError() << endl;
	}
	tTextureScore = SDL_CreateTextureFromSurface(pRend, tSurface);
	if (tTextureScore == NULL) {
		cout << "TEXTURE FAIL 5  \n\n";
	}
	SDL_FreeSurface(tSurface);

	ifstream inFile;
	inFile.open("highScore.txt", fstream::in);

	inFile >> highScore[0] >> highScore[1] >> highScore[2] >> highScore[3] >> highScore[4];

	inFile.close();

	
}

void ScoreManager::AddScore(SDL_Renderer* pRend, int i)
{
	
	if (score < 999)
	{
		score+=i;
		if (score < 10)
		{
			newScore = "00" + to_string(score);
		}
		else if (score < 100)
		{
			newScore = "0" + to_string(score);
		}
		else
		{
			newScore = to_string(score);
		}
		textNum = newScore.c_str();

		tSurface = TTF_RenderText_Solid(font, textNum, white);
		if (tSurface == NULL) {
			cout << "SURFACE FAIL  4 \n\n";
			cout << SDL_GetError() << endl;
		}
		tTextureScore = SDL_CreateTextureFromSurface(pRend, tSurface);
		if (tTextureScore == NULL) {
			cout << "TEXTURE FAIL 5  \n\n";
			cout << SDL_GetError() << endl;
		}
		SDL_FreeSurface(tSurface);
	}
}

void ScoreManager::SaveScores()
{
	if (score > highScore[0])
	{
		highScore[4] = highScore[3];
		highScore[3] = highScore[2];
		highScore[2] = highScore[1];
		highScore[1] = highScore[0];
		highScore[0] = score;
	}
	else if (score > highScore[1])
	{
		highScore[4] = highScore[3];
		highScore[3] = highScore[2];
		highScore[2] = highScore[1];
		highScore[1] = score;
	}
	else if (score > highScore[2])
	{
		highScore[4] = highScore[3];
		highScore[3] = highScore[2];
		highScore[2] = score;
	}
	else if (score > highScore[3])
	{
		highScore[4] = highScore[3];
		highScore[3] = score;
	}
	else if (score > highScore[4])
	{
		highScore[4] = score;
	}

	ofstream outFile;
	outFile.open("highScore.txt", fstream::out);

	for (int i : highScore)
	{
		outFile << i << endl;
	}

	outFile.close();
}


void ScoreManager::Reset(SDL_Renderer* pRend)
{


	score = 0;
	if (score < 10)
	{
		newScore = "00" + to_string(score);
	}
	else if (score < 100)
	{
		newScore = "0" + to_string(score);
	}
	else
	{
		newScore = to_string(score);
	}
	textNum = newScore.c_str();
	tSurface = TTF_RenderText_Solid(font, textNum, white);
	if (tSurface == NULL) {
		cout << "SURFACE FAIL  4 \n\n";
		cout << SDL_GetError() << endl;
	}
	tTextureScore = SDL_CreateTextureFromSurface(pRend, tSurface);
	if (tTextureScore == NULL) {
		cout << SDL_GetError() << endl;
		cout << "TEXTURE FAIL 5  \n\n";
	}
	SDL_FreeSurface(tSurface);
}
ScoreManager::~ScoreManager() {}

