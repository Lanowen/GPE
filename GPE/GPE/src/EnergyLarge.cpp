#include <EnergyLarge.hpp>

EnergyLarge::EnergyLarge(GameState* owner, Vector3 pos) : PowerUp(owner, pos), timer(0) {
	SceneManager* gameSceneMgr = Root::getSingletonPtr()->getSceneManager("GameSceneMgr");
	//ent = gameSceneMgr->createEntity("Samus", "Samus.mesh" );
	ent = gameSceneMgr->createEntity("sphere.mesh" );

	ent->setMaterialName("Energy/Pink");
	
	node->attachObject(ent);
	node->setPosition(pos);

	scale = 0.003;


	node->setScale(scale,scale,scale);
}

EnergyLarge::~EnergyLarge(){
	
}

void EnergyLarge::Update(Ogre::Real deltaTime){
	timer += deltaTime;
	if( timer >= Math::TWO_PI)
		timer -= Math::TWO_PI;

	Real amt = Math::Sin(timer*6)*0.2 + 0.8;

	node->setScale(scale*amt,scale*amt,scale*amt);
}