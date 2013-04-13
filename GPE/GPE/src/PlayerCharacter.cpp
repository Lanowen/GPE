#include "PlayerCharacter.hpp"
#include <Util.hpp>

#include <Scripting_Helpers.hpp>
#include <Scripting_ExposePx.hpp>
#include <Scripting_ExposeGPE.hpp>

#include <Projectile.hpp>

#define TURN_SPEED 15
#define WALK_SPEED 2
#define RUN_SPEED 7
#define AIR_POWER 13
#define MAX_AIR_STANDING_SPEED 3
#define FLIP_SPEED 10
#define GRAVITY -20
#define JUMP_VEL 20
#define SHOOT_ANIMATION_LENGTH 3

PlayerCharacter::PlayerCharacter(OIS::Keyboard* im_pKeyboard, OIS::JoyStick* im_pJoyStick, int im_pJoyDeadZone, GameState* owner) : GameObject(owner), IInputListener(owner)
{
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
	cDesc.userData = this;

	mCCT = owner->getControllerManager()->createController(*mPhys, mPhysScene, cDesc);
	PX_ASSERT(mCCT);

	PxFilterData filterData;
	filterData.word0 = 1; // word0 = own ID
	filterData.word1 = 2;	// word1 = ID mask to filter pairs that trigger a contact callback;

	const PxU32 numShapes = mCCT->getActor()->getNbShapes();
	PxShape** shapes = new PxShape*[numShapes];
	mCCT->getActor()->getShapes(shapes, numShapes);
	for(PxU32 i = 0; i < numShapes; i++)
	{
		PxShape* shape = shapes[i];
		shape->setSimulationFilterData(filterData);
	}
	delete[] shapes;

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
	ent = gameSceneMgr->createEntity("Samus", "samustestSamus.mesh" );
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

	HandleScope scope(Isolate::GetCurrent());

	//Persistent<Object> bo = Persistent<Object>::New(Isolate::GetCurrent(),BooleanObject::New(mGrounded )->ToObject());
	//bo->SetInternalField(0, External::New( &mGrounded ));
	//bo.MakeWeak(Isolate::GetCurrent(),NULL, &CleanupHandleOnly);
	//exposeObject("mGrounded", Number::New(23987234.234));

	EXPOSE_TO_SCRIPTS(PlayerCharacter, V8PlayerCharacter, "PlayerCharacter");
	//exposeObject("testVect", wrap<PxVec3, V8PxVec3>(PxVec3(1,2,3)));
	//exposeObject("testFunc", FunctionTemplate::New( InvocationCallback( PlayerCharacter::get ) ));
	loadScript("playerController.js");

}

PlayerCharacter::~PlayerCharacter()
{

}

void PlayerCharacter::release(){
	owner->DeleteGameObject(this);
}

void PlayerCharacter::Update(Real deltaTime){
	//runScripts();
	timeSinceLastShot += deltaTime;
	getInput(deltaTime);
	advancePhysics(deltaTime);
	updateAnimation(deltaTime);
}

