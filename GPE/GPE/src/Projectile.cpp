#include <Projectile.hpp>

#include <Util.hpp>

#define PROJECTILESPEED 20

BillboardSet* Projectile::bbs;


Projectile::Projectile(GameState* owner, GameObject* spawner, Vector3 pos, Quaternion dir, bool netOwned) : GameObject(owner), spawner(spawner) {
	Initialize(Util::vec_from_to<Vector3, PxVec3>(pos), Util::quat_from_to<Quaternion, PxQuat>(dir));
	netOwned = netOwned;
}

Projectile::Projectile(GameState* owner, GameObject* spawner, PxVec3 pos, PxQuat dir, bool netOwned) : GameObject(owner), spawner(spawner) {
	Initialize(pos, dir);
	netOwned = netOwned;
}

void Projectile::Initialize(SceneManager* sceneMgr){
	bbs = sceneMgr->createBillboardSet(1);
	bbs->setDefaultDimensions(1,1);
	bbs->setMaterialName("Examples/Flare");
	sceneMgr->getRootSceneNode()->attachObject(bbs);
}


void Projectile::Initialize(PxVec3 pos, PxQuat dir){
	actor = owner->getPhysics()->createRigidDynamic(PxTransform(pos, dir));
	actor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	actor->setLinearVelocity(dir.rotate(PxVec3(0,0,1)*PROJECTILESPEED));

	actor->userData = (GameObject*)this;

	actor->setName("Projectile");

	PxMaterial* mat = owner->getPhysics()->createMaterial(0,0,0);
	mat->setFrictionCombineMode(PxCombineMode::eMULTIPLY);
	mat->setRestitutionCombineMode(PxCombineMode::eMULTIPLY);
	PxShape* shape = actor->createShape(PxSphereGeometry(0.25), *mat);
	PxRigidBodyExt::setMassAndUpdateInertia(*actor,1.0);

	PxFilterData filterData;
	filterData.word0 = 2; // word0 = own ID
	filterData.word1 = 1|2|4|8;	// word1 = ID mask to filter pairs that trigger a contact callback;
	shape->setSimulationFilterData(filterData);

	owner->getMainPhysicsScene()->addActor(*actor);

	//loadScript("BasicProjectile.js");

	SceneManager* gameSceneMgr = Root::getSingletonPtr()->getSceneManager("GameSceneMgr");

	NameValuePairList params;
	params["numberOfChains"] = "2";
	params["maxElements"] = "10";

	mTrail = (RibbonTrail*)gameSceneMgr->createMovableObject("RibbonTrail", &params);
	node = gameSceneMgr->getRootSceneNode()->createChildSceneNode();
	gameSceneMgr->getRootSceneNode()->attachObject(mTrail);

	mTrail->setMaterialName("Examples/LightRibbonTrail");
	mTrail->setTrailLength(1);

	mTrail->setInitialColour(0, 1.0, 0.8, 0);
	mTrail->setColourChange(0, 0.5, 0.5, 0.5, 0.5);
	mTrail->setInitialWidth(0, 0.5);
	mTrail->setWidthChange(0, 10);

	//light = gameSceneMgr->createLight();
	//light->setDiffuseColour(mTrail->getInitialColour(0));
	//node->attachObject(light);
	mFlare = bbs->createBillboard(Vector3::ZERO, mTrail->getInitialColour(0));
	

	node->setPosition(Util::vec_from_to<PxVec3, Vector3>(actor->getGlobalPose().p));
	mTrail->addNode(node);

	registerEventCallback("Projectile_Hit", boost::bind(&Projectile::OnProjectileHit, this, _1));
}

Projectile::~Projectile(){
	bbs->removeBillboard(mFlare);
	Root::getSingletonPtr()->getSceneManager("GameSceneMgr")->destroyRibbonTrail(mTrail);
	node->removeAndDestroyAllChildren();
	Root::getSingletonPtr()->getSceneManager("GameSceneMgr")->destroySceneNode(node);
	actor->release();
}

void Projectile::OnProjectileHit(const EventData* other){
	GameObject*  otherGO = reinterpret_cast<GameObject*>(other->data);
	ProjectileEvent pe;
	pe.power = 1;
	pe.data = this;
	otherGO->dispatchEvent("OnDamage", &pe);
}

void Projectile::Update(Real deltaTime){
	node->translate(Util::vec_from_to<PxVec3, Vector3>(actor->getGlobalPose().p) - node->getPosition());
	mFlare->setPosition(node->getPosition());
	//node->setPosition(Util::vec_from_to<PxVec3, Vector3>(actor->getGlobalPose().p));	
}

PxVec3 Projectile::getPosition(){
	return actor->getGlobalPose().p;
}

GameObject* Projectile::getSpawner(){
	return spawner;
}