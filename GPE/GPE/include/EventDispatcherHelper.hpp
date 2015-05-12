#pragma once

#include<string>
#include<list>

#include <boost\function.hpp>
#include "EventData.hpp"

class EventDispatcherHelper{
public:
	EventDispatcherHelper();
	virtual ~EventDispatcherHelper();
	
	std::string currEvent;
	std::list<boost::function<void(const EventData*)>>::iterator* tempNextCpp;

	void runThroughList(std::string eventName, std::list<boost::function<void(const EventData*)>>& inList, const EventData* data);
};