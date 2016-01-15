#include "stdafx.h"

#include "NetworkedObjectManager.hpp"
#include "GameObject.hpp"

namespace gpe {

	NetworkedObjectManager::NetworkedObjectManager() : counter_(0) {
	}

	NetworkedObjectManager::~NetworkedObjectManager() {
	}

	int NetworkedObjectManager::addGameObject(GameObject* obj) {
		obj->net_id_ = counter_++;
		objects_[obj->net_id_] = obj;
		obj->net_owned_ = true;
		return obj->net_id_;
	}

	void NetworkedObjectManager::addGameObject(int id, GameObject* obj) {
		if (objects_.find(id) == objects_.end()) {
			objects_[id] = obj;
			obj->net_owned_ = true;
			obj->net_id_ = id;
		}
	}

	void NetworkedObjectManager::removeGameObject(int id) {
		std::map<int, GameObject*>::iterator itr;
		if ((itr = objects_.find(id)) != objects_.end()) {
			(*itr).second->net_owned_ = false;
			objects_.erase(itr);
		}
	}

	void NetworkedObjectManager::removeGameObject(GameObject* go) {
		std::map<int, GameObject*>::iterator itr;
		if ((itr = objects_.find(go->net_id_)) != objects_.end()) {
			(*itr).second->net_owned_ = false;
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