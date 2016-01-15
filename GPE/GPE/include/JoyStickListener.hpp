#pragma once

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

		inline void RegisterJoyListener(IJoyStickListener* listener) {
			joylisteners_.push_back(listener);
		}

		inline void DeregisterJoyListener(IJoyStickListener* listener) {
			to_delete_.push(listener);
		}

	private:
		inline bool PovMoved(const OIS::JoyStickEvent &e, int pov) {
			std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
			for (; itr != joylisteners_.end(); itr++) {
				(*itr)->PovMoved(e, pov);
			}

			return true;
		}

		inline bool AxisMoved(const OIS::JoyStickEvent &e, int axis) {
			std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
			for (; itr != joylisteners_.end(); itr++) {
				(*itr)->AxisMoved(e, axis);
			}

			return true;
		}

		inline bool SliderMoved(const OIS::JoyStickEvent &e, int sliderID) {
			std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
			for (; itr != joylisteners_.end(); itr++) {
				(*itr)->SliderMoved(e, sliderID);
			}

			return true;
		}

		inline bool ButtonPressed(const OIS::JoyStickEvent &e, int button) {
			std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
			for (; itr != joylisteners_.end(); itr++) {
				(*itr)->ButtonPressed(e, button);
			}

			return true;
		}

		inline bool ButtonReleased(const OIS::JoyStickEvent &e, int button) {
			std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
			for (; itr != joylisteners_.end(); itr++) {
				(*itr)->ButtonReleased(e, button);
			}

			return true;
		}

		inline void JoyStickListenerPost() {
			while (to_delete_.size() > 0) {
				std::vector<IJoyStickListener*>::iterator itr = std::find<std::vector<IJoyStickListener*>::iterator, IJoyStickListener*>(joylisteners_.begin(), joylisteners_.end(), to_delete_.top());
				if (itr != joylisteners_.end())
					joylisteners_.erase(itr);

				to_delete_.pop();
			}
		}

	private:
		std::vector<IJoyStickListener*> joylisteners_;
		std::stack<IJoyStickListener*> to_delete_;
	};
}