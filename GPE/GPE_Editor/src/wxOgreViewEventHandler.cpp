#include <wxOgreViewEventHandler.hpp>

//================================================================================= BEGIN_EVENT_TABLE()//
BEGIN_EVENT_TABLE(wxOgreViewEventHandler, wxOgreView)
	EVT_MOTION(wxOgreViewEventHandler::MouseDragged)
	EVT_MOUSEWHEEL(wxOgreViewEventHandler::scrollWheel)
END_EVENT_TABLE()

//================================================================================= wxOgre()//
wxOgreViewEventHandler::wxOgreViewEventHandler (wxWindow* parent,
                                                wxWindowID id,
                                                const wxPoint &pos,
                                                const wxSize &size,
                                                long style,
                                                const wxValidator& validator,
                                                const wxString &name) : wxOgreView(parent, id, pos, size, style, validator, name)
{}

//================================================================================= MouseDragged()//
void wxOgreViewEventHandler::MouseDragged(wxMouseEvent& msevent)
{
    static long currentX;
    static long currentY;

    if(msevent.Dragging())
    {
        //choose the yaw direction
        if(msevent.GetX()<currentX)
        {
            mpRenderWindow->getViewport(0)->getCamera()->yaw(Ogre::Radian((currentX-msevent.GetX()) * 0.001f));
            currentX = msevent.GetX();
        }
        else
        {
            mpRenderWindow->getViewport(0)->getCamera()->yaw(Ogre::Radian((msevent.GetX()-currentX) * -0.001f));
            currentX = msevent.GetX();
        }
        //choose the pitch direction
        if(msevent.GetY()<currentY)
        {
            mpRenderWindow->getViewport(0)->getCamera()->pitch(Ogre::Radian((currentY-msevent.GetY()) * 0.001f));
            currentY = msevent.GetY();
        }
        else
        {
            mpRenderWindow->getViewport(0)->getCamera()->pitch(Ogre::Radian((msevent.GetY()-currentY) * -0.001f));
            currentY = msevent.GetY();
        }
    }
    if(msevent.Moving())
    {
        currentX = msevent.GetX();
        currentY = msevent.GetY();
    }
}

//================================================================================= scrollWheel()//
void wxOgreViewEventHandler::scrollWheel(wxMouseEvent& msevent)
{
    //move Camera in z-direction
    mpRenderWindow->getViewport(0)->getCamera()
    ->moveRelative(Ogre::Vector3(0.0f,0.0f,msevent.GetWheelRotation() * -0.005f));
}
