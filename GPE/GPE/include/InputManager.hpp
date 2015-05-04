#pragma once

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISJoyStick.h>

#include <OgreRenderWindow.h>

using namespace OIS;

namespace gpe {
	class InputManager : public KeyListener, public MouseListener, public JoyStickListener {
		friend class KeyListener;
		friend class MouseListener;
		friend class JoyStickListener;
		friend class GameStateManager;

	public:
		InputManager(Ogre::RenderWindow* render_window);
		~InputManager();

	private:
		// KeyListener
		virtual bool KeyPressed(const KeyEvent &e);
		virtual bool KeyReleased(const KeyEvent &e);
		// MouseListener
		virtual bool MouseMoved(const MouseEvent &e);
		virtual bool MousePressed(const MouseEvent &e, MouseButtonID id);
		virtual bool MouseReleased(const MouseEvent &e, MouseButtonID id);
		// JoyStickListener
		virtual bool PovMoved(const JoyStickEvent &e, int pov);
		virtual bool AxisMoved(const JoyStickEvent &e, int axis);
		virtual bool SliderMoved(const JoyStickEvent &e, int slider_id);
		virtual bool ButtonPressed(const JoyStickEvent &e, int button);
		virtual bool ButtonReleased(const JoyStickEvent &e, int button);

// WindowEventListener
		//Adjust mouse clipping area
		virtual void WindowResized(int width, int height);

	private:
		
	};
}