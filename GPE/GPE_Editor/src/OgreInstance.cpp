#include <OgreInstance.hpp>

OgreInstance::OgreInstance(){
    Ogre::LogManager* logMgr = new Ogre::LogManager();

    m_Log = Ogre::LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
    m_Log->setDebugOutputEnabled(true);

	#ifdef _DEBUG
        //mResourcesCfg = "resources_d.cfg";
        mPluginsCfg = "plugins_d.cfg";
    #else
		//mResourcesCfg = "resources.cfg";
        mPluginsCfg = "plugins.cfg";
    #endif

	m_Root = new Ogre::Root(mPluginsCfg);
}

OgreInstance::~OgreInstance(){

}