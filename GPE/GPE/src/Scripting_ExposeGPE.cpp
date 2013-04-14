#include <Scripting_ExposeGPE.hpp>
#include <Scripting_Helpers.hpp>

#include <Scripting_ExposePx.hpp>
#include <Scripting_ExposeOGRE.hpp>

#include <GameObject.hpp>
#include <PlayerCharacter.hpp>
#include <Enemy.hpp>
#include <GameState.hpp>

Local<FunctionTemplate> V8GPE::NewFunctionTemplate(InvocationCallback callback, Handle<Value> data, Handle<Signature> signature)
	{
		Local<FunctionTemplate> GPEFuncTemplateBase = FunctionTemplate::New();
		Local<FunctionTemplate> GPEFuncTemplate = FunctionTemplate::New();
		Local<FunctionTemplate> temp;
		Local<FunctionTemplate> temp2;
		Local<ObjectTemplate> objTemp;

		GPEFuncTemplate->SetClassName(v8::String::New("GPE"));
		GPEFuncTemplateBase->PrototypeTemplate()->Set(v8::String::New("GPE"), GPEFuncTemplate->InstanceTemplate());


		//Types
			//GPEGameObject
				V8GameObject::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8GameObject::getTemplate()->SetClassName(v8::String::New("GameObject"));
				GPEFuncTemplateBase->PrototypeTemplate()->Set(v8::String::New("GameObject"), V8GameObject::getTemplate());

				objTemp = V8GameObject::getTemplate()->PrototypeTemplate();
				V8GameObject::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

				objTemp->Set(v8::String::New("loadScript"), FunctionTemplate::New(InvocationCallback( V8GameObject::loadScript )));
				objTemp->Set(v8::String::New("dispatchEvent"), FunctionTemplate::New(InvocationCallback( V8GameObject::dispatchEvent )));
				objTemp->Set(v8::String::New("release"), FunctionTemplate::New(InvocationCallback( V8GameObject::release )));
				
			//GPEPlayerController
				V8PlayerCharacter::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8PlayerCharacter::getTemplate()->SetClassName(v8::String::New("PlayerCharacter"));
				GPEFuncTemplateBase->PrototypeTemplate()->Set(v8::String::New("PlayerCharacter"), V8PlayerCharacter::getTemplate());

				V8PlayerCharacter::getTemplate()->Inherit(V8GameObject::getTemplate());

				objTemp = V8PlayerCharacter::getTemplate()->InstanceTemplate();
				objTemp->SetInternalFieldCount(1);

				V8PlayerCharacter::getTemplate()->PrototypeTemplate()->Set(v8::String::New("addForceAtLocalPos"), FunctionTemplate::New(InvocationCallback( V8PlayerCharacter::addForceAtLocalPos )));

				objTemp->SetAccessor(v8::String::New("entity"), V8PlayerCharacter::getEntity);
				objTemp->SetAccessor(v8::String::New("gunTip"), V8PlayerCharacter::getGunTip);
				objTemp->SetAccessor(v8::String::New("animationStateSet"), V8PlayerCharacter::getAniStates);
				objTemp->SetAccessor(v8::String::New("node"), V8PlayerCharacter::getSceneNode);
				objTemp->SetAccessor(v8::String::New("childNode"), V8PlayerCharacter::getChildNode);
				objTemp->SetAccessor(v8::String::New("CCT"), V8PlayerCharacter::getCCT);
				//objTemp->SetAccessor(v8::String::New("phys"), V8PlayerCharacter::getPhys);
				objTemp->SetAccessor(v8::String::New("physScene"), V8PlayerCharacter::getPhysScene);

				objTemp->SetAccessor(v8::String::New("direction"), V8PlayerCharacter::getDirection, V8PlayerCharacter::setDirection);
				objTemp->SetAccessor(v8::String::New("gunDirection"), V8PlayerCharacter::getGunDirection, V8PlayerCharacter::setGunDirection);
				objTemp->SetAccessor(v8::String::New("timeSinceLastShot"), V8PlayerCharacter::getTimeSinceLastShot, V8PlayerCharacter::setTimeSinceLastShot);
				objTemp->SetAccessor(v8::String::New("grounded"), V8PlayerCharacter::getGrounded, V8PlayerCharacter::setGrounded);
				objTemp->SetAccessor(v8::String::New("isTurning"), V8PlayerCharacter::getIsTurning, V8PlayerCharacter::setIsTurning);
				objTemp->SetAccessor(v8::String::New("shiftPressed"), V8PlayerCharacter::getShiftPressed, V8PlayerCharacter::setShiftPressed);
				objTemp->SetAccessor(v8::String::New("flipping"), V8PlayerCharacter::getFlipping, V8PlayerCharacter::setFlipping);
				objTemp->SetAccessor(v8::String::New("yawTarget"), V8PlayerCharacter::getYaw_Target, V8PlayerCharacter::setYaw_Target);
				objTemp->SetAccessor(v8::String::New("inputVel"), V8PlayerCharacter::getInputVel, V8PlayerCharacter::setInputVel);
				objTemp->SetAccessor(v8::String::New("velocity"), V8PlayerCharacter::getVelocity, V8PlayerCharacter::setVelocity);

			//GPEEnemy
				V8Enemy::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8Enemy::getTemplate()->SetClassName(v8::String::New("Enemy"));
				GPEFuncTemplateBase->PrototypeTemplate()->Set(v8::String::New("Enemy"), V8Enemy::getTemplate());

				V8Enemy::getTemplate()->Inherit(V8GameObject::getTemplate());

				objTemp = V8Enemy::getTemplate()->InstanceTemplate();
				objTemp->SetInternalFieldCount(1);

				objTemp->SetAccessor(v8::String::New("entity"), V8Enemy::getEntity);
				objTemp->SetAccessor(v8::String::New("animationStateSet"), V8Enemy::getAniStates);
				objTemp->SetAccessor(v8::String::New("node"), V8Enemy::getSceneNode);
				objTemp->SetAccessor(v8::String::New("childNode"), V8Enemy::getChildNode);
				objTemp->SetAccessor(v8::String::New("CCT"), V8Enemy::getCCT);
				objTemp->SetAccessor(v8::String::New("physScene"), V8Enemy::getPhysScene);

			//GPEGameState
				V8GameState::getTemplate() = Persistent<FunctionTemplate>::New(Isolate::GetCurrent(),FunctionTemplate::New());
				V8GameState::getTemplate()->SetClassName(v8::String::New("GameState"));
				GPEFuncTemplateBase->PrototypeTemplate()->Set(v8::String::New("GameState"), V8GameState::getTemplate());

				objTemp = V8GameState::getTemplate()->PrototypeTemplate();
				V8GameState::getTemplate()->InstanceTemplate()->SetInternalFieldCount(1);

		//ENUMS

				//temp = FunctionTemplate::New();
				//temp->SetClassName(v8::String::New("PxDataAccessFlag"));
				//GPEFuncTemplate->PrototypeTemplate()->Set("PxDataAccessFlag", temp->InstanceTemplate());

				//temp->PrototypeTemplate()->Set(v8::String::New("eREADABLE"), Uint32::New(PxDataAccessFlag::Enum::eREADABLE));


		//Functions
			//Nothing
				//temp = FunctionTemplate::New();
				//temp->SetClassName(v8::String::New("PxMath"));
				//GPEFuncTemplate->PrototypeTemplate()->Set("PxMath", temp->InstanceTemplate());

				//temp->PrototypeTemplate()->Set(v8::String::New("Max"),			FunctionTemplate::New(func_math_max));
				

		return(GPEFuncTemplateBase);
	}


