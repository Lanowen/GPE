#pragma once

#include <OIS.h>
#include <vector>

namespace gpe {

	class IMouseListener {
	public:
		virtual bool MouseMoved(const OIS::MouseEvent &evt) = 0;
		virtual bool MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
		virtual bool MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
	};

	class MouseListener : public IMouseListener {
		friend class GameState;
		friend class GameStateManager;
	public:
		MouseListener() {}
		virtual ~MouseListener() {}

		inline virtual void RegisterMouseListener(IMouseListener* listener) {
			mouselisteners_.push_back(listener);
		}

		inline virtual void DeregisterMouseListener(IMouseListener* listener) {
			std::vector<IMouseListener*>::iterator itr = std::find<std::vector<IMouseListener*>::iterator, IMouseListener*>(mouselisteners_.begin(), mouselisteners_.end(), listener);
			if (itr != mouselisteners_.end())
				mouselisteners_.erase(itr);
		}

	private:
		inline virtual bool MouseMoved(const OIS::MouseEvent &evt) {
			std::vector<IMouseListener*>::iterator itr = mouselisteners_.begin();
			for (; itr != mouselisteners_.end(); itr++) {
				(*itr)->MouseMoved(evt);
			}

			return true;
		}

		inline virtual bool MousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
			std::vector<IMouseListener*>::iterator itr = mouselisteners_.begin();
			for (; itr != mouselisteners_.end(); itr++) {
				(*itr)->MousePressed(evt, id);
			}

			return true;
		}

		inline virtual bool MouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
			std::vector<IMouseListener*>::iterator itr = mouselisteners_.begin();
			for (; itr != mouselisteners_.end(); itr++) {
				(*itr)->MouseReleased(evt, id);
			}

			return true;
		}

	private:
		std::vector<IMouseListener*> mouselisteners_;
	};
}