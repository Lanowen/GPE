#pragma once

#include <Ogre.h>
#include <PxPhysicsAPI.h>

#include <GameObject.hpp>

enum POWERUP_TYPE {
	NONE,
	ENERGY_SMALL,
	ENERGY_LARGE,
	MISSILE
};

using namespace Ogre;
using namespace physx;

class PowerUp : public GameObject {
public:
	PowerUp(GameState* owner, Vector3 pos);
	virtual ~PowerUp();

	virtual GO_TYPE getType(){ return POWERUP;}

	virtual POWERUP_TYPE getPowerUpType() { return NONE; }

protected:
	PxActor* actor;
	SceneNode* node;
};