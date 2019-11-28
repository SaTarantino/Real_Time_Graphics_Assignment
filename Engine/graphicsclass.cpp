////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Timer = 0;
	m_ShaderManager = 0;
	m_Light = 0;
	m_Position = 0;
	m_Camera = 0;
	m_TerrainModel = 0;
	m_Delta747Model = 0;
	m_ControlTower = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(0.0f, 0.0f, -10.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(64.0f);

	// Create and Initialize the Terrain model.
	m_TerrainModel = new ModelClass;
	if(!m_TerrainModel)
	{
		return false;
	}

	result = m_TerrainModel->Initialize(m_D3D->GetDevice(), "../Engine/data/terrainModel.txt", L"../Engine/data/grass2.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the Terrain model.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the Delta 747 Model.
	m_Delta747Model = new ModelClass;
	if(!m_Delta747Model)
	{
		return false;
	}

	result = m_Delta747Model->Initialize(m_D3D->GetDevice(), "../Engine/data/Airliner757.txt", L"../Engine/data/metal.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the Delta 747 model.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the Control Tower model.
	m_ControlTower = new ModelClass;
	if(!m_ControlTower)
	{
		return false;
	}

	result = m_ControlTower->Initialize(m_D3D->GetDevice(), "../Engine/data/controlTower.txt", L"../Engine/data/controlTowerTexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Control Tower model.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the Airfield model.
	m_AirfieldModel = new ModelClass;
	if (!m_AirfieldModel)
	{
		return false;
	}

	result = m_AirfieldModel->Initialize(m_D3D->GetDevice(), "../Engine/data/bigAirfieldModel.txt", L"../Engine/data/airfieldTexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Airfield model.", L"Error", MB_OK);
		return false;
	}


	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the model objects.
	if(m_TerrainModel)
	{
		m_TerrainModel->Shutdown();
		delete m_TerrainModel;
		m_TerrainModel = 0;
	}

	if(m_Delta747Model)
	{
		m_Delta747Model->Shutdown();
		delete m_Delta747Model;
		m_Delta747Model = 0;
	}

	if(m_ControlTower)
	{
		m_ControlTower->Shutdown();
		delete m_ControlTower;
		m_ControlTower = 0;
	}

	if (m_AirfieldModel)
	{
		m_AirfieldModel->Shutdown();
		delete m_AirfieldModel;
		m_AirfieldModel = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	// Update the system stats.
	m_Timer->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovementInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::HandleMovementInput(float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsAPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsDPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsWPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsSPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsIPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsKPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsUPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsOPressed();
	m_Position->LookDownward(keyDown);

	/*keyDown = m_Input->IsJPressed();
	m_Position->MoveLeft(keyDown);*/

	/*keyDown = m_Input->IsLPressed();
	m_Position->LookDownward(keyDown);*/

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	return true;
}

bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	XMMATRIX airplaneScale = XMMatrixScaling(0.45f, 0.45f, 0.45f);
	bool result;

	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.0005f * m_Timer->GetTime();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);



	// Setup the rotation and translation of the Terrain model.
	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixScaling(10.f, 10.f, 10.5f);

	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the Terrain model using the texture shader.
	m_TerrainModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_TerrainModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_TerrainModel->GetTexture());
	if(!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Delta 747 model.
	m_D3D->GetWorldMatrix(worldMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, airplaneScale);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(-3.0f, 0.0f, 0.0f));

	// Move the Delta 747 model. 
	translateMatrix = XMMatrixTranslation(-3.5f, 10.0f + sin(timeGetTime() / 500.0f), 10.0f + sin(timeGetTime() / 500.0f));
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);
	
		
	// Render the Delta 747 using the light shader.
	m_Delta747Model->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Delta747Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
									   m_Delta747Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
									   m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	
	// Setup the rotation and translation of the Control Tower model.
	m_D3D->GetWorldMatrix(worldMatrix);

	translateMatrix = XMMatrixTranslation(50.0f, 0.0f, 0.0f);
	
	worldMatrix = XMMatrixScaling(1.5f, 1.5f, 1.5f);

	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the Control Tower model.
	m_ControlTower->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_ControlTower->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
										m_ControlTower->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
										m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Airfield model.
	m_D3D->GetWorldMatrix(worldMatrix);
	translateMatrix = XMMatrixTranslation(-3.0f, 0.05f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the Airfield model.
	m_AirfieldModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_AirfieldModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_AirfieldModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}