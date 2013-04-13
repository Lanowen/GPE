//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef OGRE_DEMO_HPP
#define OGRE_DEMO_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameState.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

class Game
{
public:
	Game();
	~Game();

	void go();

private:
	GameState* m_pGameState;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||