#pragma once

#include <Ogre.h>
#include <PxPhysicsAPI.h>
#include <characterkinematic/PxController.h>
#include <characterkinematic/PxBoxController.h>
#include <characterkinematic/PxControllerManager.h>

#include <GameObject.hpp>
#include <GameState.hpp>

using namespace Ogre;
using namespace physx;

class Enemy : public physx::PxUserControllerHitReport/*, public physx::PxControllerBehaviorCallback*/, public GameObject {
	friend class V8Enemy;
public:
    Enemy(GameState* owner, std::string mesh);
	virtual ~Enemy();

	virtual void Update(Real deltaTime);
	virtual void release();

protected:
	void AdvancePhysics(Real deltaTime);
	void UpdateAnimation(Real deltaTime);

	virtual void onShapeHit(const physx::PxControllerShapeHit & hit);
	virtual void onControllerHit(const physx::PxControllersHit& hit);
	virtual void onObstacleHit(const physx::PxControllerObstacleHit& hit);
	static void addForceAtLocalPos(physx::PxRigidBody& body, const physx::PxVec3& force, const physx::PxVec3& pos, physx::PxForceMode::Enum mode, bool wakeup=true);
	static inline void addForceAtPosInternal(physx::PxRigidBody& body, const physx::PxVec3& force, const physx::PxVec3& pos, physx::PxForceMode::Enum mode, bool wakeup);

private:
	Entity* ent;
    AnimationStateSet* m_aniStates;
	SceneNode* node, * childNode;
	PxController* mCCT;
	PxScene* mPhysScene;
	PxVec3 displacement;
	PxVec3 moveDir, castDir;
	PxQuat rotRight, rotLeft;
};