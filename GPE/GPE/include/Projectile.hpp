#pragma once

#include <Ogre.h>
#include <PxPhysicsAPI.h>

#include <GameObject.hpp>
#include <GameState.hpp>

using namespace physx;
using namespace Ogre;
using namespace gpe;

class ProjectileEvent: public EventData {
public:
	ProjectileEvent(){};
	virtual ~ProjectileEvent(){};

	int power;
};

class Projectile : public GameObject {
public:
	Projectile(gpe::GameState* owner, GameObject* spawner, Vector3 pos, Quaternion dir, bool netOwned = true);
	Projectile(gpe::GameState* owner, GameObject* spawner, PxVec3 pos, PxQuat dir, bool netOwned = true);
	virtual ~Projectile();

	virtual GO_TYPE getType() { return GO_TYPE::PROJECTILE; }

	virtual void Update(Real deltaTime);

	static void Initialize(SceneManager* sceneMgr);

	PxVec3 getPosition();

	GameObject* getSpawner();

private:
	void Initialize(PxVec3 pos, PxQuat dir);

	void OnProjectileHit(const EventData* other);

private:
	PxRigidDynamic* actor;
	SceneNode* node;
	GameObject* spawner;

	AnimationState* mAnimState;

	RibbonTrail* mTrail;
	Billboard* mFlare;
	Light* light;
	static BillboardSet* bbs;
};