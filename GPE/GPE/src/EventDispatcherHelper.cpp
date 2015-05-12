#include "EventDispatcherHelper.hpp"

EventDispatcherHelper::EventDispatcherHelper(){
	tempNextCpp = 0;
	currEvent = "";
};

EventDispatcherHelper::~EventDispatcherHelper(){

}

void EventDispatcherHelper::runThroughList(std::string eventName, std::list<boost::function<void(const EventData*)>>& inList, const EventData* data){
	currEvent = eventName;

	std::list<boost::function<void(const EventData*)>>::iterator itr = inList.begin();

	for(tempNextCpp = &itr; *tempNextCpp != inList.end(); ++*tempNextCpp){
		(**tempNextCpp)(data);

		//This might not be working properly...
		if(tempNextCpp == 0 || *tempNextCpp == inList.end()){
			break;
		}
	}

	tempNextCpp = 0;
	currEvent = "";
};
