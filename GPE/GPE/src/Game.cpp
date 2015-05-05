#include <Game.hpp>
#include <GameState.hpp>

namespace gpe {

	Game::Game() {
		gamestatemanager_ = new GameStateManager("GPE");
		gamestatemanager_handle = gamestatemanager_;
	}

	Game::~Game() {
		delete gamestatemanager_;
	}

	void Game::go() {
		GPE_extern_go();
	}
}