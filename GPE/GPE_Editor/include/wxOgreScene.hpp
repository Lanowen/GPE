/// The main ogre scene class
/** The wxOgreScene class creates the scene that is
    rendered in the render windows of the wxOgreView objects
    that are expected by the constructor. This scene was created
    to test the functionality of the wxOgreView class. You can modify
    this class to get the appropriate behaviour for your own application.
*/

#pragma once

#include <wxOgreViewEventHandler.hpp>

class wxOgreScene
{
public:
     /** A new wxOgreScene must receive two pointers to the wxOgreViews used in the scene.
        @param MainOgreView pointer to wxOgreViewEventHandler.
        @param SecOgreView pointer to wxOgreView.
     */
	wxOgreScene (wxOgreView*, wxOgreViewEventHandler*);
	/** Standard Destructor*/
	~wxOgreScene();

private:
    /// The render timer id
    static const int ID_RENDERTIMER;
    /// Set to false until wxOgreScene is completely initialized
    bool mIsInitialized;

    //Ogre scene components
    /// Ogre Root pointer
    Ogre::Root* mpRoot;

	Ogre::Log*	m_Log;

    /// Main RenderWindow pointer
	Ogre::RenderWindow* mpMainWindow;
	/// Second RenderWindow pointer
	Ogre::RenderWindow* mpSecWindow;
	/// Ogre Viewport pointer
    Ogre::Viewport* mpViewPort;
    /// First Camera pointer
	Ogre::Camera* mpCamera1;
	/// Second Camera pointer
	Ogre::Camera* mpCamera2;
	/// Ogre SceneManager pointer
	Ogre::SceneManager* mpSceneMgr;
	/// The Light pointer
	Ogre::Light* mpLight;
    /// The resource path for the meshes and materials
    Ogre::String mResourcePath;
	/// Rendering timer pointer
	wxTimer	*mpTimer;

    /** Toggles the rendering timer */
    void toggleTimerRendering();
    /** Render timer event function
        @param event the timer event. */
    void OnRenderTimer(wxTimerEvent& event);
    /** Initialize the main resources */
    void initializeMainResources();
};
