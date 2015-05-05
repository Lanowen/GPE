#include "EventDispatcherHelper.hpp"

EventDispatcherHelper::EventDispatcherHelper(){
	tempNextCpp = 0;
	//tempNextJS = 0;
	currEvent = "";
};

EventDispatcherHelper::~EventDispatcherHelper(){

}

//void EventDispatcherHelper::runThroughList(std::string eventName, std::list<v8::Persistent<v8::Function>>& inList){
//	//v8::Locker locker;
//	v8::HandleScope handleScope(Isolate::GetCurrent());
//
//	currEvent = eventName;
//
//	std::list<v8::Persistent<v8::Function>>::iterator itr = inList.begin();
//
//	for(tempNextJS = &itr; *tempNextJS != inList.end(); ++*tempNextJS){
//		v8::TryCatch trycatch;
//
//		v8::Local<v8::Value> v = (**tempNextJS)->Call((**tempNextJS)->CreationContext()->Global(),0,NULL);
//
//		if (v.IsEmpty()) {
//			V8Scripting::reportException(&trycatch);
//		}
//
//		//This might not be working properly...
//		if(tempNextJS == 0 ||*tempNextJS == inList.end()){
//			break;
//		}
//	}
//
//	tempNextJS = 0;
//	currEvent = "";
//};

//void EventDispatcherHelper::runThroughList(std::string eventName, std::list<v8::Persistent<v8::Function>>& inList, int argc, Handle<Value> argv[]){
//	//v8::Locker locker;
//	v8::HandleScope handleScope(Isolate::GetCurrent());
//
//	currEvent = eventName;
//
//	std::list<v8::Persistent<v8::Function>>::iterator itr = inList.begin();
//
//	for(tempNextJS = &itr; *tempNextJS != inList.end(); ++*tempNextJS){
//		v8::TryCatch trycatch;
//
//		v8::Local<v8::Value> v = (**tempNextJS)->Call((**tempNextJS)->CreationContext()->Global(), argc, argv);
//
//		if (v.IsEmpty()) {
//			V8Scripting::reportException(&trycatch);
//		}
//
//
//		//This might not be working properly...
//		if(tempNextJS == 0 || *tempNextJS == inList.end()){
//			break;
//		}
//	}
//
//	tempNextJS = 0;
//	currEvent = "";
//};

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
