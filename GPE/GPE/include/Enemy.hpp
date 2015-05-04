#pragma once

#include <Ogre.h>
#include <PxPhysicsAPI.h>
#include <characterkinematic/PxController.h>
#include <characterkinematic/PxBoxController.h>
#include <characterkinematic/PxControllerManager.h>

#include <GameObject.hpp>
#include <GameState.hpp>

#include <Projectile.hpp>

using namespace Ogre;
using namespace physx;
using namespace gpe;

class Enemy : public PxUserControllerHitReport/*, public physx::PxControllerBehaviorCallback*/, public GameObject {
public:
    Enemy(GameState* owner, std::string mesh/*, std::string script*/, bool netOwned = true);
	virtual ~Enemy();

	virtual void Update(Real deltaTime);
	virtual void release();

	Vector3 getPosition();
	void setPosition(PxVec3 pos);

	virtual GO_TYPE getType() { return GO_TYPE::ENEMY; }

protected:
	void AdvancePhysics(Real deltaTime);
	void UpdateAnimation(Real deltaTime);

	virtual void onShapeHit(const physx::PxControllerShapeHit & hit);
	virtual void onControllerHit(const physx::PxControllersHit& hit);
	virtual void onObstacleHit(const physx::PxControllerObstacleHit& hit);
	static void addForceAtLocalPos(physx::PxRigidBody& body, const physx::PxVec3& force, const physx::PxVec3& pos, physx::PxForceMode::Enum mode, bool wakeup=true);
	static inline void addForceAtPosInternal(physx::PxRigidBody& body, const physx::PxVec3& force, const physx::PxVec3& pos, physx::PxForceMode::Enum mode, bool wakeup);

	void OnDamage(const EventData* data);

private:
	Entity* ent;
    AnimationStateSet* m_aniStates;
	SceneNode* node, * childNode;
	PxController* mCCT;
	PxScene* mPhysScene;
	PxVec3 moveDir, castDir;
	PxQuat rotRight, rotLeft;
	int rotCount;
	bool falling;
	int life;
};