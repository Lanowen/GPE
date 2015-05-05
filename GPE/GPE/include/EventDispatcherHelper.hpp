#pragma once

#include<string>
#include<list>
//#include<v8.h>
//#include<V8Scripting.hpp>

#include <boost\function.hpp>
#include "EventData.hpp"

class EventDispatcherHelper{
public:
	EventDispatcherHelper();
	virtual ~EventDispatcherHelper();
	
	std::string currEvent;
	//std::list<v8::Persistent<v8::Function>>::iterator* tempNextJS;
	std::list<boost::function<void(const EventData*)>>::iterator* tempNextCpp;

	//void runThroughList(std::string eventName, std::list<v8::Persistent<v8::Function>>& inList);
	//void runThroughList(std::string eventName, std::list<v8::Persistent<v8::Function>>& inList, int argc, Handle<Value> argv[]);

	void runThroughList(std::string eventName, std::list<boost::function<void(const EventData*)>>& inList, const EventData* data);
};