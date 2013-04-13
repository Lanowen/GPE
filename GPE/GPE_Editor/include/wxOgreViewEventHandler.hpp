/// Subclass of wxOgreView implementing some mouse events.
/** The wxOgreViewEventHandler class extends wxOgreView. It defines two mouse
    event functions to interact with the corresponding render window. You can
    modify or add some event functions to get the appropriate behaviour for
    your own application.
*/

#pragma once

#include <wxOgreView.hpp>

class wxOgreViewEventHandler : public wxOgreView
{
    ///Event table for the mouse events
    DECLARE_EVENT_TABLE();
    /// The mouse dragging event
    /** This event function moves the camera in dependency of mouse coordinates,
        while the mouse is dragged over the render window.
        @param event a mouse event. */
    void MouseDragged(wxMouseEvent& msevent);
    /// The scroll wheel event
    /** This event function is used to zoom into or out of the scene.
        @param event a mouse event. */
    void scrollWheel(wxMouseEvent& msevent);

public:
    ///Constructor
    /** @param parent pointer to a parent window.
        @param id pointer to a parent window.
        @param pos Window position. wxDefaultPosition indicates that wxWidgets should generate a default
               position for the window. If using the wxWindow class directly, supply an actual position.
        @param size Window size. wxDefaultSize indicates that wxWidgets should generate a default size
               for the window. If no suitable size can be found, the window will be sized to 20x20 pixels
               so that the window is visible but obviously not correctly sized.
        @param style Window style. For generic window styles, please see wxWindow.
        @param validator pointer to a pvalidator.
        @param name wxOgreView name. */
    wxOgreViewEventHandler (wxWindow* parent,
                            wxWindowID id = -1,
                            const wxPoint &pos=wxDefaultPosition,
                            const wxSize &size=wxDefaultSize,
                            long style=0,
                            const wxValidator& validator = wxDefaultValidator,
                            const wxString &name=wxPanelNameStr);

};
