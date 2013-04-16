//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef Game_STATE_HPP
#define Game_STATE_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include <Ogre.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>
#include <OIS/OISJoyStick.h>

#include <Physics.hpp>

#include <VisualDebugger.hpp>
#include <DynamicConstraints.hpp>
//#include <V8Scripting.hpp>
#include <SceneWideEvent.hpp>

#include <list>

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

	void RegisterHit(PlayerCharacter* player, PxControllersHit hit);

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

    int                         m_pJoyDeadZone;

    Ogre::String                mResourcesCfg;
    Ogre::String                mPluginsCfg;

	physx::PxPhysics*					mPhysics;
	physx::PxCooking*					mCooking;
	physx::PxScene*						mPxScene;
	physx::PxMaterial*					mMaterial;
	physx::PxDefaultCpuDispatcher*		mCpuDispatcher;
	physx::pxtask::CudaContextManager*		mCudaContextManager;
	physx::PxU32						mNbThreads;
	bool						mCreateCudaCtxManager;
	physx::PxControllerManager*		mControllerManager;
	VisualDebugger*				mVisualDebugger;

	SceneWideEvent*				mEventHandler;
	//V8Scripting*				mScripting;

	std::vector<Vector3> spawnPoints;
	std::vector<PlayerCharacter*> players;
	std::list<PlayerHit> hitsThisFrame;


protected:

	virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count);
	virtual void onWake(PxActor** actors, PxU32 count);
	virtual void onSleep(PxActor** actors, PxU32 count);
	virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
	virtual void onTrigger(PxTriggerPair* pairs, PxU32 count);

private:
    //PlayerCharacter*                m_pPlayerChar;
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

};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||
