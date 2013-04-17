#include "PlayerCharacter.hpp"
#include <Util.hpp>

//#include <Scripting_Helpers.hpp>
//#include <Scripting_ExposePx.hpp>
//#include <Scripting_ExposeGPE.hpp>

#include <Projectile.hpp>
#include <GameState.hpp>

#define TURN_SPEED 15
#define WALK_SPEED 2
#define RUN_SPEED 7
#define AIR_POWER 13
#define MAX_AIR_STANDING_SPEED 3
#define FLIP_SPEED 10
#define GRAVITY -20
#define JUMP_VEL 20
#define SHOOT_ANIMATION_LENGTH 3
#define MAX_LIFE 8
#define INVULNERABILITY_TIME 1
#define HURTSPEED 20
#define HURTANIMTIME 0.2

PlayerCharacter::PlayerCharacter(OIS::Keyboard* im_pKeyboard, OIS::JoyStick* im_pJoyStick, int im_pJoyDeadZone, GameState* owner, bool netOwned) : GameObject(owner), IKeyListener(owner), IJoyStickListener(owner), m_pCamera(0)
{
	netOwned = netOwned;
	mPhys = owner->getPhysics();
	mPhysScene = owner->getMainPhysicsScene();

	PxBoxControllerDesc cDesc;
	
	cDesc.material		= mPhys->createMaterial(0.9f, 0.5f, 0.0f);
	cDesc.position		= PxExtendedVec3(0.f,15.f,0.f);
	cDesc.contactOffset	= 0.005f;
	
	cDesc.stepOffset = 0.05f;
	cDesc.slopeLimit = 0.707f;
	cDesc.upDirection = PxVec3(0.0f, 1.0f, 0.0f);
	cDesc.interactionMode = PxCCTInteractionMode::eINCLUDE;
	//cDesc.maxJumpHeight
	//cDesc.groupsBitmask
	cDesc.density = 10.0;
	cDesc.halfHeight = 2.9f*0.5f;
	cDesc.halfSideExtent = 0.4;
	cDesc.halfForwardExtent = 0.4;
	cDesc.callback		= this;
	//cDesc.behaviorCallback
	cDesc.userData = (GameObject*)this;

	mCCT = owner->getControllerManager()->createController(*mPhys, mPhysScene, cDesc);
	PX_ASSERT(mCCT);

	mCCT->getActor()->userData = (GameObject*)this;

	PxFilterData filterData;
	filterData.word0 = 1; // word0 = own ID
					//bullets and powerups
	filterData.word1 = 2|16;	// word1 = ID mask to filter pairs that trigger a contact callback;

	const PxU32 numShapes = mCCT->getActor()->getNbShapes();
	PxShape** shapes = new PxShape*[numShapes];
	mCCT->getActor()->getShapes(shapes, numShapes);
	for(PxU32 i = 0; i < numShapes; i++)
	{
		PxShape* shape = shapes[i];
		shape->setSimulationFilterData(filterData);
	}
	delete[] shapes;

	ZeroMemory(mButtons, 10);

	//mActiveGroups = 1;
	mGrounded = false;
	//mJumpTime = 0;
	//mMaxJumpVelocity = 10.0f;
	//mJumpVelocity0.zero();
	//mMaxGroundSpeed = 4.0f;
	//mMaxAirSpeed = 3.0f;
	//mAirMovement = 0.15f;
	//mMaxTurnSpeed = 30.0f;
	mIsTurning = false;
	mFlipping = false;
	mRunningPressed = false;
	mVelocity = mInputVel = PxVec3(0,0,0);
	mGunDirection = FORWARD;
	timeSinceLastShot = 1000;

	mYaw_Target = Math::PI/2;
	mDirection = RIGHT;

    m_pKeyboard = im_pKeyboard;
    m_pJoyStick = im_pJoyStick;
    m_pJoyDeadZone = im_pJoyDeadZone;

    SceneManager* gameSceneMgr = Root::getSingletonPtr()->getSceneManager("GameSceneMgr");
	//ent = gameSceneMgr->createEntity("Samus", "Samus.mesh" );
	ent = gameSceneMgr->createEntity("samustestSamus.mesh" );
	ent->getSkeleton()->setBlendMode(SkeletonAnimationBlendMode::ANIMBLEND_CUMULATIVE);


	node = gameSceneMgr->getRootSceneNode()->createChildSceneNode();
	childNode = node->createChildSceneNode();
	node->setPosition(Vector3(mCCT->getPosition().x, mCCT->getPosition().y, mCCT->getPosition().z));
	childNode->setPosition(Vector3::ZERO);
	childNode->attachObject(ent);

    m_aniStates = ent->getAllAnimationStates();

	m_aniStates->getAnimationState("Walk_full")->setLoop(true);
	m_aniStates->getAnimationState("Run_full")->setLoop(true);
	m_aniStates->getAnimationState("Walk_full_upper")->setLoop(true);
	m_aniStates->getAnimationState("Run_full_upper")->setLoop(true);
	m_aniStates->getAnimationState("Crouch")->setLoop(true);
	m_aniStates->getAnimationState("Falling")->setLoop(true);

	m_aniStates->getAnimationState("Jump_up")->setLoop(false);
	m_aniStates->getAnimationState("Jump_peaking")->setLoop(false);
	m_aniStates->getAnimationState("Walk_step")->setLoop(false);
	m_aniStates->getAnimationState("Run_step")->setLoop(false);
	m_aniStates->getAnimationState("Crouch")->setLoop(false);
	m_aniStates->getAnimationState("Aim_up_angled")->setLoop(false);
	m_aniStates->getAnimationState("Aim_down_angled")->setLoop(false);

	m_GunTip = ent->getSkeleton()->getBone("Bone_Gun_Tip");

	timeSinceHurt = 100000;
	life = MAX_LIFE;
	hurtTravelDir = PxVec3(0);
	netUpdateTimer = 0;

	//HandleScope scope(Isolate::GetCurrent());

	//Persistent<Object> bo = Persistent<Object>::New(Isolate::GetCurrent(),BooleanObject::New(mGrounded )->ToObject());
	//bo->SetInternalField(0, External::New( &mGrounded ));
	//bo.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
	//exposeObject("mGrounded", Number::New(23987234.234));

	/*exposeObject("TURN_SPEED", Number::New(TURN_SPEED));
	exposeObject("WALK_SPEED", Number::New(WALK_SPEED));
	exposeObject("RUN_SPEED", Number::New(RUN_SPEED));
	exposeObject("AIR_POWER", Number::New(AIR_POWER));
	exposeObject("MAX_AIR_STANDING_SPEED", Number::New(MAX_AIR_STANDING_SPEED));
	exposeObject("FLIP_SPEED", Number::New(FLIP_SPEED));
	exposeObject("GRAVITY", Number::New(GRAVITY));
	exposeObject("JUMP_VEL", Number::New(JUMP_VEL));
	exposeObject("SHOOT_ANIMATION_LENGTH", Number::New(SHOOT_ANIMATION_LENGTH));

	exposeObject("LEFT", Uint32::New(LEFT));
	exposeObject("RIGHT", Uint32::New(RIGHT));
	exposeObject("UPANGLED", Uint32::New(UPANGLED));
	exposeObject("DOWNANGLED", Uint32::New(DOWNANGLED));
	exposeObject("FORWARD", Uint32::New(FORWARD));
	exposeObject("UP", Uint32::New(UP));
	exposeObject("DOWN", Uint32::New(DOWN));

	exposeObject("Player", wrapPtr<PlayerCharacter, V8PlayerCharacter>(this));
	loadScript("playerController.js");*/

	registerEventCallback("OnDamage", boost::bind(&PlayerCharacter::OnDamage, this, _1));

}

