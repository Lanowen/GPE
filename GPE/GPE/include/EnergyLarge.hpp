#pragma once

#include <PowerUp.hpp>

using namespace Ogre;
using namespace physx;
using namespace gpe;

class EnergyLarge : public PowerUp {
public:
	EnergyLarge(GameState* owner, Vector3 pos);
	virtual ~EnergyLarge();

	virtual POWERUP_TYPE getPowerUpType() { return ENERGY_LARGE; }

	virtual void Update(Ogre::Real deltaTime);

protected:
	Entity* ent;
	Real scale, timer;
};