#pragma once

#include <Ogre.h>
#include <list>
#include <vector>
//#include <v8.h>
//#include <ScriptingObject.hpp>
#include <EventDispatcherHelper.hpp>

#include <GameState.hpp>

#include <GPENet.hpp>

namespace gpe {

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

		void registerEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc);
		void removeEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc);

		void dispatchEvent(std::string eventName, const EventData* data);

		//Need compiler v120 for this. God fuck.
		//template<class... Args>
		//void dispatchEvent(std::string eventName, Args... args);

		virtual void release();
		virtual void Update(Ogre::Real deltaTime);

		virtual GO_TYPE getType() = 0;

		int netId;
		bool netOwned; //this means I own this bitch

		void setSocket(boost::shared_ptr<GPENet::SocketBase> base);

	protected:
		GameState* owner;
		boost::shared_ptr<GPENet::SocketBase> socket;

	private:
		std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>> eventsCpp;

		bool released;

	};

}