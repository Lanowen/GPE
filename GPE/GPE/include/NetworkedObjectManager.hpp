#pragma once

#include <map>

namespace gpe {

	class GameObject;

	class NetworkedObjectManager {
	public:
		NetworkedObjectManager();
		virtual ~NetworkedObjectManager();

		int addGameObject(GameObject* obj);
		void addGameObject(int id, GameObject* obj);
		void removeGameObject(int id);
		void removeGameObject(GameObject* go);

		GameObject* getGameObject(int id);

		inline std::map<int, GameObject*>& get_objects() { return objects_; }
		

	private:
		unsigned int counter_;

		std::map<int, GameObject*> objects_;
	};
}