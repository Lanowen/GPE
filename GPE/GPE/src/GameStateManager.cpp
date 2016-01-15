#include "stdafx.h"

#include "GameStateManager.hpp"
#include "GameState.hpp"

namespace gpe {

	GameStateManager::GameStateManager(char* window_title) : joystick_dead_zone_(0), time_since_last_frame_(0), target_frame_rate_(1.0 / 60.0), joystick_(nullptr), mouse_(nullptr), 
																keyboard_(nullptr), ois_inputmanager_(nullptr), log_(nullptr), render_window_(nullptr), root_(nullptr) {
		Ogre::LogManager* logmgr = new Ogre::LogManager();

		log_ = logmgr->createLog("GPE_logfile.txt", true, true, false);
#ifdef _DEBUG
		log_->setDebugOutputEnabled(true);
#endif

		Ogre::String resources_cfg;
		Ogre::String plugins_cfg;
#ifdef _DEBUG
		resources_cfg = "resources_d.cfg";
		plugins_cfg = "plugins_d.cfg";
#else
		resources_cfg = "resources.cfg";
		plugins_cfg = "plugins.cfg";
#endif

		root_ = new Ogre::Root(plugins_cfg);

		// Load resource paths from config file
		Ogre::ConfigFile cf;
		cf.load(resources_cfg);

		// Go through all sections & settings in the file
		Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

		Ogre::String sec_name, type_name, arch_name;
		while (seci.hasMoreElements()) {
			sec_name = seci.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
			Ogre::ConfigFile::SettingsMultiMap::iterator i;
			for (i = settings->begin(); i != settings->end(); ++i) {
				type_name = i->first;
				arch_name = i->second;
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
					arch_name, type_name, sec_name);
			}
		}

		if (!root_->showConfigDialog())
			system("EXIT");
			//return false;

		render_window_ = root_->initialise(true, window_title);
		render_window_->setActive(true);

		root_->addFrameListener(this);