//GameObject

	Handle<Value> V8GameObject::loadScript(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsString()) 
        {
			GameObject* thisGO = unwrap<GameObject>(args.Holder());

			thisGO->loadScript(*v8::String::Utf8Value(args[0]->ToString()));

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8GameObject::dispatchEvent(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsString()) 
        {
			GameObject* thisGO = unwrap<GameObject>(args.Holder());

			thisGO->dispatchEvent(*v8::String::Utf8Value(args[0]->ToString()));

			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 2 && !args[0].IsEmpty() && args[0]->IsString() &&
			!args[1].IsEmpty() && args[0]->IsArray()){
			GameObject* thisGO = unwrap<GameObject>(args.Holder());

			Local<Array> arr = Local<Array>::Cast(args[1]);

			Persistent<Value> *params = new Persistent<Value>[arr->Length()];
			
			for(int i = 0; i < arr->Length(); i++){
				params[i] = Persistent<Value>::New(Isolate::GetCurrent(),arr->Get(i));
			}

			params->MakeWeak(Isolate::GetCurrent(),params, &CleanupDeleteArray);

			thisGO->dispatchEvent(*v8::String::Utf8Value(args[0]->ToString()), arr->Length(), params);

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8GameObject::release(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 1 && !args[0].IsEmpty() && args[0]->IsString()) 
        {
			GameObject* thisGO = unwrap<GameObject>(args.Holder());

			thisGO->release();

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

//PlayerCharacter
	//physx::PxRigidBody& body, const physx::PxVec3& force, const physx::PxVec3& pos, physx::PxForceMode::Enum mode, bool wakeup=true);
	Handle<Value> V8PlayerCharacter::addForceAtLocalPos(const Arguments& args){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(args.Length() == 4 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxRigidBody::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1]) &&
			!args[2].IsEmpty() && args[2]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[2]) &&
			!args[3].IsEmpty() && args[3]->IsUint32()) 
        {
			PlayerCharacter* thisObj = unwrap<PlayerCharacter>(args.Holder());

			thisObj->addForceAtLocalPos(*unwrap<PxRigidBody>(args[0]->ToObject()), *unwrap<PxVec3>(args[1]->ToObject()), *unwrap<PxVec3>(args[2]->ToObject()), (PxForceMode::Enum)args[3]->Uint32Value());

			return scope.Close( args.Holder() );
		}
		else if(args.Length() == 5 && !args[0].IsEmpty() && args[0]->IsObject() && V8PxRigidBody::getTemplate()->HasInstance(args[0]) &&
			!args[1].IsEmpty() && args[1]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[1]) &&
			!args[2].IsEmpty() && args[2]->IsObject() && V8PxVec3::getTemplate()->HasInstance(args[2]) &&
			!args[3].IsEmpty() && args[3]->IsUint32() &&
			!args[43].IsEmpty() && args[4]->IsBoolean()) 
        {
			PlayerCharacter* thisObj = unwrap<PlayerCharacter>(args.Holder());

			thisObj->addForceAtLocalPos(*unwrap<PxRigidBody>(args[0]->ToObject()), *unwrap<PxVec3>(args[1]->ToObject()), *unwrap<PxVec3>(args[2]->ToObject()), (PxForceMode::Enum)args[3]->Uint32Value(), args[4]->BooleanValue());

			return scope.Close( args.Holder() );
		}

		return scope.Close( Undefined() );
	}

	Handle<Value> V8PlayerCharacter::getEntity( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( wrapByVal<Entity, V8Entity>(*thisObj->ent));
	}

	Handle<Value> V8PlayerCharacter::getGunTip( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		//TODO: Chande this to Bone
		return scope.Close( wrapByVal<Node, V8Node>(*thisObj->m_GunTip));
	}

	Handle<Value> V8PlayerCharacter::getAniStates( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( wrapByVal<AnimationStateSet, V8AnimationStateSet>(*thisObj->m_aniStates));
	}

	Handle<Value> V8PlayerCharacter::getSceneNode( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		//TODO: Chande this to SceneNode
		return scope.Close( wrapByVal<Node, V8Node>(*thisObj->node));
	}

	Handle<Value> V8PlayerCharacter::getChildNode( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		//TODO: Chande this to SceneNode
		return scope.Close( wrapByVal<Node, V8Node>(*thisObj->childNode));
	}

	Handle<Value> V8PlayerCharacter::getCCT( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( wrapByVal<PxController, V8PxController>(*thisObj->mCCT));
	}

	//Handle<Value> V8PlayerCharacter::getPhys( Local<v8::String> property , const AccessorInfo& info ){
	//	//Locker lock(Isolate::GetCurrent());
	//	HandleScope scope(Isolate::GetCurrent());

	//	PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

	//	return scope.Close( wrapByVal<PxPhysics, V8PxPhysics>(*thisObj->mPhys));
	//}

	Handle<Value> V8PlayerCharacter::getPhysScene( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( wrapByVal<PxScene, V8PxScene>(*thisObj->mPhysScene));
	}

	Handle<Value> V8PlayerCharacter::getDirection( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( Uint32::New( thisObj->mDirection ));
	}

	void V8PlayerCharacter::setDirection( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

			thisObj->mDirection = (DIRECTION)value->Uint32Value();
		}
	}

	Handle<Value> V8PlayerCharacter::getGunDirection( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( Uint32::New( thisObj->mGunDirection ));
	}

	void V8PlayerCharacter::setGunDirection( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsUint32()){
			PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

			thisObj->mGunDirection = (GUNDIRECTION)value->Uint32Value();
		}
	}

	Handle<Value> V8PlayerCharacter::getTimeSinceLastShot( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( Number::New( thisObj->timeSinceLastShot ));
	}

	void V8PlayerCharacter::setTimeSinceLastShot( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsNumber()){
			PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

			thisObj->timeSinceLastShot = value->NumberValue();
		}
	}

	Handle<Value> V8PlayerCharacter::getGrounded( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( Boolean::New( thisObj->mGrounded ));
	}

	void V8PlayerCharacter::setGrounded( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsBoolean()){
			PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

			thisObj->mGrounded = value->BooleanValue();
		}
	}

	Handle<Value> V8PlayerCharacter::getIsTurning( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( Boolean::New( thisObj->mIsTurning ));
	}

	void V8PlayerCharacter::setIsTurning( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsBoolean()){
			PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

			thisObj->mIsTurning = value->BooleanValue();
		}
	}

	Handle<Value> V8PlayerCharacter::getShiftPressed( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( Boolean::New( thisObj->mShiftPressed ));
	}

	void V8PlayerCharacter::setShiftPressed( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsBoolean()){
			PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

			thisObj->mShiftPressed = value->BooleanValue();
		}
	}

	Handle<Value> V8PlayerCharacter::getFlipping( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( Boolean::New( thisObj->mFlipping ));
	}

	void V8PlayerCharacter::setFlipping( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsBoolean()){
			PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

			thisObj->mFlipping = value->BooleanValue();
		}
	}

	Handle<Value> V8PlayerCharacter::getYaw_Target( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( wrapByVal<Radian, V8Radian>(thisObj->mYaw_Target) );
	}

	void V8PlayerCharacter::setYaw_Target( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8Radian::getTemplate()->HasInstance(value) ){
			PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

			thisObj->mYaw_Target = *unwrap<Radian>(value->ToObject());
		}
	}

	Handle<Value> V8PlayerCharacter::getInputVel( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( wrapByVal<PxVec3, V8PxVec3>(thisObj->mInputVel) );
	}

	void V8PlayerCharacter::setInputVel( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8Radian::getTemplate()->HasInstance(value) ){
			PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

			thisObj->mInputVel = *unwrap<PxVec3>(value->ToObject());
		}
	}

	Handle<Value> V8PlayerCharacter::getVelocity( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

		return scope.Close( wrapByVal<PxVec3, V8PxVec3>(thisObj->mVelocity) );
	}

	void V8PlayerCharacter::setVelocity( Local<v8::String> property, Local<Value> value, const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		if(!value.IsEmpty() && value->IsObject() && V8Radian::getTemplate()->HasInstance(value) ){
			PlayerCharacter* thisObj = unwrap<PlayerCharacter>(info.Holder());

			thisObj->mVelocity = *unwrap<PxVec3>(value->ToObject());
		}
	}

