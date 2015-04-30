//|||||||||||||||||||||||||||||||||||||||||||||||

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

//#include <Scripting_Helpers.hpp>
//#include <Scripting_ExposeGPE.hpp>

//|||||||||||||||||||||||||||||||||||||||||||||||

PxFilterFlags FilterShader(
        PxFilterObjectAttributes attributes0, PxFilterData filterData0,
        PxFilterObjectAttributes attributes1, PxFilterData filterData1,
        PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
        // let triggers through
        if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
        {
                pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
                return PxFilterFlag::eDEFAULT;
        }
        // generate contacts for all that were not filtered above
        pairFlags = PxPairFlag::eCONTACT_DEFAULT;

        // trigger the contact callback for pairs (A,B) where
        // the filtermask of A contains the ID of B and vice versa.
        if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
                pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;

        return PxFilterFlag::eDEFAULT;
}

template<> GameState* Ogre::Singleton<GameState>::msSingleton = 0;

//PxSimulationFilterShader gDefaultFilterShader = PxDefaultSimulationFilterShader;
PxSimulationFilterShader gDefaultFilterShader = FilterShader;

std::string GameState::ip = "";
bool GameState::isServer = false;

//|||||||||||||||||||||||||||||||||||||||||||||||

GameState::GameState()
{
    m_pRoot			    = 0;
    m_pRenderWnd		= 0;
    m_pViewport			= 0;
    m_pLog			    = 0;
    m_pTimer			= 0;
    m_pRSQ              = 0;

    m_pInputMgr			= 0;
    m_pKeyboard			= 0;
    m_pMouse			= 0;
    m_pJoyStick         = 0;

    mResourcesCfg       = Ogre::BLANKSTRING;
	mPluginsCfg			= Ogre::BLANKSTRING;

    m_bShutdown         = false;
    m_MoveSpeed		    = 1.f;
    m_RotateSpeed	    = 1.f;

    m_bLMouseDown       = false;
    m_bRMouseDown       = false;

    m_pCurrentObject	= 0;
    m_pCurrentEntity    = 0;
    //m_pDetailsPanel	    = 0;
    m_pPlane            = 0;
	m_pBackPlane		= 0;
	//m_pPlayerChar		= 0;

    zoomState           = 0;
	mNbThreads			= 4;
	mCreateCudaCtxManager = false;
	mControllerManager  = 0;
	mCudaContextManager	= 0;

	mEventHandler		= 0;
	//mScripting			= 0;
	pxVisualDebuggerHidden = false;
	fetchingResults = false;
	hackSendEnemyPosTime = 0;
}

GameState::~GameState() {
	//if(m_pBackPlane){
	//	delete m_pBackPlane;
	//}

	for(int i = 0; i < mGameObjects.size(); i++){
		delete mGameObjects[i];
	}
}

bool GameState::initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener, OIS::MouseListener *pMouseListener)
{
//-----------------------------------------------------------------------
    Ogre::LogManager* logMgr = new Ogre::LogManager();

    m_pLog = Ogre::LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
    m_pLog->setDebugOutputEnabled(true);
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
    #ifdef _DEBUG
        mResourcesCfg = "resources_d.cfg";
        mPluginsCfg = "plugins_d.cfg";
    #else
        mResourcesCfg = "resources.cfg";
        mPluginsCfg = "plugins.cfg";
    #endif
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
    m_pRoot = new Ogre::Root(mPluginsCfg);
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
	if(!m_pRoot->showConfigDialog())
        return false;

    m_pRenderWnd = m_pRoot->initialise(true, wndTitle);
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
    m_pViewport = m_pRenderWnd->addViewport(0);
    m_pViewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0, 1.0f));

    m_pViewport->setCamera(0);
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
    unsigned long hWnd = 0;
    OIS::ParamList paramList;
    m_pRenderWnd->getCustomAttribute("WINDOW", &hWnd);

	paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	paramList.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	paramList.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));

    paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));

    m_pInputMgr = OIS::InputManager::createInputSystem(paramList);

    m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputMgr->createInputObject(OIS::OISKeyboard, true));
    m_pMouse = static_cast<OIS::Mouse*>(m_pInputMgr->createInputObject(OIS::OISMouse, true));

    m_pMouse->getMouseState().height = m_pRenderWnd->getHeight();
    m_pMouse->getMouseState().width  = m_pRenderWnd->getWidth();

    if(pKeyListener == 0)
        m_pKeyboard->setEventCallback(this);
    else
        m_pKeyboard->setEventCallback(pKeyListener);

    if(pMouseListener == 0)
        m_pMouse->setEventCallback(this);
    else
        m_pMouse->setEventCallback(pMouseListener);


    if (m_pInputMgr->getNumberOfDevices(OIS::OISJoyStick) > 0) {
        //mJoysticks.resize( mInputSystem->numJoySticks() );
//        mJoysticks.resize( mInputSystem->getNumberOfDevices(OIS::OISJoyStick) );
//
//        itJoystick    = mJoysticks.begin();
//        itJoystickEnd = mJoysticks.end();
//        for(; itJoystick != itJoystickEnd; ++itJoystick ) {
//            (*itJoystick) = static_cast<OIS::JoyStick*>( mInputSystem->createInputObject( OIS::OISJoyStick, true ) );
//            (*itJoystick)->setEventCallback( this );
//        }
        m_pJoyStick = static_cast<OIS::JoyStick*>(m_pInputMgr->createInputObject(OIS::OISJoyStick, true));
        m_pJoyStick->setEventCallback(this);

        //m_pJoyDeadZone1 = (Ogre::Math.Abs(m_pJoyStick->getJoyStickState()->mAxes[0].abs) + Ogre::Math.Abs(m_pJoyStick->getJoyStickState()->mAxes[1].abs))/2
        //m_pJoyDeadZone2 = (Ogre::Math.Abs(m_pJoyStick->getJoyStickState()->mAxes[2].abs) + Ogre::Math.Abs(m_pJoyStick->getJoyStickState()->mAxes[3].abs))/2
        m_JoyDeadZone = m_pJoyStick->MAX_AXIS*0.4;
    }

    m_pRoot->addFrameListener(this);
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
    m_pTimer = new Ogre::Timer();
    m_pTimer->reset();
