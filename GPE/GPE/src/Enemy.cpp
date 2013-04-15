#include <Enemy.hpp>

#include <Util.hpp>

#include <Scripting_Helpers.hpp>
#include <Scripting_ExposePx.hpp>
#include <Scripting_ExposeGPE.hpp>

#define MOVESPEED 2
#define HALFEXTENT 0.4

#include <PlayerCharacter.hpp>


Enemy::Enemy(GameState* owner, std::string mesh, std::string script) : GameObject(owner)
{
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

	displacement = PxVec3(0,0,0);

	mPhysScene = owner->getMainPhysicsScene();

    m_aniStates = ent->getAllAnimationStates();


	HandleScope scope(Isolate::GetCurrent());

	exposeObject("Enemy", wrapPtr<Enemy, V8Enemy>(this));

	loadScript(script);
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
	HandleScope handleScope(Isolate::GetCurrent());
	Handle<Value> args[1];
	args[0] = Number::New(deltaTime);
	dispatchEvent("AdvancePhysics", 1, args);
}


void Enemy::onShapeHit(const PxControllerShapeHit & hit){
	HandleScope handleScope(Isolate::GetCurrent());
	Handle<Value> args[1];
	args[0] = wrapByVal<PxControllerShapeHit, V8PxControllerShapeHit>(const_cast<PxControllerShapeHit&>(hit));
	dispatchEvent("onShapeHit", 1, args);
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