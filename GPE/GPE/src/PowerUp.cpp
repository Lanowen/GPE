#include <PowerUp.hpp>

PowerUp::PowerUp(GameState* owner, Vector3 pos) : GameObject(owner) {
	PxPhysics* phys = owner->getPhysics();

	
	PxFilterData filterData;
	filterData.word0 = 16; // word0 = own ID
	filterData.word1 = 2;	// word1 = ID mask to filter pairs that trigger a contact callback;

	PxRigidStatic* box = phys->createRigidStatic(PxTransform(Util::vec_from_to<Vector3, PxVec3>(pos)));
	PxShape* shape = box->createShape(PxBoxGeometry(0.5f,0.5f,0.5f), *phys->createMaterial(0,0,0));
	shape->setSimulationFilterData(filterData);
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	owner->getMainPhysicsScene()->addActor(*box);

	box->userData = (GameObject*)this;

	actor = box;

	SceneManager* gameSceneMgr = Root::getSingletonPtr()->getSceneManager("GameSceneMgr");

	node = gameSceneMgr->getRootSceneNode()->createChildSceneNode();
}

PowerUp::~PowerUp(){
	node->removeAndDestroyAllChildren();
	Root::getSingletonPtr()->getSceneManager("GameSceneMgr")->destroySceneNode(node);
	actor->release();
}