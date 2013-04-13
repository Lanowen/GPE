#pragma once

#define _UNICODE
#include <wx/wxprec.h>
#include <wx/wx.h>

#include <wxOgreView.hpp>
#include <wxOgreScene.hpp>
#include <wxOgreViewEventHandler.hpp>
//#include <OgreInstance.hpp>

class MainEditor : public wxApp {
public:
	virtual bool OnInit();
};

class EditorFrame: public wxFrame
{
public:

    EditorFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

	//OgreInstance* mOgre;
	//wxOgreView* mTestView;

	///The main Ogre Scene
    wxOgreScene* mpMainScene;
    ///The wxOgreView object
    wxOgreView* mpMainOgreView;
    ///The wxOgreViewEventHandler object
    wxOgreViewEventHandler* mpSecOgreView;

    DECLARE_EVENT_TABLE()
};

