#include <GameStateManager.hpp>
#include <GameState.hpp>

namespace gpe {

	GameStateManager::GameStateManager(char* window_title) : joystick_dead_zone_(0), joystick_(0), mouse_(0), keyboard_(0), ois_inputmanager_(0), log_(0), render_window_(0), root_(0) {
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

		keyboard_ = static_cast<OIS::Keyboard*>(ois_inputmanager_->createInputObject(OIS::OISKeyboard, true));
		mouse_ = static_cast<OIS::Mouse*>(ois_inputmanager_->createInputObject(OIS::OISMouse, true));

		mouse_->getMouseState().height = render_window_->getHeight();
		mouse_->getMouseState().width = render_window_->getWidth();

		keyboard_->setEventCallback(this);
		mouse_->setEventCallback(this);


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
	}


	GameStateManager::~GameStateManager() {
		// clean up all the states
		for each (pair<String, GameState*> state in gamestates_) {
			state.second->Exit();
			state.second->gamestatemanager_ = 0;
			delete state.second;
		}

		if (ois_inputmanager_) {
			ois_inputmanager_->destroyInputObject(mouse_);
			ois_inputmanager_->destroyInputObject(keyboard_);
			ois_inputmanager_->destroyInputObject(joystick_);

			OIS::InputManager::destroyInputSystem(ois_inputmanager_);
			ois_inputmanager_ = 0;
		}

		if (root_)
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

	bool GameStateManager::frameRenderingQueued(const Ogre::FrameEvent& evt) {
		//Need to capture/update each device
		keyboard_->capture();
		mouse_->capture();
		if (joystick_) {
			joystick_->capture();
		}

		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->frameRenderingQueued(evt);
		}

		return true;
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
				ois_inputmanager_->destroyInputObject(mouse_);
				ois_inputmanager_->destroyInputObject(keyboard_);
				ois_inputmanager_->destroyInputObject(joystick_);

				OIS::InputManager::destroyInputSystem(ois_inputmanager_);
				ois_inputmanager_ = 0;
			}
		}
	}

	bool GameStateManager::keyPressed(const OIS::KeyEvent &keyEventRef) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->keyPressed(keyEventRef);
		}

		return true;
	}

	bool GameStateManager::keyReleased(const OIS::KeyEvent &keyEventRef) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->keyReleased(keyEventRef);
		}

		return true;
	}

	bool GameStateManager::mouseMoved(const OIS::MouseEvent &evt) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->mouseMoved(evt);
		}

		return true;
	}

	bool GameStateManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->mousePressed(evt, id);
		}

		return true;
	}

	bool GameStateManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->mouseReleased(evt, id);
		}

		return true;
	}

	bool GameStateManager::povMoved(const OIS::JoyStickEvent &evt, int pov) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->povMoved(evt, pov);
		}

		return true;
	}

	bool GameStateManager::axisMoved(const OIS::JoyStickEvent &evt, int axis) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->axisMoved(evt, axis);
		}

		return true;
	}

	bool GameStateManager::sliderMoved(const OIS::JoyStickEvent &e, int sliderID) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->sliderMoved(e, sliderID);
		}

		return true;
	}

	bool GameStateManager::buttonPressed(const OIS::JoyStickEvent &evt, int button) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->buttonPressed(evt, button);
		}

		return true;
	}

	bool GameStateManager::buttonReleased(const OIS::JoyStickEvent &evt, int button) {
		if (!gamestates_.empty()) {
			return (--gamestates_.end())->second->buttonReleased(evt, button);
		}

		return true;
	}
}