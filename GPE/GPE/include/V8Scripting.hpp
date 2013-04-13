#pragma once

#include <v8.h>
#include <OgreSingleton.h>
#include <ScriptingManager.hpp>

using namespace v8;

class V8Scripting : public Ogre::Singleton<V8Scripting>
{
public:
	V8Scripting();
	virtual ~V8Scripting();
	void exposeBaseFunctions();

	Persistent<ObjectTemplate> globalObjectTemp;
	Persistent<Context> globalContext;
	Persistent<FunctionTemplate> globalFunctionTemp;

	ScriptingManager *scriptMgr;

public:
	static Handle<Value> printMessage(const Arguments& args);
	static void reportException(TryCatch* try_catch);
};