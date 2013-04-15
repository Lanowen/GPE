//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameState.hpp"
#include <OgreManualObject.h>
#include <PxConstraint.h>

#include <IInputListener.hpp>
#include <GameObject.hpp>
#include <PlayerCharacter.hpp>
#include <Enemy.hpp>

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

    mResourcesCfg       = Ogre::StringUtil::BLANK;
    mPluginsCfg         = Ogre::StringUtil::BLANK;

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
}

GameState::~GameState() {
	if(m_pBackPlane){
		delete m_pBackPlane;
	}

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
        m_pJoyDeadZone = m_pJoyStick->MAX_AXIS*0.2;
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

    createScene();

    m_pLog->logMessage("Game initialized!");

    m_pRSQ = m_pSceneMgr->createRayQuery(Ogre::Ray());

    m_pRoot->startRendering();

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void
GameState::createScene()
{
    m_pLog->logMessage("[GameState]: Creating Scene...");

    //buildGUI();

    m_pRenderWnd->resetStatistics();

    m_pSceneMgr = m_pRoot->createSceneManager(Ogre::ST_GENERIC, "GameSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(1.f, 1.f, 1.f));

    m_pCamera = m_pSceneMgr->createCamera("GameCamera");
    m_pCamera->setPosition(Ogre::Vector3(0,5,10));
    m_pCamera->lookAt(Ogre::Vector3::ZERO);
    m_pCamera->setNearClipDistance(1);

    m_pCamera->setAspectRatio(Ogre::Real(m_pViewport->getActualWidth()) /
        Ogre::Real(m_pViewport->getActualHeight()));

    m_pViewport->setCamera(m_pCamera);

    m_pBackPlane = new Ogre::Plane(Ogre::Vector3::UNIT_Z, -0.5f);

    Ogre::MeshManager::getSingleton().createPlane("bgPlane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                  *m_pBackPlane, 16384, 16384,1,1,true,1,16384,16384);

    m_pPlane = m_pSceneMgr->createEntity("BGSelector", "bgPlane");
    m_pPlane->setMaterialName("SelectionPlane/Grid");
    m_pPlane->setCastShadows(false);
    m_pPlane->setQueryFlags(BG_SELECT);
    m_pPlane->setVisible(false);

    m_pSceneMgr->getRootSceneNode()->createChildSceneNode("PlaneAxis")->attachObject(m_pPlane);
//================================================================================================================
//================================================================================================================
	Physics* Phys = new Physics();

	Phys->init(mCreateCudaCtxManager);

	mPhysics = Phys->mPhysics;
	mCudaContextManager = Phys->mCudaContextManager;

	mControllerManager = PxCreateControllerManager(mPhysics->getFoundation());

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

	DataStreamPtr levelData = ResourceGroupManager::getSingletonPtr()->openResource("level1.txt");
	for(int y = 0; !levelData->eof(); y--){

		ZeroMemory(buf, 512);
		size_t length_read = levelData->readLine(buf, 512);

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
				node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(x,y,0));
				ent = m_pSceneMgr->createEntity("SimpleBox.mesh" );
				node->attachObject( ent );
				node->setScale( size );

				physx::PxRigidStatic* derp = mPhysics->createRigidStatic(physx::PxTransform(physx::PxVec3(x,y,0)));
				physx::PxShape* shape = derp->createShape(physx::PxBoxGeometry(0.5f,0.5f,0.5f), *mMaterial);
				shape->setSimulationFilterData(filterData);
				mPxScene->addActor(*derp);

				static_World->addEntity(ent,Ogre::Vector3(x,y,0),Ogre::Quaternion::IDENTITY,size);

				m_pSceneMgr->destroyEntity(ent);
				m_pSceneMgr->destroySceneNode(node);
				}
				break;
			case 's':
				spawnPoints.push_back(Vector3(x,y,0));
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
							Enemy *nme = new Enemy(this, itr->second.model);//, itr->second.script);
							nme->setPosition(PxVec3(x,y,0));
							AddGameObject(nme);
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

	PlayerCharacter* player = SpawnPlayer();
	player->giveGamera(m_pCamera);
	//Create Level Ends Here

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
	testConn->freezeZPos();

	Enemy *testEnemy = new Enemy(this, "SimpleBox.mesh");
	AddGameObject(testEnemy);*/
}

Vector3 GameState::GetBestSpawnpoint(){
	int spawnPoint = rand()%spawnPoints.size();
	unsigned int bestValue = 0;

	for(int i = 0; i < spawnPoints.size(); i++){
		int tempval = 0;
		for(int j = 0; j < players.size(); j++){
			tempval += players[i]->getPosition().squaredDistance(spawnPoints[i]);
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
}


PlayerCharacter* GameState::SpawnPlayer(){
	PlayerCharacter* newPlayer = new PlayerCharacter(m_pKeyboard, m_pJoyStick, m_pJoyDeadZone, this);
	newPlayer->setPosition(GetBestSpawnpoint());
	AddGameObject(newPlayer);

	return newPlayer;
}

void GameState::RegisterInputListener(IInputListener* listener){
	mInputListeners.push_back(listener);
}

void GameState::DeregisterInputListener(IInputListener* listener){
	std::vector<IInputListener*>::iterator itr = std::find<std::vector<IInputListener*>::iterator, IInputListener*>(mInputListeners.begin(), mInputListeners.end(), listener);
	if(itr != mInputListeners.end())
		mInputListeners.erase(itr);
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
	if(itr != mGameObjects.end())
		mGameObjects.erase(itr);
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
	std::vector<IInputListener*>::iterator itr = mInputListeners.begin();
	for(;itr != mInputListeners.end(); itr++){
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
	std::vector<IInputListener*>::iterator itr = mInputListeners.begin();
	for(;itr != mInputListeners.end(); itr++){
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
    printf("povMoved: %d   %d\n", pov, e.state.mPOV[pov].direction);

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

    switch(axis){
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
    }

    return true;
}

bool GameState::sliderMoved( const OIS::JoyStickEvent &e, int sliderID ) {
//    itJoystickListener    = mJoystickListeners.begin();
//    itJoystickListenerEnd = mJoystickListeners.end();
//    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
//        if(!itJoystickListener->second->sliderMoved( e, sliderID ))
//            break;
//    }

    printf("sliderMoved: %d\n", sliderID);

    return true;
}

bool GameState::buttonPressed( const OIS::JoyStickEvent &e, int button ) {
//    itJoystickListener    = mJoystickListeners.begin();
//    itJoystickListenerEnd = mJoystickListeners.end();
//    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
//        if(!itJoystickListener->second->buttonPressed( e, button ))
//            break;
//    }

    printf("buttonPressed: %d\n", button);

    return true;
}

bool GameState::buttonReleased( const OIS::JoyStickEvent &e, int button ) {
//    itJoystickListener    = mJoystickListeners.begin();
//    itJoystickListenerEnd = mJoystickListeners.end();
//    for(; itJoystickListener != itJoystickListenerEnd; ++itJoystickListener ) {
//        if(!itJoystickListener->second->buttonReleased( e, button ))
//            break;
//    }

    printf("buttonReleased: %d\n", button);

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

			if(pairHeader.actors[1]->userData != 0){
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

			if(pairHeader.actors[0]->userData != 0){
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
	Util::dout << "onTrigger called...." << std::endl;
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
