#include "NetworkedObjectManager.hpp"
#include "GameObject.hpp"

namespace gpe {

	NetworkedObjectManager::NetworkedObjectManager() : counter_(0) {
	}

	NetworkedObjectManager::~NetworkedObjectManager() {
	}

	int NetworkedObjectManager::addGameObject(GameObject* obj) {
		obj->netId_ = counter_++;
		objects_[obj->netId_] = obj;

		return obj->netId_;
	}

	void NetworkedObjectManager::addGameObject(int id, GameObject* obj) {
		if (objects_.find(id) == objects_.end()) {
			objects_[id] = obj;
			obj->netId_ = id;
		}
	}

	void NetworkedObjectManager::removeGameObject(int id) {
		std::map<int, GameObject*>::iterator itr;
		if ((itr = objects_.find(id)) != objects_.end()) {
			objects_.erase(itr);
		}
	}

	void NetworkedObjectManager::removeGameObject(GameObject* go) {
		std::map<int, GameObject*>::iterator itr;
		if ((itr = objects_.find(go->netId_)) != objects_.end()) {
			objects_.erase(itr);
		}
	}

	GameObject* NetworkedObjectManager::getGameObject(int id) {
		std::map<int, GameObject*>::iterator itr;
		if ((itr = objects_.find(id)) != objects_.end()) {
			return itr->second;
		}

		return 0;
	}
}