#include <Enemy.hpp>

#include <Util.hpp>

#include <Scripting_Helpers.hpp>
#include <Scripting_ExposePx.hpp>
#include <Scripting_ExposeGPE.hpp>

#define MOVESPEED 2
#define HALFEXTENT 0.4

#include <PlayerCharacter.hpp>


Enemy::Enemy(GameState* owner, std::string mesh/*, std::string script*/, bool netOwned) : GameObject(owner){

	netOwned = netOwned;

	float scale = 0.5;

	PxBoxControllerDesc cDesc;
	
	cDesc.material		= owner->getPhysics()->createMaterial(0.9f, 0.5f, 0.0f);
	cDesc.position		= PxExtendedVec3(3.f,0.8,0.f);
	cDesc.contactOffset	= 0.005f;
	
	cDesc.stepOffset = 0.05f;
	cDesc.slopeLimit = 0.707f;
	cDesc.upDirection = PxVec3(0.0f, 1.0f, 0.0f);
	cDesc.interactionMode = PxCCTInteractionMode::eINCLUDE;
	//cDesc.maxJumpHeight
	//cDesc.groupsBitmask
	cDesc.density = 10.0;
	cDesc.halfHeight = HALFEXTENT;
	cDesc.halfSideExtent = HALFEXTENT;
	cDesc.halfForwardExtent = HALFEXTENT;
	cDesc.callback		= this;
	//cDesc.behaviorCallback
	cDesc.userData = (GameObject*)this;

	mCCT = owner->getControllerManager()->createController(*owner->getPhysics(), owner->getMainPhysicsScene(),cDesc);
	PX_ASSERT(mCCT);

	mCCT->getActor()->userData = (GameObject*)this ;

	PxFilterData filterData;
	filterData.word0 = 8; // word0 = own ID
	filterData.word1 = 2;	// word1 = ID mask to filter pairs that trigger a contact callback;

	//Util::dout << "enemy: " << (int)this << " derp " << (int)(GameObject*)this << std::endl;

	const PxU32 numShapes = mCCT->getActor()->getNbShapes();
	PxShape** shapes = new PxShape*[numShapes];
	mCCT->getActor()->getShapes(shapes, numShapes);
	for(PxU32 i = 0; i < numShapes; i++)
	{
		PxShape* shape = shapes[i];
		shape->setSimulationFilterData(filterData);
	}
	delete[] shapes;

    SceneManager* gameSceneMgr = Root::getSingletonPtr()->getSceneManager("GameSceneMgr");
	ent = gameSceneMgr->createEntity( mesh );

	node = gameSceneMgr->getRootSceneNode()->createChildSceneNode();
	node->setPosition(Vector3(mCCT->getPosition().x, mCCT->getPosition().y, mCCT->getPosition().z));
	node->setScale(0.8, 0.8, 0.8);

	childNode = node->createChildSceneNode();
	childNode->setPosition(Vector3::ZERO);
	childNode->attachObject(ent);

	mPhysScene = owner->getMainPhysicsScene();
    m_aniStates = ent->getAllAnimationStates();


	moveDir = PxVec3(1,0,0);
	castDir = PxVec3(0,-1,0);

	rotLeft = PxQuat(Math::HALF_PI, PxVec3(0,0,1));
	rotRight = PxQuat(-Math::HALF_PI, PxVec3(0, 0, 1));

	rotCount = 0;
	falling = false;
	life = 3;

	registerEventCallback("OnDamage", boost::bind(&Enemy::OnDamage, this, _1));

	//HandleScope scope(Isolate::GetCurrent());
	//exposeObject("Enemy", wrapPtr<Enemy, V8Enemy>(this));
	//loadScript(script);
}

Enemy::~Enemy()
{
	mCCT->release();
	node->removeAndDestroyAllChildren();
	Root::getSingletonPtr()->getSceneManager("GameSceneMgr")->destroySceneNode(node);
}

void Enemy::release(){
	GameObject::release();
}

void Enemy::Update(Real deltaTime){
	//runScripts();
	AdvancePhysics(deltaTime);
	UpdateAnimation(deltaTime);
}

Vector3 Enemy::getPosition(){
	return Util::vec_from_to<PxExtendedVec3, Vector3>(mCCT->getPosition());
}

void Enemy::setPosition(PxVec3 pos){
	mCCT->setPosition(Util::vec_from_to<PxVec3, PxExtendedVec3>(pos));
}

