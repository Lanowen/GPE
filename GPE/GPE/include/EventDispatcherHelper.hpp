#pragma once

#include<string>
#include<list>
#include<v8.h>
#include<V8Scripting.hpp>

class EventDispatcherHelper{
public:
	EventDispatcherHelper();
	virtual ~EventDispatcherHelper();
	
	std::string currEvent;
	std::list<v8::Persistent<v8::Function>>::iterator* tempNext;

	void runThroughList(std::string eventName, std::list<v8::Persistent<v8::Function>>& inList);
	void runThroughList(std::string eventName, std::list<v8::Persistent<v8::Function>>& inList, int argc, Handle<Value> argv[]);
};