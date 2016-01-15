#pragma once

#include <boost\function.hpp>

namespace gpe
{
	class EventData;

	class EventDispatcherHelper
	{
	public:
		EventDispatcherHelper();
		virtual ~EventDispatcherHelper();

		std::string currEvent_;
		std::list<boost::function<void(const EventData*)>>::iterator* tempNextCpp_;

		void runThroughList(std::string eventName, std::list<boost::function<void(const EventData*)>>& inList, const EventData* data);
	};
}