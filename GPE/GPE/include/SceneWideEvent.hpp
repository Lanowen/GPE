#pragma once

#include <list>
//#include <v8.h>
#include <OgreSingleton.h>
#include <EventDispatcherHelper.hpp>

#include <EventData.hpp>

class SceneWideEvent : public Ogre::Singleton<SceneWideEvent> , public EventDispatcherHelper {

public:
	SceneWideEvent();

	//static const std::string ONFRAMEQUEUED;

	/*static v8::Handle<v8::Value> v8registerEventCallback(const v8::Arguments& args);
	static v8::Handle<v8::Value> v8removeEventCallback(const v8::Arguments& args);*/

	//void registerEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc);
	//void removeEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc);

	void registerEventCallback(std::string eventName,boost::function<void(const EventData*)> inFunc);
	void removeEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc);

	//static void dispatch_SceneWide(std::string currEvent);
	static void dispatch_SceneWide(std::string currEvent, const EventData* data);

private:	
	//std::list<v8::Persistent<v8::Function>> m_onFrameQueued;
	//static std::vector<v8::Persistent<v8::Function>> onHit;
	//static std::vector<v8::Persistent<v8::Function>> onClick;

	//std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>> m_otherEvents;

	std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>> m_otherEvents;
};