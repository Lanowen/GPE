#pragma once

#include <OIS.h>
#include <vector>

namespace gpe {

	class IJoyStickListener {
	public:
		virtual bool PovMoved(const OIS::JoyStickEvent &e, int pov) = 0;
		virtual bool AxisMoved(const OIS::JoyStickEvent &e, int axis) = 0;
		virtual bool SliderMoved(const OIS::JoyStickEvent &e, int sliderID) = 0;
		virtual bool ButtonPressed(const OIS::JoyStickEvent &e, int button) = 0;
		virtual bool ButtonReleased(const OIS::JoyStickEvent &e, int button) = 0;
	};

	class JoyStickListener : public IJoyStickListener {
		friend class GameState;
		friend class GameStateManager;
	public:
		JoyStickListener() { }
		virtual ~JoyStickListener() {}

		inline virtual void RegisterJoyListener(IJoyStickListener* listener) {
			joylisteners_.push_back(listener);
		}

		inline virtual void DeregisterJoyListener(IJoyStickListener* listener) {
			std::vector<IJoyStickListener*>::iterator itr = std::find<std::vector<IJoyStickListener*>::iterator, IJoyStickListener*>(joylisteners_.begin(), joylisteners_.end(), listener);
			if (itr != joylisteners_.end())
				joylisteners_.erase(itr);
		}

	private:
		inline virtual bool PovMoved(const OIS::JoyStickEvent &e, int pov) {
			std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
			for (; itr != joylisteners_.end(); itr++) {
				(*itr)->PovMoved(e, pov);
			}

			return true;
		}

		inline virtual bool AxisMoved(const OIS::JoyStickEvent &e, int axis) {
			std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
			for (; itr != joylisteners_.end(); itr++) {
				(*itr)->AxisMoved(e, axis);
			}

			return true;
		}

		inline virtual bool SliderMoved(const OIS::JoyStickEvent &e, int sliderID) {
			std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
			for (; itr != joylisteners_.end(); itr++) {
				(*itr)->SliderMoved(e, sliderID);
			}

			return true;
		}

		inline virtual bool ButtonPressed(const OIS::JoyStickEvent &e, int button) {
			std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
			for (; itr != joylisteners_.end(); itr++) {
				(*itr)->ButtonPressed(e, button);
			}

			return true;
		}

		inline virtual bool ButtonReleased(const OIS::JoyStickEvent &e, int button) {
			std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
			for (; itr != joylisteners_.end(); itr++) {
				(*itr)->ButtonReleased(e, button);
			}

			return true;
		}

	private:
		std::vector<IJoyStickListener*> joylisteners_;
	};
}