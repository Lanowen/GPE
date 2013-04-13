//|||||||||||||||||||||||||||||||||||||||||||||||

#include "Game.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

Game::Game()
{
	m_pGameState = 0;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

Game::~Game()
{
	delete m_pGameState;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void Game::go()
{
    m_pGameState = new GameState();

	if(m_pGameState->initOgre("MetroidGame", 0, 0))
		return;
}

//|||||||||||||||||||||||||||||||||||||||||||||||
