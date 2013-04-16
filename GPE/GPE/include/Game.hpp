#pragma once


#include "GameState.hpp"


class Game
{
public:
	Game();
	~Game();

	void go();

private:
	GameState* m_pGameState;
};
