#pragma once
#include <GameStateManager.hpp>

extern void GPE_extern_go();

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

	extern GameStateManager* gamestatemanager_handle;
}
