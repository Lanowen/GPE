#pragma once

#include <Ogre.h>

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>
#include <OIS/OISJoyStick.h>

#include <PxPhysicsAPI.h>
#include <characterkinematic/PxController.h>
#include <characterkinematic/PxBoxController.h>
#include <characterkinematic/PxControllerManager.h>

#include <GameObject.hpp>
#include <IKeyListener.hpp>
#include <IJoyStickListener.hpp>

enum DIRECTION {
	LEFT = 0,
	RIGHT
};

enum GUNDIRECTION {
	UPANGLED,
	DOWNANGLED,
	FORWARD,
	UP,
	DOWN
};

enum STATE {
	IDLE = 0,
	WALKING,
	RUNNING,
	CROUCHED,
	MORPH_BALL,
	GRAPPLE,
	SHOOTING,
	JUMPING,
	FALLING,
	FLIPPNG,
	WALL_JUMPING,
	HURT,
	DEAD
};

enum ARM_STATE {
	ARM_IDLE = 0,
	ARM_SHOOTING,
	ARM_GRAPPLE,
};

using namespace Ogre;
using namespace physx;

class PlayerCharacter : public physx::PxUserControllerHitReport/*, public physx::PxControllerBehaviorCallback*/, public GameObject, public IKeyListener, public IJoyStickListener
{
	friend class V8PlayerCharacter;
public:
    PlayerCharacter(OIS::Keyboard* im_pKeyboard, OIS::JoyStick* im_pJoyStick, int im_pJoyDeadZone, GameState* owner);
    virtual ~PlayerCharacter();

	virtual void release();
	virtual void Update(Real deltaTime);

	virtual bool keyPressed(const OIS::KeyEvent &keyEventRef);
    virtual bool keyReleased(const OIS::KeyEvent &keyEventRef);

	virtual bool povMoved( const OIS::JoyStickEvent &e, int pov );
    virtual bool axisMoved( const OIS::JoyStickEvent &e, int axis );
    virtual bool sliderMoved( const OIS::JoyStickEvent &e, int sliderID );
    virtual bool buttonPressed( const OIS::JoyStickEvent &e, int button );
    virtual bool buttonReleased( const OIS::JoyStickEvent &e, int button );

	void giveGamera(Camera* cam);

	bool IsAlive();

	Vector3 getPosition();
	void setPosition(Vector3 pos);
	void DoHit(PxControllersHit hit);

	virtual GO_TYPE getType() { return GO_TYPE::PLAYER; }

	bool isInvulnerable();
	bool PlayerCharacter::canMove();

protected:		
    void getInput(Real deltaTime);
	virtual void onShapeHit(const physx::PxControllerShapeHit & hit);
	virtual void onControllerHit(const physx::PxControllersHit& hit);
	virtual void onObstacleHit(const physx::PxControllerObstacleHit& hit);
	static void addForceAtLocalPos(physx::PxRigidBody& body, const physx::PxVec3& force, const physx::PxVec3& pos, physx::PxForceMode::Enum mode, bool wakeup=true);
	static inline void addForceAtPosInternal(physx::PxRigidBody& body, const physx::PxVec3& force, const physx::PxVec3& pos, physx::PxForceMode::Enum mode, bool wakeup);

	void AdvancePhysics(Real deltaTime);
	void UpdateAnimation(Real deltaTime);

	void OnDamage(const EventData* data);
	void getHurt(PxVec3 direction);

	void updateFlipping(Real deltaTime);
	void addTimeToAnimations(Real deltaTime);

public:
	bool isAlive;
    int m_pJoyDeadZone;
    OIS::Keyboard* m_pKeyboard;
    OIS::JoyStick* m_pJoyStick;

	Entity* ent;
	Bone* m_GunTip;
        
    AnimationStateSet* m_aniStates;

	SceneNode* node,* childNode;
	//Real     mMaxJumpVelocity, mJumpTime, mFallTime;
	DIRECTION mDirection;
	GUNDIRECTION mGunDirection;
	Real timeSinceLastShot;
	bool     mGrounded, mIsTurning, mRunningPressed, mFlipping;
	//Real     mMaxGroundSpeed, mMaxAirSpeed, mMaxTurnSpeed, mAirMovement;
	Radian   mYaw_Target;
	PxVec3	 mInputVel, mVelocity;

	PxController* mCCT;
	PxPhysics* mPhys;
	PxScene* mPhysScene;
	//std::map<STATE, Animation> animations;
	Camera* m_pCamera;

	Real timeSinceHurt;
	int life;
	PxVec3 hurtTravelDir;
};