PlayerCharacter::~PlayerCharacter()
{
	mCCT->release();
	node->removeAndDestroyAllChildren();
	Root::getSingletonPtr()->getSceneManager("GameSceneMgr")->destroySceneNode(node);
}

void PlayerCharacter::release(){
	GameObject::release();
}

bool PlayerCharacter::isInvulnerable(){
	return timeSinceHurt < INVULNERABILITY_TIME;
}

bool PlayerCharacter::canMove(){
	return timeSinceHurt > HURTANIMTIME;
}

void PlayerCharacter::giveGamera(Camera* cam){
	m_pCamera = cam;
}

void PlayerCharacter::resetLife(){
	life = MAX_LIFE;
}

void PlayerCharacter::getPowerUp(POWERUP_TYPE type){
	switch(type){
	case POWERUP_TYPE::ENERGY_LARGE:
		life+=4;
		if(life > MAX_LIFE)
			life = MAX_LIFE;
		break;
	case POWERUP_TYPE::ENERGY_SMALL:
		life++;
		if(life > MAX_LIFE)
			life = MAX_LIFE;
		break;
	case POWERUP_TYPE::MISSILE:

		break;
	}
}


void PlayerCharacter::getHurt(PxVec3 direction){
	if(netOwned){ //don't want to mess with this on other players for now...
		life --;

		if(life <= 0){
			SerializableUINT32 i;
			i.val = netId;

			socket->Send(i, NEW_NETUPDATES::PLAYER_DEATH, GPENet::DatagramImportance::RELIABLE_ORDERED);
		}
	}

	timeSinceHurt = 0;

	mVelocity.y = 0;
	mVelocity.x = 0;

	if(direction.x >= 0){
		hurtTravelDir.x = 0.9009009;
	}
	else {
		hurtTravelDir.x = -0.9009009;
	}

	if(direction.y >= 0){
		hurtTravelDir.y = 0.45045045;
	}
	else {
		hurtTravelDir.y = -0.45045045;
	}

	if(socket.get() != 0){
		IDandPos idp;
		idp.id = netId;
		idp.px = hurtTravelDir.x;
		idp.py = hurtTravelDir.y;
		idp.pz = hurtTravelDir.z;

		socket->Send(idp, NEW_NETUPDATES::PLAYER_HURT, GPENet::DatagramImportance::RELIABLE_ORDERED);
	}
}

void PlayerCharacter::DoHit(PxControllersHit hit){
	//Util::dout << "Thats a hit on me" << std::endl;
	if(netOwned && !isInvulnerable()){
		getHurt(mCCT->getPosition()-hit.worldPos);
	}
}

void PlayerCharacter::OnDamage(const EventData* data){
	if(netOwned && !isInvulnerable()){
		ProjectileEvent* pevt = (ProjectileEvent*)data;
		GameObject* go = (GameObject*)pevt->data;

		if(go->getType() == GO_TYPE::PROJECTILE){
			Projectile* proj = (Projectile*)go;
			if(proj->getSpawner() != (GameObject*)this)
				getHurt(toVec3(mCCT->getPosition())-(proj->getPosition() - PxVec3(0,1,0)));
		}
	}
}

