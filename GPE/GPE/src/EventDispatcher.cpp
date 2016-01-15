#include "stdafx.h"

#include "EventDispatcher.hpp"
#include "EventData.hpp"

using namespace std;

namespace gpe
{
	EventDispatcher::EventDispatcher()
	{

	}

	void EventDispatcher::registerEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc)
	{
		std::list<boost::function<void(const EventData*)>>::iterator itr;

		std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itrListeners = events_.find(eventName);
		if(itrListeners != events_.end())
		{
			std::list<boost::function<void(const EventData*)>>* listeners = &itrListeners->second;


			for(itr = listeners->begin(); itr != listeners->end(); itr++)
			{
				if(boost::function_equal((*itr).functor.func_ptr, inFunc.functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, inFunc.functor.obj_ptr))
					break;
			}
			//itr = std::find(listeners->begin(), listeners->end(), inFunc.functor);
			if(itr == listeners->end())
			{
				listeners->push_back(inFunc);
			}
		} else
		{
			events_[eventName].push_back(inFunc);
		}
	}

	void EventDispatcher::removeEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc)
	{
		std::list<boost::function<void(const EventData*)>>::iterator itr;

		std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itrListeners = events_.find(eventName);
		if(itrListeners != events_.end())
		{
			std::list<boost::function<void(const EventData*)>>* listeners = &itrListeners->second;

			//itr = std::find(listeners->begin(), listeners->end(), inFunc.functor);
			for(itr = listeners->begin(); itr != listeners->end(); itr++)
			{
				if(boost::function_equal((*itr).functor.func_ptr, inFunc.functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, inFunc.functor.obj_ptr))
					break;
			}
			if(itr != listeners->end())
			{
				if(tempNextCpp_)
				{

					//HACK: this compare might not work
					if(boost::function_equal((*itr).functor.func_ptr, (**tempNextCpp_).functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, (**tempNextCpp_).functor.obj_ptr) && currEvent_ == eventName)
					{
						*tempNextCpp_ = listeners->erase(itr);
					} else
					{
						listeners->erase(itr);
					}
				} else
				{
					listeners->erase(itr);
				}
			}
		}
	}

	void EventDispatcher::dispatch_event(std::string eventName, const EventData* data)
	{
		bool found = false;

		std::list<boost::function<void(const EventData*)>>* listeners = NULL;

		std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itr = events_.find(eventName);
		if(itr != events_.end())
		{
			listeners = &itr->second;
		}

		if(listeners && listeners->size())
		{
			runThroughList(eventName, *listeners, data);
		}
	}
}