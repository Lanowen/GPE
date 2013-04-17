#include <NetworkedObjectManager.hpp>
#include <GameObject.hpp>

NetworkedObjectManager::NetworkedObjectManager() : counter (0) {
}

NetworkedObjectManager::~NetworkedObjectManager(){
}

int NetworkedObjectManager::addGameObject(GameObject* obj){
	obj->netId = counter++;
	objects[obj->netId] = obj;

	return obj->netId;
}

void NetworkedObjectManager::addGameObject(int id, GameObject* obj){
	if(objects.find(id) == objects.end()){
		objects[id] = obj;
		obj->netId = id;
	}
}

void NetworkedObjectManager::removeGameObject(int id){
	std::map<int, GameObject*>::iterator itr;
	if((itr = objects.find(id)) != objects.end()){
		objects.erase(itr);
	}
}

void NetworkedObjectManager::removeGameObject(GameObject* go){
	std::map<int, GameObject*>::iterator itr;
	if((itr = objects.find(go->netId)) != objects.end()){
		objects.erase(itr);
	}
}

GameObject* NetworkedObjectManager::getGameObject(int id){
	std::map<int, GameObject*>::iterator itr;
	if((itr = objects.find(id)) != objects.end()){
		return itr->second;
	}

	return 0;
}