void PlayerCharacter::Update(Real deltaTime){
	//runScripts();
	timeSinceLastShot += deltaTime;
	timeSinceHurt += deltaTime;

	if(canMove()){
		getInput(deltaTime);
	}

	if(!mFlipping){
		if(mInputVel.x > 0){
			mDirection = RIGHT;
			if((node->getOrientation()*Vector3::UNIT_Z).dotProduct(Vector3::UNIT_X) < 0.95) {
				mIsTurning = true;
				mYaw_Target = Math::PI/2;
			}
		}
		else if(mInputVel.x < 0){
			mDirection = LEFT;
			if((node->getOrientation()*Vector3::UNIT_Z).dotProduct(Vector3::NEGATIVE_UNIT_X) < 0.95){
				mIsTurning = true;
				mYaw_Target = -Math::PI/2;
			}
		}
	}

	AdvancePhysics(deltaTime);
	UpdateAnimation(deltaTime);

	if(m_pCamera){
		m_pCamera->setPosition(ent->getParentSceneNode()->_getDerivedPosition() + Vector3(0,0,20));
		m_pCamera->lookAt(ent->getParentSceneNode()->_getDerivedPosition());
	}

	if(socket.get() != 0){
		netUpdateTimer += deltaTime;
		if(mInputVel != mLastInputVel){
			IDandPos idp;
			idp.id = netId;
			idp.px = mInputVel.x;
			idp.py = mInputVel.y;
			idp.pz = mInputVel.z;
			mLastInputVel = mInputVel;

			socket->Send(idp, NEW_NETUPDATES::PLAYER_INPUTVEL, GPENet::DatagramImportance::RELIABLE_ORDERED);
		}

		if(netUpdateTimer >= 0.5){
			netUpdateTimer -= 0.5;

			IDandPos idp;
			idp.id = netId;
			PxExtendedVec3 cctPos = mCCT->getPosition();
			idp.px = cctPos.x;
			idp.py = cctPos.y;
			idp.pz = cctPos.z;

			socket->Send(idp, NEW_NETUPDATES::SET_POS, GPENet::DatagramImportance::RELIABLE_ORDERED);
		}
	}
}

void PlayerCharacter::AdvancePhysics(Real deltaTime){ 
	PxVec3 disp = PxVec3(0);

	mVelocity.y += GRAVITY*deltaTime;

	Vector3 pos = Util::vec_from_to<PxExtendedVec3, Vector3>(mCCT->getPosition());

	if(!mIsTurning && mGrounded){
		if(mRunningPressed)
			disp += mInputVel * RUN_SPEED;
		else
			disp += mInputVel * WALK_SPEED;
	}
	else if(!mGrounded){
		if(PxSign(mVelocity.x*mInputVel.x) < 0 || (PxSign(mVelocity.x*mInputVel.x) > 0 && PxAbs(mVelocity.x) < MAX_AIR_STANDING_SPEED))
			mVelocity += mInputVel * AIR_POWER * deltaTime;

		if(mFlipping){
			if(mVelocity.x < 0 && mDirection == RIGHT){
				mDirection = LEFT;
				mIsTurning = true;
				mYaw_Target = -Math::PI/2;
			}
			else if(mVelocity.x > 0 && mDirection == LEFT){
				mDirection = RIGHT;
				mIsTurning = true;
				mYaw_Target = Math::PI/2;
			}
		}
	}

	if(mGrounded && m_aniStates->getAnimationState("Jump_up")->getEnabled() && m_aniStates->getAnimationState("Jump_up")->getTimePosition() >= m_aniStates->getAnimationState("Jump_up")->getLength()*0.75){
		mVelocity.y = JUMP_VEL;
		mGrounded = false;
		m_aniStates->getAnimationState("Run_full")->setEnabled(false);
		m_aniStates->getAnimationState("Walk_full")->setEnabled(false);
		m_aniStates->getAnimationState("Run_step")->setEnabled(false);
		m_aniStates->getAnimationState("Walk_step")->setEnabled(false);

		m_aniStates->getAnimationState("Run_full_upper")->setEnabled(false);
		m_aniStates->getAnimationState("Walk_full_upper")->setEnabled(false);
		m_aniStates->getAnimationState("Run_step_upper")->setEnabled(false);
		m_aniStates->getAnimationState("Walk_step_upper")->setEnabled(false);
		m_aniStates->getAnimationState("Run_full_upper_shoot")->setEnabled(false);
		m_aniStates->getAnimationState("Walk_full_upper_shoot")->setEnabled(false);
		m_aniStates->getAnimationState("Run_step_upper_shoot")->setEnabled(false);
		m_aniStates->getAnimationState("Walk_step_upper_shoot")->setEnabled(false);


		if(PxAbs(disp.x) > 0){
			mFlipping = true;
			m_aniStates->getAnimationState("Flipping")->setEnabled(true);
			m_aniStates->getAnimationState("Jump_up")->setEnabled(false);
		}
		mVelocity.x = disp.x;
		disp.x = 0;
	}

	disp += mVelocity;
	
	if(timeSinceHurt < HURTANIMTIME){
		disp += hurtTravelDir*HURTSPEED;
	}

	disp *= deltaTime;

	disp.z = -mCCT->getPosition().z; //keep it at ZERO_ZZZZZz

	mCCT->move(disp,0,deltaTime,PxSceneQueryHitType::eBLOCK,0);

	pos = Util::vec_from_to<PxExtendedVec3, Vector3>(mCCT->getPosition());

	node->setPosition(pos);	
}

bool PlayerCharacter::IsAlive(){
	return isAlive;
}

Vector3 PlayerCharacter::getPosition(){
	return Util::vec_from_to<PxExtendedVec3, Vector3>(mCCT->getPosition());
}

void PlayerCharacter::setPosition(Vector3 pos){
	mCCT->setPosition(Util::vec_from_to<Vector3,PxExtendedVec3>(pos));
}

