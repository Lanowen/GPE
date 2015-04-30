//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef Game_STATE_HPP
#define Game_STATE_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

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

#include <VisualDebugger.hpp>
#include <DynamicConstraints.hpp>
//#include <V8Scripting.hpp>
#include <SceneWideEvent.hpp>
#include <NetworkedObjectManager.hpp>

#include <list>

#include <GPENet.hpp>

class PlayerCharacter;
class GameObject;
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

class GameState : public Singleton<GameState>, public FrameListener, public WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener, public PxSimulationEventCallback//, OgreBites::SdkTrayListener
{
	friend class IKeyListener;
	friend class IJoyStickListener;

public:
	GameState();
	~GameState();

	bool initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener = 0, OIS::MouseListener *pMouseListener = 0);

	PxPhysics* getPhysics();
	PxScene* getMainPhysicsScene();
	PxControllerManager* getControllerManager();

	void AddGameObject(GameObject* go);
	void DeleteGameObject(GameObject* go);
	void RemoveGameObject(GameObject* go);

	void RespawnPlayer(PlayerCharacter* player);
	PlayerCharacter* SpawnPlayer();
	PlayerCharacter* SpawnMainPlayer();

	void RespawnPlayer(PlayerCharacter* player,Vector3 pos);
	PlayerCharacter* SpawnPlayer(Vector3 pos);
	PlayerCharacter* SpawnMainPlayer(Vector3 pos);

	void RegisterHit(PlayerCharacter* player, PxControllersHit hit);

	static std::string ip;
	static bool isServer;

private:

	struct PlayerHit {
		bool operator == (const PlayerHit& other){
			return player == other.player;
		}

		PlayerCharacter* player;
		PxControllersHit hit;
	};

	void enter();
	void createScene();
	void exit();

	Vector3 GetBestSpawnpoint();

	void moveCamera();
	void getInput(double timeSinceLastFrame);
    //void buildGUI();

    void RegisterKeyListener(IKeyListener* listener);
	void DeregisterKeyListener(IKeyListener* listener);
	void RegisterJoyListener(IJoyStickListener* listener);
	void DeregisterJoyListener(IJoyStickListener* listener);

	// FrameListener
    virtual bool frameRenderingQueued(const FrameEvent& evt);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &e );
    virtual bool keyReleased( const OIS::KeyEvent &e );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &e );
    virtual bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );
    // OIS::JoyStickListener
    virtual bool povMoved( const OIS::JoyStickEvent &e, int pov );
    virtual bool axisMoved( const OIS::JoyStickEvent &e, int axis );
    virtual bool sliderMoved( const OIS::JoyStickEvent &e, int sliderID );
    virtual bool buttonPressed( const OIS::JoyStickEvent &e, int button );
    virtual bool buttonReleased( const OIS::JoyStickEvent &e, int button );

// WindowEventListener

    //Adjust mouse clipping area
    virtual void windowResized(RenderWindow* rw);

    //Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(RenderWindow* rw);

	void update(double timeSinceLastFrame);

	Root*				    m_pRoot;
	RenderWindow*			m_pRenderWnd;
	Viewport*				m_pViewport;
	Log*				    m_pLog;
	Timer*				m_pTimer;

	OIS::InputManager*			m_pInputMgr;
	OIS::Keyboard*				m_pKeyboard;
	OIS::Mouse*				    m_pMouse;
	OIS::JoyStick*              m_pJoyStick;

    int                         m_JoyDeadZone;

    Ogre::String                mResourcesCfg;
    Ogre::String                mPluginsCfg;

	physx::PxPhysics*					mPhysics;
	physx::PxCooking*					mCooking;
	physx::PxScene*						mPxScene;
	physx::PxMaterial*					mMaterial;
	physx::PxDefaultCpuDispatcher*		mCpuDispatcher;
	physx::PxCudaContextManager*		mCudaContextManager;
	physx::PxU32						mNbThreads;
	bool						mCreateCudaCtxManager;
	physx::PxControllerManager*		mControllerManager;
	VisualDebugger*				mVisualDebugger;

	SceneWideEvent*				mEventHandler;
	//V8Scripting*				mScripting;

	std::vector<Vector3> spawnPoints;
	std::vector<PlayerCharacter*> players;
	std::list<PlayerHit> hitsThisFrame;

////#ifdef CLIENT
//	boost::shared_ptr<GPENet::Client> client;
////#endif
////#ifdef SERVER
//	boost::shared_ptr<GPENet::Server> server;
////#endif

	boost::shared_ptr<GPENet::SocketBase> socket;

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
    PlayerCharacter*                m_pPlayerChar;
	//std::vector<Enemy*> mEnemies;

	std::vector<GameObject*> mGameObjects;
	std::vector<IKeyListener*> mKeyListeners;
	std::vector<IJoyStickListener*> mJoyListeners;

	Vector3			    m_TranslateVector;
	Real			        m_MoveSpeed;
	Degree			    m_RotateSpeed;
	float				        m_MoveScale;
	Degree			    m_RotScale;

	RaySceneQuery*		m_pRSQ;
	SceneNode*		    m_pCurrentObject;
	Entity*			    m_pCurrentEntity;
	Entity*			    m_pPlane;
	Plane*                m_pBackPlane;

	unsigned int                zoomState;

	ManualObject*         m_Grid;

	void						advanceSimulation(float dtime);
	bool				        m_bLMouseDown, m_bRMouseDown;

	Camera*		        m_pCamera;
	SceneManager*	        m_pSceneMgr;
    FrameEvent            m_FrameEvent;
    bool				        m_bShutdown;
	bool			pxVisualDebuggerHidden;
	bool fetchingResults;

	std::list<GameObject*> toDelete;

	NetworkedObjectManager netMan;

	Real hackSendEnemyPosTime;

};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
