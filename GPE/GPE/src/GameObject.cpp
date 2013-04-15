#include <GameObject.hpp>
#include <iostream>
#include <algorithm>
//#include <V8Scripting.hpp>
#include <SceneWideEvent.hpp>

GameObject::GameObject(GameState* owner) : owner(owner), released(false) {
	//HandleScope scope;

	//fcnTemplate = Persistent<FunctionTemplate>::New(FunctionTemplate::New());
}

GameObject::~GameObject(){
	/*for(std::vector<ScriptingObject*>::iterator itr = attachedScripts.begin(); itr != attachedScripts.end(); itr++){
		delete *itr;
	}

	for(std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itr = events.begin(); itr != events.end(); itr++){	
		for(std::list<v8::Persistent<v8::Function>>::iterator itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++){
			SceneWideEvent::getSingletonPtr()->removeEventCallback(itr->first, *itr2);
			itr2->Dispose();
		}
	}

	fcnTemplate.Dispose();*/

	for(std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itr = eventsCpp.begin(); itr != eventsCpp.end(); itr++){	
		for(std::list<boost::function<void(const EventData*)>>::iterator itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++){
			SceneWideEvent::getSingletonPtr()->removeEventCallback(itr->first, *itr2);
		}
	}
}

//v8::Handle<v8::Value> GameObject::v8registerEventCallback(const v8::Arguments& args){
//	//v8::Locker locker;
//    v8::HandleScope scope;
//
//	if(args.Length() == 2 && !args[0].IsEmpty() && !args[1].IsEmpty() && args[0]->IsString() && args[1]->IsFunction() ) 
//    {
//		std::string eventName = *v8::String::Utf8Value(args[0]->ToString());
//
//		SceneWideEvent::getSingletonPtr()->registerEventCallback(eventName, v8::Persistent<v8::Function>::New(v8::Local<v8::Function>::Cast(args[1])));
//
//		GameObject* parentGO = static_cast<GameObject*>(External::Cast(*args.Holder()->GetHiddenValue(v8::String::New("GameObject")))->Value());
//		parentGO->registerEventCallback( eventName , v8::Persistent<v8::Function>::New(v8::Local<v8::Function>::Cast(args[1])) );
//	}
//
//	return v8::Undefined();
//}

//v8::Handle<v8::Value> GameObject::v8removeEventCallback(const v8::Arguments& args){
//	//v8::Locker locker;
//    v8::HandleScope scope;
//
//	if(args.Length() == 2 && !args[0].IsEmpty() && !args[1].IsEmpty() && args[0]->IsString() && args[1]->IsFunction() ) 
//    {
//		std::string eventName = *v8::String::Utf8Value(args[0]->ToString());
//
//		SceneWideEvent::getSingletonPtr()->removeEventCallback(eventName, v8::Persistent<v8::Function>::New(v8::Local<v8::Function>::Cast(args[1])));
//
//		GameObject* parentGO = static_cast<GameObject*>(External::Cast(*args.Holder()->GetHiddenValue(v8::String::New("GameObject")))->Value());
//		parentGO->removeEventCallback( eventName , v8::Persistent<v8::Function>::New(v8::Local<v8::Function>::Cast(args[1])) );
//	}
//
//	return v8::Undefined();
//}

//void GameObject::registerEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc){
//	std::list<v8::Persistent<v8::Function>>::iterator itr;
//
//	std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itrListeners = events.find(eventName);
//	if(itrListeners != events.end()){
//		std::list<v8::Persistent<v8::Function>>* listeners = &itrListeners->second;		
//
//		itr = std::find(listeners->begin(), listeners->end(), inFunc);
//		if(itr == listeners->end()){
//			listeners->push_back(inFunc);
//		}
//	}
//	else {
//		events[eventName].push_back(inFunc);
//	}
//}

void GameObject::registerEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc){
	std::list<boost::function<void(const EventData*)>>::iterator itr;

	SceneWideEvent::getSingletonPtr()->registerEventCallback(eventName,inFunc);

	std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itrListeners = eventsCpp.find(eventName);
	if(itrListeners != eventsCpp.end()){
		std::list<boost::function<void(const EventData*)>>* listeners = &itrListeners->second;		

		
		for(itr = listeners->begin(); itr != listeners->end(); itr++){
			if(boost::function_equal((*itr).functor.func_ptr, inFunc.functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, inFunc.functor.obj_ptr))
				break;
		}
		//itr = std::find(listeners->begin(), listeners->end(), inFunc.functor);
		if(itr == listeners->end()){
			listeners->push_back(inFunc);
		}
	}
	else {
		eventsCpp[eventName].push_back(inFunc);
	}
}

