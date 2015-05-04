#pragma once

#include <PxPhysicsAPI.h>
#include <extensions/PxExtensionsAPI.h>
#include <extensions/PxDefaultAllocator.h>
#include <extensions/PxDefaultErrorCallback.h>
#include <extensions/PxDefaultCpuDispatcher.h>
#include <extensions/PxDefaultSimulationFilterShader.h>
#include <pxtask/PxCudaContextManager.h>
#include <foundation/PxFoundation.h>

#include <OgreSingleton.h>

#include <VisualDebugger.hpp>

using namespace physx;



namespace gpe {

	class GameState;
	
	class PhysicsScene {
		friend class Physics;
	public:
		~PhysicsScene();

		inline bool get_fetching_results() { return fetching_results_; }

		PX_FORCE_INLINE void AdvanceSimulation(PxReal timestep) {
			scene_->simulate(timestep);
			fetching_results_ = true;
			PxU32 err;
			bool res = scene_->fetchResults(true, &err);
			fetching_results_ = false;

			if (!visual_debugger_hidden_)
				visual_debugger_->update(scene_->getRenderBuffer());
		}

		inline void ToggleVisualDebugger() {
			if (visual_debugger_hidden_) {
				visual_debugger_hidden_ = false;
				visual_debugger_->showAll();
			}
			else {
				visual_debugger_hidden_ = true;
				visual_debugger_->hideAll();
			}
		}

		inline PxScene* get_scene() { return scene_; }
		inline PxCpuDispatcher* get_cpu_dispatcher() { return cpu_dispatcher_; }
		inline PxControllerManager* get_controller_manager() { return controller_manager_; }
		inline VisualDebugger* get_visual_debugger() { return visual_debugger_; }

	private:
		PhysicsScene(PxScene* scene, PxCpuDispatcher* cpu_dispatcher, PxControllerManager* controller_manager, VisualDebugger* visual_debugger);

	private:
		PxScene* scene_;
		PxCpuDispatcher*		cpu_dispatcher_;
		PxControllerManager*		controller_manager_;
		VisualDebugger*				visual_debugger_;		

		bool fetching_results_;
		bool visual_debugger_hidden_;
	};

	class Physics : public Ogre::Singleton<Physics> {
	public:
		Physics(bool create_cuda_context_manager);
		virtual ~Physics();

		inline PxPhysics* get_physics() { return physics_; }
		inline PxCooking* get_cooking() { return cooking_; }
		inline PxCudaContextManager* get_cuda_context_manager() { return cuda_context_manager_; }

		PhysicsScene* CreateScene(PxVec3 gravity, GameState* gs, int num_threads = 1);
		PhysicsScene* CreateScene(PxSceneDesc& scenedesc, GameState* gs);
		
		static inline Physics& getSingleton() { assert(msSingleton);  return *msSingleton; }
		static inline Physics* getSingletonPtr() { return msSingleton; }

	private:
		PxPhysics*						physics_;
		PxCooking*						cooking_;
		PxCudaContextManager*		cuda_context_manager_;
	};
}