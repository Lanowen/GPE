#include "EventDispatcherHelper.hpp"

EventDispatcherHelper::EventDispatcherHelper(){
	tempNextCpp_ = 0;
	currEvent_ = "";
};

EventDispatcherHelper::~EventDispatcherHelper(){

}

void EventDispatcherHelper::runThroughList(std::string eventName, std::list<boost::function<void(const EventData*)>>& inList, const EventData* data){
	currEvent_ = eventName;

	std::list<boost::function<void(const EventData*)>>::iterator itr = inList.begin();

	for(tempNextCpp_ = &itr; *tempNextCpp_ != inList.end(); ++*tempNextCpp_){
		(**tempNextCpp_)(data);

		//This might not be working properly...
		if(tempNextCpp_ == 0 || *tempNextCpp_ == inList.end()){
			break;
		}
	}

	tempNextCpp_ = 0;
	currEvent_ = "";
};
