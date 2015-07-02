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

#include "VisualDebugger.hpp"

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

		inline PxScene* get_scene() const { return scene_; }
		inline PxCpuDispatcher* get_cpu_dispatcher() const { return cpu_dispatcher_; }
		inline PxControllerManager* get_controller_manager() const { return controller_manager_; }
		inline VisualDebugger* get_visual_debugger() const { return visual_debugger_; }

	private:
		PhysicsScene(PxScene* scene, PxCpuDispatcher* cpu_dispatcher, PxControllerManager* controller_manager, VisualDebugger* visual_debugger);

	private:
		PxScene* scene_;
		PxCpuDispatcher* cpu_dispatcher_;
		PxControllerManager* controller_manager_;
		VisualDebugger* visual_debugger_;

		bool fetching_results_;
		bool visual_debugger_hidden_;
	};

	class Physics : public Ogre::Singleton<Physics> {
	public:
		
		virtual ~Physics();

		static void Initialize() { if (!msSingleton) new Physics(); }

		inline PxPhysics* get_physics() { return physics_; }
		inline PxCooking* get_cooking() { return cooking_; }
		inline PxCudaContextManager* get_cuda_context_manager() { return cuda_context_manager_; }
		inline PxMaterial* get_default_material() { return default_material_; }

		PhysicsScene* CreateScene(PxVec3 gravity, PxSimulationEventCallback* callback, Ogre::SceneManager* scene_manager, int num_threads = 1);
		PhysicsScene* CreateScene(PxSceneDesc& scenedesc, Ogre::SceneManager* scene_manager);
		
		static inline Physics& getSingleton() { assert(msSingleton);  return *msSingleton; }
		static inline Physics* getSingletonPtr() { return msSingleton; }

		static inline PxTriangleMesh* CreateTrimesh(char* src) {
			PxDefaultFileInputData readbuffer(src);
			if (!readbuffer.isValid() || readbuffer.getLength() == 0)
				return 0;

			PxTriangleMesh* trimesh = Physics::getSingletonPtr()->get_physics()->createTriangleMesh(readbuffer);
			return trimesh;
		}

		PxSceneDesc CreateDefaultSceneDesc(PxVec3 gravity, PxSimulationEventCallback* callback, int num_threads = 1);

		inline void CookTrimesh(char* output_src, std::vector<PxVec3>& vertices, std::vector<PxU32>& faces) {
			PxTriangleMeshDesc meshDesc;
			meshDesc.points.count = vertices.size();
			meshDesc.points.stride = sizeof(PxVec3);
			meshDesc.points.data = vertices.data();

			meshDesc.triangles.count = faces.size() / 3;
			meshDesc.triangles.stride = 3 * sizeof(PxU32);
			meshDesc.triangles.data = faces.data();
			bool isvalid = cooking_->validateTriangleMesh(meshDesc);

			PxDefaultFileOutputStream writebuffer(output_src);
			bool status = cooking_->cookTriangleMesh(meshDesc, writebuffer);
			if (!status)
				throw Ogre::Exception(0, "PhysX cooking failed, see console for error messages.", "gpe::Physics::CookTrimesh");
		}

	private:
		Physics();

	private:
		PxMaterial* default_material_;
		PxPhysics* physics_;
		PxCooking* cooking_;
		PxCudaContextManager* cuda_context_manager_;
	};
}