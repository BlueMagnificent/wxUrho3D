///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Nov  6 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUI_H__
#define __GUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/timer.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame 
{
private:
    
protected:
    wxMenuBar* m_menuBar;
    wxMenu* m_menuFile;
    wxTimer mTimer;
    wxPanel* mRenderPanel;
    wxStatusBar* m_statusBar;
    
    // Virtual event handlers, overide them in your derived class
    virtual void OnCloseFrame( wxCloseEvent& event ) { event.Skip(); }
    virtual void OnExitClick( wxCommandEvent& event ) { event.Skip(); }
    virtual void OnTimerFire( wxTimerEvent& event ) { event.Skip(); }
    
    
public:
    
    MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("WxUrho3D_MinGW Window"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
    
    ~MainFrameBase();
    
};

#endif //__GUI_H__

