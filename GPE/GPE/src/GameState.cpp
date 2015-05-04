
#include "GameState.hpp"
#include <OgreManualObject.h>
#include <PxConstraint.h>

#include <IKeyListener.hpp>
#include <IJoyStickListener.hpp>
#include <GameObject.hpp>
#include <PlayerCharacter.hpp>
#include <Enemy.hpp>

#include <PowerUp.hpp>
#include <EnergyLarge.hpp>

namespace gpe {

	std::string GameState::ip_ = "";
	bool GameState::isserver_ = false;

	GameState::GameState() {
		viewport_ = 0;
		b_shutdown_ = false;
		m_bLMouseDown = false;
		m_bRMouseDown = false;
		zoomState = 0;
		hackSendEnemyPosTime = 0;

		if (isserver_) {
			socket = GPENet::Server::Create();

			socket->AddQueuedCallback(GPENet::CONNECT, boost::bind(&GameState::onClientConnect, this, _1));
			socket->AddQueuedCallback(PLAYER_DEATH, boost::bind(&GameState::onPlayerDied, this, _1));
		}
		else {
			socket = GPENet::Client::Create(boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::any(), 0), boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::from_string(ip_), 1774));

			socket->AddQueuedCallback(CREATE_ENEMY, boost::bind(&GameState::createEnemy, this, _1));
			socket->AddQueuedCallback(CREATE_MAINPLAYER, boost::bind(&GameState::createMainPlayer, this, _1));
			socket->AddQueuedCallback(CREATE_PLAYER, boost::bind(&GameState::createPlayer, this, _1));
		}

		socket->AddQueuedCallback(NET_EVENT, boost::bind(&GameState::getNetEvent, this, _1));
		socket->AddQueuedCallback(CREATE_BULLET, boost::bind(&GameState::createBullet, this, _1));

		socket->AddQueuedCallback(PLAYER_INPUTVEL, boost::bind(&GameState::handleInputVel, this, _1));
		socket->AddQueuedCallback(PLAYER_INPUT_BUTTON_PRESS, boost::bind(&GameState::handleButtonPressed, this, _1));
		socket->AddQueuedCallback(PLAYER_INPUT_BUTTON_RELEASE, boost::bind(&GameState::handleButtonReleased, this, _1));
		socket->AddQueuedCallback(PLAYER_HURT, boost::bind(&GameState::handlePlayerHurt, this, _1));
		socket->AddQueuedCallback(SET_POS, boost::bind(&GameState::setIDPosition, this, _1));
		socket->AddQueuedCallback(ENEMY_DEATH, boost::bind(&GameState::handleEnemyDeath, this, _1));

		socket->AddQueuedCallback(GPENet::DISCONNECT, boost::bind(&GameState::handleDisconnect, this, _1));
		socket->AddQueuedCallback(COLLECT_POWERUP, boost::bind(&GameState::handlePowerup, this, _1));
		socket->AddQueuedCallback(CREATE_POWERUP, boost::bind(&GameState::handleCreatePowerup, this, _1));

		createScene();
	}

	GameState::~GameState() {
		for (int i = 0; i < gameobjects_.size(); i++) {
			delete gameobjects_[i];
		}
	}

	void GameState::handleCreatePowerup(GPENet::Datagram dg) {
		boost::shared_ptr<CreatePowerUp> cpu = dg.getData<CreatePowerUp>();

		Vector3 pos(cpu->px, cpu->py, cpu->pz);

		switch (cpu->powerupType) {
		case POWERUP_TYPE::ENERGY_LARGE:
		{
			EnergyLarge* en = new EnergyLarge(this, pos);

			netMan.addGameObject(cpu->id, en);
			AddGameObject(en);
		}
			break;
		case POWERUP_TYPE::ENERGY_SMALL:

			break;
		case POWERUP_TYPE::MISSILE:

			break;
		}
	}

	void GameState::handlePowerup(GPENet::Datagram dg) {
		boost::shared_ptr<GetPowerUp> gpu = dg.getData<GetPowerUp>();
		GameObject* go = netMan.getGameObject(gpu->targetid);
		GameObject* puGo = netMan.getGameObject(gpu->puID);

		if (go->getType() == GO_TYPE::PLAYER && go->netOwned) {
			PlayerCharacter* player = (PlayerCharacter*)go;

			player->getPowerUp((POWERUP_TYPE)gpu->powerupType);
		}

		if (puGo->getType() == GO_TYPE::POWERUP) {
			puGo->release();
		}
	}

	void GameState::onPlayerDied(GPENet::Datagram dg) {
		boost::shared_ptr<SerializableUINT32> id = dg.getData<SerializableUINT32>();
		GameObject* go = netMan.getGameObject(id->val);

		if (go->getType() == GO_TYPE::PLAYER) {
			PlayerCharacter* player = (PlayerCharacter*)go;

			Vector3 pos = GetBestSpawnpoint();

			RespawnPlayer(player, pos);

			IDandPos idp;
			idp.id = id->val;

			idp.px = pos.x;
			idp.py = pos.y;
			idp.pz = pos.z;

			socket->Send(idp, NEW_NETUPDATES::CREATE_PLAYER, GPENet::DatagramImportance::RELIABLE_ORDERED);
		}
	}

	void GameState::handleDisconnect(GPENet::Datagram dg) {
		boost::shared_ptr<SerializableUINT32> id = dg.getData<SerializableUINT32>();
		GameObject* go = netMan.getGameObject(id->val);

		go->release();

		netMan.removeGameObject(id->val);
	}

	void GameState::handleEnemyDeath(GPENet::Datagram dg) {
		boost::shared_ptr<SerializableUINT32> id = dg.getData<SerializableUINT32>();
		GameObject* go = netMan.getGameObject(id->val);

		if (go->getType() == GO_TYPE::ENEMY) {
			Enemy* nme = (Enemy*)go;

			nme->release();
		}
	}

	void GameState::handleEnemyDeathPowerup(Vector3 pos) {
		EnergyLarge* en = new EnergyLarge(this, pos);

		int id = netMan.addGameObject(en);
		AddGameObject(en);

		CreatePowerUp cpu; //oh no a cpu now!
		cpu.id = id;

		cpu.powerupType = en->getPowerUpType();

		cpu.px = pos.x;
		cpu.py = pos.y;
		cpu.pz = pos.z;

		socket->Send(cpu, NEW_NETUPDATES::CREATE_POWERUP, GPENet::DatagramImportance::RELIABLE_ORDERED);
	}

	void GameState::handlePlayerHurt(GPENet::Datagram dg) {
		boost::shared_ptr<IDandPos> idp = dg.getData<IDandPos>();
		GameObject* go = netMan.getGameObject(idp->id);

		if (go->getType() == GO_TYPE::PLAYER) {
			PlayerCharacter* player = (PlayerCharacter*)go;

			player->getHurt(PxVec3(idp->px, idp->py, idp->pz));
		}
	}

	void GameState::setIDPosition(GPENet::Datagram dg) {
		boost::shared_ptr<IDandPos> idp = dg.getData<IDandPos>();
		GameObject* go = netMan.getGameObject(idp->id);

		if (go->getType() == GO_TYPE::PLAYER) {
			PlayerCharacter* player = (PlayerCharacter*)go;

			player->setPosition(Vector3(idp->px, idp->py, idp->pz));
		}
		else if (go->getType() == GO_TYPE::ENEMY) {
			Enemy* nme = (Enemy*)go;

			nme->setPosition(PxVec3(idp->px, idp->py, idp->pz));
		}
	}

	void GameState::handleInputVel(GPENet::Datagram dg) {
		boost::shared_ptr<IDandPos> idp = dg.getData<IDandPos>();
		GameObject* go = netMan.getGameObject(idp->id);

		if (go->getType() == GO_TYPE::PLAYER) {
			PlayerCharacter* player = (PlayerCharacter*)go;

			player->setInputVel(PxVec3(idp->px, idp->py, idp->pz));
		}
	}

	void GameState::handleButtonPressed(GPENet::Datagram dg) {
		boost::shared_ptr<ButtonPress> bp = dg.getData<ButtonPress>();
		GameObject* go = netMan.getGameObject(bp->id);

		if (go->getType() == GO_TYPE::PLAYER) {
			PlayerCharacter* player = (PlayerCharacter*)go;

			player->doButtonPressed(bp->bid);
		}
	}

	void GameState::handleButtonReleased(GPENet::Datagram dg) {
		boost::shared_ptr<ButtonPress> bp = dg.getData<ButtonPress>();
		GameObject* go = netMan.getGameObject(bp->id);

		if (go->getType() == GO_TYPE::PLAYER) {
			PlayerCharacter* player = (PlayerCharacter*)go;

			player->doButtonReleased(bp->bid);
		}
	}

	void GameState::createEnemy(GPENet::Datagram dg) {
		boost::shared_ptr<IDandPos> ce = dg.getData<IDandPos>();
		Enemy *nme = new Enemy(this, "GeemerGeemer.mesh", false);
		nme->setPosition(PxVec3(ce->px, ce->py, ce->pz));
		nme->netOwned = false;
		AddGameObject(nme);
		netMan.addGameObject(ce->id, nme);
	}

	void GameState::onClientConnect(GPENet::Datagram dg) {
		std::map<int, GameObject*>::iterator itr = netMan.objects.begin();
		boost::shared_ptr<GPENet::Server> server = boost::static_pointer_cast<GPENet::Server>(socket);
		for (; itr != netMan.objects.end(); itr++) {
			int id = itr->first;
			GameObject* go = itr->second;

			switch (go->getType()) {
			case GO_TYPE::ENEMY:
			{
				Enemy* nme = (Enemy*)go;
				IDandPos idp;
				idp.id = id;
				Vector3 pos = nme->getPosition();
				idp.px = pos.x;
				idp.py = pos.y;
				idp.pz = pos.z;

				server->SendTo(dg.senderid, idp, CREATE_ENEMY, GPENet::RELIABLE_ORDERED);
			}
				break;
			case GO_TYPE::PLAYER:
			{
				PlayerCharacter* pl = (PlayerCharacter*)go;
				IDandPos idp;
				idp.id = id;
				Vector3 pos = pl->getPosition();
				idp.px = pos.x;
				idp.py = pos.y;
				idp.pz = pos.z;

				server->SendTo(dg.senderid, idp, CREATE_PLAYER, GPENet::RELIABLE_ORDERED);
			}
				break;
			}
		}

		PlayerCharacter* player = SpawnPlayer();

		int id = netMan.addGameObject(player);

		IDandPos idp;
		idp.id = id;
		Vector3 pos = player->getPosition();
		idp.px = pos.x;
		idp.py = pos.y;
		idp.pz = pos.z;
		player->netOwned = false;

		boost::shared_ptr<GPENet::Client> client = server->getClient(dg.senderid);
		client->hackedInt = id;

		server->SendTo(dg.senderid, idp, CREATE_MAINPLAYER, GPENet::RELIABLE_ORDERED);
		server->SendToExcluding(dg.senderid, idp, CREATE_PLAYER, GPENet::RELIABLE_ORDERED);
	}

	void GameState::createMainPlayer(GPENet::Datagram dg) {
		boost::shared_ptr<IDandPos> cpl = dg.getData<IDandPos>();

		PlayerCharacter* player;
		if ((player = (PlayerCharacter*)netMan.getGameObject(cpl->id)) == 0) {
			player = SpawnMainPlayer(Vector3(cpl->px, cpl->py, cpl->pz));
			player->giveGamera(camera_);
			player->setSocket(socket);
			netMan.addGameObject(cpl->id, player);
		}
		else {
			RespawnPlayer(player, Vector3(cpl->px, cpl->py, cpl->pz));
		}
	}

	void GameState::createPlayer(GPENet::Datagram dg) {
		boost::shared_ptr<IDandPos> cpl = dg.getData<IDandPos>();

		PlayerCharacter* player;
		if ((player = (PlayerCharacter*)netMan.getGameObject(cpl->id)) == 0) {
			player = SpawnPlayer(Vector3(cpl->px, cpl->py, cpl->pz));
			player->netOwned = false;
			netMan.addGameObject(cpl->id, player);
		}
		else {
			RespawnPlayer(player, Vector3(cpl->px, cpl->py, cpl->pz));
		}
	}

	void GameState::createBullet(GPENet::Datagram dg) {
		boost::shared_ptr<CreateBullet> cb = dg.getData<CreateBullet>();

		PlayerCharacter* player = (PlayerCharacter*)netMan.getGameObject(cb->parentid);
		Projectile* proj = new Projectile(this, player, PxVec3(cb->px, cb->py, cb->pz), PxQuat(cb->dx, cb->dy, cb->dz, cb->dw), false);
		AddGameObject(proj);
	}

	void GameState::getNetEvent(GPENet::Datagram dg) {
		boost::shared_ptr<NetEvent> ne = dg.getData<NetEvent>();

		GameObject* go = netMan.getGameObject(ne->targetid);
		go->dispatchEvent(ne->eventName, 0);
	}

	void GameState::createScene() {
		Ogre::Log* log = Ogre::LogManager::getSingleton().getDefaultLog();

		log->logMessage("[GameState]: Creating Scene...");

		scene_manager_ = Ogre::Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC, "GameSceneMgr");
		scene_manager_->setAmbientLight(Ogre::ColourValue(1.f, 1.f, 1.f));

		camera_ = scene_manager_->createCamera("GameCamera");
		camera_->setPosition(Ogre::Vector3(65, -15, 120));
		camera_->setDirection(0, 0, -1);
		camera_->setNearClipDistance(1);

		//camera_->setAspectRatio(Ogre::Real(viewport_->getActualWidth()) /
		//						  Ogre::Real(viewport_->getActualHeight()));

		//viewport_->setCamera(camera_);
		//================================================================================================================
		Physics* physics = new Physics(false);

		physics_material_ = physics->get_physics()->createMaterial(0.9f, 0.5f, 0.0f);

		physics_scene_ = physics->CreateScene(PxVec3(0, -9.81, 0), this);

		//Create Level Begins here

		Ogre::StaticGeometry* static_World = scene_manager_->createStaticGeometry("WorldTest");

		Ogre::Vector3 size(1.0, 1.0, 1.0);

		Ogre::Entity* ent;
		Ogre::SceneNode* node;

		PxFilterData filterData;
		filterData.word0 = 4; // word0 = own ID
		filterData.word1 = 2;	// word1 = ID mask to filter pairs that trigger a contact callback;



		struct EnemyDef {
			std::string classID;
			std::string model;
			//std::string script;
		};

		std::map<char, EnemyDef> enemyDefs;

		char buf[512];

		DataStreamPtr levelData = ResourceGroupManager::getSingletonPtr()->openResource("testlevel.txt");
		for (int y = 0; !levelData->eof(); y--) {

			ZeroMemory(buf, 512);
			size_t length_read = levelData->readLine(buf, 512);

			int x_offset = 0, y_offset = 0;

			for (int x = 0; x < length_read; x++) {
				switch (buf[x]) {
				case '#':
				{
					EnemyDef ed;
					char id;

					std::stringstream ss;
					ss << buf;

					ss >> id >> id >> ed.classID >> ed.model;// >> ed.script;

					enemyDefs[id] = ed;
					x = length_read;
				}
					break;
				case 'b':
				{
					node = scene_manager_->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(x + x_offset, y + y_offset, 0));
					ent = scene_manager_->createEntity("SimpleBox.mesh");
					node->attachObject(ent);
					node->setScale(size);

					physx::PxRigidStatic* box = physics->get_physics()->createRigidStatic(physx::PxTransform(physx::PxVec3(x + x_offset, y + y_offset, 0), PxQuat::createIdentity()));
					PxBoxGeometry geo(0.5f, 0.5f, 0.5f);
					physx::PxShape* shape = box->createShape(geo, *physics_material_);
					shape->setSimulationFilterData(filterData);
					physics_scene_->get_scene()->addActor(*box);

					static_World->addEntity(ent, Ogre::Vector3(x + x_offset, y + y_offset, 0), Ogre::Quaternion::IDENTITY, size);

					scene_manager_->destroyEntity(ent);
					scene_manager_->destroySceneNode(node);
				}
					break;
				case 's':
					spawn_points_.push_back(Vector3(x + x_offset, y + y_offset, 0));
					break;
				case ' ':
					//do nothing
					break;
				default:
				{
					std::map<char, EnemyDef>::iterator itr;
					for (itr = enemyDefs.begin(); itr != enemyDefs.end(); itr++) {
						if (buf[x] == itr->first) {

							if (itr->second.classID == "Enemy") {
								if (isserver_) {
									Enemy *nme = new Enemy(this, itr->second.model);
									nme->setPosition(PxVec3(x + x_offset, y + y_offset, 0));
									nme->setSocket(socket);
									AddGameObject(nme);
									netMan.addGameObject(nme);
								}

							}
							break;
						}
					}
				}
					break;
				}
			}

		}

		levelData->close();
		static_World->build();
		srand(time(0));
		//Create Level Ends Here

		Projectile::Initialize(scene_manager_);
	}

	Vector3 GameState::GetBestSpawnpoint() {
		int spawnPoint = rand() % spawn_points_.size();
		unsigned int bestValue = 0;

		for (int i = 0; i < spawn_points_.size(); i++) {
			int tempval = 0;
			for (int j = 0; j < players_.size(); j++) {
				tempval += players_[j]->getPosition().squaredDistance(spawn_points_[i]);
			}

			if (bestValue < tempval) {
				bestValue = tempval;
				spawnPoint = i;
			}
		}

		return spawn_points_[spawnPoint];
	}

	void GameState::RespawnPlayer(PlayerCharacter* player) {
		player->setPosition(GetBestSpawnpoint());
		player->resetLife();
	}


	PlayerCharacter* GameState::SpawnMainPlayer() {
		PlayerCharacter* newPlayer = new PlayerCharacter(gamestatemanager_->get_keyboard(), gamestatemanager_->get_joystick(), gamestatemanager_->get_joystick_dead_zone(), this);

		newPlayer->setPosition(GetBestSpawnpoint());
		players_.push_back(newPlayer);
		AddGameObject(newPlayer);

		return newPlayer;
	}

	PlayerCharacter* GameState::SpawnPlayer() {
		PlayerCharacter* newPlayer = new PlayerCharacter(0, 0, gamestatemanager_->get_joystick_dead_zone(), this);

		newPlayer->setPosition(GetBestSpawnpoint());
		players_.push_back(newPlayer);
		AddGameObject(newPlayer);

		return newPlayer;
	}

	void GameState::RespawnPlayer(PlayerCharacter* player, Vector3 pos) {
		player->setPosition(pos);
		player->resetLife();
	}


	PlayerCharacter* GameState::SpawnPlayer(Vector3 pos) {
		PlayerCharacter* newPlayer = new PlayerCharacter(0, 0, gamestatemanager_->get_joystick_dead_zone(), this);

		newPlayer->setPosition(pos);
		players_.push_back(newPlayer);
		AddGameObject(newPlayer);

		return newPlayer;
	}

	PlayerCharacter* GameState::SpawnMainPlayer(Vector3 pos) {
		PlayerCharacter* newPlayer = new PlayerCharacter(gamestatemanager_->get_keyboard(), gamestatemanager_->get_joystick(), gamestatemanager_->get_joystick_dead_zone(), this);

		newPlayer->setPosition(pos);
		players_.push_back(newPlayer);
		AddGameObject(newPlayer);

		return newPlayer;
	}

	void GameState::RegisterKeyListener(IKeyListener* listener) {
		keylisteners_.push_back(listener);
	}

	void GameState::DeregisterKeyListener(IKeyListener* listener) {
		std::vector<IKeyListener*>::iterator itr = std::find<std::vector<IKeyListener*>::iterator, IKeyListener*>(keylisteners_.begin(), keylisteners_.end(), listener);
		if (itr != keylisteners_.end())
			keylisteners_.erase(itr);
	}

	void GameState::RegisterJoyListener(IJoyStickListener* listener) {
		joylisteners_.push_back(listener);
	}

	void GameState::DeregisterJoyListener(IJoyStickListener* listener) {
		std::vector<IJoyStickListener*>::iterator itr = std::find<std::vector<IJoyStickListener*>::iterator, IJoyStickListener*>(joylisteners_.begin(), joylisteners_.end(), listener);
		if (itr != joylisteners_.end())
			joylisteners_.erase(itr);
	}

	void GameState::AddGameObject(GameObject* go) {
		gameobjects_.push_back(go);
	}

	void GameState::DeleteGameObject(GameObject* go) {

		if (!physics_scene_->get_fetching_results()) {
			RemoveGameObject(go);

			delete go;
		}
		else {
			if (std::find<std::list<GameObject*>::iterator, GameObject*>(toDelete.begin(), toDelete.end(), go) == toDelete.end()) {
				toDelete.push_back(go);
			}
		}
	}

	void GameState::RemoveGameObject(GameObject* go) {
		std::vector<GameObject*>::iterator itr = std::find<std::vector<GameObject*>::iterator, GameObject*>(gameobjects_.begin(), gameobjects_.end(), go);
		if (itr != gameobjects_.end()) {
			gameobjects_.erase(itr);
			netMan.removeGameObject(go);
		}

		if (go->getType() == GO_TYPE::PLAYER) {
			PlayerCharacter* player = (PlayerCharacter*)go;

			std::vector<PlayerCharacter*>::iterator itr = std::find(players_.begin(), players_.end(), player);

			if (itr != players_.end())
				players_.erase(itr);
		}
	}

	void GameState::RegisterHit(PlayerCharacter* player, PxControllersHit hit) {
		PlayerHit ph;
		ph.player = player;
		ph.hit = hit;
		std::list<PlayerHit>::iterator itr = std::find<std::list<PlayerHit>::iterator, PlayerHit>(hits_this_frame_.begin(), hits_this_frame_.end(), ph);
		if (itr == hits_this_frame_.end())
			hits_this_frame_.push_back(ph);
	}

	bool GameState::keyPressed(const OIS::KeyEvent &keyEventRef) {
		if (keyEventRef.key == OIS::KC_F1) {
			switch (camera_->getPolygonMode()) {
			case Ogre::PM_SOLID:
				camera_->setPolygonMode(Ogre::PM_WIREFRAME);
				Ogre::LogManager::getSingleton().getDefaultLog()->logMessage("[GameState]: Switched PolygonMode to PM_WIREFRAME view...");
				break;
			case Ogre::PM_WIREFRAME:
				camera_->setPolygonMode(Ogre::PM_POINTS);
				Ogre::LogManager::getSingleton().getDefaultLog()->logMessage("[GameState]: Switched PolygonMode to PM_POINTS view...");
				break;
			default:
				camera_->setPolygonMode(Ogre::PM_SOLID);
				Ogre::LogManager::getSingleton().getDefaultLog()->logMessage("[GameState]: Switched PolygonMode to PM_SOLID view...");
			}
		}

		if (keyEventRef.key == OIS::KC_F2) {
			physics_scene_->ToggleVisualDebugger();
		}

		std::vector<IKeyListener*>::iterator itr = keylisteners_.begin();
		for (; itr != keylisteners_.end(); itr++) {
			(*itr)->keyPressed(keyEventRef);
		}
		
		if (gamestatemanager_->get_keyboard()->isKeyDown(OIS::KC_ESCAPE)) {
			b_shutdown_ = true;
			return true;
		}

		return true;
	}

	bool GameState::keyReleased(const OIS::KeyEvent &keyEventRef) {
		std::vector<IKeyListener*>::iterator itr = keylisteners_.begin();
		for (; itr != keylisteners_.end(); itr++) {
			(*itr)->keyReleased(keyEventRef);
		}
		return true;
	}

	bool GameState::mouseMoved(const OIS::MouseEvent &evt) {
		if (m_bRMouseDown) {
			camera_->yaw(Ogre::Degree(evt.state.X.rel * -0.1f));
			camera_->pitch(Ogre::Degree(evt.state.Y.rel * -0.1f));
		}

		// Scroll wheel.
		if (evt.state.Z.rel) {
			Ogre::Vector3 translatevector = Ogre::Vector3::ZERO;
			if (camera_->getPosition().z > 1) {
				translatevector.z = -1.0f*evt.state.Z.rel / abs(evt.state.Z.rel);

				if (evt.state.Z.rel > 0) {
					translatevector.x = (evt.state.X.abs / float(evt.state.width) - 0.5f);
					translatevector.y = -(evt.state.Y.abs / float(evt.state.height) - 0.5f);
				}
			}
			else {
				if (evt.state.Z.rel < 0) {
					translatevector.z = 1.0f;

				}
			}

			camera_->moveRelative(translatevector);

			Ogre::Vector3 camPos = camera_->getPosition();
			if (camPos.z < 0) {
				camera_->setPosition(camPos.x, camPos.y, 1);
			}
		}

		return true;
	}

	bool GameState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
		if (id == OIS::MB_Left) {
			m_bLMouseDown = true;
		}
		else if (id == OIS::MB_Right) {
			m_bRMouseDown = true;
		}

		return true;
	}

	bool GameState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {

		if (id == OIS::MB_Left) {
			m_bLMouseDown = false;
		}
		else if (id == OIS::MB_Right) {
			m_bRMouseDown = false;
		}

		return true;
	}

	bool GameState::povMoved(const OIS::JoyStickEvent &e, int pov) {
		std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
		for (; itr != joylisteners_.end(); itr++) {
			(*itr)->povMoved(e, pov);
		}

		return true;
	}

	bool GameState::axisMoved(const OIS::JoyStickEvent &e, int axis) {
		std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
		for (; itr != joylisteners_.end(); itr++) {
			(*itr)->axisMoved(e, axis);
		}

		return true;
	}

	bool GameState::sliderMoved(const OIS::JoyStickEvent &e, int sliderID) {
		std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
		for (; itr != joylisteners_.end(); itr++) {
			(*itr)->sliderMoved(e, sliderID);
		}

		return true;
	}

	bool GameState::buttonPressed(const OIS::JoyStickEvent &e, int button) {
		std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
		for (; itr != joylisteners_.end(); itr++) {
			(*itr)->buttonPressed(e, button);
		}

		return true;
	}

	bool GameState::buttonReleased(const OIS::JoyStickEvent &e, int button) {
		std::vector<IJoyStickListener*>::iterator itr = joylisteners_.begin();
		for (; itr != joylisteners_.end(); itr++) {
			(*itr)->buttonReleased(e, button);
		}

		return true;
	}

	void GameState::MoveCamera(double timeSinceLastFrame) {

		Ogre::Vector3 translatevector = Ogre::Vector3::ZERO;

		if (gamestatemanager_->get_keyboard()->isKeyDown(OIS::KC_LEFT))
			translatevector.x = -1.0f * 10;

		if (gamestatemanager_->get_keyboard()->isKeyDown(OIS::KC_RIGHT))
			translatevector.x = 10;

		if (gamestatemanager_->get_keyboard()->isKeyDown(OIS::KC_UP))
			translatevector.y = 10;

		if (gamestatemanager_->get_keyboard()->isKeyDown(OIS::KC_DOWN))
			translatevector.y = -1.0f * 10;

		translatevector *= timeSinceLastFrame;

		if (gamestatemanager_->get_keyboard()->isKeyDown(OIS::KC_LSHIFT) || gamestatemanager_->get_keyboard()->isKeyDown(OIS::KC_RSHIFT))
			camera_->moveRelative(translatevector * 10);
		else
			camera_->moveRelative(translatevector);

		Ogre::Vector3 camPos = camera_->getPosition();
		if (camPos.z < 0) {
			camera_->setPosition(camPos.x, camPos.y, 1);
		}
	}

	void GameState::update(double timeSinceLastFrame) {
		std::vector<GameObject*>::iterator GOItr = gameobjects_.begin();

		for (; GOItr != gameobjects_.end(); GOItr++) {
			(*GOItr)->Update(timeSinceLastFrame);
		}

		if (isserver_) {
			hackSendEnemyPosTime += timeSinceLastFrame;

			if (hackSendEnemyPosTime > 1) {
				hackSendEnemyPosTime -= 1;
				std::vector<GameObject*>::iterator itr = gameobjects_.begin();
				for (; itr != gameobjects_.end(); itr++) {
					if ((*itr)->netOwned) {
						if ((*itr)->getType() == GO_TYPE::ENEMY) {
							Enemy* nme = (Enemy*)(*itr);
							IDandPos idp;

							idp.id = (*itr)->netId;
							Vector3 pos = nme->getPosition();
							idp.px = pos.x;
							idp.py = pos.y;
							idp.pz = pos.z;

							socket->Send(idp, NEW_NETUPDATES::SET_POS, GPENet::DatagramImportance::RELIABLE_ORDERED);
						}
					}
				}
			}
		}

		socket->Update(timeSinceLastFrame);

		MoveCamera(timeSinceLastFrame);
	}

	void GameState::advanceSimulation(float dtime) {
		const PxReal timestep = 1.0f / 60.0f;
		while (dtime > 0.0f) {
			const PxReal dt = dtime >= timestep ? timestep : dtime;
			physics_scene_->AdvanceSimulation(dt);
			dtime -= dt;

			if (toDelete.size() > 0) {
				std::list<GameObject*>::iterator itr = toDelete.begin();
				for (; itr != toDelete.end(); itr++) {
					GameObject* temp = *itr;
					RemoveGameObject(temp);
					delete temp;
				}
				toDelete.clear();
			}

			if (hits_this_frame_.size() > 0) {
				std::list<PlayerHit>::iterator itr = hits_this_frame_.begin();
				for (; itr != hits_this_frame_.end(); itr++) {
					itr->player->DoHit(itr->hit);
				}
				hits_this_frame_.clear();
			}
		}
	}


	bool GameState::frameRenderingQueued(const Ogre::FrameEvent& evt) {
		//if (evt.timeSinceLastFrame > 0.5f)
		//	return true;

		if (gamestatemanager_->get_render_window()->isClosed())
			return false;

		if (b_shutdown_)
			return false;

		socket->fetchCallbacks();

		update(evt.timeSinceLastFrame);

		advanceSimulation(evt.timeSinceLastFrame);

		return true;
	}


	void GameState::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) {
		Util::dout << "onConstraintBreak called...." << std::endl;
	}

	void GameState::onWake(PxActor** actors, PxU32 count) {
		Util::dout << "onWake called...." << std::endl;
	}

	void GameState::onSleep(PxActor** actors, PxU32 count) {
		Util::dout << "onSleep called...." << std::endl;
	}

	void GameState::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) {
		if (pairHeader.actors[0]->getName() == "Projectile") {
			GameObject* go = reinterpret_cast<GameObject*>(pairHeader.actors[0]->userData);

			if (pairHeader.actors[1]->userData != 0 && pairHeader.actors[0]->userData != pairHeader.actors[1]->userData) {
				if (pairHeader.actors[1]->getName() == "Projectile") {
					go->release();
					GameObject*  otherGO = reinterpret_cast<GameObject*>(pairHeader.actors[1]->userData);
					otherGO->release();
				}
				else {
					EventData d;
					d.data = pairHeader.actors[1]->userData;
					go->dispatchEvent("Projectile_Hit", &d);
				}
			}

			go->release();
		}

		if (pairHeader.actors[1]->getName() == "Projectile") {
			GameObject* go = reinterpret_cast<GameObject*>(pairHeader.actors[1]->userData);

			if (pairHeader.actors[0]->userData != 0 && pairHeader.actors[0]->userData != pairHeader.actors[1]->userData) {
				if (pairHeader.actors[0]->getName() == "Projectile") {
					go->release();
					GameObject*  otherGO = reinterpret_cast<GameObject*>(pairHeader.actors[0]->userData);
					otherGO->release();
				}
				else {
					EventData d;
					d.data = pairHeader.actors[0]->userData;
					go->dispatchEvent("Projectile_Hit", &d);
				}
			}

			go->release();
		}
	}

	void GameState::onTrigger(PxTriggerPair* pairs, PxU32 count) {
		if (isserver_) {
			for (int i = 0; i < count; i++) {
				if (!(pairs[i].flags & (PxTriggerPairFlag::Enum::eDELETED_SHAPE_TRIGGER | PxTriggerPairFlag::Enum::eDELETED_SHAPE_OTHER))) {
					if (pairs[i].triggerShape->getActor()->userData != 0 && pairs[i].otherShape->getActor()->userData != 0) {
						GameObject* trigggo = reinterpret_cast<GameObject*>(pairs[i].triggerShape->getActor()->userData);
						GameObject* go = reinterpret_cast<GameObject*>(pairs[i].otherShape->getActor()->userData);

						if (go->getType() == GO_TYPE::PLAYER && trigggo->getType() == GO_TYPE::POWERUP) {
							PowerUp* pu = (PowerUp*)trigggo;
							GetPowerUp gpu; //lol

							gpu.targetid = go->netId;
							gpu.puID = trigggo->netId;
							gpu.powerupType = pu->getPowerUpType();

							socket->Send(gpu, NEW_NETUPDATES::COLLECT_POWERUP, GPENet::DatagramImportance::RELIABLE_ORDERED);

							trigggo->release();
						}
					}
				}
			}
		}
	}
}