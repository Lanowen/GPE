#include <Physics.hpp>

template<> Physics* Ogre::Singleton<Physics>::msSingleton = 0;

static PxDefaultAllocator gDefaultAllocatorCallback;
static PxDefaultErrorCallback gDefaultErrorCallback;

Physics::Physics() : mPhysics(0), mCooking(0), mCudaContextManager(0) {

}

Physics::~Physics(){

}

void Physics::init(bool mCreateCudaCtxManager){
	
	Ogre::Log* m_pLog = m_pLog = Ogre::LogManager::getSingleton().getDefaultLog();

	PxAllocatorCallback* allocator = &gDefaultAllocatorCallback;

	//PxFoundation& foundation = mPhysics->getFoundation();

	PxFoundation* mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *allocator, gDefaultErrorCallback);
	if(!mFoundation)
		m_pLog->logMessage("PxCreateFoundation failed!");

	//not build for v110 compiler yet
	/*PxProfileZoneManager* mProfileZoneManager = &PxProfileZoneManager::createProfileZoneManager(mFoundation);
	if(!mProfileZoneManager)
		m_pLog->logMessage("PxProfileZoneManager::createProfileZoneManager failed!");*/

//	if(mCreateCudaCtxManager)
//	{
//#ifdef PX_WINDOWS
//		pxtask::CudaContextManagerDesc cudaContextManagerDesc;
//		mCudaContextManager = pxtask::createCudaContextManager(*mFoundation, cudaContextManagerDesc, mProfileZoneManager);
//		if( mCudaContextManager )
//		{
//			if( !mCudaContextManager->contextIsValid() )
//			{
//				mCudaContextManager->release();
//				mCudaContextManager = NULL;
//			}
//		}
//#endif
//	}

	PxTolerancesScale scale;
	scale.length = 1;				// length in cm
	scale.mass = 1;				// mass in grams
	scale.speed *= scale.length;	// speed in cm/s

	//mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *allocator, gDefaultErrorCallback, PxTolerancesScale());
	//mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, physx::PxTolerancesScale(), true, mProfileZoneManager);
	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, scale, true);
	if(!mPhysics)
		m_pLog->logMessage("PxCreatePhysics failed!");

	//if(getApplication().getOrCreateProfileZone(*mFoundation))
	//	mProfileZoneManager->addProfileZone(*getApplication().getProfileZone());

	if(!PxInitExtensions(*mPhysics))
		m_pLog->logMessage("PxInitExtensions failed!");

	PxCookingParams params(scale);
	params.meshWeldTolerance = 0.001f;
	params.meshPreprocessParams = PxMeshPreprocessingFlags(PxMeshPreprocessingFlag::eWELD_VERTICES | PxMeshPreprocessingFlag::eREMOVE_UNREFERENCED_VERTICES | PxMeshPreprocessingFlag::eREMOVE_DUPLICATED_TRIANGLES);
	mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, params);
	if(!mCooking)
		m_pLog->logMessage("PxCreateCooking failed!");

	/*if (mCreateCudaCtxManager)
	{
		pxtask::CudaContextManagerDesc cudaContextManagerDesc;
		mCudaContextManager = pxtask::createCudaContextManager(cudaContextManagerDesc, &mPhysics->getProfileZoneManager());
	}*/
}

