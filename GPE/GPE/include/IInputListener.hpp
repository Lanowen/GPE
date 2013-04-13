#pragma once

#include <OIS\OIS.h>
#include <GameState.hpp>

class IInputListener{
public:
	IInputListener(GameState* owner) : listenerOwner(owner) { listenerOwner->RegisterInputListener(this); }
	virtual ~IInputListener(){ listenerOwner->DeregisterInputListener(this); }

	virtual bool keyPressed(const OIS::KeyEvent &keyEventRef) = 0;
    virtual bool keyReleased(const OIS::KeyEvent &keyEventRef) = 0;

private:
	GameState* listenerOwner;
};