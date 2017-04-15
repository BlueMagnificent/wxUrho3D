#include "wxUrho3D.h"

using namespace Urho3D;

wxUrho3D::wxUrho3D(wxWindow *parent, Urho3D::Context *context) : MainFrameBase( parent )
  , Urho3D::Object(context)
  , context_(context)
{
    SetupUrho3D();

    mRenderPanel->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( wxUrho3D::OnRenderPanelMouseEnter ), NULL, this );
    mRenderPanel->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( wxUrho3D::OnRenderPanelMouseLeave ), NULL, this );

    mHasFocus = false;

    mTimer.Start(30);
}

wxUrho3D::~wxUrho3D()
{

}

void wxUrho3D::OnCloseFrame(wxCloseEvent& event)
{
    mTimer.Stop();
    engine_->Exit();

    mRenderPanel->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( wxUrho3D::OnRenderPanelMouseEnter ), NULL, this );
    mRenderPanel->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( wxUrho3D::OnRenderPanelMouseLeave ), NULL, this );

    Destroy();
}


void wxUrho3D::SetupUrho3D()
{
    engine_ = new Engine(context_);

    VariantMap engineParameters_;

    engineParameters_["ResourcePaths"] = "Data;CoreData";
    engineParameters_["LogName"]   = "wxUrho3D.log";
    engineParameters_["ExternalWindow"] = mRenderPanel->GetHandle();
    engineParameters_["FullScreen"]  = false;
    engineParameters_["WindowResizable"] = true;

    engine_->Initialize(engineParameters_);

    ResourceCache* cache = GetSubsystem<ResourceCache>();
    XMLFile* xmlFile = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");

    DebugHud* dbg = engine_->CreateDebugHud();
    dbg->SetDefaultStyle(xmlFile);

    CreateScene();
    SetupOrbitingCam();
    SetupViewport();

    SubscribeToEvents();
}

void wxUrho3D::RenderUrho3DFrame()
{
    if(engine_ && !engine_->IsExiting())
        engine_->RunFrame();
}


void wxUrho3D::CreateScene()
{
    ResourceCache* cache = GetSubsystem<ResourceCache>();
    scene_ = new Scene(context_);

    scene_->CreateComponent<Octree>();

    Node* planeNode = scene_->CreateChild("Plane");
    planeNode->SetScale(Vector3(100.0f, 1.0f, 100.0f));

    StaticModel* planeObject = planeNode->CreateComponent<StaticModel>();
    planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml"));

    Node* modelNode = scene_->CreateChild("ModelNode");
    modelNode->SetScale(0.3f);

    StaticModel* model = modelNode->CreateComponent<StaticModel>();
    model->SetModel(cache->GetResource<Model>("Models/Mushroom.mdl"));
    model->SetMaterial(cache->GetResource<Material>("Materials/Mushroom.xml"));


    Node* lightNode = scene_->CreateChild("DirectionalLightNode");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));


    Light* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetCastShadows(true);

}

void wxUrho3D::SetupOrbitingCam()
{
    camBaseNode_ = scene_->CreateChild("Base Cam Node");
    camYawNode_ = camBaseNode_->CreateChild("Cam Yaw Node");
    camPitchNode_ = camYawNode_->CreateChild("Cam Pitch Node");

    cameraNode_ = camPitchNode_->CreateChild("Cam Node");
    cameraNode_->CreateComponent<Camera>();

    cameraNode_->Translate(Vector3(0,0,-10));
}


void wxUrho3D::SetupViewport()
{
    Renderer* renderer = GetSubsystem<Renderer>();

    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0,viewport);
}

void wxUrho3D::SubscribeToEvents()
{
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(wxUrho3D, HandleUpdate));
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(wxUrho3D, HandleKeyDown));
    SubscribeToEvent(E_MOUSEMOVE, URHO3D_HANDLER(wxUrho3D, HandleMouseMove));
}


void wxUrho3D::HandleUpdate(StringHash eventType, VariantMap &eventData)
{
    UpdateOrbitingCam();
}

