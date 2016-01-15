#include "stdafx.h"

#include "Physics.hpp"
#include <Ogre.h>
#include "GameState.hpp"

static PxDefaultAllocator gDefaultAllocatorCallback;
static PxDefaultErrorCallback gDefaultErrorCallback;

template<> gpe::Physics* Ogre::Singleton<gpe::Physics>::msSingleton = 0;


PxFilterFlags FilterShader(
	PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize) {
	// let triggers through
	if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1)) {
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
		return PxFilterFlag::eDEFAULT;
	}
	// generate contacts for all that were not filtered above
	pairFlags = PxPairFlag::eCONTACT_DEFAULT;

	// trigger the contact callback for pairs (A,B) where
	// the filtermask of A contains the ID of B and vice versa.
	if ((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;

	return PxFilterFlag::eDEFAULT;
}

//PxSimulationFilterShader gDefaultFilterShader = PxDefaultSimulationFilterShader;
PxSimulationFilterShader g_default_filter_shader = FilterShader;

namespace gpe {	
	Physics::Physics() : physics_(0), cooking_(0), cuda_context_manager_(0){
		Ogre::Log* log = Ogre::LogManager::getSingleton().getDefaultLog();

		PxAllocatorCallback* allocator = &gDefaultAllocatorCallback;

		PxFoundation* mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *allocator, gDefaultErrorCallback);
		if (!mFoundation)
			log->logMessage("PxCreateFoundation failed!");

		//not build for v110 compiler yet
		/*PxProfileZoneManager* mProfileZoneManager = &PxProfileZoneManager::createProfileZoneManager(mFoundation);
		if(!mProfileZoneManager)
		log->logMessage("PxProfileZoneManager::createProfileZoneManager failed!");*/

		//	if(create_cuda_context_manager)
		//	{
		//#ifdef PX_WINDOWS
		//		pxtask::CudaContextManagerDesc cudaContextManagerDesc;
		//		cuda_context_manager_ = pxtask::createCudaContextManager(*mFoundation, cudaContextManagerDesc, mProfileZoneManager);
		//		if( cuda_context_manager_ )
		//		{
		//			if( !cuda_context_manager_->contextIsValid() )
		//			{
		//				cuda_context_manager_->release();
		//				cuda_context_manager_ = NULL;
		//			}
		//		}
		//#endif
		//	}

		PxTolerancesScale scale;
		scale.length = 1;				// length in cm
		scale.mass = 1;				// mass in grams
		scale.speed *= scale.length;	// speed in cm/s

		physics_ = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, scale, true);
		if (!physics_)
			log->logMessage("PxCreatePhysics failed!");

		//if(getApplication().getOrCreateProfileZone(*mFoundation))
		//	mProfileZoneManager->addProfileZone(*getApplication().getProfileZone());

		if (!PxInitExtensions(*physics_))
			log->logMessage("PxInitExtensions failed!");

		PxCookingParams params(scale);
		params.meshWeldTolerance = 0.001f;
		params.meshPreprocessParams = PxMeshPreprocessingFlags(PxMeshPreprocessingFlag::eWELD_VERTICES | PxMeshPreprocessingFlag::eREMOVE_UNREFERENCED_VERTICES | PxMeshPreprocessingFlag::eREMOVE_DUPLICATED_TRIANGLES);
		cooking_ = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, params);
		if (!cooking_)
			log->logMessage("PxCreateCooking failed!");

		/*if (create_cuda_context_manager)
		{
		pxtask::CudaContextManagerDesc cudaContextManagerDesc;
		cuda_context_manager_ = pxtask::createCudaContextManager(cudaContextManagerDesc, &physics_->getProfileZoneManager());
		}*/

		default_material_ = physics_->createMaterial(0.9f, 0.5f, 0.0f);
		default_material_->setFrictionCombineMode(PxCombineMode::eMAX);
		default_material_->setRestitutionCombineMode(PxCombineMode::eMAX);

		msSingleton = this;
	}

	Physics::~Physics() {

	}

	PxSceneDesc Physics::CreateDefaultSceneDesc(PxVec3 gravity, PxSimulationEventCallback* callback, int num_threads) {
		Ogre::Log* log = Ogre::LogManager::getSingleton().getDefaultLog();

		PxSceneDesc scenedesc(physics_->getTolerancesScale());

		scenedesc.gravity = gravity;

		if (!scenedesc.cpuDispatcher) {
			PxCpuDispatcher* cpu_dispatcher = physx::PxDefaultCpuDispatcherCreate(num_threads);
			if (!cpu_dispatcher)
				log->logMessage("PxDefaultCpuDispatcherCreate failed!");
			scenedesc.cpuDispatcher = cpu_dispatcher;
		}
		if (!scenedesc.filterShader)
			scenedesc.filterShader = g_default_filter_shader;

		scenedesc.simulationEventCallback = callback;

		if (!scenedesc.gpuDispatcher && cuda_context_manager_) {
			scenedesc.gpuDispatcher = cuda_context_manager_->getGpuDispatcher();
		}
		

		return scenedesc;
	}

	PhysicsScene* Physics::CreateScene(PxVec3 gravity, PxSimulationEventCallback* callback, Ogre::SceneManager* scene_manager, int num_threads) {
		Ogre::Log* log = Ogre::LogManager::getSingleton().getDefaultLog();

		PxSceneDesc scenedesc = CreateDefaultSceneDesc(gravity, callback, num_threads);
		PxScene* physics_scene = physics_->createScene(scenedesc);

		if (!physics_scene)
			log->logMessage("createScene failed!");

		PxControllerManager* controller_manager = PxCreateControllerManager(*physics_scene);
		VisualDebugger*	visual_debugger = new VisualDebugger(physics_scene, scene_manager);

		return new PhysicsScene(physics_scene, scenedesc.cpuDispatcher, controller_manager, visual_debugger);
	}

	PhysicsScene* Physics::CreateScene(PxSceneDesc& scenedesc, Ogre::SceneManager* scene_manager) {
		Ogre::Log* log = Ogre::LogManager::getSingleton().getDefaultLog();

		PxScene* physics_scene = physics_->createScene(scenedesc);

		if (!physics_scene)
			log->logMessage("createScene failed!");

		PxControllerManager* controller_manager = PxCreateControllerManager(*physics_scene);
		VisualDebugger*	visual_debugger = new VisualDebugger(physics_scene, scene_manager);

		return new PhysicsScene(physics_scene, scenedesc.cpuDispatcher, controller_manager, visual_debugger);
	}

	PhysicsScene::PhysicsScene(PxScene* scene, PxCpuDispatcher* cpu_dispatcher, PxControllerManager* controller_manager, VisualDebugger* visual_debugger) : scene_(scene), cpu_dispatcher_(cpu_dispatcher), controller_manager_(controller_manager), visual_debugger_(visual_debugger) {
#if _DEBUG
		visual_debugger_->showAll();
		visual_debugger_hidden_ = false;
#else 
		visual_debugger_->hideAll();
		visual_debugger_hidden_ = true;
#endif
	}

}