#include <ScriptingObject.hpp>
#include <V8Scripting.hpp>
#include <PxPhysics.h>

#include <Scripting_Helpers.hpp>

//#include <OgreResourceManager.h>

ScriptingObject::ScriptingObject() {
	//Locker lock(Isolate::GetCurrent());
	HandleScope handleScope;

	Context::Scope thisScope(V8Scripting::getSingletonPtr()->globalContext);

	objTemplate = Persistent<ObjectTemplate>::New(V8Scripting::getSingletonPtr()->globalFunctionTemp->InstanceTemplate());
	
	context = Context::New(NULL, objTemplate);
}

ScriptingObject::ScriptingObject(Persistent<FunctionTemplate>& internalTempl) {
	//Locker lock(Isolate::GetCurrent());
	HandleScope handleScope;

	Context::Scope thisScope(V8Scripting::getSingletonPtr()->globalContext);

	internalTempl->Inherit(V8Scripting::getSingletonPtr()->globalFunctionTemp);
	
	objTemplate = Persistent<ObjectTemplate>::New(internalTempl->InstanceTemplate());	

	context = Context::New(NULL, objTemplate);
}

ScriptingObject::~ScriptingObject(){
	objTemplate.Dispose();
	context.Dispose();
}