void PlayerCharacter::UpdateAnimation(Real deltaTime){
	/*HandleScope handleScope(Isolate::GetCurrent());
	Handle<Value> args[1];
	args[0] = Number::New(deltaTime);
	dispatchEvent("UpdateAnimation", 1, args);*/

	if(!mFlipping){
		if(mGunDirection == UPANGLED){
			m_aniStates->getAnimationState("Run_full_upper")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_full_upper")->setEnabled(false);
			m_aniStates->getAnimationState("Run_step_upper")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_step_upper")->setEnabled(false);
			m_aniStates->getAnimationState("Run_full_upper_shoot")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_full_upper_shoot")->setEnabled(false);
			m_aniStates->getAnimationState("Run_step_upper_shoot")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_step_upper_shoot")->setEnabled(false);

			if(!mGrounded){
				m_aniStates->getAnimationState("Jump_up")->setEnabled(false);
				//m_aniStates->getAnimationState("Jump_peaking")->setEnabled(false);
			}

			m_aniStates->getAnimationState("Aim_up_angled")->setEnabled(true);
			m_aniStates->getAnimationState("Aim_down_angled")->setEnabled(false);
		}
		else if(mGunDirection == DOWNANGLED){
			m_aniStates->getAnimationState("Run_full_upper")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_full_upper")->setEnabled(false);
			m_aniStates->getAnimationState("Run_step_upper")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_step_upper")->setEnabled(false);
			m_aniStates->getAnimationState("Run_full_upper_shoot")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_full_upper_shoot")->setEnabled(false);
			m_aniStates->getAnimationState("Run_step_upper_shoot")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_step_upper_shoot")->setEnabled(false);
			
			if(!mGrounded){
				m_aniStates->getAnimationState("Jump_up")->setEnabled(false);
				//m_aniStates->getAnimationState("Jump_peaking")->setEnabled(false);
			}

			m_aniStates->getAnimationState("Aim_up_angled")->setEnabled(false);
			m_aniStates->getAnimationState("Aim_down_angled")->setEnabled(true);
		}
		else {
			m_aniStates->getAnimationState("Aim_up_angled")->setEnabled(false);
			m_aniStates->getAnimationState("Aim_down_angled")->setEnabled(false);
		}
	}


	if(!mGrounded){
		m_aniStates->getAnimationState("Run_full")->setEnabled(false);
		m_aniStates->getAnimationState("Walk_full")->setEnabled(false);
		m_aniStates->getAnimationState("Run_full_upper")->setEnabled(false);
		m_aniStates->getAnimationState("Walk_full_upper")->setEnabled(false);

		if(mFlipping){
			m_aniStates->getAnimationState("Run_full_upper_shoot")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_full_upper_shoot")->setEnabled(false);
			m_aniStates->getAnimationState("Run_step_upper_shoot")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_step_upper_shoot")->setEnabled(false);
		}

		if(!m_aniStates->getAnimationState("Flipping")->getEnabled()){
			if(mVelocity.y < -1){
				if(!m_aniStates->getAnimationState("Falling")->getEnabled()){
					m_aniStates->getAnimationState("Falling")->setEnabled(true);
					m_aniStates->getAnimationState("Falling")->setTimePosition(0);
				}
				m_aniStates->getAnimationState("Jump_peaking")->setEnabled(false);
				m_aniStates->getAnimationState("Jump_up")->setEnabled(false);
			}
			else if(mVelocity.y < 6 && !m_aniStates->getAnimationState("Jump_peaking")->getEnabled() && !m_aniStates->getAnimationState("Falling")->getEnabled()){
				m_aniStates->getAnimationState("Jump_peaking")->setTimePosition(0);
				m_aniStates->getAnimationState("Jump_peaking")->setEnabled(true);
				
				m_aniStates->getAnimationState("Jump_up")->setEnabled(false);
			}
			//Util::dout << m_aniStates->getAnimationState("Jump_peaking")->getEnabled() << " " << m_aniStates->getAnimationState("Jump_peaking")->getTimePosition() << " " << m_aniStates->getAnimationState("Jump_peaking")->getLength() << std::endl;
		}
	}
	else {
		m_aniStates->getAnimationState("Flipping")->setEnabled(false);
		m_aniStates->getAnimationState("Falling")->setEnabled(false);
		m_aniStates->getAnimationState("Jump_peaking")->setEnabled(false);
		if(mInputVel.isZero()){
			m_aniStates->getAnimationState("Run_full")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_full")->setEnabled(false);
			m_aniStates->getAnimationState("Run_step")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_step")->setEnabled(false);

			
			m_aniStates->getAnimationState("Run_full_upper")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_full_upper")->setEnabled(false);
			m_aniStates->getAnimationState("Run_step_upper")->setEnabled(false);
			m_aniStates->getAnimationState("Walk_step_upper")->setEnabled(false);

			if(mGunDirection == UPANGLED){
				m_aniStates->getAnimationState("Aim_up_angled")->setEnabled(true);
				m_aniStates->getAnimationState("Aim_down_angled")->setEnabled(false);
			}
			else if(mGunDirection == DOWNANGLED){
				m_aniStates->getAnimationState("Aim_up_angled")->setEnabled(false);
				m_aniStates->getAnimationState("Aim_down_angled")->setEnabled(true);
			}
			else {
				m_aniStates->getAnimationState("Aim_up_angled")->setEnabled(false);
				m_aniStates->getAnimationState("Aim_down_angled")->setEnabled(false);
			}
		}
		else {
			if(mIsTurning){
				//turning animation
				m_aniStates->getAnimationState("Run_full")->setEnabled(false);
				m_aniStates->getAnimationState("Walk_full")->setEnabled(false);
				m_aniStates->getAnimationState("Run_step")->setEnabled(false);
				m_aniStates->getAnimationState("Walk_step")->setEnabled(false);

				m_aniStates->getAnimationState("Run_full_upper")->setEnabled(false);
				m_aniStates->getAnimationState("Walk_full_upper")->setEnabled(false);
				m_aniStates->getAnimationState("Run_step_upper")->setEnabled(false);
				m_aniStates->getAnimationState("Walk_step_upper")->setEnabled(false);
				m_aniStates->getAnimationState("Run_full_upper_shoot")->setEnabled(false);
				m_aniStates->getAnimationState("Walk_full_upper_shoot")->setEnabled(false);
				m_aniStates->getAnimationState("Run_step_upper_shoot")->setEnabled(false);
				m_aniStates->getAnimationState("Walk_step_upper_shoot")->setEnabled(false);
			}
			else if(mRunningPressed){
				if(!m_aniStates->getAnimationState("Run_full")->getEnabled() && !m_aniStates->getAnimationState("Run_step")->getEnabled() ){
					m_aniStates->getAnimationState("Run_step")->setEnabled(true);
					m_aniStates->getAnimationState("Run_step")->setTimePosition(0);

					if(timeSinceLastShot > SHOOT_ANIMATION_LENGTH && mGunDirection == FORWARD){
						m_aniStates->getAnimationState("Run_step_upper")->setEnabled(true);
						m_aniStates->getAnimationState("Run_step_upper")->setTimePosition(m_aniStates->getAnimationState("Run_step")->getTimePosition());
						m_aniStates->getAnimationState("Run_step_upper_shoot")->setEnabled(false);
					}
					else {
						m_aniStates->getAnimationState("Run_step_upper_shoot")->setEnabled(true);
						m_aniStates->getAnimationState("Run_step_upper_shoot")->setTimePosition(m_aniStates->getAnimationState("Run_step_upper")->getTimePosition());
					}
				}
				if(m_aniStates->getAnimationState("Run_step")->getEnabled() && m_aniStates->getAnimationState("Run_step")->hasEnded()){
					m_aniStates->getAnimationState("Run_full")->setEnabled(true);
					m_aniStates->getAnimationState("Run_full")->setTimePosition(0);

					m_aniStates->getAnimationState("Run_step")->setEnabled(false);
					m_aniStates->getAnimationState("Run_step_upper")->setEnabled(false);

					if(timeSinceLastShot > SHOOT_ANIMATION_LENGTH && mGunDirection == FORWARD){
						m_aniStates->getAnimationState("Run_full_upper")->setEnabled(true);
						m_aniStates->getAnimationState("Run_full_upper")->setTimePosition(m_aniStates->getAnimationState("Run_full")->getTimePosition());
					}
					else {
						m_aniStates->getAnimationState("Run_full_upper_shoot")->setEnabled(true);
						m_aniStates->getAnimationState("Run_full_upper_shoot")->setTimePosition(m_aniStates->getAnimationState("Run_full_upper")->getTimePosition());
					}
				}
				m_aniStates->getAnimationState("Walk_full")->setEnabled(false);
				m_aniStates->getAnimationState("Walk_step")->setEnabled(false);

				m_aniStates->getAnimationState("Walk_step_upper")->setEnabled(false);
				m_aniStates->getAnimationState("Walk_full_upper")->setEnabled(false);

				m_aniStates->getAnimationState("Walk_full_upper_shoot")->setEnabled(false);
				m_aniStates->getAnimationState("Walk_step_upper_shoot")->setEnabled(false);
			}
			else{
				if(!m_aniStates->getAnimationState("Walk_full")->getEnabled() && !m_aniStates->getAnimationState("Walk_step")->getEnabled() ){
					m_aniStates->getAnimationState("Walk_step")->setEnabled(true);
					m_aniStates->getAnimationState("Walk_step")->setTimePosition(0);

					if(timeSinceLastShot > SHOOT_ANIMATION_LENGTH && mGunDirection == FORWARD){
						m_aniStates->getAnimationState("Walk_step_upper")->setEnabled(true);
						m_aniStates->getAnimationState("Walk_step_upper")->setTimePosition(m_aniStates->getAnimationState("Walk_step")->getTimePosition());
						m_aniStates->getAnimationState("Walk_step_upper_shoot")->setEnabled(false);
					}
					else {
						m_aniStates->getAnimationState("Walk_step_upper_shoot")->setEnabled(true);
						m_aniStates->getAnimationState("Walk_step_upper_shoot")->setTimePosition(m_aniStates->getAnimationState("Walk_step_upper")->getTimePosition());
					}
				}
				if(m_aniStates->getAnimationState("Walk_step")->getEnabled() && m_aniStates->getAnimationState("Walk_step")->hasEnded() ){
					m_aniStates->getAnimationState("Walk_step")->setEnabled(false);
					m_aniStates->getAnimationState("Walk_full")->setEnabled(true);
					m_aniStates->getAnimationState("Walk_full")->setTimePosition(0);

					m_aniStates->getAnimationState("Walk_step_upper")->setEnabled(false);

					if(timeSinceLastShot > SHOOT_ANIMATION_LENGTH && mGunDirection == FORWARD){
						m_aniStates->getAnimationState("Walk_full_upper")->setEnabled(true);
						m_aniStates->getAnimationState("Walk_full_upper")->setTimePosition(m_aniStates->getAnimationState("Walk_full")->getTimePosition());
						m_aniStates->getAnimationState("Walk_full_upper_shoot")->setEnabled(false);
					}
					else {
						m_aniStates->getAnimationState("Walk_full_upper_shoot")->setEnabled(true);
						m_aniStates->getAnimationState("Walk_full_upper_shoot")->setTimePosition(m_aniStates->getAnimationState("Walk_full_upper")->getTimePosition());
					}
				}
				m_aniStates->getAnimationState("Run_full")->setEnabled(false);
				m_aniStates->getAnimationState("Run_step")->setEnabled(false);

				m_aniStates->getAnimationState("Run_full_upper")->setEnabled(false);
				m_aniStates->getAnimationState("Run_step_upper")->setEnabled(false);			

				m_aniStates->getAnimationState("Run_full_upper_shoot")->setEnabled(false);
				m_aniStates->getAnimationState("Run_step_upper_shoot")->setEnabled(false);
			}
		}
	}
	if(mIsTurning){
		Radian yaw = node->_getDerivedOrientation().getYaw();
		Radian temp = Math::Abs(mYaw_Target - yaw);
		if(temp < Radian(TURN_SPEED * deltaTime)){
			yaw = temp;
			mIsTurning = false;
		}
		else {
			yaw = Radian(TURN_SPEED * deltaTime);
		}
		node->yaw(yaw * (mDirection == LEFT ? -1 : 1));
	}

	updateFlipping(deltaTime);
	addTimeToAnimations(deltaTime);
}

