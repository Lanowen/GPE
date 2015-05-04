#include "OgrePlatform.h"
#include <OgreException.h>
#include <Game.hpp>

#include <GPENet.hpp>
#include <GameState.hpp>

#include <SerializationClassExports.hpp>

using namespace Ogre;
using namespace gpe;


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "OgreString.h"
#endif

//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR cmdLine, INT)
//#else
//int main(int argc, char *argv[])
//#endif
{
	try
	{
//        bool nograb = false;
//#if OGRE_PLATFORM != OGRE_PLATFORM_WIN32
//        if (argc >= 2 && Ogre::String(argv[1]) == "nograb")
//            nograb = true;
//#else
        // somewhat hacky, but much simpler than other solutions
        //if (Ogre::String(cmdLine).find("nograb") != Ogre::String::npos)
            //nograb = true;
		size_t pos;
		if ((pos = Ogre::String(cmdLine).find("server")) != Ogre::String::npos)
			GameState::isserver_ = true;
		if ((pos = Ogre::String(cmdLine).find("client")) != Ogre::String::npos)
			GameState::isserver_ = false;
		if ((pos = Ogre::String(cmdLine).find("ip")) != Ogre::String::npos){
			size_t space = Ogre::String(cmdLine).find(" ", pos);
			GameState::ip_ = Ogre::String(cmdLine).substr(pos + 3, space-(pos + 3));
		}
//#endif
		Game gpeGame;
		gpeGame.go();
	}
	catch (Ogre::Exception& e)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
#endif
	}


}
