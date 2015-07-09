#include "GameState.hpp"

#include "GameObject.hpp"
#include "GPE_Exception.hpp"

namespace gpe {

	GameState::GameState(std::string name) : viewport_(0), target_frame_rate_(1.0 / 60.0), time_since_last_frame_(0), name_(name) {
	}

	GameState::~GameState() {
		for (unsigned int i = 0; i < gameobjects_.size(); i++) {
			gameobjects_[i]->release();
			//delete gameobjects_[i];
		}
	}

	void GameState::AddGameObject(GameObject* go) {
		if (go->released_ == false && go->owner_ != this)
			throw General_Exception("You cannot add a gameobject to two scenes!");
		else if (go->owner_ == this)
			throw General_Exception("You cannot add a gameobject to the same scene twice!");

		go->released_ = false;
		go->owner_ = this;
		gameobjects_.push_back(go);
		go->AddedToState(this);
	}

	void GameState::DeleteGameObject(GameObject* go) {

		if (!physics_scene_->get_fetching_results()) {
			RemoveGameObject(go);
			go->release();
			//delete go;
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
			go->RemovedFromState(this);
			go->released_ = true;
			go->owner_ = 0;
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
		if (gamestatemanager_->get_render_window()->isClosed())
			return false;

		bool res = true;
		time_since_last_frame_ += evt.timeSinceLastFrame;
		
		if(time_since_last_frame_ >= target_frame_rate_) {
			AdvanceSimulation(target_frame_rate_);
			res = Update(target_frame_rate_);
			time_since_last_frame_ = fmod(time_since_last_frame_, target_frame_rate_);
		}		

		if (gameobjects_to_delete_.size() > 0) {
			std::list<GameObject*>::iterator itr = gameobjects_to_delete_.begin();
			for (; itr != gameobjects_to_delete_.end(); itr++) {
				GameObject* temp = *itr;
				RemoveGameObject(temp);
				temp->release();
				//delete temp;
			}
			gameobjects_to_delete_.clear();
		}
		KeyListenerPost();
		MouseListenerPost();
		JoyStickListenerPost();

		return res;
	}

}