#pragma once
#include <GameStateManager.hpp>

namespace gpe {

	class Game
	{
	public:
		Game();
		~Game();

		void go();

	private:
		GameStateManager* gamestatemanager_;
	};
}
