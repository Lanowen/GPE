#include <Enemy.hpp>

#include <Util.hpp>

#define MOVESPEED 2
#define HALFEXTENT 0.4


Enemy::Enemy(GameState* owner) : GameObject(owner)
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
	cDesc.userData = this;

	mCCT = owner->getControllerManager()->createController(*owner->getPhysics(), owner->getMainPhysicsScene(),cDesc);
	PX_ASSERT(mCCT);

	PxFilterData filterData;
	filterData.word0 = 8; // word0 = own ID
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

    SceneManager* gameSceneMgr = Root::getSingletonPtr()->getSceneManager("GameSceneMgr");
	ent = gameSceneMgr->createEntity("EnemyBro", "SimpleBox.mesh" );

	node = gameSceneMgr->getRootSceneNode()->createChildSceneNode();
	node->setPosition(Vector3(mCCT->getPosition().x, mCCT->getPosition().y, mCCT->getPosition().z));
	node->attachObject(ent);
	node->setScale(0.8, 0.8, 0.8);

	moveDir = PxVec3(1,0,0);
	castDir = PxVec3(0,-1,0);

	mPhysScene = owner->getMainPhysicsScene();

	//nodeOffset = node->createChildSceneNode();

	//nodeOffset->attachObject(ent);
	//nodeOffset->setScale(scale, scale, scale);
	//nodeOffset->setPosition(0, -cDesc.halfHeight, 0);

    m_aniStates = ent->getAllAnimationStates();

	rotLeft = PxQuat((PxReal)Math::HALF_PI, PxVec3(0,0,1));
	rotRight = PxQuat((PxReal)-Math::HALF_PI, PxVec3(0,0,1));

	//loadScript("Enemy.js");
}

Enemy::~Enemy()
{

}

void Enemy::release(){
	owner->DeleteGameObject(this);
}

void Enemy::Update(Real deltaTime){
	//runScripts();
	advancePhysics(deltaTime);
	updateAnimation(deltaTime);
}

void Enemy::updateAnimation(Real deltaTime){
    if(m_aniStates && m_aniStates->hasEnabledAnimationState()){
        ConstEnabledAnimationStateIterator itrAnim = m_aniStates->getEnabledAnimationStateIterator();

        while(itrAnim.hasMoreElements()){
        	itrAnim.getNext()->addTime(deltaTime);
        }
    }
}
void Enemy::advancePhysics(Real deltaTime){ 
	PxVec3 disp = PxVec3(0);
	//disp += castDir * 9.81;

	Vector3 pos = Util::vec_from_to<PxExtendedVec3, Vector3>(mCCT->getPosition());

	PxSceneQueryHit hit1, hit2;
	if(!mPhysScene->raycastAny(toVec3(mCCT->getPosition()) - moveDir*HALFEXTENT, castDir, 1+HALFEXTENT, hit1, PxSceneQueryFilterData(PxSceneQueryFilterFlag::eSTATIC)) && !mPhysScene->raycastAny(toVec3(mCCT->getPosition()) + moveDir*HALFEXTENT, castDir, 1+HALFEXTENT, hit2, PxSceneQueryFilterData(PxSceneQueryFilterFlag::eSTATIC))){
		//Util::dout << "Lol, off edge" << std::endl;
		mCCT->move(moveDir*0.1f,0,deltaTime,PxSceneQueryHitType::eBLOCK,0);
		disp += castDir * 9.81;
		moveDir = rotRight.rotate(moveDir);
		castDir = rotRight.rotate(castDir);
		//Util::dout << castDir.x << " " << castDir.y << " " << castDir.z << std::endl;
	}

	disp += moveDir*MOVESPEED;

	mCCT->move(disp*deltaTime,0,deltaTime,PxSceneQueryHitType::eBLOCK,0);

	pos = Util::vec_from_to<PxExtendedVec3, Vector3>(mCCT->getPosition());
	node->setPosition(pos);	
}

void Enemy::onShapeHit(const physx::PxControllerShapeHit & hit){
	
	if(hit.dir.dot(moveDir) > .95){
		//Util::dout << "Hitdir: " << hit.dir.x << " " << hit.dir.y << " " << hit.dir.z << std::endl;
		moveDir = rotLeft.rotate(moveDir);
		castDir = rotLeft.rotate(castDir);
	}
}

void Enemy::onControllerHit(const physx::PxControllersHit& hit){
	Util::dout << "Enemy controller hit something" << std::endl;
}

void Enemy::onObstacleHit(const physx::PxControllerObstacleHit& hit){

}