void PlayerCharacter::updateFlipping(Real deltaTime){
	if(mFlipping){
		childNode->pitch(Radian(FLIP_SPEED * deltaTime));
	}
	else {
		Radian deltaAngle = childNode->getOrientation().getPitch();
		childNode->pitch(-deltaAngle);
		
	}
}

void PlayerCharacter::addTimeToAnimations(Real deltaTime){
	if(m_aniStates->hasEnabledAnimationState()){
        ConstEnabledAnimationStateIterator itrAnim = m_aniStates->getEnabledAnimationStateIterator();

        while(itrAnim.hasMoreElements()){
            AnimationState *anim = itrAnim.getNext();
            anim->addTime(deltaTime);
            //if(!anim.getLoop() && anim.getLength() == anim.getTimePosition()){
            //anim.setEnabled(false);
            //anim.setTimePosition(0);
            //}
        }
    }
}

bool PlayerCharacter::keyPressed(const OIS::KeyEvent &keyEventRef){
	if(m_pKeyboard){
	if(keyEventRef.key == OIS::KC_SPACE && mGrounded && !m_aniStates->getAnimationState("Jump_up")->getEnabled())
    {
		m_aniStates->getAnimationState("Jump_up")->setTimePosition(0);
		m_aniStates->getAnimationState("Jump_up")->setEnabled(true);
    }


	if(keyEventRef.key == OIS::KC_LCONTROL && !mIsTurning){
		timeSinceLastShot = 0;
		Quaternion dir;
		if(mGunDirection == UPANGLED){
			dir = Quaternion(Radian(Math::HALF_PI*0.5), Vector3::UNIT_Z*(mDirection?1:-1))*node->_getDerivedOrientation()/*node->_getDerivedOrientation()*m_GunTip->_getDerivedOrientation()*/;
		}
		else if(mGunDirection == DOWNANGLED){
			dir = Quaternion(Radian(-Math::HALF_PI*0.5), Vector3::UNIT_Z*(mDirection?1:-1))*node->_getDerivedOrientation()/*node->_getDerivedOrientation()*m_GunTip->_getDerivedOrientation()*/;
		}
		else {
			dir = node->_getDerivedOrientation()/*node->_getDerivedOrientation()*m_GunTip->_getDerivedOrientation()*/;
		}

		owner->AddGameObject(new Projectile(owner, this, node->_getFullTransform()*m_GunTip->_getDerivedPosition(), dir));

		if(!mGrounded){
			if(m_aniStates->getAnimationState("Jump_up")->getEnabled()){
				m_aniStates->getAnimationState("Jump_up")->setEnabled(false);
				
			}

			if(mFlipping){
				mFlipping = false;
				m_aniStates->getAnimationState("Flipping")->setEnabled(false);
				m_aniStates->getAnimationState("Falling")->setEnabled(true);
			}
		}
	}
	}

	return(true);
}

