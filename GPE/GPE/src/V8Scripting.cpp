#include <V8Scripting.hpp>
#include <Scripting_ExposePx.hpp>
#include <Scripting_ExposeGPE.hpp>
#include <Scripting_ExposeOGRE.hpp>
#include <GameObject.hpp>
#include <Util.hpp>

template<> V8Scripting* Ogre::Singleton<V8Scripting>::msSingleton = 0;

V8Scripting::V8Scripting() {
	HandleScope handleScope(Isolate::GetCurrent());

	globalFunctionTemp = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());

	exposeBaseFunctions();

	globalObjectTemp = Persistent<ObjectTemplate>::New(Isolate::GetCurrent(),globalFunctionTemp->InstanceTemplate());

	globalContext = Context::New(NULL, globalObjectTemp);

	globalContext->Enter();
	//Locker lock(Isolate::GetCurrent());
	scriptMgr = new ScriptingManager();
}

V8Scripting::~V8Scripting(){
	globalObjectTemp.Dispose();
	globalContext.Dispose();
	globalFunctionTemp.Dispose();

	delete scriptMgr;
}

void V8Scripting::exposeBaseFunctions(){
	//Locker lock(Isolate::GetCurrent());
	HandleScope handleScope(Isolate::GetCurrent());

	//Hacky as shit, FU JS
	Local<FunctionTemplate> temp1, temp2;
	temp1 = V8PhysX::NewFunctionTemplate();
	temp2 = V8OGRE::NewFunctionTemplate();

	temp1->Inherit(temp2);
	temp2 = V8GPE::NewFunctionTemplate();
	temp2->Inherit(temp1);
	
	globalFunctionTemp->Inherit(temp2);

	globalFunctionTemp->PrototypeTemplate()->Set(v8::String::New("print"),FunctionTemplate::New(printMessage));

	globalFunctionTemp->PrototypeTemplate()->Set(v8::String::New("registerEventCallback"),FunctionTemplate::New(GameObject::v8registerEventCallback));
	globalFunctionTemp->PrototypeTemplate()->Set(v8::String::New("removeEventCallback"),FunctionTemplate::New(GameObject::v8removeEventCallback));
}

Handle<Value> V8Scripting::printMessage(const Arguments& args) 
    {
        //Locker lock(Isolate::GetCurrent());
        HandleScope scope(Isolate::GetCurrent());

		if(args.Length()){
			for(int i = 0; i < args.Length(); i++){
				if(i > 0){
					std::cout << " ";
					Util::dout << " ";
				}

				v8::String::Utf8Value message( args[i]->ToString() );
				if( message.length() ) 
				{
					//Print the message to std::cout
					std::cout << *message;     
					Util::dout << *message;
				}
			}

			std::cout << std::endl;
			Util::dout << std::endl;

			return scope.Close( Boolean::New( true ) );
		}

        return Undefined();
    }

void V8Scripting::reportException(TryCatch* try_catch) {
	//Locker lock(Isolate::GetCurrent());
  v8::HandleScope handle_scope(Isolate::GetCurrent());
  v8::String::Utf8Value exception(try_catch->Exception());
  const char* exception_string = *exception;
  v8::Handle<v8::Message> message = try_catch->Message();
  if (message.IsEmpty()) {
    // V8 didn't provide any extra information about this error; just
    // print the exception.
    //printf("%s\n", exception_string);
	  std::cout << exception_string << std::endl;
	  Util::dout << exception_string << std::endl;
  } else {
    // Print (filename):(line number): (message).
    v8::String::Utf8Value filename(message->GetScriptResourceName());
    const char* filename_string = *filename;
    int linenum = message->GetLineNumber();
    //printf("%s:%i: %s\n", filename_string, linenum, exception_string);
	std::cout << filename_string << ":" << linenum << ": " << exception_string << std::endl;
	Util::dout << filename_string << ":" << linenum << ": " << exception_string << std::endl;
    // Print line of source code.
    v8::String::Utf8Value sourceline(message->GetSourceLine());
    char* sourceline_string = *sourceline;
	// Trim leading spaces
	int whiteSpaces = 0;
	while(isspace(*sourceline_string)) {sourceline_string++; whiteSpaces++;};
    //printf("%s\n", sourceline_string);
	std::cout << sourceline_string << std::endl;
	Util::dout << sourceline_string << std::endl;
    // Print wavy underline (GetUnderline is deprecated).
    int start = message->GetStartColumn();
    for (int i = 0; i < start - whiteSpaces; i++) {
      //printf(" ");
		std::cout << " ";
		Util::dout << " ";
    }
    int end = message->GetEndColumn();
    for (int i = start; i < end; i++) {
      //printf("^");
		std::cout << "^";
		Util::dout << "^";
    }
    //printf("\n");
	std::cout << std::endl;
	Util::dout << std::endl;
  }
}