		//Register as a Window listener
		Ogre::WindowEventUtilities::addWindowEventListener(render_window_, this);
		log_->logMessage("Game initialized!");

		Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		unsigned long hWnd = 0;
		OIS::ParamList paramList;
		render_window_->getCustomAttribute("WINDOW", &hWnd);

		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));

		paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));

		ois_inputmanager_ = OIS::InputManager::createInputSystem(paramList);

		if (ois_inputmanager_->getNumberOfDevices(OIS::OISKeyboard) > 0) {
			keyboard_ = static_cast<OIS::Keyboard*>(ois_inputmanager_->createInputObject(OIS::OISKeyboard, true));

			keyboard_->setEventCallback(this);
		}
		

		if (ois_inputmanager_->getNumberOfDevices(OIS::OISMouse) > 0) {
			mouse_ = static_cast<OIS::Mouse*>(ois_inputmanager_->createInputObject(OIS::OISMouse, true));

			mouse_->getMouseState().height = render_window_->getHeight();
			mouse_->getMouseState().width = render_window_->getWidth();

			mouse_->setEventCallback(this);
		}

		if (ois_inputmanager_->getNumberOfDevices(OIS::OISJoyStick) > 0) {
			//mJoysticks.resize( mInputSystem->numJoySticks() );
			//        mJoysticks.resize( mInputSystem->getNumberOfDevices(OIS::OISJoyStick) );
			//
			//        itJoystick    = mJoysticks.begin();
			//        itJoystickEnd = mJoysticks.end();
			//        for(; itJoystick != itJoystickEnd; ++itJoystick ) {
			//            (*itJoystick) = static_cast<OIS::JoyStick*>( mInputSystem->createInputObject( OIS::OISJoyStick, true ) );
			//            (*itJoystick)->setEventCallback( this );
			//        }
			joystick_ = static_cast<OIS::JoyStick*>(ois_inputmanager_->createInputObject(OIS::OISJoyStick, true));
			joystick_->setEventCallback(this);

			joystick_dead_zone_ = joystick_->MAX_AXIS*0.4;
		}

		Physics::Initialize();
	}


	GameStateManager::~GameStateManager() {
		// clean up all the states
		for each (pair<String, GameState*> state in gamestates_) {
			state.second->Exit();
			state.second->gamestatemanager_ = 0;
			delete state.second;
		}

		if (mouse_ != nullptr) {
			ois_inputmanager_->destroyInputObject(mouse_);
			mouse_ = nullptr;
		}
		if (keyboard_ != nullptr) {
			ois_inputmanager_->destroyInputObject(keyboard_);
			keyboard_ = nullptr;
		}
		if (joystick_ != nullptr) {
			ois_inputmanager_->destroyInputObject(joystick_);
			joystick_ = nullptr;
		}

		if (ois_inputmanager_ != nullptr) {
			OIS::InputManager::destroyInputSystem(ois_inputmanager_);
			ois_inputmanager_ = nullptr;
		}

		if (root_ != nullptr)
			delete root_;
	}

	void GameStateManager::ChangeState(GameState* state) {
		Clear();
		Push(state);
	}

	void GameStateManager::Clear() {
		for each (pair<String, GameState*> state in gamestates_) {
			state.second->Exit();
			state.second->gamestatemanager_ = 0;
		}

		gamestates_.clear();
	}

	void GameStateManager::Pop() {
		
		if (!gamestates_.empty()) {
			(--gamestates_.end())->second->Exit();
			(--gamestates_.end())->second->gamestatemanager_ = 0;
			gamestates_.erase((--gamestates_.end()));
		}
			

		if (!gamestates_.empty()) {
			(--gamestates_.end())->second->Resume();
		}
	}

	void GameStateManager::Push(GameState* state) {
		if (!gamestates_.empty()) {
			(--gamestates_.end())->second->Pause();
		}

		state->gamestatemanager_ = this;
		gamestates_.emplace(state->get_name(), state);
		state->Enter();
	}

	bool GameStateManager::frameStarted(const Ogre::FrameEvent& evt) {
		if (gamestates_.empty())
			return false;
			
		time_since_last_frame_ += evt.timeSinceLastFrame;

		if (time_since_last_frame_ >= target_frame_rate_) {
			(--gamestates_.end())->second->AdvanceSimulation(target_frame_rate_);
		}

		return true;
	}

	bool GameStateManager::frameRenderingQueued(const Ogre::FrameEvent& evt) {
		if (gamestates_.empty())
			return false;

		if (get_render_window()->isClosed())
			return false;

		bool res = true;

		if (time_since_last_frame_ >= target_frame_rate_) {

			(--gamestates_.end())->second->get_physics_scene()->FetchResults(); //block until physics thread joins

			//Need to capture/update each device
			if (keyboard_ != nullptr) {
				keyboard_->capture();
			}
			if (mouse_ != nullptr) {
				mouse_->capture();
			}
			if (joystick_ != nullptr) {
				joystick_->capture();
			}			

			res &= (--gamestates_.end())->second->Update(target_frame_rate_);
		}

		return res;
	}

	bool GameStateManager::frameEnded(const Ogre::FrameEvent& evt) {
		if (gamestates_.empty())
			return false;

		bool res = true;

		if (time_since_last_frame_ >= target_frame_rate_) {
			
			res &= (--gamestates_.end())->second->PostUpdate();

			time_since_last_frame_ = fmod(time_since_last_frame_, target_frame_rate_);
		}

		return res;
	}

	//Adjust mouse clipping area
	void GameStateManager::windowResized(Ogre::RenderWindow* rw) {
		unsigned int width, height, depth;
		int left, top;
		rw->getMetrics(width, height, depth, left, top);

		const OIS::MouseState &ms = mouse_->getMouseState();
		ms.width = width;
		ms.height = height;
	}

	//Unattach OIS before window shutdown (very important under Linux)
	void GameStateManager::windowClosed(Ogre::RenderWindow* rw) {
		//Only close for window that created OIS (the main window in these demos)
		if (rw == render_window_) {
			if (ois_inputmanager_) {
				if (mouse_ != nullptr) {
					ois_inputmanager_->destroyInputObject(mouse_);
					mouse_ = nullptr;
				}
				if (keyboard_ != nullptr) {
					ois_inputmanager_->destroyInputObject(keyboard_);
					keyboard_ = nullptr;
				}
				if (joystick_ != nullptr) {
					ois_inputmanager_->destroyInputObject(joystick_);
					joystick_ = nullptr;
				}

				if (ois_inputmanager_ != nullptr) {
					OIS::InputManager::destroyInputSystem(ois_inputmanager_);
					ois_inputmanager_ = nullptr;
				}
			}
		}

		Stop();
	}

	bool GameStateManager::keyPressed(const OIS::KeyEvent &keyEventRef) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->KeyPressed(keyEventRef);
		}

		return true;
	}

	bool GameStateManager::keyReleased(const OIS::KeyEvent &keyEventRef) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->KeyReleased(keyEventRef);
		}

		return true;
	}

	bool GameStateManager::mouseMoved(const OIS::MouseEvent &evt) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->MouseMoved(evt);
		}

		return true;
	}

	bool GameStateManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->MousePressed(evt, id);
		}

		return true;
	}

	bool GameStateManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->MouseReleased(evt, id);
		}

		return true;
	}

	bool GameStateManager::povMoved(const OIS::JoyStickEvent &evt, int pov) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->PovMoved(evt, pov);
		}

		return true;
	}

	bool GameStateManager::axisMoved(const OIS::JoyStickEvent &evt, int axis) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->AxisMoved(evt, axis);
		}

		return true;
	}

	bool GameStateManager::sliderMoved(const OIS::JoyStickEvent &e, int sliderID) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->SliderMoved(e, sliderID);
		}

		return true;
	}

	bool GameStateManager::buttonPressed(const OIS::JoyStickEvent &evt, int button) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->ButtonPressed(evt, button);
		}

		return true;
	}

	bool GameStateManager::buttonReleased(const OIS::JoyStickEvent &evt, int button) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->ButtonReleased(evt, button);
		}

		return true;
	}
}