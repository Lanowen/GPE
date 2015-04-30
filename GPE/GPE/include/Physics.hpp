#pragma once

#include <PxPhysicsAPI.h>
#include <extensions/PxExtensionsAPI.h>
#include <extensions/PxDefaultAllocator.h>
#include <extensions/PxDefaultErrorCallback.h>
#include <extensions/PxDefaultCpuDispatcher.h>
#include <extensions/PxDefaultSimulationFilterShader.h>
#include <pxtask/PxCudaContextManager.h>
#include <foundation/PxFoundation.h>

#include <Ogre.h>
//#include <OgreSingleton.h>

using namespace physx;

class Physics : public Ogre::Singleton<Physics>
{
public:
	Physics();
	virtual ~Physics();
	void init(bool mCreateCudaCtxManager);
	PxPhysics*						mPhysics;
	PxCooking*						mCooking;
	PxCudaContextManager*		mCudaContextManager;
};