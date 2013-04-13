#pragma once

#include <Ogre.h>

class OgreInstance {
public:
	OgreInstance();
	~OgreInstance();

	Ogre::Root*	m_Root;
	Ogre::Log*	m_Log;

	Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
};