//-----------------------------------------------------------------------

    m_pRenderWnd->setActive(true);
	mEventHandler = new SceneWideEvent();
    

	if(isServer){
		socket = GPENet::Server::Create();

		socket->AddQueuedCallback(GPENet::CONNECT, boost::bind(&GameState::onClientConnect, this, _1));
		socket->AddQueuedCallback(PLAYER_DEATH, boost::bind(&GameState::onPlayerDied, this, _1));
	}
	else {
		socket = GPENet::Client::Create(boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::any(), 0), boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::from_string(ip), 1774));

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

	//m_pRSQ = m_pSceneMgr->createRayQuery(Ogre::Ray());

    m_pLog->logMessage("Game initialized!");

    m_pRoot->startRendering();

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::handleCreatePowerup(GPENet::Datagram dg){
	boost::shared_ptr<CreatePowerUp> cpu = dg.getData<CreatePowerUp>();

	Vector3 pos(cpu->px, cpu->py, cpu->pz);

	switch(cpu->powerupType){
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

void GameState::handlePowerup(GPENet::Datagram dg){
	boost::shared_ptr<GetPowerUp> gpu = dg.getData<GetPowerUp>();
	GameObject* go = netMan.getGameObject(gpu->targetid);
	GameObject* puGo = netMan.getGameObject(gpu->puID);

	if(go->getType() == GO_TYPE::PLAYER && go->netOwned){
		PlayerCharacter* player = (PlayerCharacter*)go;

		player->getPowerUp((POWERUP_TYPE)gpu->powerupType);
	}

	if(puGo->getType() == GO_TYPE::POWERUP){
		puGo->release();
	}	
}

void GameState::onPlayerDied(GPENet::Datagram dg){
	boost::shared_ptr<SerializableUINT32> id = dg.getData<SerializableUINT32>();
	GameObject* go = netMan.getGameObject(id->val);

	if(go->getType() == GO_TYPE::PLAYER){
		PlayerCharacter* player = (PlayerCharacter*)go;

		Vector3 pos = GetBestSpawnpoint();

		RespawnPlayer(player,pos);

		IDandPos idp;
		idp.id = id->val;

		idp.px = pos.x;
		idp.py = pos.y;
		idp.pz = pos.z;

		socket->Send(idp, NEW_NETUPDATES::CREATE_PLAYER, GPENet::DatagramImportance::RELIABLE_ORDERED);
	}
}

void GameState::handleDisconnect(GPENet::Datagram dg){
	boost::shared_ptr<SerializableUINT32> id = dg.getData<SerializableUINT32>();
	GameObject* go = netMan.getGameObject(id->val);

	go->release();

	netMan.removeGameObject(id->val);
}

void GameState::handleEnemyDeath(GPENet::Datagram dg){
	boost::shared_ptr<SerializableUINT32> id = dg.getData<SerializableUINT32>();
	GameObject* go = netMan.getGameObject(id->val);

	if(go->getType() == GO_TYPE::ENEMY){
		Enemy* nme = (Enemy*)go;

		nme->release();
	}
}

void GameState::handleEnemyDeathPowerup(Vector3 pos){
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

void GameState::handlePlayerHurt(GPENet::Datagram dg){
	boost::shared_ptr<IDandPos> idp = dg.getData<IDandPos>();
	GameObject* go = netMan.getGameObject(idp->id);

	if(go->getType() == GO_TYPE::PLAYER){
		PlayerCharacter* player = (PlayerCharacter*)go;

		player->getHurt(PxVec3(idp->px, idp->py, idp->pz));
	}
}

void GameState::setIDPosition(GPENet::Datagram dg){
	boost::shared_ptr<IDandPos> idp = dg.getData<IDandPos>();
	GameObject* go = netMan.getGameObject(idp->id);

	if(go->getType() == GO_TYPE::PLAYER){
		PlayerCharacter* player = (PlayerCharacter*)go;

		player->setPosition(Vector3(idp->px, idp->py, idp->pz));
	}
	else if(go->getType() == GO_TYPE::ENEMY){
		Enemy* nme = (Enemy*)go;

		nme->setPosition(PxVec3(idp->px, idp->py, idp->pz));
	}
}

void GameState::handleInputVel(GPENet::Datagram dg){
	boost::shared_ptr<IDandPos> idp = dg.getData<IDandPos>();
	GameObject* go = netMan.getGameObject(idp->id);

	if(go->getType() == GO_TYPE::PLAYER){
		PlayerCharacter* player = (PlayerCharacter*)go;

		player->setInputVel(PxVec3(idp->px, idp->py, idp->pz));
	}
}

void GameState::handleButtonPressed(GPENet::Datagram dg){
	boost::shared_ptr<ButtonPress> bp = dg.getData<ButtonPress>();
	GameObject* go = netMan.getGameObject(bp->id);

	if(go->getType() == GO_TYPE::PLAYER){
		PlayerCharacter* player = (PlayerCharacter*)go;

		player->doButtonPressed(bp->bid);
	}
}

void GameState::handleButtonReleased(GPENet::Datagram dg){
	boost::shared_ptr<ButtonPress> bp = dg.getData<ButtonPress>();
	GameObject* go = netMan.getGameObject(bp->id);

	if(go->getType() == GO_TYPE::PLAYER){
		PlayerCharacter* player = (PlayerCharacter*)go;

		player->doButtonReleased(bp->bid);
	}
}

void GameState::createEnemy(GPENet::Datagram dg){
	boost::shared_ptr<IDandPos> ce = dg.getData<IDandPos>();
	Enemy *nme = new Enemy(this, "GeemerGeemer.mesh", false);
	nme->setPosition(PxVec3(ce->px,ce->py,ce->pz));
	nme->netOwned = false;
	AddGameObject(nme);
	netMan.addGameObject(ce->id, nme);
}

void GameState::onClientConnect(GPENet::Datagram dg){
	std::map<int, GameObject*>::iterator itr = netMan.objects.begin();
	boost::shared_ptr<GPENet::Server> server = boost::static_pointer_cast<GPENet::Server>(socket);
	for(;itr != netMan.objects.end(); itr++){
		int id = itr->first;
		GameObject* go = itr->second;

		switch(go->getType()){
		case GO_TYPE::ENEMY:
			{
			Enemy* nme = (Enemy*)go;
			IDandPos idp;
			idp.id = id;
			Vector3 pos = nme->getPosition();
			idp.px = pos.x;
			idp.py = pos.y;
			idp.pz = pos.z;

			server->SendTo(dg.senderid, idp,CREATE_ENEMY,GPENet::RELIABLE_ORDERED);
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

			server->SendTo(dg.senderid, idp,CREATE_PLAYER,GPENet::RELIABLE_ORDERED);
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

	server->SendTo(dg.senderid, idp, CREATE_MAINPLAYER,GPENet::RELIABLE_ORDERED);
	server->SendToExcluding(dg.senderid, idp, CREATE_PLAYER,GPENet::RELIABLE_ORDERED);
}

void GameState::createMainPlayer(GPENet::Datagram dg){
	boost::shared_ptr<IDandPos> cpl = dg.getData<IDandPos>();

	PlayerCharacter* player;
	if((player = (PlayerCharacter*)netMan.getGameObject(cpl->id)) == 0){
		player = SpawnMainPlayer(Vector3(cpl->px, cpl->py, cpl->pz));
		player->giveGamera(m_pCamera);
		player->setSocket(socket);
		netMan.addGameObject(cpl->id, player);
	}
	else {
		RespawnPlayer(player, Vector3(cpl->px, cpl->py, cpl->pz));
	}
}

void GameState::createPlayer(GPENet::Datagram dg){
	boost::shared_ptr<IDandPos> cpl = dg.getData<IDandPos>();

	PlayerCharacter* player;
	if((player = (PlayerCharacter*)netMan.getGameObject(cpl->id)) == 0){
		player = SpawnPlayer(Vector3(cpl->px, cpl->py, cpl->pz));
		player->netOwned = false;
		netMan.addGameObject(cpl->id, player);
	}
	else {
		RespawnPlayer(player, Vector3(cpl->px, cpl->py, cpl->pz));
	}
}

void GameState::createBullet(GPENet::Datagram dg){
	boost::shared_ptr<CreateBullet> cb = dg.getData<CreateBullet>();

	PlayerCharacter* player = (PlayerCharacter*)netMan.getGameObject(cb->parentid);
	Projectile* proj = new Projectile(this, player, PxVec3(cb->px, cb->py, cb->pz), PxQuat(cb->dx, cb->dy, cb->dz, cb->dw), false);
	AddGameObject(proj);
}

void GameState::getNetEvent(GPENet::Datagram dg){
	boost::shared_ptr<NetEvent> ne = dg.getData<NetEvent>();

	GameObject* go = netMan.getGameObject(ne->targetid);
	go->dispatchEvent(ne->eventName, 0);
}

void
GameState::createScene()
{
    m_pLog->logMessage("[GameState]: Creating Scene...");

    //buildGUI();

    m_pRenderWnd->resetStatistics();

    m_pSceneMgr = m_pRoot->createSceneManager(Ogre::ST_GENERIC, "GameSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(1.f, 1.f, 1.f));

    m_pCamera = m_pSceneMgr->createCamera("GameCamera");
    m_pCamera->setPosition(Ogre::Vector3(65,-15,120));
    m_pCamera->setDirection(0,0,-1);
    m_pCamera->setNearClipDistance(1);

    m_pCamera->setAspectRatio(Ogre::Real(m_pViewport->getActualWidth()) /
        Ogre::Real(m_pViewport->getActualHeight()));

    m_pViewport->setCamera(m_pCamera);

    /*m_pBackPlane = new Ogre::Plane(Ogre::Vector3::UNIT_Z, -0.5f);

    Ogre::MeshManager::getSingleton().createPlane("bgPlane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                  *m_pBackPlane, 16384, 16384,1,1,true,1,16384,16384);

    m_pPlane = m_pSceneMgr->createEntity("BGSelector", "bgPlane");
    m_pPlane->setMaterialName("SelectionPlane/Grid");
    m_pPlane->setCastShadows(false);
    m_pPlane->setQueryFlags(BG_SELECT);
    m_pPlane->setVisible(false);

    m_pSceneMgr->getRootSceneNode()->createChildSceneNode("PlaneAxis")->attachObject(m_pPlane);*/
//================================================================================================================
//================================================================================================================
	Physics* Phys = new Physics();

	Phys->init(mCreateCudaCtxManager);

	mPhysics = Phys->mPhysics;
	mCudaContextManager = Phys->mCudaContextManager;

	physx::PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
	{
		sceneDesc.gravity = physx::PxVec3(0.f, -9.81f, 0.f);

		if(!sceneDesc.cpuDispatcher)
		{
			mCpuDispatcher = physx::PxDefaultCpuDispatcherCreate(mNbThreads);
			if(!mCpuDispatcher)
				m_pLog->logMessage("PxDefaultCpuDispatcherCreate failed!");
			sceneDesc.cpuDispatcher	= mCpuDispatcher;
		}
		if(!sceneDesc.filterShader)
			sceneDesc.filterShader = gDefaultFilterShader;

		sceneDesc.simulationEventCallback = this;

		if(!sceneDesc.gpuDispatcher && mCudaContextManager)
		{
			sceneDesc.gpuDispatcher = mCudaContextManager->getGpuDispatcher();
		}
	}

	mPxScene = mPhysics->createScene(sceneDesc);
	if (!mPxScene)
		m_pLog->logMessage("createScene failed!");

	mControllerManager = PxCreateControllerManager(*mPxScene);

	//mScene->setSimulationEventCallback(this);

	//mMaterial = mPhysics->createMaterial(0.9f, 0.5f, 0.0f);
	mMaterial = mPhysics->createMaterial(0.9f, 0.5f, 0.0f);

	//if(!mMaterial)
		//m_pLog->logMessage("createMaterial failed!");

//#if _DEBUG
	mVisualDebugger = new VisualDebugger(mPxScene,m_pSceneMgr);

#if _DEBUG
	mVisualDebugger->showAll();
	pxVisualDebuggerHidden = false;
#else 
	mVisualDebugger->hideAll();
	pxVisualDebuggerHidden = true;
#endif
	
	//mPhysWorld->getRemoteDebugger()->connect();

	//mPhysRenderSystem = new Critter::RenderSystem(mPhysScene, m_pSceneMgr);

//================================================================================================================
	//mScripting = new V8Scripting();

//================================================================================================================

	//PlayerCharacter* playerChar = new PlayerCharacter(m_pKeyboard, m_pJoyStick, m_pJoyDeadZone, this);
	//playerChar->giveGamera(m_pCamera);
	//AddGameObject(playerChar);

	//Create Level Begins here

    Ogre::StaticGeometry* static_World = m_pSceneMgr->createStaticGeometry("WorldTest");

    Ogre::Vector3 size(1.0,1.0,1.0);

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
	for(int y = 0; !levelData->eof(); y--){

		ZeroMemory(buf, 512);
		size_t length_read = levelData->readLine(buf, 512);

		int x_offset = 0, y_offset = 0;

		//mPxScene->shiftOrigin(PxVec3(x_offset, y_offset, 0));

		for(int x = 0; x < length_read; x++){
			switch(buf[x]){
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
				node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(x + x_offset, y + y_offset, 0));
				ent = m_pSceneMgr->createEntity("SimpleBox.mesh" );
				node->attachObject( ent );
				node->setScale( size );

				physx::PxRigidStatic* box = mPhysics->createRigidStatic(physx::PxTransform(physx::PxVec3(x + x_offset, y + y_offset, 0), PxQuat::createIdentity()));
				PxBoxGeometry geo(0.5f, 0.5f, 0.5f);
				//PxSphereGeometry geo(0.5);
				//Util::dout << "Box isValid: " << geo.isValid() << " ~ " << x << " " << y << " ~ " << mPhysics->getTolerancesScale().length;
				physx::PxShape* shape = box->createShape(geo, *mMaterial);
				shape->setSimulationFilterData(filterData);
				mPxScene->addActor(*box);

				static_World->addEntity(ent, Ogre::Vector3(x + x_offset, y + y_offset, 0), Ogre::Quaternion::IDENTITY, size);

				m_pSceneMgr->destroyEntity(ent);
				m_pSceneMgr->destroySceneNode(node);
				}
				break;
			case 's':
				spawnPoints.push_back(Vector3(x + x_offset, y + y_offset, 0));
				break;
			case ' ':
				//do nothing
				break;
			default:
				{
				std::map<char, EnemyDef>::iterator itr;
				for(itr = enemyDefs.begin(); itr != enemyDefs.end(); itr++){
					if(buf[x] == itr->first){

						if(itr->second.classID == "Enemy"){
							if(isServer){
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

	//PlayerCharacter* player = SpawnPlayer();
	//player->giveGamera(m_pCamera);

	//Create Level Ends Here

	Projectile::Initialize(m_pSceneMgr);

	/*physx::PxRigidDynamic* derp2 = mPhysics->createRigidDynamic(PxTransform(PxVec3(3.2,5.0f,0.f)));
	physx::PxShape* hmm = derp2->createShape(PxBoxGeometry(0.5f,0.5f,0.5f), *mMaterial);
	physx::PxRigidBodyExt::setMassAndUpdateInertia(*derp2,10.0f);

	hmm->setSimulationFilterData(filterData);

	mPxScene->addActor(*derp2);

	DynamicConstraints* testConn = new DynamicConstraints();
	PxConstraintShaderTable pxcst;
	pxcst.solverPrep = testConn->solverPrep;
	pxcst.project = testConn->constraintProj;
	pxcst.visualize = testConn->vis;
	pxcst.solverPrepSpu = 0;
	pxcst.solverPrepSpuByteSize = 0;


	testConn->mConstraint = mPhysics->createConstraint(derp2, 0, *testConn, pxcst, sizeof(DynamicConstraints::freeze));
	testConn->mConstraint->setFlags(physx::PxConstraintFlag::ePROJECTION);
	
	testConn->freezeXRot();
	testConn->freezeYRot();
	testConn->freezeZPos();*/
}

Vector3 GameState::GetBestSpawnpoint(){
	int spawnPoint = rand()%spawnPoints.size();
	unsigned int bestValue = 0;

	for(int i = 0; i < spawnPoints.size(); i++){
		int tempval = 0;
		for(int j = 0; j < players.size(); j++){
			tempval += players[j]->getPosition().squaredDistance(spawnPoints[i]);
		}

		if(bestValue < tempval){
			bestValue = tempval;
			spawnPoint = i;
		}
	}

	return spawnPoints[spawnPoint];
}

void GameState::RespawnPlayer(PlayerCharacter* player){
	player->setPosition(GetBestSpawnpoint());
	player->resetLife();
}


PlayerCharacter* GameState::SpawnMainPlayer(){
	PlayerCharacter* newPlayer = new PlayerCharacter(m_pKeyboard, m_pJoyStick, m_JoyDeadZone, this);

	newPlayer->setPosition(GetBestSpawnpoint());
	players.push_back(newPlayer);
	AddGameObject(newPlayer);

	return newPlayer;
}

PlayerCharacter* GameState::SpawnPlayer(){
	PlayerCharacter* newPlayer = new PlayerCharacter(0, 0, m_JoyDeadZone, this);

	newPlayer->setPosition(GetBestSpawnpoint());
	players.push_back(newPlayer);
	AddGameObject(newPlayer);

	return newPlayer;
}

void GameState::RespawnPlayer(PlayerCharacter* player, Vector3 pos){
	player->setPosition(pos);
	player->resetLife();
}


PlayerCharacter* GameState::SpawnPlayer(Vector3 pos){
	PlayerCharacter* newPlayer = new PlayerCharacter(0, 0, m_JoyDeadZone, this);
	
	newPlayer->setPosition(pos);
	players.push_back(newPlayer);
	AddGameObject(newPlayer);

	return newPlayer;
}

PlayerCharacter* GameState::SpawnMainPlayer(Vector3 pos){
	PlayerCharacter* newPlayer = new PlayerCharacter(m_pKeyboard, m_pJoyStick, m_JoyDeadZone, this);
	
	newPlayer->setPosition(pos);
	players.push_back(newPlayer);
	AddGameObject(newPlayer);

	return newPlayer;
}

void GameState::RegisterKeyListener(IKeyListener* listener){
	mKeyListeners.push_back(listener);
}

void GameState::DeregisterKeyListener(IKeyListener* listener){
	std::vector<IKeyListener*>::iterator itr = std::find<std::vector<IKeyListener*>::iterator, IKeyListener*>(mKeyListeners.begin(), mKeyListeners.end(), listener);
	if(itr != mKeyListeners.end())
		mKeyListeners.erase(itr);
}

void GameState::RegisterJoyListener(IJoyStickListener* listener){
	mJoyListeners.push_back(listener);
}

void GameState::DeregisterJoyListener(IJoyStickListener* listener){
	std::vector<IJoyStickListener*>::iterator itr = std::find<std::vector<IJoyStickListener*>::iterator, IJoyStickListener*>(mJoyListeners.begin(), mJoyListeners.end(), listener);
	if(itr != mJoyListeners.end())
		mJoyListeners.erase(itr);
}

PxPhysics* GameState::getPhysics(){
	return mPhysics;
}

PxScene* GameState::getMainPhysicsScene(){
	return mPxScene;
}

PxControllerManager* GameState::getControllerManager(){
	return mControllerManager;
}

void GameState::AddGameObject(GameObject* go){
	mGameObjects.push_back(go);
}

void GameState::DeleteGameObject(GameObject* go){
	
	if(!fetchingResults){	
		RemoveGameObject(go);

		delete go;
	}
	else {
		if(std::find<std::list<GameObject*>::iterator, GameObject*>(toDelete.begin(), toDelete.end(), go) == toDelete.end()){
			toDelete.push_back(go);
		}		
	}
}

void GameState::RemoveGameObject(GameObject* go){
	std::vector<GameObject*>::iterator itr = std::find<std::vector<GameObject*>::iterator, GameObject*>(mGameObjects.begin(), mGameObjects.end(), go);
	if(itr != mGameObjects.end()){
		mGameObjects.erase(itr);
		netMan.removeGameObject(go);
	}

	if(go->getType() == GO_TYPE::PLAYER){
		PlayerCharacter* player = (PlayerCharacter*)go;

		std::vector<PlayerCharacter*>::iterator itr = std::find(players.begin(), players.end(), player);

		if(itr != players.end())
			players.erase(itr);
	}
}

void GameState::RegisterHit(PlayerCharacter* player, PxControllersHit hit){
	PlayerHit ph;
	ph.player = player;
	ph.hit = hit;
	std::list<PlayerHit>::iterator itr = std::find<std::list<PlayerHit>::iterator, PlayerHit>(hitsThisFrame.begin(), hitsThisFrame.end(), ph);
	if(itr == hitsThisFrame.end())
		hitsThisFrame.push_back(ph);
}

bool GameState::keyPressed(const OIS::KeyEvent &keyEventRef){
    //CEGUI::System &sys = CEGUI::System::getSingleton();
    //sys.injectKeyDown(keyEventRef.key);
    //sys.injectChar(keyEventRef.text);

    //if(m_pKeyboard->isKeyDown(OIS::KC_F1)){
	if(keyEventRef.key == OIS::KC_F1){
        switch (m_pCamera->getPolygonMode()){
            case Ogre::PM_SOLID:
                m_pCamera->setPolygonMode(Ogre::PM_WIREFRAME);
                m_pLog->logMessage("[GameState]: Switched PolygonMode to PM_WIREFRAME view...");
                break;
            case Ogre::PM_WIREFRAME:
                m_pCamera->setPolygonMode(Ogre::PM_POINTS);
                m_pLog->logMessage("[GameState]: Switched PolygonMode to PM_POINTS view...");
                break;
            default:
                m_pCamera->setPolygonMode(Ogre::PM_SOLID);
                m_pLog->logMessage("[GameState]: Switched PolygonMode to PM_SOLID view...");
        }
    }

	if(keyEventRef.key == OIS::KC_F2){
		if(pxVisualDebuggerHidden){
			pxVisualDebuggerHidden = false;
			mVisualDebugger->showAll();
		}
		else {
			pxVisualDebuggerHidden = true;
			mVisualDebugger->hideAll();
		}
	}

    //m_pPlayerChar->keyPressed(keyEventRef);
	std::vector<IKeyListener*>::iterator itr = mKeyListeners.begin();
	for(;itr != mKeyListeners.end(); itr++){
		(*itr)->keyPressed(keyEventRef);
	}

    if(m_pKeyboard->isKeyDown(OIS::KC_ESCAPE)){
        m_bShutdown = true;
        return true;
    }


    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::keyReleased(const OIS::KeyEvent &keyEventRef){
    //CEGUI::System::getSingleton().injectKeyUp(keyEventRef.key);
    //m_pPlayerChar->keyReleased(keyEventRef);
	std::vector<IKeyListener*>::iterator itr = mKeyListeners.begin();
	for(;itr != mKeyListeners.end(); itr++){
		(*itr)->keyReleased(keyEventRef);
	}
    return true;
}

bool GameState::mouseMoved(const OIS::MouseEvent &evt){
	//CEGUI::System &sys = CEGUI::System::getSingleton();
    //sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);

    if(m_bRMouseDown)
    {
        m_pCamera->yaw(Ogre::Degree(evt.state.X.rel * -0.1f));
        m_pCamera->pitch(Ogre::Degree(evt.state.Y.rel * -0.1f));
    }

    // Scroll wheel.
    if(evt.state.Z.rel){
        //sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);
        m_TranslateVector = Ogre::Vector3::ZERO;
        if(m_pCamera->getPosition().z > 1 ){
            m_TranslateVector.z = -m_MoveSpeed*evt.state.Z.rel/abs(evt.state.Z.rel);

            if(evt.state.Z.rel > 0){
                m_TranslateVector.x = (evt.state.X.abs / float(evt.state.width) - 0.5f);
                m_TranslateVector.y = -(evt.state.Y.abs / float(evt.state.height) - 0.5f);
            }
        }
        else {
            if(evt.state.Z.rel < 0){
                m_TranslateVector.z = m_MoveSpeed;

            }
        }
        moveCamera();
    }

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id){
    if(id == OIS::MB_Left)
    {
        //onLeftPressed(evt);
        m_bLMouseDown = true;
    }
    else if(id == OIS::MB_Right)
    {
        m_bRMouseDown = true;
    }

    return true;
}

bool
GameState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id){

    if(id == OIS::MB_Left)
    {
        m_bLMouseDown = false;
    }
    else if(id == OIS::MB_Right)
    {
        m_bRMouseDown = false;
    }

    return true;
}

bool GameState::povMoved( const OIS::JoyStickEvent &e, int pov ) {
//    itJoystickListener    = mJoystickListeners.begin();
//    itJoystickListenerEnd = mJoystickListeners.end();
//    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
//        if(!itJoystickListener->second->povMoved( e, pov ))
//            break;
//    }

	std::vector<IJoyStickListener*>::iterator itr = mJoyListeners.begin();
	for(;itr != mJoyListeners.end(); itr++){
		(*itr)->povMoved(e, pov);
	}

    //printf("povMoved: %d   %d\n", pov, e.state.mPOV[pov].direction);

    return true;
}

bool GameState::axisMoved( const OIS::JoyStickEvent &e, int axis ) {
//    itJoystickListener    = mJoystickListeners.begin();
//    itJoystickListenerEnd = mJoystickListeners.end();
//    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
//        if(!itJoystickListener->second->axisMoved( e, axis ))
//            break;
//    }

//    for (std::vector<OIS::Axis>::const_iterator itrAxis = e.state.mAxes.begin(); itrAxis != e.state.mAxes.end(); itrAxis++){
//        printf("%d axisMoved:  %d %d %d\t", axis, itrAxis.abs, itrAxis[1].abs, itrAxis[2].abs);
//        printf("\n");
//
//    }

	std::vector<IJoyStickListener*>::iterator itr = mJoyListeners.begin();
	for(;itr != mJoyListeners.end(); itr++){
		(*itr)->axisMoved(e, axis);
	}

    /*switch(axis){
        case 0: case 1:
            if ( Ogre::Math::Abs(e.state.mAxes[0].abs) > m_pJoyDeadZone || Ogre::Math::Abs(e.state.mAxes[1].abs) > m_pJoyDeadZone){
                printf("1 axisMoved: x:%d y:%d\n",e.state.mAxes[1].abs, e.state.mAxes[0].abs);
            }
            break;
        case 2:case 3:
            if (Ogre::Math::Abs(e.state.mAxes[2].abs) > m_pJoyDeadZone || Ogre::Math::Abs(e.state.mAxes[3].abs) > m_pJoyDeadZone){
                printf("2 axisMoved: x:%d y:%d\n",e.state.mAxes[3].abs, e.state.mAxes[2].abs);
            }
            break;
        case 4:
            printf("3 axisMoved: %d\n", e.state.mAxes[4].abs);
            break;
    }*/

    return true;
}

bool GameState::sliderMoved( const OIS::JoyStickEvent &e, int sliderID ) {
//    itJoystickListener    = mJoystickListeners.begin();
//    itJoystickListenerEnd = mJoystickListeners.end();
//    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
//        if(!itJoystickListener->second->sliderMoved( e, sliderID ))
//            break;
//    }

    //printf("sliderMoved: %d\n", sliderID);

	std::vector<IJoyStickListener*>::iterator itr = mJoyListeners.begin();
	for(;itr != mJoyListeners.end(); itr++){
		(*itr)->sliderMoved(e, sliderID);
	}

    return true;
}

bool GameState::buttonPressed( const OIS::JoyStickEvent &e, int button ) {
//    itJoystickListener    = mJoystickListeners.begin();
//    itJoystickListenerEnd = mJoystickListeners.end();
//    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
//        if(!itJoystickListener->second->buttonPressed( e, button ))
//            break;
//    }

	std::vector<IJoyStickListener*>::iterator itr = mJoyListeners.begin();
	for(;itr != mJoyListeners.end(); itr++){
		(*itr)->buttonPressed(e, button);
	}

	//Util::dout << "buttonPressed: " << button <<std::endl;
    //printf("buttonPressed: %d\n", button);

    return true;
}

bool GameState::buttonReleased( const OIS::JoyStickEvent &e, int button ) {
//    itJoystickListener    = mJoystickListeners.begin();
//    itJoystickListenerEnd = mJoystickListeners.end();
//    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
//        if(!itJoystickListener->second->buttonReleased( e, button ))
//            break;
//    }


	std::vector<IJoyStickListener*>::iterator itr = mJoyListeners.begin();
	for(;itr != mJoyListeners.end(); itr++){
		(*itr)->buttonReleased(e, button);
	}

    //printf("buttonReleased: %d\n", button);

    return true;
}

void GameState::moveCamera()
{

    if(m_pKeyboard->isKeyDown(OIS::KC_LSHIFT) || m_pKeyboard->isKeyDown(OIS::KC_RSHIFT))
        m_pCamera->moveRelative(m_TranslateVector*10);

    m_pCamera->moveRelative(m_TranslateVector);

    Ogre::Vector3 camPos = m_pCamera->getPosition();
    if(camPos.z < 0){
        m_pCamera->setPosition(camPos.x,camPos.y,1);
    }
}

void GameState::getInput(double timeSinceLastFrame)
{
    if(m_pKeyboard->isKeyDown(OIS::KC_LEFT))
        m_TranslateVector.x = -m_MoveScale*10;

    if(m_pKeyboard->isKeyDown(OIS::KC_RIGHT))
        m_TranslateVector.x = m_MoveScale*10;

    if(m_pKeyboard->isKeyDown(OIS::KC_UP))
        m_TranslateVector.y = m_MoveScale*10;

    if(m_pKeyboard->isKeyDown(OIS::KC_DOWN))
        m_TranslateVector.y = -m_MoveScale*10;
}

void GameState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;

    m_MoveScale = m_MoveSpeed   * timeSinceLastFrame;
    m_RotScale  = m_RotateSpeed * timeSinceLastFrame;

    m_TranslateVector = Ogre::Vector3::ZERO;

	

	//m_pPlayerChar->Update(timeSinceLastFrame);

	std::vector<GameObject*>::iterator GOItr = mGameObjects.begin();

	for(; GOItr != mGameObjects.end(); GOItr++){
		(*GOItr)->Update(timeSinceLastFrame);
	}

	if(isServer){
		hackSendEnemyPosTime += timeSinceLastFrame;

		if(hackSendEnemyPosTime > 1){
			hackSendEnemyPosTime -= 1;
			vector<GameObject*>::iterator itr = mGameObjects.begin();
			for(;itr != mGameObjects.end(); itr++){
				if((*itr)->netOwned){
					if((*itr)->getType() == GO_TYPE::ENEMY){
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

    getInput(timeSinceLastFrame);
    moveCamera();
}

void GameState::advanceSimulation(float dtime)
{
	const PxReal timestep = 1.0f/60.0f;
	while(dtime>0.0f)
	{
		const PxReal dt = dtime>=timestep ? timestep : dtime;
		mPxScene->simulate(dt);
		fetchingResults = true;
		mPxScene->fetchResults(true);
		fetchingResults = false;
		dtime -= dt;

		if(toDelete.size() > 0){
			std::list<GameObject*>::iterator itr = toDelete.begin();
			for(;itr != toDelete.end(); itr++){
				GameObject* temp = *itr;
				RemoveGameObject(temp);
				delete temp;
			}
			toDelete.clear();
		}

		if(hitsThisFrame.size() > 0){
			std::list<PlayerHit>::iterator itr = hitsThisFrame.begin();
			for(;itr != hitsThisFrame.end(); itr++){
				itr->player->DoHit(itr->hit);				
			}
			hitsThisFrame.clear();
		}		
	}
}


bool GameState::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	//if (evt.timeSinceLastFrame > 0.5f)
	//	return true;

    if(m_pRenderWnd->isClosed())
        return false;

    if(m_bShutdown)
        return false;

    //Need to capture/update each device
    m_pKeyboard->capture();
    m_pMouse->capture();
    if( m_pJoyStick ) {
        m_pJoyStick->capture();
    }

	socket->fetchCallbacks();

    update(evt.timeSinceLastFrame);

	advanceSimulation(evt.timeSinceLastFrame);

	//while(!V8::IdleNotification(1)) {};
	

	if(!pxVisualDebuggerHidden)
		mVisualDebugger->update(mPxScene->getRenderBuffer());


	//mPhysWorld->advance(evt.timeSinceLastFrame);

	//m_pPlayerChar->updateAnimation(evt.timeSinceLastFrame);

    return true;
}


void GameState::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count){
	Util::dout << "onConstraintBreak called...." << std::endl;
}

void GameState::onWake(PxActor** actors, PxU32 count){
	Util::dout << "onWake called...." << std::endl;
}

void GameState::onSleep(PxActor** actors, PxU32 count){
	Util::dout << "onSleep called...." << std::endl;
}

void GameState::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs){
	//Util::dout << "onContact called...." << nbPairs << std::endl;
	//for(int pairs = 0; pairs < nbPairs; pairs++){ //this might be wrong

		/*if(pairHeader.actors[0]->getName() == "Projectile" || pairHeader.actors[1]->getName() == "Projectile"){
			for(int i = 0; i < 2; i++){
				if(pairHeader.actors[i]->userData != 0){
					GameObject* go = reinterpret_cast<GameObject*>(pairHeader.actors[i]->userData);
					go->dispatchEvent("Projectile_Hit");
				}
			}
		}*/

		if(pairHeader.actors[0]->getName() == "Projectile"){
			GameObject* go = reinterpret_cast<GameObject*>(pairHeader.actors[0]->userData);

			if(pairHeader.actors[1]->userData != 0 && pairHeader.actors[0]->userData != pairHeader.actors[1]->userData){
				if(pairHeader.actors[1]->getName() == "Projectile"){
					go->release();
					GameObject*  otherGO = reinterpret_cast<GameObject*>(pairHeader.actors[1]->userData);
					otherGO->release();
				}
				else{
					/*HandleScope scope(Isolate::GetCurrent());
					GameObject*  otherGO = reinterpret_cast<GameObject*>(pairHeader.actors[1]->userData);
					Handle<Value> args[1];
					args[0] = wrapPtr<GameObject, V8GameObject>(otherGO);
					go->dispatchEvent("Projectile_Hit", 1, args);*/
					EventData d;
					d.data = pairHeader.actors[1]->userData;
					go->dispatchEvent("Projectile_Hit", &d);
				}
			}

			go->release();
		}

		if(pairHeader.actors[1]->getName() == "Projectile"){
			GameObject* go = reinterpret_cast<GameObject*>(pairHeader.actors[1]->userData);

			if(pairHeader.actors[0]->userData != 0 && pairHeader.actors[0]->userData != pairHeader.actors[1]->userData){
				if(pairHeader.actors[0]->getName() == "Projectile"){
					go->release();
					GameObject*  otherGO = reinterpret_cast<GameObject*>(pairHeader.actors[0]->userData);
					otherGO->release();
				}
				else{
					/*HandleScope scope(Isolate::GetCurrent());
					GameObject*  otherGO = reinterpret_cast<GameObject*>(pairHeader.actors[0]->userData);
					Handle<Value> args[1];
					args[0] = wrapPtr<GameObject, V8GameObject>(otherGO);
					go->dispatchEvent("Projectile_Hit", 1, args);*/
					EventData d;
					d.data = pairHeader.actors[0]->userData;
					go->dispatchEvent("Projectile_Hit", &d);
				}
			}

			go->release();
		}

		//for(int i = 0; i < 2; i++){
		//	
		//		if(pairHeader.actors[i]->isRigidDynamic()){
		//			if(!(pairHeader.flags & (i? PxContactPairHeaderFlag::Enum::eDELETED_ACTOR_0 : PxContactPairHeaderFlag::Enum::eDELETED_ACTOR_1))){
		//				if(std::find<std::list<PxActor*>::iterator, PxActor*>(toDelete.begin(), toDelete.end(), pairHeader.actors[i]) == toDelete.end()){
		//					toDelete.push_back(pairHeader.actors[i]);
		//				}
		//				else {
		//					Util::dout << "This thing is already in here...." << std::endl;
		//				}
		//			}else {
		//				if(i == 0 && pairHeader.flags & PxContactPairHeaderFlag::Enum::eDELETED_ACTOR_0){
		//					Util::dout << "0 already deleted" << std::endl;
		//				}
		//				else if(i == 1 && pairHeader.flags & PxContactPairHeaderFlag::Enum::eDELETED_ACTOR_1){
		//					Util::dout << "1 already deleted" << std::endl;
		//				}
		//			}
		//	
		//		}
		//		//else if(pairHeader.actors[i]->
		//	}
		//}
	//}
}

void GameState::onTrigger(PxTriggerPair* pairs, PxU32 count){
	//Util::dout << "onTrigger called...." << std::endl;
	if(isServer){
		for(int i = 0; i < count; i++){
			if(!(pairs[i].flags & (PxTriggerPairFlag::Enum::eDELETED_SHAPE_TRIGGER | PxTriggerPairFlag::Enum::eDELETED_SHAPE_OTHER))){
				if (pairs[i].triggerShape->getActor()->userData != 0 && pairs[i].otherShape->getActor()->userData != 0){
					GameObject* trigggo = reinterpret_cast<GameObject*>(pairs[i].triggerShape->getActor()->userData);
					GameObject* go = reinterpret_cast<GameObject*>(pairs[i].otherShape->getActor()->userData);

					if(go->getType() == GO_TYPE::PLAYER && trigggo->getType() == GO_TYPE::POWERUP){
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

//Adjust mouse clipping area
void GameState::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = m_pMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void GameState::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == m_pRenderWnd )
    {
        if( m_pInputMgr )
        {
            m_pInputMgr->destroyInputObject( m_pMouse );
            m_pInputMgr->destroyInputObject( m_pKeyboard );
            m_pInputMgr->destroyInputObject( m_pJoyStick );

            OIS::InputManager::destroyInputSystem(m_pInputMgr);
            m_pInputMgr = 0;
        }
    }
}