void PlayerCharacter::advancePhysics(Real deltaTime){ 
	PxVec3 disp = PxVec3(0);

	mVelocity.y += GRAVITY*deltaTime;

	Vector3 pos = Util::vec_from_to<PxExtendedVec3, Vector3>(mCCT->getPosition());

	if(!mIsTurning && mGrounded){
		if(mShiftPressed)
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

	mCCT->move(disp*deltaTime,0,deltaTime,PxSceneQueryHitType::eBLOCK,0);

	pos = Util::vec_from_to<PxExtendedVec3, Vector3>(mCCT->getPosition());

	node->setPosition(pos);	
}


void PlayerCharacter::updateAnimation(Real deltaTime){

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
			m_aniStates->getAnimationState("Jump_up")->setEnabled(false);
			m_aniStates->getAnimationState("Jump_peaking")->setEnabled(false);

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
			m_aniStates->getAnimationState("Jump_up")->setEnabled(false);
			m_aniStates->getAnimationState("Jump_peaking")->setEnabled(false);

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
			else if(mShiftPressed){
				if(!m_aniStates->getAnimationState("Run_full")->getEnabled() && !m_aniStates->getAnimationState("Run_step")->getEnabled() ){
					m_aniStates->getAnimationState("Run_step")->setEnabled(true);
					m_aniStates->getAnimationState("Run_step")->setTimePosition(0);

					if(timeSinceLastShot > SHOOT_ANIMATION_LENGTH && mGunDirection == FORWARD){
						m_aniStates->getAnimationState("Run_step_upper")->setEnabled(true);
						m_aniStates->getAnimationState("Run_step_upper")->setTimePosition(m_aniStates->getAnimationState("Run_step")->getTimePosition());
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
				}
				m_aniStates->getAnimationState("Walk_full")->setEnabled(false);
				m_aniStates->getAnimationState("Walk_step")->setEnabled(false);

				m_aniStates->getAnimationState("Walk_step_upper")->setEnabled(false);
				m_aniStates->getAnimationState("Walk_full_upper")->setEnabled(false);
			}
			else{
				if(!m_aniStates->getAnimationState("Walk_full")->getEnabled() && !m_aniStates->getAnimationState("Walk_step")->getEnabled() ){
					m_aniStates->getAnimationState("Walk_step")->setEnabled(true);
					m_aniStates->getAnimationState("Walk_step")->setTimePosition(0);

					if(timeSinceLastShot > SHOOT_ANIMATION_LENGTH && mGunDirection == FORWARD){
						m_aniStates->getAnimationState("Walk_step_upper")->setEnabled(true);
						m_aniStates->getAnimationState("Walk_step_upper")->setTimePosition(m_aniStates->getAnimationState("Walk_step")->getTimePosition());
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
					}
				}
				m_aniStates->getAnimationState("Run_full")->setEnabled(false);
				m_aniStates->getAnimationState("Run_step")->setEnabled(false);

				m_aniStates->getAnimationState("Run_full_upper")->setEnabled(false);
				m_aniStates->getAnimationState("Run_step_upper")->setEnabled(false);				
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

	if(mFlipping){
		childNode->pitch(Radian(FLIP_SPEED * deltaTime));
	}
	else {
		Radian deltaAngle = childNode->getOrientation().getPitch();
		childNode->pitch(-deltaAngle);
		
	}

    if(m_aniStates->hasEnabledAnimationState()){
        ConstEnabledAnimationStateIterator itrAnim = m_aniStates->getEnabledAnimationStateIterator();

        while(itrAnim.hasMoreElements()){
			AnimationState *anim = itrAnim.getNext();
        	anim->addTime(deltaTime);
			//if(!anim->getLoop() && anim->getLength() == anim->getTimePosition()){
				//anim->setEnabled(false);
				//anim->setTimePosition(0);
			//}
        }
    }

	
	//else {
	//}
}

bool PlayerCharacter::keyPressed(const OIS::KeyEvent &keyEventRef){

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

		new Projectile(owner, this, node->_getFullTransform()*m_GunTip->_getDerivedPosition(), dir);

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

	//if(keyEventRef.key == OIS::KC_ADD){
	//	if(mController->getType() == 0) {
	//		NxBoxController* cerp = (NxBoxController*)this->mController;
	//		NxVec3 derp = cerp->getExtents();
	//		derp.y += 0.1f;
	//		cerp->setExtents(derp);
	//		//std::cout << derp.x << " " << derp.y << " " << derp.x << std::endl;
	//	}
	//	else if(mController->getType() == 1){ //capsule
	//		//NxCapsule* derp = (NxCapsule*)getShape(0);
	//		//derp->setDimensions(derp->getRadius(), derp->getHeight()+0.1f);
	//		NxCapsuleController* cerp = (NxCapsuleController*)this->mController;
	//		cerp->setHeight(cerp->getHeight()+0.1f);
	//	}
	//}

	//if(keyEventRef.key == OIS::KC_SUBTRACT){
	//	if(mController->getType() == 0) {
	//		NxBoxController* cerp = (NxBoxController*)this->mController;
	//		NxVec3 derp = cerp->getExtents();
	//		derp.y -= 0.1f;
	//		cerp->setExtents(derp);
	//		//std::cout << derp.x << " " << derp.y << " " << derp.x << std::endl;
	//	}
	//	else if(mController->getType() == 1){ //capsule
	//		//NxCapsule* derp = (NxCapsule*)getShape(0);
	//		//derp->setDimensions(derp->getRadius(), derp->getHeight()-0.1f);
	//		NxCapsuleController* cerp = (NxCapsuleController*)this->mController;
	//		cerp->setHeight(cerp->getHeight()-0.1f);
	//	}
	//}

	return(true);
}

bool PlayerCharacter::keyReleased(const OIS::KeyEvent &keyEventRef){

    if(keyEventRef.key == OIS::KC_SPACE && !mGrounded && mVelocity.y > 0)
    {
		mVelocity.y = 0;
    }
	return(true);
}

void PlayerCharacter::getInput(Real deltaTime){
    if(m_pJoyStick){
        int joyx = m_pJoyStick->getJoyStickState().mAxes[1].abs;
        if (Math::Abs(joyx) > m_pJoyDeadZone && Math::Abs(joyx) < m_pJoyStick->MAX_AXIS*0.5){
            //m_aniStates->getAnimationState("Run_full")->setEnabled(false);
            //m_aniStates->getAnimationState("Walk_full")->setEnabled(true);
            //m_aniStates->getAnimationState("Walk_full")->setLoop(true);
            //node->showBoundingBox(true);
            if(joyx/Math::Abs(joyx) > 0){
                //node->setDirection(Vector3::NEGATIVE_UNIT_X, SceneNode::TS_WORLD);
                //node->translate(2.f*timeSinceLastFrame,0,0,SceneNode::TS_WORLD);
            }
            else {
                //node->setDirection(Vector3::UNIT_X, SceneNode::TS_WORLD);
                //node->translate(-2.f*timeSinceLastFrame,0,0,SceneNode::TS_WORLD);
            }
        }
        else if (Math::Abs(joyx) >= m_pJoyStick->MAX_AXIS*0.5){
            //m_aniStates->getAnimationState("Walk_full")->setEnabled(false);
            //m_aniStates->getAnimationState("Run_full")->setEnabled(true);
            //m_aniStates->getAnimationState("Run_full")->setLoop(true);
            //node->showBoundingBox(true);
            if(joyx/Math::Abs(joyx) > 0){
                //node->setDirection(Vector3::NEGATIVE_UNIT_X, SceneNode::TS_WORLD);
                //node->translate(8.f*timeSinceLastFrame,0,0,SceneNode::TS_WORLD);
            }
            else {
                //node->setDirection(Vector3::UNIT_X, SceneNode::TS_WORLD);
                //node->translate(-8.f*timeSinceLastFrame,0,0,SceneNode::TS_WORLD);
            }
        }
        else {
            //m_aniStates->getAnimationState("Walk_full")->setEnabled(false);
            //m_aniStates->getAnimationState("Run_full")->setEnabled(false);
        }
    }

	Vector3 forward = node->getOrientation()*Vector3::UNIT_Z;

    if(m_pKeyboard->isKeyDown(OIS::KC_D) && !m_pKeyboard->isKeyDown(OIS::KC_A)){
		if(!mFlipping){
			mDirection = RIGHT;
			if(forward.dotProduct(Vector3::UNIT_X) < 0.95) {
				mIsTurning = true;
				mYaw_Target = Math::PI/2;
			}
		}

		mInputVel.x = 1;
    }


    if(m_pKeyboard->isKeyDown(OIS::KC_A) && !m_pKeyboard->isKeyDown(OIS::KC_D)){
		if(!mFlipping){
			mDirection = LEFT;
			if(forward.dotProduct(Vector3::NEGATIVE_UNIT_X) < 0.95){
				mIsTurning = true;
				mYaw_Target = -Math::PI/2;
			}
		}

		mInputVel.x = -1;
    }

	if(m_pKeyboard->isKeyDown(OIS::KC_LSHIFT)){
		mShiftPressed = true;
    }
    else {
		mShiftPressed = false;
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

void PlayerCharacter::onShapeHit(const PxControllerShapeHit & hit){
	HandleScope handleScope(Isolate::GetCurrent());
	Handle<Value> args[1];
	//args[0] = v8::String::New("Testing lol");
	args[0] = wrap<PxControllerShapeHit, V8PxControllerShapeHit>(const_cast<PxControllerShapeHit&>(hit));
	//args[0] = wrap<PxVec3, V8PxVec3>(PxVec3(1,2,3));
	dispatchEvent("onShapeHit", 1, args);
//	PxRigidDynamic* actor = hit.shape->getActor().is<PxRigidDynamic>();
//	if(actor)
//	{
//		if(actor->getRigidDynamicFlags() & PxRigidDynamicFlag::eKINEMATIC)
//			return;
//
//		// We only allow horizontal pushes. Vertical pushes when we stand on dynamic objects creates
//		// useless stress on the solver. It would be possible to enable/disable vertical pushes on
//		// particular objects, if the gameplay requires it.
//		const PxVec3 upVector = hit.controller->getUpDirection();
//		const PxF32 dp = hit.dir.dot(upVector);
////		printf("%f\n", fabsf(dp));
//		if(fabsf(dp)<1e-3f)
////		if(hit.dir.y==0.0f)
//		{
//			const PxTransform globalPose = actor->getGlobalPose();
//			const PxVec3 localPos = globalPose.transformInv(toVec3(hit.worldPos));
//			addForceAtLocalPos(*actor, hit.dir*hit.length*1000.0f, localPos, PxForceMode::eACCELERATION);
//		}
//	}
//	
//	if(hit.dir.dot(mCCT->getUpDirection()) < -0.95){
//		mGrounded = true;
//		mFlipping = false;
//		mVelocity.x = mVelocity.y = 0;
//	}
}



void PlayerCharacter::onControllerHit(const PxControllersHit& hit){
	Util::dout << "OUCH, HIT CONTROLLER OWWWW" << std::endl;
}

void PlayerCharacter::onObstacleHit(const PxControllerObstacleHit& hit){

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
