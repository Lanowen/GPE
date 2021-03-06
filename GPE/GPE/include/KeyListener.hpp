#pragma once

namespace gpe {

	class IKeyListener {
	public:
		virtual bool KeyPressed(const OIS::KeyEvent &keyEventRef) = 0;
		virtual bool KeyReleased(const OIS::KeyEvent &keyEventRef) = 0;
	};

	class KeyListener {
		friend class GameState;
		friend class GameStateManager;
	public:
		KeyListener() {}
		virtual ~KeyListener() {}

		inline void RegisterKeyListener(IKeyListener* listener) {
			keylisteners_.push_back(listener);
		}

		inline void DeregisterKeyListener(IKeyListener* listener) {
			to_delete_.push(listener);
			
		}

	private:
		inline bool KeyPressed(const OIS::KeyEvent &keyEventRef) {
			std::vector<IKeyListener*>::iterator itr = keylisteners_.begin();
			for (; itr != keylisteners_.end(); itr++) {
				(*itr)->KeyPressed(keyEventRef);
			}

			return true;
		}

		inline bool KeyReleased(const OIS::KeyEvent &keyEventRef) {
			std::vector<IKeyListener*>::iterator itr = keylisteners_.begin();
			for (; itr != keylisteners_.end(); itr++) {
				(*itr)->KeyReleased(keyEventRef);
			}
			return true;
		}

		inline void KeyListenerPost() {
			while (to_delete_.size() > 0) {
				std::vector<IKeyListener*>::iterator itr = std::find<std::vector<IKeyListener*>::iterator, IKeyListener*>(keylisteners_.begin(), keylisteners_.end(), to_delete_.top());
				if (itr != keylisteners_.end())
					keylisteners_.erase(itr);

				to_delete_.pop();
			}
		}

	private:
		std::vector<IKeyListener*> keylisteners_;
		std::stack<IKeyListener*> to_delete_;
	};
}