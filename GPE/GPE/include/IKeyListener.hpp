#pragma once

#include <OIS\OIS.h>
#include <GameState.hpp>

class IKeyListener : public OIS::KeyListener{
public:
	IKeyListener(GameState* owner) : listenerOwner(owner) { listenerOwner->RegisterKeyListener(this); }
	virtual ~IKeyListener(){ listenerOwner->DeregisterKeyListener(this); }

	//virtual bool keyPressed(const OIS::KeyEvent &keyEventRef) = 0;
    //virtual bool keyReleased(const OIS::KeyEvent &keyEventRef) = 0;

private:
	GameState* listenerOwner;
};