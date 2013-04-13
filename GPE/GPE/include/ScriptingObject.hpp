#pragma once

#include <v8.h>
#include <string>
#include <vector>

using namespace v8;

class ScriptingObject
{
	friend class GameObject;
public:
	ScriptingObject();
	ScriptingObject(Persistent<FunctionTemplate>& internalTempl);
	virtual ~ScriptingObject();

	

//private:
	Persistent<ObjectTemplate> objTemplate;
	Persistent<Context> context;
};