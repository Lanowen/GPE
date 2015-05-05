#include "GameObject.hpp"
#include <iostream>
#include <algorithm>
//#include <V8Scripting.hpp>
#include "SceneWideEvent.hpp"

namespace gpe {

	GameObject::GameObject(GameState* owner) : owner(owner), netId(-1), released(false), netOwned(true) {
	}

	GameObject::~GameObject() {
		for (std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itr = eventsCpp.begin(); itr != eventsCpp.end(); itr++) {
			for (std::list<boost::function<void(const EventData*)>>::iterator itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++) {
				SceneWideEvent::getSingletonPtr()->removeEventCallback(itr->first, *itr2);
			}
		}
	}

	void GameObject::setSocket(boost::shared_ptr<GPENet::SocketBase> base) {
		socket = base;
	}

	void GameObject::registerEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc) {
		std::list<boost::function<void(const EventData*)>>::iterator itr;

		SceneWideEvent::getSingletonPtr()->registerEventCallback(eventName, inFunc);

		std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itrListeners = eventsCpp.find(eventName);
		if (itrListeners != eventsCpp.end()) {
			std::list<boost::function<void(const EventData*)>>* listeners = &itrListeners->second;


			for (itr = listeners->begin(); itr != listeners->end(); itr++) {
				if (boost::function_equal((*itr).functor.func_ptr, inFunc.functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, inFunc.functor.obj_ptr))
					break;
			}
			//itr = std::find(listeners->begin(), listeners->end(), inFunc.functor);
			if (itr == listeners->end()) {
				listeners->push_back(inFunc);
			}
		}
		else {
			eventsCpp[eventName].push_back(inFunc);
		}
	}

	void GameObject::removeEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc) {
		std::list<boost::function<void(const EventData*)>>::iterator itr;

		SceneWideEvent::getSingletonPtr()->removeEventCallback(eventName, inFunc);

		std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itrListeners = eventsCpp.find(eventName);
		if (itrListeners != eventsCpp.end()) {
			std::list<boost::function<void(const EventData*)>>* listeners = &itrListeners->second;

			//itr = std::find(listeners->begin(), listeners->end(), inFunc.functor);
			for (itr = listeners->begin(); itr != listeners->end(); itr++) {
				if (boost::function_equal((*itr).functor.func_ptr, inFunc.functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, inFunc.functor.obj_ptr))
					break;
			}
			if (itr != listeners->end()) {
				if (tempNextCpp) {

					//this compare might not work
					if (boost::function_equal((*itr).functor.func_ptr, (**tempNextCpp).functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, (**tempNextCpp).functor.obj_ptr) && currEvent == eventName) {
						*tempNextCpp = listeners->erase(itr);
					}
					else {
						listeners->erase(itr);
					}
				}
				else {
					listeners->erase(itr);
				}
			}
		}
	}

	void GameObject::dispatchEvent(std::string eventName, const EventData* data) {


		std::list<boost::function<void(const EventData*)>>* listeners = NULL;

		std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itr = eventsCpp.find(eventName);
		if (itr != eventsCpp.end()) {
			listeners = &itr->second;
		}

		if (listeners && listeners->size()) {
			runThroughList(eventName, *listeners, data);
		}
	}

	void  GameObject::Update(Ogre::Real deltaTime) {

	}

	void GameObject::release() {
		released = true;
		owner->DeleteGameObject(this);
	}
}