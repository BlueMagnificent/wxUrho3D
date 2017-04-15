#ifndef __wxurho3d_h_
#define __wxurho3d_h_

//MainFrameBase include header
#include "gui.h"

//Urho3D includes
#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Precompiled.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/IO/IOEvents.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Viewport.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Core/ProcessUtils.h>
#include <Urho3D/Engine/DebugHud.h>
#include <Urho3D/Resource/XMLFile.h>

using namespace Urho3D;

enum CameraPosition
{
    CAM_FRONT = 100,
    CAM_BACK,
    CAM_RIGHT,
    CAM_LEFT,
    CAM_UP,
    CAM_DOWN
};



class wxUrho3D : public MainFrameBase, public Urho3D::Object
{
    URHO3D_OBJECT(wxUrho3D, Urho3D::Object)
    
    public:
        wxUrho3D( wxWindow *parent, Urho3D::Context* context );
    virtual ~wxUrho3D();
    
    //Handle Update Event
    void HandleUpdate(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void HandleKeyDown(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);
    void HandleMouseMove(Urho3D::StringHash eventType, Urho3D::VariantMap &eventData);

    //Handle Events wxWidgets
    void OnRenderPanelMouseEnter( wxMouseEvent& event );
    void OnRenderPanelMouseLeave( wxMouseEvent& event );
    
protected:

    //Setup Urho3D
    void SetupUrho3D();
    
    //Create The Scene
    void CreateScene();
    
    //Setup Rendering Viewport
    void SetupViewport();
    
    //Subscribe to Events
    void SubscribeToEvents();

    //Orbit Camera
    void SetupOrbitingCam();
    void UpdateOrbitingCam();
    void SetCameraPosition(CameraPosition pos);

    //Render Urho3D Frame
    void RenderUrho3DFrame();
    
    void OnKeyPressed(int key);


    //wxWidgets Frame Close Handler
    virtual void OnCloseFrame( wxCloseEvent& event );
    //Exit Menu Clicked Handler
    virtual void OnExitClick( wxCommandEvent& event );
    //Timer Fired Handler
    virtual void OnTimerFire( wxTimerEvent& event );

    bool mHasFocus;

    Urho3D::SharedPtr<Urho3D::Context> context_;
    Urho3D::SharedPtr<Urho3D::Engine> engine_;
    Urho3D::SharedPtr<Urho3D::Scene> scene_;

    Urho3D::SharedPtr<Urho3D::Node> cameraNode_;
    Urho3D::SharedPtr<Urho3D::Node> camPitchNode_;
    Urho3D::SharedPtr<Urho3D::Node> camYawNode_;
    Urho3D::SharedPtr<Urho3D::Node> camBaseNode_;


    
};


#endif // #ifndef __wxurho3d_h_

