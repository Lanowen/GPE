#pragma once

#include <Ogre.h>
#include <OgreCamera.h>
//#include <OgreOverlay.h>
//#include <OgreOverlayElement.h>
//#include <OgreOverlayManager.h>
#include <OgreViewport.h>
#include "Physics.hpp"
#include <list>
#include "GameStateManager.hpp"
#include "MouseListener.hpp"
#include "KeyListener.hpp"
#include "JoyStickListener.hpp"
#include "EventDispatcher.hpp"

using namespace Ogre;
using namespace physx;

namespace gpe {

	class GameObject;

	class GameState : public MouseListener, public KeyListener, public JoyStickListener//, OgreBites::SdkTrayListener
	{
		friend class GameStateManager;
	public:
		GameState(std::string name);
		~GameState();

		inline PhysicsScene* get_physics_scene() { return physics_scene_; }
		inline SceneManager* get_scene_manager() { return scene_manager_; }
		inline GameStateManager* get_gamestatemanager() { return gamestatemanager_; }
		
		inline std::vector<GameObject*>& get_gameobjects() { return gameobjects_; }
		inline EventDispatcher* get_event_dispatcher() { return event_dispatcher_; }

		void AddGameObject(GameObject* go);
		void DeleteGameObject(GameObject* go);
		void RemoveGameObject(GameObject* go);

		inline Ogre::CompositorInstance* AddCompositor(char* compositor) {
			return Ogre::CompositorManager::getSingleton().addCompositor(viewport_, compositor);
		}

	protected:
		inline void set_physics_scene(PhysicsScene* phys_scene) { physics_scene_ = phys_scene; }
		inline void set_scene_manager(SceneManager* scene_man) { scene_manager_ = scene_man; }
		inline void set_event_dispatcher(EventDispatcher* event_handler) { event_dispatcher_ = event_handler; }

	private:

		inline void set_gamestatemanager(GameStateManager* gsm) { gamestatemanager_ = gsm; }

	protected:
		virtual void Enter() {
			gamestatemanager_->get_render_window()->resetStatistics();

			viewport_ = gamestatemanager_->get_render_window()->addViewport(0);
			viewport_->setBackgroundColour(Ogre::ColourValue(0, 0, 0, 1.0f));

			camera_->setAspectRatio(Ogre::Real(viewport_->getActualWidth()) /
									Ogre::Real(viewport_->getActualHeight()));

			viewport_->setCamera(camera_);
		}
		virtual void Exit() {}
		virtual void Pause() {}
		virtual void Resume() {}
		const std::string get_name() { return name_; }

		inline virtual void AdvanceSimulation(PxReal frameRate) {
			get_physics_scene()->AdvanceSimulation(frameRate);
		}

		virtual bool Update(Ogre::Real timeSinceLastFrame);
		virtual bool PostUpdate();

	protected:
		Camera* camera_;

	private:
		const std::string name_;

		GameStateManager* gamestatemanager_;
		PhysicsScene* physics_scene_;

		Viewport* viewport_;
		SceneManager* scene_manager_;
		EventDispatcher* event_dispatcher_;

		std::vector<GameObject*> gameobjects_;

		std::list<GameObject*> gameobjects_to_delete_;
	};

}