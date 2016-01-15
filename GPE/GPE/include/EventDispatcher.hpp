#pragma once

#include "EventDispatcherHelper.hpp"

namespace gpe
{
	class EventData;

	class EventDispatcher : public EventDispatcherHelper
	{

	public:
		EventDispatcher();

		void registerEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc);
		void removeEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc);

		void dispatch_event(std::string currEvent_, const EventData* data);

	private:

		std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>> events_;
	};
}