#include "GameState.hpp"

#include "GameObject.hpp"

namespace gpe {

	GameState::GameState(std::string name) : viewport_(0), target_frame_rate_(1.0 / 60.0), time_since_last_frame_(0), name_(name) {
	}

	GameState::~GameState() {
		for (unsigned int i = 0; i < gameobjects_.size(); i++) {
			delete gameobjects_[i];
		}
	}

	void GameState::AddGameObject(GameObject* go) {
		go->released = false;
		gameobjects_.push_back(go);		
	}

	void GameState::DeleteGameObject(GameObject* go) {

		if (!physics_scene_->get_fetching_results()) {
			RemoveGameObject(go);
			delete go;
		}
		else {
			if (std::find<std::list<GameObject*>::iterator, GameObject*>(gameobjects_to_delete_.begin(), gameobjects_to_delete_.end(), go) == gameobjects_to_delete_.end()) {
				gameobjects_to_delete_.push_back(go);
			}
		}
	}

	void GameState::RemoveGameObject(GameObject* go) {
		std::vector<GameObject*>::iterator itr = std::find<std::vector<GameObject*>::iterator, GameObject*>(gameobjects_.begin(), gameobjects_.end(), go);
		if (itr != gameobjects_.end()) {
			gameobjects_.erase(itr);
			go->released = true;
		}
	}

	bool GameState::Update(Ogre::Real timeSinceLastFrame) {
		std::vector<GameObject*>::iterator GOItr = gameobjects_.begin();

		for (; GOItr != gameobjects_.end(); GOItr++) {
			(*GOItr)->Update(timeSinceLastFrame);
		}

		return true;
	}

	bool GameState::frameRenderingQueued(const Ogre::FrameEvent& evt) {
		//if (evt.timeSinceLastFrame > 0.5f)
		//	return true;
		if (gamestatemanager_->get_render_window()->isClosed())
			return false;

		bool res = true;
		time_since_last_frame_ += evt.timeSinceLastFrame;
		
		while (time_since_last_frame_ >= target_frame_rate_) {
			AdvanceSimulation(target_frame_rate_);
			res = Update(target_frame_rate_);
			time_since_last_frame_ -= target_frame_rate_;
			if (!res)
				break;
		}		

		if (gameobjects_to_delete_.size() > 0) {
			std::list<GameObject*>::iterator itr = gameobjects_to_delete_.begin();
			for (; itr != gameobjects_to_delete_.end(); itr++) {
				GameObject* temp = *itr;
				RemoveGameObject(temp);
				delete temp;
			}
			gameobjects_to_delete_.clear();
		}
		return res;
	}

}