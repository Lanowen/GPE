#pragma once

#include "EventDispatcherHelper.hpp"

namespace GPENet
{
	class SocketBase;
}

namespace gpe {

	typedef int GO_TYPE;

	class GameObject : public EventDispatcherHelper {
		friend class GameState;
		friend class NetworkedObjectManager;
	public:
		GameObject(std::string name);
		
		inline GameState* get_owner() { return owner_; }
		inline std::string get_name() { return name_; }
		inline bool get_net_owned() { return net_owned_; }
		inline int get_net_id() { return net_id_; }

		void registerEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc);
		void removeEventCallback(std::string eventName, boost::function<void(const EventData*)> inFunc);

		void dispatchEvent(std::string eventName, const EventData* data);

		//Need compiler v120 for this.....
		//template<class... Args>
		//void dispatchEvent(std::string eventName, Args... args);

		
		virtual void Update(Ogre::Real deltaTime);		

		inline virtual GO_TYPE getType() = 0;
#ifndef WIN8_ARM
		inline void setSocket(std::shared_ptr<GPENet::SocketBase> base) {
			socket_ = base;
		}
#endif

	protected:
		virtual ~GameObject();

#ifndef WIN8_ARM
		std::shared_ptr<GPENet::SocketBase> socket_;
#endif

		//This is where you do your logic adding physics and graphics objects to their respective Scenes
		virtual void AddedToState(GameState* owner) = 0;

		//This is where you do your logic removing physics and graphics objects from their respective Scenes
		virtual void RemovedFromState(GameState* owner) = 0;

	private:
		virtual void release();

		std::unordered_map<std::string, std::list<boost::function<void(const EventData*)>>> eventsCpp_;
		GameState* owner_;
		std::string name_;

		bool released_;
		int net_id_;
		bool net_owned_;
	};

}