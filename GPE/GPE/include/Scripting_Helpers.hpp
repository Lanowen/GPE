#pragma once

#include <v8.h>
#include <cassert>
#include <malloc.h>
#include <cstdarg>
#include <assert.h>
#include <cstdarg>
#include <sstream>

using namespace v8;

//Best idea ever
template<class T>
class BaseV8TemplateObject {
public:
	static Persistent<FunctionTemplate> templ;

	static inline Persistent<FunctionTemplate>& getTemplate(){
		return templ;
	}
	
};


//god yes
template<class T>
Persistent<FunctionTemplate> BaseV8TemplateObject<T>::templ;

template <class TYPE>
static inline TYPE* unwrap( const Local<v8::Object>& wrapped ){
	Local<External> external = Local<External>::Cast( wrapped->GetInternalField(0) );
	TYPE* obj = reinterpret_cast<TYPE*>(external->Value());

	return obj;
}

static inline void CleanupDelete(Isolate* isolate, Persistent<Value> object, void* parameter){
	//assert(object.IsNearDeath());
	delete parameter;
   	object.Dispose();
	object.Clear();
}

static inline void CleanupDeleteArray(Isolate* isolate, Persistent<Value> object, void* parameter){
	//assert(object.IsNearDeath());
	delete[] parameter;
	object.Dispose();
	object.Clear();
}

static inline void CleanupFree(Isolate* isolate, Persistent<Value> object, void* parameter){
	//assert(object.IsNearDeath());
	free(parameter);
	object.Dispose();
	object.Clear();
}

static inline void CleanupHandleOnly(Isolate* isolate, Persistent<Value> object, void* parameter){
	//assert(object.IsNearDeath());
	object.Dispose();
	object.Clear();
}

static inline Handle<v8::String> v8stringCreate(int len, ...){
	va_list args;
	va_start(args, len);

	std::stringstream ss;

	for(int i = 0; i < len; ++i )
		ss << va_arg(args, char*);

	va_end(args);

	return v8::String::New(ss.str().c_str());
}

template <class TYPE, class TEMPL>
static inline Handle<Value> wrapPtrCleanup(TYPE* obj ){
	HandleScope scope(Isolate::GetCurrent());

	Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(),TEMPL::getTemplate()->InstanceTemplate()->NewInstance());
	self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDelete);
	self->SetInternalField(0, External::New( obj ));

	return scope.Close( self );
}

template <class TYPE, class TEMPL>
static inline Handle<Value> wrapPtr(TYPE* obj ){
	HandleScope scope(Isolate::GetCurrent());

	Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(),TEMPL::getTemplate()->InstanceTemplate()->NewInstance());
	self.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
	self->SetInternalField(0, External::New( obj ));

	return scope.Close( self );
}

template <class TYPE, class TEMPL>
static inline Handle<Value> wrapByVal(TYPE& obj ){
	HandleScope scope(Isolate::GetCurrent());

	Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(),TEMPL::getTemplate()->InstanceTemplate()->NewInstance());
	self.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
	self->SetInternalField(0, External::New( &obj ));

	return scope.Close( self );
}

template <class TYPE, class TEMPL>
static inline Handle<Value> wrap(TYPE& obj ){
	HandleScope scope(Isolate::GetCurrent());

	TYPE* newObj = new TYPE(obj);

	Persistent<Object> self = Persistent<Object>::New(Isolate::GetCurrent(),TEMPL::getTemplate()->InstanceTemplate()->NewInstance());
	self.MakeWeak(Isolate::GetCurrent(),newObj, &CleanupDelete);
	self->SetInternalField(0, External::New( newObj ));

	return scope.Close( self );
}

template<class T>
class createArray{
public:
	static inline Handle<Value> makeArray(const Arguments& args);
};

template<class T>
Handle<Value> createArray<T>::makeArray(const Arguments& args){
	//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsUint32()) {
			T* obj = new T[ args[0]->Uint32Value() ];
			Persistent<External> self = Persistent<External>::New(Isolate::GetCurrent(), External::New( obj ) );
			self.MakeWeak(Isolate::GetCurrent(),obj, &CleanupDeleteArray);

			//std::cout << "What " << *v8::String::Utf8Value(self->ToString()) << std::endl;

			return scope.Close( self );
		}

		return scope.Close( Undefined() );
}

//template<class T, class templ>
//static inline Handle<Value> autoWrap(const Arguments& args){
//	//Locker lock(Isolate::GetCurrent());
//	HandleScope scope(Isolate::GetCurrent());
//
//	if(args.Length() == 0) 
//    {
//
//		T* ptr = reinterpret_cast<T*>(External::Cast(*args.Holder()->GetHiddenValue(v8::String::New("GameObject")))->Value());
//
//		Persistent<Object> obj = Persistent<Object>::New(Isolate::GetCurrent(),templ::getTemplate()->InstanceTemplate()->NewInstance());			
//		obj.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly );
//		obj->SetInternalField(0, External::New( ptr ));
//		
//		return scope.Close( obj );
//	}
//	//boost::type_traits<PlayerCharacter>(
//
//	return scope.Close( Undefined() );
//}

//#define EXPOSE_TO_SCRIPTS(type, templateObj, name) exposeObject(name, FunctionTemplate::New( InvocationCallback( autoWrap<type, templateObj> ) ))
//#define EXPOSE_TO_SCRIPTS(type, templateObj, name, obj) exposeObject(name, wrapByVal<type, templateObj>(obj))

