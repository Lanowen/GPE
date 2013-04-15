#include <Projectile.hpp>

#include <Util.hpp>

#define PROJECTILESPEED 20


Projectile::Projectile(GameState* owner, GameObject* spawner, Vector3 pos, Quaternion dir) : GameObject(owner), spawner(spawner) {
	Initialize(Util::vec_from_to<Vector3, PxVec3>(pos), Util::quat_from_to<Quaternion, PxQuat>(dir));
}

Projectile::Projectile(GameState* owner, GameObject* spawner, PxVec3 pos, PxQuat dir) : GameObject(owner), spawner(spawner) {
	Initialize(pos, dir);
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

	loadScript("BasicProjectile.js");
}

Projectile::~Projectile(){
	//node->removeAndDestroyAllChildren();
	//Root::getSingletonPtr()->getSceneManager("GameSceneMgr")->destroySceneNode(node);
	actor->release();
}