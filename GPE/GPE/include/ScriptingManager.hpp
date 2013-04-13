#pragma once

#include <v8.h>
#include <string>
#include <map>
#include <OgreResourceManager.h>

using namespace v8;

class ScriptingManager
{
private:
	typedef std::map<std::string, Persistent<Script>> scriptNamePair;

public:
	ScriptingManager();
	virtual ~ScriptingManager();

	//std::vector<Persistent<Script>> scripts;
	scriptNamePair scripts;

	Handle<Script> ScriptingManager::getCompiledScript(std::string inScript);
};