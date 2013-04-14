#pragma once

#include <v8.h>

#include <Scripting_Helpers.hpp>

using namespace v8;

class V8GameObject : public BaseV8TemplateObject<V8GameObject>{
public:
	//Functions
	static Handle<Value> loadScript( const Arguments& args );
	static Handle<Value> dispatchEvent( const Arguments& args );
	static Handle<Value> release( const Arguments& args );
};

class V8PlayerCharacter : public BaseV8TemplateObject<V8PlayerCharacter>{
public:
	//Functions
	static Handle<Value> addForceAtLocalPos( const Arguments& args );

	//Accessors
	static Handle<Value> getEntity( Local<v8::String> property, const AccessorInfo& info );
	static Handle<Value> getGunTip( Local<v8::String> property, const AccessorInfo& info );
	static Handle<Value> getAniStates( Local<v8::String> property, const AccessorInfo& info );
	static Handle<Value> getSceneNode( Local<v8::String> property, const AccessorInfo& info );
	static Handle<Value> getChildNode( Local<v8::String> property, const AccessorInfo& info );
	static Handle<Value> getCCT( Local<v8::String> property, const AccessorInfo& info );
	//static Handle<Value> getPhys( Local<v8::String> property, const AccessorInfo& info );	
	static Handle<Value> getPhysScene( Local<v8::String> property, const AccessorInfo& info );	

	static Handle<Value> getDirection( Local<v8::String> property, const AccessorInfo& info );
	static void setDirection( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getGunDirection( Local<v8::String> property, const AccessorInfo& info );
	static void setGunDirection( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getTimeSinceLastShot( Local<v8::String> property, const AccessorInfo& info );
	static void setTimeSinceLastShot( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getGrounded( Local<v8::String> property, const AccessorInfo& info );
	static void setGrounded( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getIsTurning( Local<v8::String> property, const AccessorInfo& info );
	static void setIsTurning( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getShiftPressed( Local<v8::String> property, const AccessorInfo& info );
	static void setShiftPressed( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getFlipping( Local<v8::String> property, const AccessorInfo& info );
	static void setFlipping( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getYaw_Target( Local<v8::String> property, const AccessorInfo& info );
	static void setYaw_Target( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getInputVel( Local<v8::String> property, const AccessorInfo& info );
	static void setInputVel( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
	static Handle<Value> getVelocity( Local<v8::String> property, const AccessorInfo& info );
	static void setVelocity( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
};

class V8Enemy : public BaseV8TemplateObject<V8Enemy>{
public:
	//Accessors
	static Handle<Value> getEntity( Local<v8::String> property, const AccessorInfo& info );
	static Handle<Value> getAniStates( Local<v8::String> property, const AccessorInfo& info );
	static Handle<Value> getSceneNode( Local<v8::String> property, const AccessorInfo& info );
	static Handle<Value> getChildNode( Local<v8::String> property, const AccessorInfo& info );
	static Handle<Value> getCCT( Local<v8::String> property, const AccessorInfo& info );
	static Handle<Value> getPhysScene( Local<v8::String> property, const AccessorInfo& info );

	//static Handle<Value> getDirection( Local<v8::String> property, const AccessorInfo& info );
	//static void setDirection( Local<v8::String> property, Local<Value> value, const AccessorInfo& info );
};

class V8GameState : public BaseV8TemplateObject<V8GameState>{
public:
	//Functions
};


class V8GPE {
public:
	static Local<FunctionTemplate> NewFunctionTemplate(InvocationCallback callback = 0, Handle<Value> data = Handle<Value>(), Handle<Signature> signature = Handle<Signature>());			

private:

};