//Enemy
	Handle<Value> V8Enemy::getEntity( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		Enemy* thisObj = unwrap<Enemy>(info.Holder());

		return scope.Close( wrapByVal<Entity, V8Entity>(*thisObj->ent));
	}

	Handle<Value> V8Enemy::getAniStates( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		Enemy* thisObj = unwrap<Enemy>(info.Holder());

		return scope.Close( wrapByVal<AnimationStateSet, V8AnimationStateSet>(*thisObj->m_aniStates));
	}

	Handle<Value> V8Enemy::getSceneNode( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		Enemy* thisObj = unwrap<Enemy>(info.Holder());

		//TODO: Chande this to SceneNode
		return scope.Close( wrapByVal<Node, V8Node>(*thisObj->node));
	}

	Handle<Value> V8Enemy::getChildNode( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		Enemy* thisObj = unwrap<Enemy>(info.Holder());

		//TODO: Chande this to SceneNode
		return scope.Close( wrapByVal<Node, V8Node>(*thisObj->childNode));
	}

	Handle<Value> V8Enemy::getCCT( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		Enemy* thisObj = unwrap<Enemy>(info.Holder());

		return scope.Close( wrapByVal<PxController, V8PxController>(*thisObj->mCCT));
	}

	Handle<Value> V8Enemy::getPhysScene( Local<v8::String> property , const AccessorInfo& info ){
		//Locker lock(Isolate::GetCurrent());
		HandleScope scope(Isolate::GetCurrent());

		Enemy* thisObj = unwrap<Enemy>(info.Holder());

		return scope.Close( wrapByVal<PxScene, V8PxScene>(*thisObj->mPhysScene));
	}