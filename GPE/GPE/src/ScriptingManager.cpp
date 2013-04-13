#include <ScriptingManager.hpp>
#include <OgreResourceManager.h>
#include <algorithm>
#include <iostream>
#include <V8Scripting.hpp>

ScriptingManager::ScriptingManager() {
	if(Ogre::ResourceGroupManager::getSingleton().resourceGroupExists("Scripts")){
		Ogre::DataStreamListPtr scriptList = Ogre::ResourceGroupManager::getSingleton().openResources("*.js","Scripts");

		for(Ogre::DataStreamList::iterator itrScripts = scriptList->begin(); itrScripts != scriptList->end(); itrScripts++){
			scripts[(*itrScripts)->getName()] = Persistent<Script>::New( Script::New( String::New( (*itrScripts)->getAsString().c_str()) , String::New((*itrScripts)->getName().c_str()) ) );
		}
	}
}

ScriptingManager::~ScriptingManager(){
	for(scriptNamePair::iterator itr = scripts.begin(); itr != scripts.end(); itr++){
		itr->second.Dispose();
	}
}

Handle<Script> ScriptingManager::getCompiledScript(std::string inScript){
	scriptNamePair::iterator itr = scripts.find(inScript);
	if(itr != scripts.end()){
		return(itr->second);
	}
	
	return(Handle<Script>());
}
