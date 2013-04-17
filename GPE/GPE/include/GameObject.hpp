#pragma once

#include <Ogre.h>
#include <list>
#include <vector>
//#include <v8.h>
//#include <ScriptingObject.hpp>
#include <EventDispatcherHelper.hpp>

#include <GameState.hpp>

#include <GPENet.hpp>

enum GO_TYPE{
	PLAYER,
	ENEMY,
	PROJECTILE,
	POWERUP
};

class GameObject : public EventDispatcherHelper {
	friend class GameState;
public:
	GameObject(GameState* owner);
	virtual ~GameObject();

	//static v8::Handle<v8::Value> v8registerEventCallback(const v8::Arguments& args);
	//static v8::Handle<v8::Value> v8removeEventCallback(const v8::Arguments& args);

	//void registerEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc);
	//void removeEventCallback(std::string eventName, v8::Persistent<v8::Function> inFunc);

	void registerEventCallback(std::string eventName,boost::function<void(const EventData*)> inFunc);
	void removeEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc);

	//bool loadScript(std::string inScript);

	//void dispatchEvent(std::string eventName);
	//void dispatchEvent(std::string eventName, int argc, v8::Handle<Value> argv[]);
	void dispatchEvent(std::string eventName, const EventData* data);

	//Need compiler v120 for this. God fuck.
	//template<class... Args>
	//void dispatchEvent(std::string eventName, Args... args);

	virtual void release();
	virtual void Update(Ogre::Real deltaTime);

	//void exposeObject(std::string name, Handle<Data> val);

	virtual GO_TYPE getType() = 0;

	int netId;
	bool netOwned; //this means I own this bitch

	void setSocket(boost::shared_ptr<GPENet::SocketBase> base);

protected:
	GameState* owner;
	boost::shared_ptr<GPENet::SocketBase> socket;
	//Persistent<FunctionTemplate> fcnTemplate;

	

private:	
	//std::vector<ScriptingObject*> attachedScripts;
	//std::unordered_map<std::string, std::list<v8::Persistent<v8::Function>>> events;
	std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>> eventsCpp;
	
	bool released;
	
};