bool PlayerCharacter::keyReleased(const OIS::KeyEvent &keyEventRef){
	if(m_pKeyboard){
    if(keyEventRef.key == OIS::KC_SPACE && !mGrounded && mVelocity.y > 0)
    {
		mVelocity.y = 0;
    }
	}
	return(true);
}

bool PlayerCharacter::povMoved( const OIS::JoyStickEvent &e, int pov ) {

    return true;
}

bool PlayerCharacter::axisMoved( const OIS::JoyStickEvent &e, int axis ) {


    return true;
}

bool PlayerCharacter::sliderMoved( const OIS::JoyStickEvent &e, int sliderID ) {

    return true;
}

		//
		//	4					5
		//		6		7	
		//	9				3
		//				8 2   1
		//					0

bool PlayerCharacter::buttonPressed( const OIS::JoyStickEvent &e, int button ) {
	if(m_pJoyStick){
		ButtonPress bp; //no oil spills here
		bp.id = netId;
		bp.bid = button;

		socket->Send(bp, NEW_NETUPDATES::PLAYER_INPUT_BUTTON_PRESS, GPENet::DatagramImportance::RELIABLE_ORDERED);

		doButtonPressed(button);
	}

    return true;
}


void PlayerCharacter::doButtonPressed( int button ) {

	mButtons[button] = true;
	
	if(button == 1 && mGrounded && !m_aniStates->getAnimationState("Jump_up")->getEnabled())
	{
		m_aniStates->getAnimationState("Jump_up")->setTimePosition(0);
		m_aniStates->getAnimationState("Jump_up")->setEnabled(true);
	}

	bool wasFlipping = false;

	if(!mGrounded){
		if(m_aniStates->getAnimationState("Jump_up")->getEnabled()){
			m_aniStates->getAnimationState("Jump_up")->setEnabled(false);
				
		}

		if(mFlipping){
			wasFlipping = true;
			mFlipping = false;
			m_aniStates->getAnimationState("Flipping")->setEnabled(false);
			m_aniStates->getAnimationState("Falling")->setEnabled(true);
		}		
	}


	if((button == 2 || button == 3) && !mIsTurning){
		timeSinceLastShot = 0;
		Quaternion dir;
		if(mGunDirection == UPANGLED){
			dir = Quaternion(Radian(Math::HALF_PI*0.5), Vector3::UNIT_Z*(mDirection?1:-1))*node->_getDerivedOrientation()/*node->_getDerivedOrientation()*m_GunTip->_getDerivedOrientation()*/;
		}
		else if(mGunDirection == DOWNANGLED){
			dir = Quaternion(Radian(-Math::HALF_PI*0.5), Vector3::UNIT_Z*(mDirection?1:-1))*node->_getDerivedOrientation()/*node->_getDerivedOrientation()*m_GunTip->_getDerivedOrientation()*/;
		}
		else {
			dir = node->_getDerivedOrientation()/*node->_getDerivedOrientation()*m_GunTip->_getDerivedOrientation()*/;
		}
		if(!wasFlipping){
			owner->AddGameObject(new Projectile(owner, this, node->_getFullTransform()*m_GunTip->_getDerivedPosition(), dir));
		}
		else {
			owner->AddGameObject(new Projectile(owner, this, node->_getDerivedPosition()+(mDirection == LEFT? Vector3(-1,0,0) : Vector3(1,0,0)), dir));
		}

		
	}	
}