void Enemy::UpdateAnimation(Real deltaTime){
    if(m_aniStates && m_aniStates->hasEnabledAnimationState()){
        ConstEnabledAnimationStateIterator itrAnim = m_aniStates->getEnabledAnimationStateIterator();

        while(itrAnim.hasMoreElements()){
        	itrAnim.getNext()->addTime(deltaTime);
        }
    }
}
void Enemy::AdvancePhysics(Real deltaTime){ 
	/*HandleScope handleScope(Isolate::GetCurrent());
	Handle<Value> args[1];
	args[0] = Number::New(deltaTime);
	dispatchEvent("AdvancePhysics", 1, args);*/

	PxVec3 disp(0);

    if (falling) {

        disp.y = -9.81* deltaTime;

        mCCT->move(disp, 0, deltaTime, PxSceneQueryHitType::eBLOCK);

        node->setPosition(Util::vec_from_to<PxExtendedVec3, Vector3>(mCCT->getPosition()));
        return;
    }

	bool hitRes1=false, hitRes2 = false;
	PxRaycastHit hit1, hit2;
    if (!(hitRes1 = mPhysScene->raycastSingle(toVec3(mCCT->getPosition()) - (moveDir*HALFEXTENT), castDir, 1 + HALFEXTENT, PxSceneQueryFlag::eBLOCKING_HIT, hit1, PxSceneQueryFilterData(PxSceneQueryFilterFlag::eSTATIC))) &&
        !(hitRes2 = mPhysScene->raycastSingle(toVec3(mCCT->getPosition()) + (moveDir*HALFEXTENT), castDir, 1 + HALFEXTENT, PxSceneQueryFlag::eBLOCKING_HIT, hit1, PxSceneQueryFilterData(PxSceneQueryFilterFlag::eSTATIC))))
    {
        moveDir = rotRight.rotate(moveDir);
        castDir = rotRight.rotate(castDir);

        //mCCT->move(moveDir*0.05, 0, deltaTime, PxSceneQueryHitType::eBLOCK);
        //print("lol off edge,", time);
        rotCount++;
        if (rotCount > 4) {
			falling = true;
            moveDir.x = 1;
            moveDir.y = 0;
            castDir.x = 0;
            castDir.y = -1;
        }

    }
    else {
		if(hitRes1 && hit1.distance > HALFEXTENT){
			mCCT->move(castDir*(hit1.distance-HALFEXTENT), 0, deltaTime, PxSceneQueryHitType::eTOUCH);
		}
		else if(!hitRes1 && hitRes2 && hit2.distance > HALFEXTENT){
			mCCT->move(castDir*(hit2.distance-HALFEXTENT), 0, deltaTime, PxSceneQueryHitType::eTOUCH);
		}
        rotCount = 0;
    }

    disp += moveDir *MOVESPEED;

    disp *= deltaTime;

    mCCT->move(disp, 0, deltaTime, PxSceneQueryHitType::eBLOCK);

	node->setPosition(Util::vec_from_to<PxExtendedVec3, Vector3>(mCCT->getPosition()));
}

void Enemy::OnDamage(const EventData* data){
	if(netOwned){
		const ProjectileEvent* pe = static_cast<const ProjectileEvent*>(data);
		life -= pe->power;

		if (life <= 0){
			SerializableUINT32 idp;
			idp.val = netId;

			socket->Send(idp, NEW_NETUPDATES::ENEMY_DEATH, GPENet::DatagramImportance::RELIABLE_ORDERED);
			owner->handleEnemyDeathPowerup(node->getPosition());
			release();
		}
	}
}


void Enemy::onShapeHit(const PxControllerShapeHit & hit){
	/*HandleScope handleScope(Isolate::GetCurrent());
	Handle<Value> args[1];
	args[0] = wrapByVal<PxControllerShapeHit, V8PxControllerShapeHit>(const_cast<PxControllerShapeHit&>(hit));
	dispatchEvent("onShapeHit", 1, args);*/

	if(hit.dir.dot(moveDir) > .95){
        moveDir = rotLeft.rotate(moveDir);
        castDir = rotLeft.rotate(castDir);
    }

    if (falling) {
        falling = false;
        rotCount = 0;
    }
}

void Enemy::onControllerHit(const PxControllersHit& hit){
	/*HandleScope handleScope(Isolate::GetCurrent());
	Handle<Value> args[1];
	args[0] = wrapByVal<PxControllersHit, V8PxControllersHit>(const_cast<PxControllersHit&>(hit));
	dispatchEvent("onControllerHit", 1, args);*/
	if (hit.other->getActor()->userData != 0){
		GameObject* go = reinterpret_cast<GameObject*>(hit.other->getActor()->userData);
		if(go->getType() == GO_TYPE::PLAYER)
			owner->RegisterHit((PlayerCharacter*)go, hit);
	}	
}

void Enemy::onObstacleHit(const PxControllerObstacleHit& hit){
	/*HandleScope handleScope(Isolate::GetCurrent());
	Handle<Value> args[1];
	args[0] = wrapByVal<PxControllerObstacleHit, V8PxControllerObstacleHit>(const_cast<PxControllerObstacleHit&>(hit));
	dispatchEvent("onObstacleHit", 1, args);*/
}

void Enemy::addForceAtLocalPos(PxRigidBody& body, const PxVec3& force, const PxVec3& pos, PxForceMode::Enum mode, bool wakeup){
	//transform pos to world space
	const PxVec3 globalForcePos = body.getGlobalPose().transform(pos);

	addForceAtPosInternal(body, force, globalForcePos, mode, wakeup);
}

inline void Enemy::addForceAtPosInternal(PxRigidBody& body, const PxVec3& force, const PxVec3& pos, PxForceMode::Enum mode, bool wakeup){
	/*if(mode == PxForceMode::eACCELERATION || mode == PxForceMode::eVELOCITY_CHANGE)
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