#include <InputManager.hpp>
#include <OgreStringConverter.h>

namespace gpe {

	InputManager::InputManager(Ogre::RenderWindow* render_window) {
		unsigned long hWnd = 0;
		OIS::ParamList paramList;
		render_window->getCustomAttribute("WINDOW", &hWnd);

		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));

		paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));

		ois_input_manager_ = OIS::InputManager::createInputSystem(paramList);

		keyboard_ = static_cast<OIS::Keyboard*>(ois_input_manager_->createInputObject(OIS::OISKeyboard, true));
		mouse_ = static_cast<OIS::Mouse*>(ois_input_manager_->createInputObject(OIS::OISMouse, true));

		mouse_->getMouseState().height = render_window->getHeight();
		mouse_->getMouseState().width = render_window->getWidth();

		keyboard_->setEventCallback(this);
		mouse_->setEventCallback(this);


		if (ois_input_manager_->getNumberOfDevices(OIS::OISJoyStick) > 0) {
			//mJoysticks.resize( mInputSystem->numJoySticks() );
			//        mJoysticks.resize( mInputSystem->getNumberOfDevices(OIS::OISJoyStick) );
			//
			//        itJoystick    = mJoysticks.begin();
			//        itJoystickEnd = mJoysticks.end();
			//        for(; itJoystick != itJoystickEnd; ++itJoystick ) {
			//            (*itJoystick) = static_cast<OIS::JoyStick*>( mInputSystem->createInputObject( OIS::OISJoyStick, true ) );
			//            (*itJoystick)->setEventCallback( this );
			//        }
			joystick_ = static_cast<OIS::JoyStick*>(ois_input_manager_->createInputObject(OIS::OISJoyStick, true));
			joystick_->setEventCallback(this);

			//m_pJoyDeadZone1 = (Ogre::Math.Abs(m_pJoyStick->getJoyStickState()->mAxes[0].abs) + Ogre::Math.Abs(m_pJoyStick->getJoyStickState()->mAxes[1].abs))/2
			//m_pJoyDeadZone2 = (Ogre::Math.Abs(m_pJoyStick->getJoyStickState()->mAxes[2].abs) + Ogre::Math.Abs(m_pJoyStick->getJoyStickState()->mAxes[3].abs))/2
			joystick_dead_zone_ = joystick_->MAX_AXIS*0.4;
		}
	}



	void InputManager::WindowResized(int width, int height) {
		const OIS::MouseState &ms = mouse_->getMouseState();
		ms.width = width;
		ms.height = height;
	}

}