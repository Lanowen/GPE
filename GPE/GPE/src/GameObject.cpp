#include "GameObject.hpp"
#include <iostream>
#include <algorithm>
//#include <V8Scripting.hpp>
#include "EventDispatcher.hpp"

namespace gpe {

	GameObject::GameObject(string name) : owner_(0), net_id_(-1), released_(true), net_owned_(false), name_(name) {
	}

	GameObject::~GameObject() {
		//for (std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itr = eventsCpp_.begin(); itr != eventsCpp_.end(); itr++) {
		//	for (std::list<boost::function<void(const EventData*)>>::iterator itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++) {
		//		owner_->get_event_dispatcher()->removeEventCallback(itr->first, *itr2);
		//	}
		//}
	}

	void GameObject::setSocket(boost::shared_ptr<GPENet::SocketBase> base) {
		socket_ = base;
	}

	void GameObject::registerEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc) {
		std::list<boost::function<void(const EventData*)>>::iterator itr;

		owner_->get_event_dispatcher()->registerEventCallback(eventName, inFunc);

		std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itrListeners = eventsCpp_.find(eventName);
		if (itrListeners != eventsCpp_.end()) {
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
			eventsCpp_[eventName].push_back(inFunc);
		}
	}

	void GameObject::removeEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc) {
		std::list<boost::function<void(const EventData*)>>::iterator itr;

		owner_->get_event_dispatcher()->removeEventCallback(eventName, inFunc);

		std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itrListeners = eventsCpp_.find(eventName);
		if (itrListeners != eventsCpp_.end()) {
			std::list<boost::function<void(const EventData*)>>* listeners = &itrListeners->second;

			//itr = std::find(listeners->begin(), listeners->end(), inFunc.functor);
			for (itr = listeners->begin(); itr != listeners->end(); itr++) {
				if (boost::function_equal((*itr).functor.func_ptr, inFunc.functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, inFunc.functor.obj_ptr))
					break;
			}
			if (itr != listeners->end()) {
				if (tempNextCpp_) {

					//this compare might not work
					if (boost::function_equal((*itr).functor.func_ptr, (**tempNextCpp_).functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, (**tempNextCpp_).functor.obj_ptr) && currEvent_ == eventName) {
						*tempNextCpp_ = listeners->erase(itr);
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

		std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itr = eventsCpp_.find(eventName);
		if (itr != eventsCpp_.end()) {
			listeners = &itr->second;
		}

		if (listeners && listeners->size()) {
			runThroughList(eventName, *listeners, data);
		}
	}

	void  GameObject::Update(Ogre::Real deltaTime) {

	}

	//use this instead of GameObject::~GameObject, so that handles from GameState are sure to be cleared before deleting.
	void GameObject::release() {
		if (released_) {
			delete this;
			return;
		}

		owner_->DeleteGameObject(this);
	}
}