#pragma once

#include <Ogre.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
//#include <OgreOverlay.h>
//#include <OgreOverlayElement.h>
//#include <OgreOverlayManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISJoyStick.h>

#include <Physics.hpp>


#include <DynamicConstraints.hpp>
//#include <V8Scripting.hpp>
#include <SceneWideEvent.hpp>
#include <NetworkedObjectManager.hpp>

#include <list>

#include <GPENet.hpp>
#include <GameStateManager.hpp>

class PlayerCharacter;
class Enemy;

//|||||||||||||||||||||||||||||||||||||||||||||||

enum QueryFlags
{
    BG_SELECT       = 1<<0,
    TILE_OBJECT		= 1<<1
};

//|||||||||||||||||||||||||||||||||||||||||||||||

enum NEW_NETUPDATES {
	CREATE_ENEMY= GPENet::UPDATE_TYPE::E_LAST + 1,
	CREATE_MAINPLAYER,
	CREATE_PLAYER,
	CREATE_BULLET,
	PLAYER_INPUTVEL,
	SET_POS,
	ENEMY_POS,
	ENEMY_DEATH,
	PLAYER_INPUT_BUTTON_PRESS,
	PLAYER_INPUT_BUTTON_RELEASE,
	PLAYER_DEATH,
	PLAYER_HURT,
	COLLECT_POWERUP,
	CREATE_POWERUP,
	NET_EVENT
};


using namespace Ogre;
using namespace physx;

namespace gpe {

	class GameObject;

	class GameState : public FrameListener, public PxSimulationEventCallback//, OgreBites::SdkTrayListener
	{
		friend class IKeyListener;
		friend class IJoyStickListener;
		friend class GameStateManager;
	public:
		GameState();
		~GameState();

		inline PhysicsScene* get_physics_scene() { return physics_scene_; }
		inline SceneManager* get_scene_manager() { return scene_manager_; }
		inline GameStateManager* get_gamestatemanager() { return gamestatemanager_; }

		void AddGameObject(GameObject* go);
		void DeleteGameObject(GameObject* go);
		void RemoveGameObject(GameObject* go);

		void RespawnPlayer(PlayerCharacter* player);
		PlayerCharacter* SpawnPlayer();
		PlayerCharacter* SpawnMainPlayer();

		void RespawnPlayer(PlayerCharacter* player, Vector3 pos);
		PlayerCharacter* SpawnPlayer(Vector3 pos);
		PlayerCharacter* SpawnMainPlayer(Vector3 pos);

		void RegisterHit(PlayerCharacter* player, PxControllersHit hit);

		static std::string ip_;
		static bool isserver_;

	private:

		inline void set_gamestatemanager(GameStateManager* gsm) { gamestatemanager_ = gsm; }
		
		struct PlayerHit {
			bool operator == (const PlayerHit& other) {
				return player == other.player;
			}

			PlayerCharacter* player;
			PxControllersHit hit;
		};

		void createScene();
		void Enter() {
			gamestatemanager_->get_render_window()->resetStatistics();

			viewport_ = gamestatemanager_->get_render_window()->addViewport(0);
			viewport_->setBackgroundColour(Ogre::ColourValue(0, 0, 0, 1.0f));

			camera_->setAspectRatio(Ogre::Real(viewport_->getActualWidth()) /
									Ogre::Real(viewport_->getActualHeight()));

			viewport_->setCamera(camera_);
		}
		void Exit() {}
		void Pause() {}
		void Resume() {}
		std::string get_name() { return ""; }

		Vector3 GetBestSpawnpoint();

		void MoveCamera(double timeSinceLastFrame);
		//void buildGUI();

		void RegisterKeyListener(IKeyListener* listener);
		void DeregisterKeyListener(IKeyListener* listener);
		void RegisterJoyListener(IJoyStickListener* listener);
		void DeregisterJoyListener(IJoyStickListener* listener);

		// FrameListener
		virtual bool frameRenderingQueued(const FrameEvent& evt);

		// OIS::KeyListener
		virtual bool keyPressed(const OIS::KeyEvent &e);
		virtual bool keyReleased(const OIS::KeyEvent &e);
		// OIS::MouseListener
		virtual bool mouseMoved(const OIS::MouseEvent &e);
		virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		// OIS::JoyStickListener
		virtual bool povMoved(const OIS::JoyStickEvent &e, int pov);
		virtual bool axisMoved(const OIS::JoyStickEvent &e, int axis);
		virtual bool sliderMoved(const OIS::JoyStickEvent &e, int sliderID);
		virtual bool buttonPressed(const OIS::JoyStickEvent &e, int button);
		virtual bool buttonReleased(const OIS::JoyStickEvent &e, int button);

		void update(double timeSinceLastFrame);

		

	protected:

		virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count);
		virtual void onWake(PxActor** actors, PxU32 count);
		virtual void onSleep(PxActor** actors, PxU32 count);
		virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count);

		//Netwak stuff
		void createEnemy(GPENet::Datagram dg);
		void createMainPlayer(GPENet::Datagram dg);
		void createPlayer(GPENet::Datagram dg);
		void createBullet(GPENet::Datagram dg);
		void getNetEvent(GPENet::Datagram dg);

		void onClientConnect(GPENet::Datagram dg);
		void onPlayerDied(GPENet::Datagram dg);

		void handleInputVel(GPENet::Datagram dg);
		void handleButtonPressed(GPENet::Datagram dg);
		void handleButtonReleased(GPENet::Datagram dg);
		void handleEnemyDeath(GPENet::Datagram dg);


		void setIDPosition(GPENet::Datagram dg);

		void handlePlayerHurt(GPENet::Datagram dg);
		void handleDisconnect(GPENet::Datagram dg);
		void handlePowerup(GPENet::Datagram dg);
		void handleCreatePowerup(GPENet::Datagram dg);

	public:
		void handleEnemyDeathPowerup(Vector3 pos);

	private:

		Viewport*				viewport_;

		PhysicsScene* physics_scene_;
		physx::PxMaterial*					physics_material_;

		GameStateManager* gamestatemanager_;

		std::vector<Vector3> spawn_points_;
		std::vector<PlayerCharacter*> players_;
		std::list<PlayerHit> hits_this_frame_;

		std::vector<GameObject*> gameobjects_;
		std::vector<IKeyListener*> keylisteners_;
		std::vector<IJoyStickListener*> joylisteners_;

		unsigned int                zoomState;

		void						advanceSimulation(float dtime);
		bool				        m_bLMouseDown, m_bRMouseDown;

		Camera*		        camera_;
		SceneManager*	        scene_manager_;
		bool				        b_shutdown_;

		std::list<GameObject*> toDelete;

		NetworkedObjectManager netMan;
		boost::shared_ptr<GPENet::SocketBase> socket;
		Real hackSendEnemyPosTime;

	};

}