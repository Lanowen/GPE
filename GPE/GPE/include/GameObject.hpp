#pragma once

#include <Ogre.h>
#include <list>
#include <vector>
#include <v8.h>
#include <ScriptingObject.hpp>
#include <EventDispatcherHelper.hpp>

#include <GameState.hpp>

class GameObject : public EventDispatcherHelper {
public:
	GameObject(GameState* owner);
	virtual ~GameObject();

	static v8::Handle<v8::Value> v8registerEventCallback(const v8::Arguments& args);
	static v8::Handle<v8::Value> v8removeEventCallback(const v8::Arguments& args);

	void registerEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc);
	void removeEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc);

	bool loadScript(std::string inScript);
	//bool loadScript(std::string inScript, ScriptingObject*& retSO);

	void dispatchEvent(std::string eventName);
	void dispatchEvent(std::string eventName, int argc, v8::Handle<Value> argv[]);

	//Need compiler v120 for this. God fuck.
	//template<class... Args>
	//void dispatchEvent(std::string eventName, Args... args);

	virtual void release();
	virtual void Update(Ogre::Real deltaTime);

	void exposeObject(std::string name, Handle<Data> val);

protected:
	GameState* owner;

	Persistent<FunctionTemplate> fcnTemplate;

private:	
	std::vector<ScriptingObject*> attachedScripts;
	std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>> events;

};