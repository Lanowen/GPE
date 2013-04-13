#include <wxOgreScene.hpp>

// Required for the timer
const int wxOgreScene::ID_RENDERTIMER = wxNewId();

//================================================================================= wxOgreScene()//
wxOgreScene::wxOgreScene(wxOgreView* MainOgreView, wxOgreViewEventHandler* SecOgreView) : mResourcePath("../Media")
{
    mIsInitialized = false;

	Ogre::LogManager* logMgr = new Ogre::LogManager();

    m_Log = Ogre::LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
    m_Log->setDebugOutputEnabled(true);

    //Create a new Ogre Root
    mpRoot = new Ogre::Root();

	Ogre::String plugin;

#ifdef _DEBUG
	plugin = "RenderSystem_GL_d";
#else
	plugin = "RenderSystem_GL";
#endif

    //Select the rendering system
    mpRoot->loadPlugin(plugin);
	mpRoot->setRenderSystem(mpRoot->getAvailableRenderers().front());
    Ogre::Root::getSingleton().initialise(false);

    //Create the left render window
    MainOgreView->setRenderWindow("OgreRenderWindow1");

    //Create the right render window
    SecOgreView->setRenderWindow("OgreRenderWindow2");

    //Assign the wxOgreScene RenderWindow pointers
    mpMainWindow = MainOgreView->getRenderWindow();
    mpSecWindow = SecOgreView->getRenderWindow();

	//Initialize resource path for meshes and materials
    initializeMainResources();

	

     //Create the rendering timer
	mpTimer = new wxTimer(MainOgreView,ID_RENDERTIMER);
    //Start the rendering timer

	//mpTimer->Bind(wxEVT_TIMER, &wxOgreScene::OnRenderTimer, this);
	MainOgreView->Bind(wxEVT_TIMER, &wxOgreScene::OnRenderTimer, this, ID_RENDERTIMER);
	toggleTimerRendering();

	//MainOgreView->Connect(ID_RENDERTIMER,wxEVT_TIMER,(wxObjectEventFunction)&wxOgreScene::OnRenderTimer);

    //====================================================================================//
    //At this point the test scene is created, which shows a robot on a plane. It is not
    //needed to make the wxOgreView work, but it is a better example for the use of the
    //wxOgreViewEventHandlers than an empty scene.
    //====================================================================================//

	// Create the SceneManager, in this case a generic one
	mpSceneMgr = mpRoot->createSceneManager(Ogre::ST_GENERIC, "ExampleSMInstance");

	// Create the camera and make some settings
	mpCamera1 = mpSceneMgr->createCamera("Cam1");

	mpCamera1->setAutoAspectRatio(true);
    mpCamera1->setNearClipDistance(0.1f);
    mpCamera1->setFarClipDistance(1000.0f);
    mpCamera1->setPosition(Ogre::Vector3(0.0f, 3.0f, 3.0f));
    mpCamera1->pitch(Ogre::Radian(-0.785f));

	// Add a viewport
	mpViewPort = mpMainWindow->addViewport(mpCamera1);
    mpCamera2 = mpSceneMgr->createCamera("Cam2");

    mpCamera2->yaw(Ogre::Radian(3.14/2));
	mpCamera2->setAutoAspectRatio(true);
    mpCamera2->setNearClipDistance(0.1f);
    mpCamera2->setFarClipDistance(1000.0f);
    mpCamera2->setPosition(Ogre::Vector3(5.0f, 5.0f, 0.0f));
    mpCamera2->pitch(Ogre::Radian(-0.785f));

    mpSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	mpViewPort->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 1.0f));
    mpSceneMgr->setAmbientLight(Ogre::ColourValue(0.0f, 0.0f, 0.0f));
    mpLight = mpSceneMgr->createLight("Light1");
    mpLight->setType(Ogre::Light::LT_POINT);
    mpLight->setPosition(Ogre::Vector3(-100, 150, 250));

    mpLight = mpSceneMgr->createLight("Light2");
    mpLight->setType(Ogre::Light::LT_POINT);
    mpLight->setPosition(Ogre::Vector3(0, 150, -250));

	// Add a viewport
	mpViewPort = mpSecWindow->addViewport(mpCamera2);
	mpMainWindow->addViewport(mpCamera2, 1, 0.1f, 0.1f, 0.2f, 0.2f);
	// Create some Entities
	Ogre::MeshManager::getSingletonPtr()->createPlane("PlaneMesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                          Ogre::Plane(Ogre::Vector3::UNIT_Y, 0),  // plane
                          10.0f,                            // width
                          10.0f,                            // height
                          1,                                // xsegments
                          1,                                // ysegments
                          true,                             // normals
                          1,                                // numTexCoordSets
                          10,                               // uTile
                          10,                               // vTile
                          Ogre::Vector3::UNIT_Z);           // upVector

    // Create plane entity and a child node...
    Ogre::Entity *pEnt = mpSceneMgr->createEntity("Plane", "PlaneMesh");
    pEnt->setMaterialName("Template/texture_map");
    pEnt->setCastShadows(false);
    Ogre::SceneNode *planeNode = mpSceneMgr->getRootSceneNode()->createChildSceneNode("PlaneNode");
    planeNode->attachObject(pEnt);
    planeNode->setPosition(0.0f, 0.0f, 0.0f);

    // Create robot entity and a child node...
	Ogre::Entity *ent1 = mpSceneMgr->createEntity( "Robot", "robot.mesh" );
	ent1->setMaterialName("RobotMaterial");
	Ogre::SceneNode *node1 = mpSceneMgr->getRootSceneNode()->createChildSceneNode( "RobotNode" );
    node1->attachObject( ent1 );
    node1->setPosition(0.0f, 0.0f, 0.0f);
    node1->scale(0.02f, 0.02f, 0.02f);
    node1->yaw(Ogre::Radian(-1.57f));

    //All used Ogre components are now initialized
    mIsInitialized = true;
}

////================================================================================= ~wxOgreScene()//
wxOgreScene::~wxOgreScene()
{
    if (mpRoot)
        delete mpRoot;
}

// =============================================================================== initializeMainResources()
void wxOgreScene::initializeMainResources()
{
        // Add default texture location
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mResourcePath + "/materials/textures",
            std::string("FileSystem"), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, false);

        // Add default mesh location
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mResourcePath + "/models",
            std::string("FileSystem"), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, false);

        // Add default material location
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mResourcePath + "/materials",
            std::string("FileSystem"), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, false);


        // Initialize this resource group
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

} // initializeMainResources()

//================================================================================= toggleTimerRendering()//
void wxOgreScene::toggleTimerRendering()
{
	// Toggle Start/Stop
	if (mpTimer->IsRunning())
		mpTimer->Stop();
	mpTimer->Start(10);
}

//================================================================================= OnRenderTimer()//
void wxOgreScene::OnRenderTimer(wxTimerEvent&  WXUNUSED(event))
{
	if(mIsInitialized)
        Ogre::Root::getSingleton().renderOneFrame();
}
