#include <EventDispatcherHelper.hpp>

EventDispatcherHelper::EventDispatcherHelper(){
	tempNext = NULL;
	currEvent = "";
};

EventDispatcherHelper::~EventDispatcherHelper(){

}

void EventDispatcherHelper::runThroughList(std::string eventName, std::list<v8::Persistent<v8::Function>>& inList){
	//v8::Locker locker;
	v8::HandleScope handleScope(Isolate::GetCurrent());

	currEvent = eventName;

	std::list<v8::Persistent<v8::Function>>::iterator itr = inList.begin();

	for(tempNext = &itr; *tempNext != inList.end(); ++*tempNext){
		v8::TryCatch trycatch;

		v8::Local<v8::Value> v = (**tempNext)->Call((**tempNext)->CreationContext()->Global(),0,NULL);

		if (v.IsEmpty()) {
			V8Scripting::reportException(&trycatch);
		}

		//This might not be working properly...
		if(tempNext == 0 ||*tempNext == inList.end()){
			break;
		}
	}

	tempNext = NULL;
	currEvent = "";
};

void EventDispatcherHelper::runThroughList(std::string eventName, std::list<v8::Persistent<v8::Function>>& inList, int argc, Handle<Value> argv[]){
	//v8::Locker locker;
	v8::HandleScope handleScope(Isolate::GetCurrent());

	currEvent = eventName;

	std::list<v8::Persistent<v8::Function>>::iterator itr = inList.begin();

	for(tempNext = &itr; *tempNext != inList.end(); ++*tempNext){
		v8::TryCatch trycatch;

		v8::Local<v8::Value> v = (**tempNext)->Call((**tempNext)->CreationContext()->Global(), argc, argv);

		if (v.IsEmpty()) {
			V8Scripting::reportException(&trycatch);
		}


		//This might not be working properly...
		if(tempNext == 0 || *tempNext == inList.end()){
			break;
		}
	}

	tempNext = NULL;
	currEvent = "";
};
