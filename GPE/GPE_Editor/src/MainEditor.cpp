#include <MainEditor.hpp>

enum
{
    ID_Quit = 1,
    ID_About,
};

BEGIN_EVENT_TABLE(EditorFrame, wxFrame)
    EVT_MENU(ID_Quit,  EditorFrame::OnQuit)
    EVT_MENU(ID_About, EditorFrame::OnAbout)
END_EVENT_TABLE()

//IMPLEMENT_APP(MainEditor)

bool MainEditor::OnInit()
{
    EditorFrame *frame = new EditorFrame( _("GPE Editor"), wxPoint(50, 50), wxSize(450, 340) );
    frame->Show(true);
    SetTopWindow(frame);

    return true;
}

EditorFrame::EditorFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame(NULL, -1, title, pos, size)
{
    /*wxMenu *menuFile = new wxMenu;

    menuFile->Append( ID_About, _("&About...") );
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, _("E&xit") );

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, _("&File") );

    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText( _("Welcome to wxWidgets!") );*/

	//Attach menu items and the statusbar
    //Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));

    //Create the main Ogre scene
    wxGridSizer* MainBoxSizer = new wxGridSizer(2,2,0,0);
    this->SetSizer(MainBoxSizer);
    MainBoxSizer->RecalcSizes();

    mpMainOgreView = new wxOgreView(this);
    mpSecOgreView = new wxOgreViewEventHandler(this);

    MainBoxSizer->Add(mpMainOgreView,0, wxSHAPED|wxALL|wxALIGN_CENTER,5);
    MainBoxSizer->Add(mpSecOgreView,0, wxSHAPED|wxALL|wxALIGN_CENTER,5);
    MainBoxSizer->SetSizeHints( this );

    this->Layout();
    mpMainScene = new wxOgreScene(mpMainOgreView, mpSecOgreView);
    SetSize(800,500);
}

void EditorFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void EditorFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox( _("This is a wxWidgets Hello world sample"),
                  _("About Hello World"),
                  wxOK | wxICON_INFORMATION, this );
}