bool PlayerCharacter::buttonReleased( const OIS::JoyStickEvent &e, int button ) {
	if(m_pJoyStick){
		ButtonPress bp; //no oil spills here EITHER.
		bp.id = netId;
		bp.bid = button;

		socket->Send(bp, NEW_NETUPDATES::PLAYER_INPUT_BUTTON_RELEASE, GPENet::DatagramImportance::RELIABLE_ORDERED);

		doButtonReleased(button);
	}

    return true;
}

void PlayerCharacter::doButtonReleased( int button ) {

	mButtons[button] = false;

	if(button == 1 && !mGrounded && mVelocity.y > 0)
	{
		mVelocity.y = 0;
	}
}

void PlayerCharacter::getInput(Real deltaTime){

	Vector3 forward = node->getOrientation()*Vector3::UNIT_Z;

    if(m_pJoyStick){
		OIS::JoyStickState joyState = m_pJoyStick->getJoyStickState();
        int joyx = joyState.mAxes[1].abs;
        if (Math::Abs(joyx) > m_pJoyDeadZone && Math::Abs(joyx)){
			if(Math::Sign(joyx) > 0){
                if(!mFlipping){
					mDirection = RIGHT;
					if(forward.dotProduct(Vector3::UNIT_X) < 0.95) {
						mIsTurning = true;
						mYaw_Target = Math::PI/2;
					}
				}
				mInputVel.x = 1;
            }
            else {
               if(!mFlipping){
					mDirection = LEFT;
					if(forward.dotProduct(Vector3::NEGATIVE_UNIT_X) < 0.95){
						mIsTurning = true;
						mYaw_Target = -Math::PI/2;
					}
				}
				mInputVel.x = -1;
            }
			
        }
		else {
			mInputVel.x = 0;
		}

		//dpad
		if((joyState.mPOV[0].direction & OIS::Pov::East) != 0){
			/*if(!mFlipping){
				mDirection = RIGHT;
				if(forward.dotProduct(Vector3::UNIT_X) < 0.95) {
					mIsTurning = true;
					mYaw_Target = Math::PI/2;
				}
			}*/

			mInputVel.x = 1;
		}
		else if((joyState.mPOV[0].direction & OIS::Pov::West) != 0){
			/*if(!mFlipping){
				mDirection = LEFT;
				if(forward.dotProduct(Vector3::NEGATIVE_UNIT_X) < 0.95){
					mIsTurning = true;
					mYaw_Target = -Math::PI/2;
				}
			}*/
			mInputVel.x = -1;
		}

		//
		//	4					5
		//		6		7	
		//	9				3
		//				8 2   1
		//					0

    }
	else if(m_pKeyboard) {
		if(m_pKeyboard->isKeyDown(OIS::KC_D) && !m_pKeyboard->isKeyDown(OIS::KC_A)){
			/*if(!mFlipping){
				mDirection = RIGHT;
				if(forward.dotProduct(Vector3::UNIT_X) < 0.95) {
					mIsTurning = true;
					mYaw_Target = Math::PI/2;
				}
			}*/

			mInputVel.x = 1;
		}


		if(m_pKeyboard->isKeyDown(OIS::KC_A) && !m_pKeyboard->isKeyDown(OIS::KC_D)){
			/*if(!mFlipping){
				mDirection = LEFT;
				if(forward.dotProduct(Vector3::NEGATIVE_UNIT_X) < 0.95){
					mIsTurning = true;
					mYaw_Target = -Math::PI/2;
				}
			}*/

			mInputVel.x = -1;
		}

		if(m_pKeyboard->isKeyDown(OIS::KC_LSHIFT)){
			mRunningPressed = true;
		}
		else {
			mRunningPressed = false;
		}

		if(m_pKeyboard->isKeyDown(OIS::KC_D) == m_pKeyboard->isKeyDown(OIS::KC_A)){
			mInputVel.x = 0;
		}

		if(m_pKeyboard->isKeyDown(OIS::KC_Q) && !m_pKeyboard->isKeyDown(OIS::KC_E)){
			mGunDirection = UPANGLED;
		}
		else if(!m_pKeyboard->isKeyDown(OIS::KC_Q) && m_pKeyboard->isKeyDown(OIS::KC_E)){
			mGunDirection = DOWNANGLED;
		}
		else if(m_pKeyboard->isKeyDown(OIS::KC_Q) == m_pKeyboard->isKeyDown(OIS::KC_E)){
			if(m_pKeyboard->isKeyDown(OIS::KC_W))
				mGunDirection = UP;
			else
				mGunDirection = FORWARD;
		}
	}


	mRunningPressed = mButtons[0];

	if(mButtons[5] && !mButtons[4]){
		mGunDirection = UPANGLED;
	}
	else if(!mButtons[5] && mButtons[4]){
		mGunDirection = DOWNANGLED;
	}
	else if(mButtons[5] == mButtons[4]){
		//if(m_pKeyboard->isKeyDown(OIS::KC_W))
		//	mGunDirection = UP;
		//else
			mGunDirection = FORWARD;
	}
}

