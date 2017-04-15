///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Nov  6 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
    
    m_menuBar = new wxMenuBar( 0 );
    m_menuFile = new wxMenu();
    wxMenuItem* menuFileExit;
    menuFileExit = new wxMenuItem( m_menuFile, wxID_EXIT, wxString( _("E&xit") ) + wxT('\t') + wxT("Alt+X"), wxEmptyString, wxITEM_NORMAL );
    m_menuFile->Append( menuFileExit );
    
    m_menuBar->Append( m_menuFile, _("&File") ); 
    
    this->SetMenuBar( m_menuBar );
    
    mTimer.SetOwner( this, wxID_ANY );
    wxBoxSizer* mainSizer;
    mainSizer = new wxBoxSizer( wxVERTICAL );
    
    mRenderPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    mainSizer->Add( mRenderPanel, 1, wxEXPAND | wxALL, 5 );
    
    
    this->SetSizer( mainSizer );
    this->Layout();
    m_statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
    
    this->Centre( wxBOTH );
    
    // Connect Events
    this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
    this->Connect( menuFileExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnExitClick ) );
    this->Connect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( MainFrameBase::OnTimerFire ) );
}

MainFrameBase::~MainFrameBase()
{
    // Disconnect Events
    this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrameBase::OnCloseFrame ) );
    this->Disconnect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrameBase::OnExitClick ) );
    this->Disconnect( wxID_ANY, wxEVT_TIMER, wxTimerEventHandler( MainFrameBase::OnTimerFire ) );
    
}

