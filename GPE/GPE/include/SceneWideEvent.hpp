#pragma once

#include <list>
#include <v8.h>
#include <OgreSingleton.h>
#include <EventDispatcherHelper.hpp>

class SceneWideEvent : public Ogre::Singleton<SceneWideEvent> , public EventDispatcherHelper {

public:
	SceneWideEvent();

	static const std::string ONFRAMEQUEUED;

	/*static v8::Handle<v8::Value> v8registerEventCallback(const v8::Arguments& args);
	static v8::Handle<v8::Value> v8removeEventCallback(const v8::Arguments& args);*/

	void registerEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc);
	void removeEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc);

	static void dispatch_SceneWide(std::string currEvent);

private:	
	std::list<v8::Persistent<v8::Function>> m_onFrameQueued;
	//static std::vector<v8::Persistent<v8::Function>> onHit;
	//static std::vector<v8::Persistent<v8::Function>> onClick;

	std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>> m_otherEvents;
};