#include <NetworkedObjectManager.hpp>

NetworkedObjectManager::NetworkedObjectManager() : counter (0) {
}

NetworkedObjectManager::~NetworkedObjectManager(){
}

int NetworkedObjectManager::addGameObject(GameObject* obj){
	int newID = counter++;
	objects[newID] = obj;

	return newID;
}

void NetworkedObjectManager::addGameObject(int id, GameObject* obj){
	if(objects.find(id) == objects.end()){
		objects[id] = obj;
	}
}

void NetworkedObjectManager::releaseAndRemoveGameObject(int id){
	std::map<int, GameObject*>::iterator itr;
	if((itr = objects.find(id)) != objects.end()){
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