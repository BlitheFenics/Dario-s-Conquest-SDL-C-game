#include "Level.h"
#include "Game.h"

Level::Level()
{
}
void Level::GetCurrLevel()
{
	currentLevel = Game::GetCurrentLevel();
}

Level::~Level()
{
}
