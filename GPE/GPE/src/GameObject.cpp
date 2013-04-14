#include <GameObject.hpp>
#include <iostream>
#include <algorithm>
#include <V8Scripting.hpp>
#include <SceneWideEvent.hpp>

GameObject::GameObject(GameState* owner) : owner(owner) {
	HandleScope scope;

	fcnTemplate = Persistent<FunctionTemplate>::New(FunctionTemplate::New());
}

GameObject::~GameObject(){
	for(std::vector<ScriptingObject*>::iterator itr = attachedScripts.begin(); itr != attachedScripts.end(); itr++){
		delete *itr;
	}

	for(std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itr = events.begin(); itr != events.end(); itr++){	
		for(std::list<v8::Persistent<v8::Function>>::iterator itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++){
			SceneWideEvent::getSingletonPtr()->removeEventCallback(itr->first, *itr2);
			itr2->Dispose();
		}
	}

	fcnTemplate.Dispose();
}

v8::Handle<v8::Value> GameObject::v8registerEventCallback(const v8::Arguments& args){
	//v8::Locker locker;
    v8::HandleScope scope;

	if(args.Length() == 2 && !args[0].IsEmpty() && !args[1].IsEmpty() && args[0]->IsString() && args[1]->IsFunction() ) 
    {
		std::string eventName = *v8::String::Utf8Value(args[0]->ToString());

		SceneWideEvent::getSingletonPtr()->registerEventCallback(eventName, v8::Persistent<v8::Function>::New(v8::Local<v8::Function>::Cast(args[1])));

		GameObject* parentGO = static_cast<GameObject*>(External::Cast(*args.Holder()->GetHiddenValue(v8::String::New("GameObject")))->Value());
		parentGO->registerEventCallback( eventName , v8::Persistent<v8::Function>::New(v8::Local<v8::Function>::Cast(args[1])) );
	}

	return v8::Undefined();
}

v8::Handle<v8::Value> GameObject::v8removeEventCallback(const v8::Arguments& args){
	//v8::Locker locker;
    v8::HandleScope scope;

	if(args.Length() == 2 && !args[0].IsEmpty() && !args[1].IsEmpty() && args[0]->IsString() && args[1]->IsFunction() ) 
    {
		std::string eventName = *v8::String::Utf8Value(args[0]->ToString());

		SceneWideEvent::getSingletonPtr()->removeEventCallback(eventName, v8::Persistent<v8::Function>::New(v8::Local<v8::Function>::Cast(args[1])));

		GameObject* parentGO = static_cast<GameObject*>(External::Cast(*args.Holder()->GetHiddenValue(v8::String::New("GameObject")))->Value());
		parentGO->removeEventCallback( eventName , v8::Persistent<v8::Function>::New(v8::Local<v8::Function>::Cast(args[1])) );
	}

	return v8::Undefined();
}

void GameObject::registerEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc){
	std::list<v8::Persistent<v8::Function>>::iterator itr;

	std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itrListeners = events.find(eventName);
	if(itrListeners != events.end()){
		std::list<v8::Persistent<v8::Function>>* listeners = &itrListeners->second;		

		itr = std::find(listeners->begin(), listeners->end(), inFunc);
		if(itr == listeners->end()){
			listeners->push_back(inFunc);
		}
	}
	else {
		events[eventName].push_back(inFunc);
	}
}

void GameObject::removeEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc){
	std::list<v8::Persistent<v8::Function>>::iterator itr;

	std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itrListeners = events.find(eventName);
	if(itrListeners != events.end()){
		std::list<v8::Persistent<v8::Function>>* listeners = &itrListeners->second;

		itr = std::find(listeners->begin(), listeners->end(), inFunc);
		if(itr != listeners->end()){
			if(tempNext){
				(*itr).Dispose();
				if(*itr == **tempNext && currEvent == eventName) {
					*tempNext = listeners->erase(itr);
				}
				else {
					listeners->erase(itr);
				}
			}
			else {
				(*itr).Dispose();
				listeners->erase(itr);
			}
		}
	}
}

bool GameObject::loadScript(std::string inScript){
	Handle<Script> script = V8Scripting::getSingletonPtr()->scriptMgr->getCompiledScript(inScript);

	if(!script.IsEmpty()){
		

		//Locker lock(Isolate::GetCurrent());
		HandleScope handleScope;

		ScriptingObject* newScript = new ScriptingObject(fcnTemplate);
		attachedScripts.push_back(newScript);

		v8::Local<v8::Object> global = newScript->context->Global();

		global->SetHiddenValue(v8::String::New("GameObject"), External::New(this));

		newScript->context->Enter();

		TryCatch trycatch;
		Local<Value> v = script->Run();

		if (v.IsEmpty()) {  
			V8Scripting::reportException(&trycatch);
		}
	
		newScript->context->Exit();

		return(true);
	}

	return(false);
}

void GameObject::exposeObject(std::string name, Handle<Data> val){
	HandleScope scope;

	fcnTemplate->PrototypeTemplate()->Set(v8::String::New(name.c_str()), val, PropertyAttribute::ReadOnly);
}

void GameObject::dispatchEvent(std::string eventName){


	std::list<v8::Persistent<v8::Function>>* listeners = NULL;

	std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itr = events.find(eventName);
	if(itr != events.end()){
		listeners = &itr->second;
	}

	if(listeners && listeners->size()){
		runThroughList(eventName, *listeners);
	}
}

void GameObject::dispatchEvent(std::string eventName, int argc, v8::Handle<Value> argv[]){


	std::list<v8::Persistent<v8::Function>>* listeners = NULL;

	std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>>::iterator itr = events.find(eventName);
	if(itr != events.end()){
		listeners = &itr->second;
	}

	if(listeners && listeners->size()){
		runThroughList(eventName, *listeners, argc, argv);
	}
}

void  GameObject::Update(Ogre::Real deltaTime){

}

void GameObject::release(){
	
}