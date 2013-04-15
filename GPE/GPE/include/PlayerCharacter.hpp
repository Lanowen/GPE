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
#include <IInputListener.hpp>

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

class PlayerCharacter : public physx::PxUserControllerHitReport/*, public physx::PxControllerBehaviorCallback*/, public GameObject, public IInputListener
{
	friend class V8PlayerCharacter;
public:
    PlayerCharacter(OIS::Keyboard* im_pKeyboard, OIS::JoyStick* im_pJoyStick, int im_pJoyDeadZone, GameState* owner);
    virtual ~PlayerCharacter();

	virtual void release();
	virtual void Update(Real deltaTime);

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
    bool keyReleased(const OIS::KeyEvent &keyEventRef);

	void giveGamera(Camera* cam);

protected:		
    void getInput(Real deltaTime);
	virtual void onShapeHit(const physx::PxControllerShapeHit & hit);
	virtual void onControllerHit(const physx::PxControllersHit& hit);
	virtual void onObstacleHit(const physx::PxControllerObstacleHit& hit);
	static void addForceAtLocalPos(physx::PxRigidBody& body, const physx::PxVec3& force, const physx::PxVec3& pos, physx::PxForceMode::Enum mode, bool wakeup=true);
	static inline void addForceAtPosInternal(physx::PxRigidBody& body, const physx::PxVec3& force, const physx::PxVec3& pos, physx::PxForceMode::Enum mode, bool wakeup);

	void AdvancePhysics(Real deltaTime);
	void UpdateAnimation(Real deltaTime);

	

public:
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
	bool     mGrounded, mIsTurning, mShiftPressed, mFlipping;
	//Real     mMaxGroundSpeed, mMaxAirSpeed, mMaxTurnSpeed, mAirMovement;
	Radian   mYaw_Target;
	PxVec3	 mInputVel, mVelocity;

	PxController* mCCT;
	PxPhysics* mPhys;
	PxScene* mPhysScene;
	//std::map<STATE, Animation> animations;
	Camera* m_pCamera;
};