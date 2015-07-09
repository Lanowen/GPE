#pragma once

#include <OIS.h>
#include <vector>
#include <stack>

namespace gpe {

	class IMouseListener {
	public:
		virtual bool MouseMoved(const OIS::MouseEvent &evt) = 0;
		virtual bool MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
		virtual bool MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
	};

	class MouseListener {
		friend class GameState;
		friend class GameStateManager;
	public:
		MouseListener() {}
		virtual ~MouseListener() {}

		inline void RegisterMouseListener(IMouseListener* listener) {
			mouselisteners_.push_back(listener);
		}

		inline void DeregisterMouseListener(IMouseListener* listener) {
			to_delete_.push(listener);
		}

	private:
		inline bool MouseMoved(const OIS::MouseEvent &evt) {
			std::vector<IMouseListener*>::iterator itr = mouselisteners_.begin();
			for (; itr != mouselisteners_.end(); itr++) {
				(*itr)->MouseMoved(evt);
			}

			return true;
		}

		inline bool MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
			std::vector<IMouseListener*>::iterator itr = mouselisteners_.begin();
			for (; itr != mouselisteners_.end(); itr++) {
				(*itr)->MousePressed(evt, id);
			}

			return true;
		}

		inline bool MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
			std::vector<IMouseListener*>::iterator itr = mouselisteners_.begin();
			for (; itr != mouselisteners_.end(); itr++) {
				(*itr)->MouseReleased(evt, id);
			}

			return true;
		}

		inline void MouseListenerPost() {
			while (to_delete_.size() > 0) {
				std::vector<IMouseListener*>::iterator itr = std::find<std::vector<IMouseListener*>::iterator, IMouseListener*>(mouselisteners_.begin(), mouselisteners_.end(), to_delete_.top());
				if (itr != mouselisteners_.end())
					mouselisteners_.erase(itr);

				to_delete_.pop();
			}
		}

	private:
		std::vector<IMouseListener*> mouselisteners_;
		std::stack<IMouseListener*> to_delete_;
	};
}