void wxUrho3D::HandleKeyDown(StringHash eventType, VariantMap &eventData)
{
    if(!mHasFocus)
        return;

    using namespace Urho3D::KeyDown;
    int key = eventData[P_KEY].GetInt();

    OnKeyPressed(key);

}

void wxUrho3D::HandleMouseMove(StringHash eventType, VariantMap &eventData)
{
    using namespace Urho3D::MouseMove;
    int dx = eventData[P_DX].GetInt();
    int dy = eventData[P_DY].GetInt();

    Input* input = GetSubsystem<Input>();

    float dist;

    if(input->GetMouseButtonDown(MOUSEB_LEFT))
    {
        if(input->GetKeyDown(KEY_ALT) && input->GetKeyDown(KEY_SHIFT))
        {
            //Pan around the Screen
            dist = (cameraNode_->GetPosition().Length()) / 2000;
            Matrix3 rotationMatrix = cameraNode_->GetWorldTransform().RotationMatrix();

            Vector3 direction = rotationMatrix * Vector3(dx * -dist, dy * dist,0);


            camBaseNode_->Translate(direction);

        }
        else if(input->GetKeyDown(KEY_ALT))
        {
            //Orbit at a pivot
            camPitchNode_->Pitch(dy * 0.25f);
            camYawNode_->Yaw(dx * 0.25f);

        }

        RenderUrho3DFrame();
    }
}

void wxUrho3D::OnRenderPanelMouseEnter(wxMouseEvent &event)
{
    mHasFocus = true;
}

void wxUrho3D::OnRenderPanelMouseLeave(wxMouseEvent &event)
{
    mHasFocus = false;
}


void wxUrho3D::OnKeyPressed(int key)
{
    Input* input = GetSubsystem<Input>();
    bool ctrlDown = input->GetKeyDown(KEY_CTRL);

    switch(key)
    {
    case '1':
        SetCameraPosition(ctrlDown ? CAM_BACK : CAM_FRONT);
        break;

    case '3':
        SetCameraPosition(ctrlDown ? CAM_LEFT : CAM_RIGHT);
        break;

    case '7':
        SetCameraPosition(ctrlDown ? CAM_UP :  CAM_DOWN );
        break;

    case KEY_F2:
        GetSubsystem<DebugHud>()->ToggleAll();

    }
}


void wxUrho3D::UpdateOrbitingCam()
{
    Input* input = GetSubsystem<Input>();

    if(input->GetMouseMoveWheel() != 0)
    {
        cameraNode_->Translate(Vector3(0,0,input->GetMouseMoveWheel() * 0.3));
    }
    //In Forward and Backwards movement in case of laptop touchpad
    else if(input->GetKeyDown('W'))
    {
        cameraNode_->Translate(Vector3(0,0,0.07f));
    }
    else if(input->GetKeyDown('S'))
    {
        cameraNode_->Translate(Vector3(0,0,-0.07f));
    }
}

void wxUrho3D::SetCameraPosition(CameraPosition pos)
{
    camPitchNode_->SetRotation(Quaternion(0.0f,0.0f,0.0f));
    camYawNode_->SetRotation(Quaternion(0.0f,0.0f,0.0f));

    switch(pos)
    {
    //case CAM_FRONT:
    //there is no need for this since the cam is already
    //positioned at CAM_FRONT after the orientation of the cam nodes are
    //reset

    case CAM_BACK:
        camYawNode_->Yaw(180);
        break;
    case CAM_RIGHT:
        camYawNode_->Yaw(-90);
        break;
    case CAM_LEFT:
        camYawNode_->Yaw(90);
        break;
    case CAM_UP:
        camPitchNode_->Pitch(-90);
        break;
    case CAM_DOWN:
        camPitchNode_->Pitch(90);
        break;

    }
}


void wxUrho3D::OnExitClick(wxCommandEvent& event)
{
    Close();
}

void wxUrho3D::OnTimerFire(wxTimerEvent &event)
{
    RenderUrho3DFrame();
}