//void GameObject::removeEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc){
//	std::list<v8::Persistent<v8::Function>>::iterator itr;
//
//	std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itrListeners = events.find(eventName);
//	if(itrListeners != events.end()){
//		std::list<v8::Persistent<v8::Function>>* listeners = &itrListeners->second;
//
//		itr = std::find(listeners->begin(), listeners->end(), inFunc);
//		if(itr != listeners->end()){
//			if(tempNextJS){
//				(*itr).Dispose();
//				if(*itr == **tempNextJS && currEvent == eventName) {
//					*tempNextJS = listeners->erase(itr);
//				}
//				else {
//					listeners->erase(itr);
//				}
//			}
//			else {
//				(*itr).Dispose();
//				listeners->erase(itr);
//			}
//		}
//	}
//}

void GameObject::removeEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc){
	std::list<boost::function<void(const EventData*)>>::iterator itr;

	SceneWideEvent::getSingletonPtr()->removeEventCallback(eventName,inFunc);

	std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itrListeners = eventsCpp.find(eventName);
	if(itrListeners != eventsCpp.end()){
		std::list<boost::function<void(const EventData*)>>* listeners = &itrListeners->second;

		//itr = std::find(listeners->begin(), listeners->end(), inFunc.functor);
		for(itr = listeners->begin(); itr != listeners->end(); itr++){
			if(boost::function_equal((*itr).functor.func_ptr, inFunc.functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, inFunc.functor.obj_ptr))
				break;
		}
		if(itr != listeners->end()){
			if(tempNextCpp){

				//this compare might not work
				if(boost::function_equal((*itr).functor.func_ptr, (**tempNextCpp).functor.func_ptr) && boost::function_equal((*itr).functor.obj_ptr, (**tempNextCpp).functor.obj_ptr) && currEvent == eventName) {
					*tempNextCpp = listeners->erase(itr);
				}
				else {
					listeners->erase(itr);
				}
			}
			else {
				listeners->erase(itr);
			}
		}
	}
}

//bool GameObject::loadScript(std::string inScript){
//	Handle<Script> script = V8Scripting::getSingletonPtr()->scriptMgr->getCompiledScript(inScript);
//
//	if(!script.IsEmpty()){
//		
//
//		//Locker lock(Isolate::GetCurrent());
//		HandleScope handleScope;
//
//		ScriptingObject* newScript = new ScriptingObject(fcnTemplate);
//		attachedScripts.push_back(newScript);
//
//		v8::Local<v8::Object> global = newScript->context->Global();
//
//		global->SetHiddenValue(v8::String::New("GameObject"), External::New(this));
//
//		newScript->context->Enter();
//
//		TryCatch trycatch;
//		Local<Value> v = script->Run();
//
//		if (v.IsEmpty()) {  
//			V8Scripting::reportException(&trycatch);
//		}
//	
//		newScript->context->Exit();
//
//		return(true);
//	}
//
//	return(false);
//}

//void GameObject::exposeObject(std::string name, Handle<Data> val){
//	HandleScope scope;
//
//	fcnTemplate->PrototypeTemplate()->Set(v8::String::New(name.c_str()), val, PropertyAttribute::ReadOnly);
//}
//
//void GameObject::dispatchEvent(std::string eventName){
//
//
//	std::list<v8::Persistent<v8::Function>>* listeners = NULL;
//
//	std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itr = events.find(eventName);
//	if(itr != events.end()){
//		listeners = &itr->second;
//	}
//
//	if(listeners && listeners->size()){
//		runThroughList(eventName, *listeners);
//	}
//}
//
//void GameObject::dispatchEvent(std::string eventName, int argc, v8::Handle<Value> argv[]){
//
//
//	std::list<v8::Persistent<v8::Function>>* listeners = NULL;
//
//	std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itr = events.find(eventName);
//	if(itr != events.end()){
//		listeners = &itr->second;
//	}
//
//	if(listeners && listeners->size()){
//		runThroughList(eventName, *listeners, argc, argv);
//	}
//}

void GameObject::dispatchEvent(std::string eventName, const EventData* data){


	std::list<boost::function<void(const EventData*)>>* listeners = NULL;

	std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>>::iterator itr = eventsCpp.find(eventName);
	if(itr != eventsCpp.end()){
		listeners = &itr->second;
	}

	if(listeners && listeners->size()){
		runThroughList(eventName, *listeners, data);
	}
}

void  GameObject::Update(Ogre::Real deltaTime){

}

void GameObject::release(){
	released = true;
	owner->DeleteGameObject(this);
}