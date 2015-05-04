#pragma once

#include <map>
#include <Ogre.h>
#include <OgreSingleton.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISJoyStick.h>

using namespace std;

namespace gpe {

	class GameState;

	class GameStateManager : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener {
	public:
		GameStateManager(char* window_title);
		~GameStateManager();
		void Start(GameState* state) {
			ChangeState(state);
			root_->startRendering();
		}
		void ChangeState(GameState* state);
		void Clear();
		void Push(GameState* state);
		void Pop();
		//void FindState(String str);

		inline Ogre::Root* get_root() { return root_; }
		inline Ogre::RenderWindow* get_render_window() { return render_window_; }
		inline Ogre::Log* get_log() { return log_; }

		inline OIS::InputManager* get_ois_inputmanager() { return ois_inputmanager_; }
		inline OIS::Keyboard* get_keyboard() { return keyboard_; }
		inline OIS::Mouse* get_mouse() { return mouse_; }
		inline OIS::JoyStick* get_joystick() { return joystick_; }

		inline int get_joystick_dead_zone() { return joystick_dead_zone_; }

	protected:
		virtual void windowResized(Ogre::RenderWindow* rw);
		virtual void windowClosed(Ogre::RenderWindow* rw);
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

		// OIS::KeyListener
		virtual bool keyPressed(const OIS::KeyEvent &e);
		virtual bool keyReleased(const OIS::KeyEvent &e);
		// OIS::MouseListener
		virtual bool mouseMoved(const OIS::MouseEvent &e);
		virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		// OIS::JoyStickListener
		virtual bool povMoved(const OIS::JoyStickEvent &e, int pov);
		virtual bool axisMoved(const OIS::JoyStickEvent &e, int axis);
		virtual bool sliderMoved(const OIS::JoyStickEvent &e, int sliderID);
		virtual bool buttonPressed(const OIS::JoyStickEvent &e, int button);
		virtual bool buttonReleased(const OIS::JoyStickEvent &e, int button);

	protected:
		Ogre::Root* root_;
		Ogre::RenderWindow* render_window_;
		Ogre::Log* log_;

		OIS::InputManager*			ois_inputmanager_;
		OIS::Keyboard*				keyboard_;
		OIS::Mouse*				    mouse_;
		OIS::JoyStick*              joystick_;

		int                         joystick_dead_zone_;

	private:
		std::map<std::string, GameState*> gamestates_;
	};
}