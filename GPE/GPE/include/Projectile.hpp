#pragma once

#include <Ogre.h>
#include <PxPhysicsAPI.h>

#include <GameObject.hpp>
#include <GameState.hpp>

using namespace physx;
using namespace Ogre;

class Projectile : public GameObject {
public:
	Projectile(GameState* owner, GameObject* spawner, Vector3 pos, Quaternion dir);
	Projectile(GameState* owner, GameObject* spawner, PxVec3 pos, PxQuat dir);
	virtual ~Projectile();

	virtual GO_TYPE getType() { return GO_TYPE::PROJECTILE; }

private:
	void Initialize(PxVec3 pos, PxQuat dir);


private:
	PxRigidDynamic* actor;
	SceneNode* node;
	GameObject* spawner;
};