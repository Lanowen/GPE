#pragma once

#include <OIS.h>
#include <vector>

namespace gpe {

	class IKeyListener {
	public:
		inline virtual bool KeyPressed(const OIS::KeyEvent &keyEventRef) = 0;
		inline virtual bool KeyReleased(const OIS::KeyEvent &keyEventRef) = 0;
	};

	class KeyListener : public IKeyListener {
		friend class GameState;
		friend class GameStateManager;
	public:
		KeyListener() {}
		virtual ~KeyListener() {}

		inline virtual void RegisterKeyListener(IKeyListener* listener) {
			keylisteners_.push_back(listener);
		}

		inline virtual void DeregisterKeyListener(IKeyListener* listener) {
			std::vector<IKeyListener*>::iterator itr = std::find<std::vector<IKeyListener*>::iterator, IKeyListener*>(keylisteners_.begin(), keylisteners_.end(), listener);
			if (itr != keylisteners_.end())
				keylisteners_.erase(itr);
		}

	private:
		inline virtual  bool KeyPressed(const OIS::KeyEvent &keyEventRef) {
			std::vector<IKeyListener*>::iterator itr = keylisteners_.begin();
			for (; itr != keylisteners_.end(); itr++) {
				(*itr)->KeyPressed(keyEventRef);
			}

			return true;
		}

		inline virtual bool KeyReleased(const OIS::KeyEvent &keyEventRef) {
			std::vector<IKeyListener*>::iterator itr = keylisteners_.begin();
			for (; itr != keylisteners_.end(); itr++) {
				(*itr)->KeyReleased(keyEventRef);
			}
			return true;
		}

	private:
		std::vector<IKeyListener*> keylisteners_;
	};
}