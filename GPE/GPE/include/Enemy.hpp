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
public:
    Enemy(GameState* owner);
	virtual ~Enemy();

	virtual void onShapeHit(const physx::PxControllerShapeHit & hit);
	virtual void onControllerHit(const physx::PxControllersHit& hit);
	virtual void onObstacleHit(const physx::PxControllerObstacleHit& hit);

	virtual void Update(Real deltaTime);
	virtual void release();

protected:
	void advancePhysics(Real deltaTime);
	void updateAnimation(Real deltaTime);

private:
	Entity* ent;
    AnimationStateSet* m_aniStates;
	SceneNode* node, * nodeOffset;
	PxController* mCCT;
	PxScene* mPhysScene;
	PxVec3 moveDir, castDir;
	PxQuat rotRight, rotLeft;
};