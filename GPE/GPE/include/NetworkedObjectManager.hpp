#pragma once

class GameObject;

#include <map>

class NetworkedObjectManager {
	friend class GameState;
public:
	NetworkedObjectManager();
	virtual ~NetworkedObjectManager();

	int addGameObject(GameObject* obj);
	void addGameObject(int id, GameObject* obj);
	void removeGameObject(int id);
	void removeGameObject(GameObject* go);

	GameObject* getGameObject(int id);

private:
	int counter;
	std::map<int, GameObject*> objects;
};