void PlayerCharacter::setInputVel(PxVec3 vel){
	mInputVel = vel;
}


void PlayerCharacter::onShapeHit(const PxControllerShapeHit & hit){
	/*HandleScope handleScope(Isolate::GetCurrent());
	Handle<Value> args[1];
	args[0] = wrapByVal<PxControllerShapeHit, V8PxControllerShapeHit>(const_cast<PxControllerShapeHit&>(hit));
	dispatchEvent("onShapeHit", 1, args);*/

	PxRigidDynamic* actor = hit.shape->getActor().is<PxRigidDynamic>();
	if(actor)
	{
		if(actor->getRigidDynamicFlags() & PxRigidDynamicFlag::eKINEMATIC)
			return;

		// We only allow horizontal pushes. Vertical pushes when we stand on dynamic objects creates
		// useless stress on the solver. It would be possible to enable/disable vertical pushes on
		// particular objects, if the gameplay requires it.
		const PxVec3 upVector = hit.controller->getUpDirection();
		const PxF32 dp = hit.dir.dot(upVector);
//		printf("%f\n", fabsf(dp));
		if(fabsf(dp)<1e-3f)
//		if(hit.dir.y==0.0f)
		{
			const PxTransform globalPose = actor->getGlobalPose();
			const PxVec3 localPos = globalPose.transformInv(toVec3(hit.worldPos));
			addForceAtLocalPos(*actor, hit.dir*hit.length*1000.0f, localPos, PxForceMode::eACCELERATION);
		}
	}

	PxReal dot = hit.dir.dot(mCCT->getUpDirection());
	
	if(PxAbs(dot) > 0.95){
		if(dot < 0){
			mGrounded = true;
			mFlipping = false;
			mVelocity.x = 0;
			mVelocity.y = 0;
		}
		else if(mVelocity.y > 0){
			mVelocity.y = 0;
		}
		
	}
	
}

void PlayerCharacter::onControllerHit(const PxControllersHit& hit){
	/*HandleScope handleScope(Isolate::GetCurrent());
	Handle<Value> args[1];
	args[0] = wrapByVal<PxControllersHit, V8PxControllersHit>(const_cast<PxControllersHit&>(hit));
	dispatchEvent("onControllerHit", 1, args);*/

	if (hit.other->getActor()->userData != 0){
		GameObject* go = reinterpret_cast<GameObject*>(hit.other->getActor()->userData);
		if(go->getType() != GO_TYPE::PLAYER)
			owner->RegisterHit(this, hit);
	}	
}

void PlayerCharacter::onObstacleHit(const PxControllerObstacleHit& hit){
	/*HandleScope handleScope(Isolate::GetCurrent());
	Handle<Value> args[1];
	args[0] = wrapByVal<PxControllerObstacleHit, V8PxControllerObstacleHit>(const_cast<PxControllerObstacleHit&>(hit));
	dispatchEvent("onObstacleHit", 1, args);*/
}

void PlayerCharacter::addForceAtLocalPos(PxRigidBody& body, const PxVec3& force, const PxVec3& pos, PxForceMode::Enum mode, bool wakeup){
	//transform pos to world space
	const PxVec3 globalForcePos = body.getGlobalPose().transform(pos);

	addForceAtPosInternal(body, force, globalForcePos, mode, wakeup);
}

inline void PlayerCharacter::addForceAtPosInternal(PxRigidBody& body, const PxVec3& force, const PxVec3& pos, PxForceMode::Enum mode, bool wakeup){
/*	if(mode == PxForceMode::eACCELERATION || mode == PxForceMode::eVELOCITY_CHANGE)
	{
		Ps::getFoundation().error(PxErrorCode::eINVALID_PARAMETER, __FILE__, __LINE__, 
			"PxRigidBodyExt::addForce methods do not support eACCELERATION or eVELOCITY_CHANGE modes");
		return;
	}*/

	const PxTransform globalPose = body.getGlobalPose();
	const PxVec3 centerOfMass = globalPose.transform(body.getCMassLocalPose().p);

	const PxVec3 torque = (pos - centerOfMass).cross(force);
	body.addForce(force, mode, wakeup);
	body.addTorque(torque, mode, wakeup);
}
