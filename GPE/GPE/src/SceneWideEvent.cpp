#include <SceneWideEvent.hpp>
#include <iostream>
#include <algorithm>
#include <V8Scripting.hpp>

template<> SceneWideEvent* Ogre::Singleton<SceneWideEvent>::msSingleton = 0;

const std::string SceneWideEvent::ONFRAMEQUEUED= "Event_onFrameQueued";

SceneWideEvent::SceneWideEvent() {

}

void SceneWideEvent::registerEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc){
	std::list<v8::Persistent<v8::Function>>::iterator itr;

	//std::cout << "wat1 " << &inFunc->CreationContext() << std::endl;

	if(eventName == SceneWideEvent::ONFRAMEQUEUED){
		itr = std::find(m_onFrameQueued.begin(), m_onFrameQueued.end(), inFunc);
		if(itr == m_onFrameQueued.end()){
			m_onFrameQueued.push_back(inFunc);
		}
	}
	else {
		std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itrListeners = m_otherEvents.find(eventName);
		if(itrListeners != m_otherEvents.end()){
			std::list<v8::Persistent<v8::Function>>* listeners = &itrListeners->second;

			itr = std::find(listeners->begin(), listeners->end(), inFunc);
			if(itr == listeners->end()){
				listeners->push_back(inFunc);
			}
		}
		else {
			m_otherEvents[eventName].push_back(inFunc);
		}
	}
}

void SceneWideEvent::removeEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc){
	std::list<v8::Persistent<v8::Function>>::iterator itr;

	if(eventName == SceneWideEvent::ONFRAMEQUEUED){
		itr = std::find(m_onFrameQueued.begin(), m_onFrameQueued.end(), inFunc);
		if(itr != m_onFrameQueued.end()){
			if(tempNext){
				(*itr).Dispose();
				if(*itr == **tempNext && currEvent == eventName) {
					*tempNext = m_onFrameQueued.erase(itr);
				}
				else {
					m_onFrameQueued.erase(itr);
				}
			}
			else {
				(*itr).Dispose();
				m_onFrameQueued.erase(itr);
			}
		}
	}
	else {
		std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itrListeners = m_otherEvents.find(eventName);
		if(itrListeners != m_otherEvents.end()){
			std::list<v8::Persistent<v8::Function>>* listeners = &itrListeners->second;

			itr = std::find(listeners->begin(), listeners->end(), inFunc);
			if(itr != listeners->end()){
				if(tempNext){
					(*itr).Dispose();
					if(*itr == **tempNext && currEvent == eventName) {
						*tempNext = listeners->erase(itr);
					}
					else {
						listeners->erase(itr);
					}
				}
				else {
					(*itr).Dispose();
					listeners->erase(itr);
				}
			}
		}
	}
}

void SceneWideEvent::dispatch_SceneWide(std::string eventName){
	SceneWideEvent* inst = SceneWideEvent::getSingletonPtr();
	
	bool found = false;

	std::list<v8::Persistent<v8::Function>>* listeners = NULL;

	if(eventName == SceneWideEvent::ONFRAMEQUEUED){
		listeners = &inst->m_onFrameQueued;
	}
	else {
		std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itr = inst->m_otherEvents.find(eventName);
		if(itr != inst->m_otherEvents.end()){
			listeners = &itr->second;
		}
	}

	if(listeners && listeners->size()){
		inst->runThroughList(eventName, *listeners);
	}
}