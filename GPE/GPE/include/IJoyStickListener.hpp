#pragma once

#include <OIS\OIS.h>
#include <GameState.hpp>

class IJoyStickListener : public OIS::JoyStickListener{
public:
	IJoyStickListener(GameState* owner) : listenerOwner(owner) { listenerOwner->RegisterJoyListener(this); }
	virtual ~IJoyStickListener(){ listenerOwner->DeregisterJoyListener(this); }

	//virtual bool keyPressed(const OIS::KeyEvent &keyEventRef) = 0;
    //virtual bool keyReleased(const OIS::KeyEvent &keyEventRef) = 0;

private:
	GameState* listenerOwner;
};