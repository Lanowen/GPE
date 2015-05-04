#include <Game.hpp>
#include <GameState.hpp>

namespace gpe {

	Game::Game() {
		gamestatemanager_ = new GameStateManager("GPE");
	}

	Game::~Game() {
		delete gamestatemanager_;
	}

	void Game::go() {
		GameState* testGame = new GameState();

		gamestatemanager_->Start(testGame);
	}
}