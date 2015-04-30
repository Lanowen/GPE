#include <SceneWideEvent.hpp>
#include <iostream>
#include <algorithm>
//#include <V8Scripting.hpp>

template<> SceneWideEvent* Ogre::Singleton<SceneWideEvent>::msSingleton = 0;

//const std::string SceneWideEvent::ONFRAMEQUEUED= "Event_onFrameQueued";

SceneWideEvent::SceneWideEvent() {

}

//void SceneWideEvent::registerEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc){
//	std::list<v8::Persistent<v8::Function>>::iterator itr;
//
//	//std::cout << "wat1 " << &inFunc->CreationContext() << std::endl;
//
//	if(eventName == SceneWideEvent::ONFRAMEQUEUED){
//		itr = std::find(m_onFrameQueued.begin(), m_onFrameQueued.end(), inFunc);
//		if(itr == m_onFrameQueued.end()){
//			m_onFrameQueued.push_back(inFunc);
//		}
//	}
//	else {
//		std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itrListeners = m_otherEvents.find(eventName);
//		if(itrListeners != m_otherEvents.end()){
//			std::list<v8::Persistent<v8::Function>>* listeners = &itrListeners->second;
//
//			itr = std::find(listeners->begin(), listeners->end(), inFunc);
//			if(itr == listeners->end()){
//				listeners->push_back(inFunc);
//			}
//		}
//		else {
//			m_otherEvents[eventName].push_back(inFunc);
//		}
//	}
//}

void SceneWideEvent::registerEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc){
	std::list<boost::function<void(const EventData*)>>::iterator itr;

	std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itrListeners = m_otherEvents.find(eventName);
	if(itrListeners != m_otherEvents.end()){
		std::list<boost::function<void(const EventData*)>>* listeners = &itrListeners->second;		

		
		for(itr = listeners->begin(); itr != listeners->end(); itr++){
			if(boost::function_equal((*itr).functor.func_ptr, inFunc.functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, inFunc.functor.obj_ptr))
				break;
		}
		//itr = std::find(listeners->begin(), listeners->end(), inFunc.functor);
		if(itr == listeners->end()){
			listeners->push_back(inFunc);
		}
	}
	else {
		m_otherEvents[eventName].push_back(inFunc);
	}
}

//void SceneWideEvent::removeEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc){
//	std::list<v8::Persistent<v8::Function>>::iterator itr;
//
//	if(eventName == SceneWideEvent::ONFRAMEQUEUED){
//		itr = std::find(m_onFrameQueued.begin(), m_onFrameQueued.end(), inFunc);
//		if(itr != m_onFrameQueued.end()){
//			if(tempNextJS){
//				(*itr).Dispose();
//				if(*itr == **tempNextJS && currEvent == eventName) {
//					*tempNextJS = m_onFrameQueued.erase(itr);
//				}
//				else {
//					m_onFrameQueued.erase(itr);
//				}
//			}
//			else {
//				(*itr).Dispose();
//				m_onFrameQueued.erase(itr);
//			}
//		}
//	}
//	else {
//		std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itrListeners = m_otherEvents.find(eventName);
//		if(itrListeners != m_otherEvents.end()){
//			std::list<v8::Persistent<v8::Function>>* listeners = &itrListeners->second;
//
//			itr = std::find(listeners->begin(), listeners->end(), inFunc);
//			if(itr != listeners->end()){
//				if(tempNextJS){
//					(*itr).Dispose();
//					if(*itr == **tempNextJS && currEvent == eventName) {
//						*tempNextJS = listeners->erase(itr);
//					}
//					else {
//						listeners->erase(itr);
//					}
//				}
//				else {
//					(*itr).Dispose();
//					listeners->erase(itr);
//				}
//			}
//		}
//	}
//}

void SceneWideEvent::removeEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc){
	std::list<boost::function<void(const EventData*)>>::iterator itr;

	std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itrListeners = m_otherEvents.find(eventName);
	if(itrListeners != m_otherEvents.end()){
		std::list<boost::function<void(const EventData*)>>* listeners = &itrListeners->second;

		//itr = std::find(listeners->begin(), listeners->end(), inFunc.functor);
		for(itr = listeners->begin(); itr != listeners->end(); itr++){
			if(boost::function_equal((*itr).functor.func_ptr, inFunc.functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, inFunc.functor.obj_ptr))
				break;
		}
		if(itr != listeners->end()){
			if(tempNextCpp){

				//this compare might not work
				if(boost::function_equal((*itr).functor.func_ptr, (**tempNextCpp).functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, (**tempNextCpp).functor.obj_ptr) && currEvent == eventName) {
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

//void SceneWideEvent::dispatch_SceneWide(std::string eventName){
//	SceneWideEvent* inst = SceneWideEvent::getSingletonPtr();
//	
//	bool found = false;
//
//	std::list<v8::Persistent<v8::Function>>* listeners = NULL;
//
//	if(eventName == SceneWideEvent::ONFRAMEQUEUED){
//		listeners = &inst->m_onFrameQueued;
//	}
//	else {
//		std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itr = inst->m_otherEvents.find(eventName);
//		if(itr != inst->m_otherEvents.end()){
//			listeners = &itr->second;
//		}
//	}
//
//	if(listeners && listeners->size()){
//		inst->runThroughList(eventName, *listeners);
//	}
//}

void SceneWideEvent::dispatch_SceneWide(std::string eventName, const EventData* data){
	SceneWideEvent* inst = SceneWideEvent::getSingletonPtr();
	
	bool found = false;

	std::list<boost::function<void(const EventData*)>>* listeners = NULL;

	std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itr = inst->m_otherEvents.find(eventName);
	if(itr != inst->m_otherEvents.end()){
		listeners = &itr->second;
	}

	if(listeners && listeners->size()){
		inst->runThroughList(eventName, *listeners, data);
	}
}