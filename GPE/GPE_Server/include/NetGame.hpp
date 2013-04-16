#pragma once

#include "NetGameState.hpp"

class NetGame
{
public:
	NetGame(){
	m_pGameState = 0;
	}

	~NetGame()
	{
		delete m_pGameState;
	}

	void go(){
		m_pGameState = new NetGameState();

		if(m_pGameState->initOgre("MetroidGame", 0, 0))
			return;
	}

private:
	NetGameState* m_pGameState;
};
