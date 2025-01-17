////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include "directxmath.h"


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
	m_AirplaneModel = 0;
	m_ControlTower = 0;
	m_AirfieldModel = 0;
	m_Drone = 0;
	m_BigBuilding = 0;
	m_PredatorModel = 0;
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
	m_Position->SetPosition(1.0f, 15.0f, -200.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

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

	result = m_TerrainModel->Initialize(m_D3D->GetDevice(), "../Engine/data/terrainModel.txt", L"../Engine/data/lol.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the Terrain model.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the Sky-Domes model.
	m_SkyDomes = new ModelClass;
	if (!m_SkyDomes)
	{
		return false;
	}

	result = m_SkyDomes->Initialize(m_D3D->GetDevice(), "../Engine/data/skyDome.txt", L"../Engine/data/skyTexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Sky-Domes model.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the Airplane Model.
	m_AirplaneModel = new ModelClass;
	if(!m_AirplaneModel)
	{
		return false;
	}

	result = m_AirplaneModel->Initialize(m_D3D->GetDevice(), "../Engine/data/tal16.txt", L"../Engine/data/tal512.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the Tal 16 model.", L"Error", MB_OK);
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

	result = m_AirfieldModel->Initialize(m_D3D->GetDevice(), "../Engine/data/airfieldModel.txt", L"../Engine/data/airfieldTexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Airfield model.", L"Error", MB_OK);
		return false;
	}

	// Create and Inizialize the Big Building model.
	m_BigBuilding = new ModelClass;
	if (!m_BigBuilding)
	{
		return false;
	}

	result = m_BigBuilding->Initialize(m_D3D->GetDevice(), "../Engine/data/bigBuilding.txt", L"../Engine/data/bigBuildingTextures.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Big Building model.", L"Error", MB_OK);
		return false;
	}

	// Create and Inizialize the Drone model.
	m_Drone = new ModelClass;
	if (!m_Drone)
	{
		return false;
	}

	result = m_Drone->Initialize(m_D3D->GetDevice(), "../Engine/data/smallDrone.txt", L"../Engine/data/smallDroneTexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Drone model.", L"Error", MB_OK);
		return false;
	}

	// Create and Inizialize the Predator model.
	m_PredatorModel = new ModelClass;
	if (!m_PredatorModel)
	{
		return false;
	}

	result = m_PredatorModel->Initialize(m_D3D->GetDevice(), "../Engine/data/predator.txt", L"../Engine/data/predatorTexture.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Predator model.", L"Error", MB_OK);
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

	if (m_SkyDomes)
	{
		m_SkyDomes->Shutdown();
		delete m_SkyDomes;
		m_SkyDomes = 0;
	}

	if(m_AirplaneModel)
	{
		m_AirplaneModel->Shutdown();
		delete m_AirplaneModel;
		m_AirplaneModel = 0;
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

	if (m_BigBuilding)
	{
		m_BigBuilding->Shutdown();
		delete m_BigBuilding;
		m_BigBuilding = 0;
	}

	if (m_Drone)
	{
		m_Drone->Shutdown();
		delete m_Drone;
		m_Drone = 0;
	}

	if (m_PredatorModel)
	{
		m_PredatorModel->Shutdown();
		delete m_PredatorModel;
		m_PredatorModel = 0;
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

	keyDown = m_Input->IsLPressed();
	m_Position->LookDownward(keyDown);

	keyDown = m_Input->IsJPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsF1Pressed();
	m_Position->Camera1(keyDown);

	keyDown = m_Input->IsF2Pressed();
	m_Position->Camera2(keyDown);

	keyDown = m_Input->IsF3Pressed();
	m_Position->Camera0(keyDown);

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
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix, scalingMatrix, orbitMatrix;
	XMFLOAT3 cameraPosition;
	
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

	// Get the position of the camera
	cameraPosition = m_Camera->GetPosition();
	

	// Setup the rotation and translation of the Sky-Domes model.
	worldMatrix = XMMatrixScaling(100.f, 100.f, 100.f);
	
	// Render the Sky-Domes model using the texture shader.
	m_SkyDomes->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_SkyDomes->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
												m_SkyDomes->GetTexture());
	if (!result)
	{
		return false;
	}


	// Setup the rotation and translation of the Terrain model.
	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the Terrain model using the texture shader.
	m_TerrainModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_TerrainModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_TerrainModel->GetTexture());
	if(!result)
	{
		return false;
	}


	// Setup the rotation, translation and movement of the Airplane model.
	m_D3D->GetWorldMatrix(worldMatrix);

	orbitMatrix = XMMatrixRotationY(rotation * 0.5); // moltiply or divide for an x value for decrease or increase the speed of the orbit

	translateMatrix = XMMatrixTranslation(500.0f, 500.0f, 0.0f);
	
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, orbitMatrix);
		
	// Render the Delta 747 using the light shader.
	m_AirplaneModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_AirplaneModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
									   m_AirplaneModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
									   m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}
	

	// Setup the rotation and translation of the Control Tower model.
	m_D3D->GetWorldMatrix(worldMatrix);

	translateMatrix = XMMatrixTranslation(-100.0f, 0.0f, 50.0f);
	
	worldMatrix = XMMatrixScaling(4.f, 4.f, 4.f);
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

	translateMatrix = XMMatrixTranslation(-3.0f, 1.f, 0.0f);
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


	// Setup the rotation and translation of the Big Building model.
	m_D3D->GetWorldMatrix(worldMatrix);

	translateMatrix = XMMatrixTranslation(300.0f, 0.f, 500.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the Big Building model.
	m_BigBuilding->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_BigBuilding->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
										m_BigBuilding->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
										m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}


	// Setup the rotation and translation of the Drone model.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Pass the camera position at the translate matrix.
	translateMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y + 50, cameraPosition.z);
	orbitMatrix = XMMatrixRotationY(rotation * 0.5);

	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Make the Drone model rotate from the starting point to the camera position.
	worldMatrix = XMMatrixMultiply(translateMatrix, orbitMatrix);

	// Render the Drone model.
	m_Drone->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Drone->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
										m_Drone->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
										m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Setup the rotation and translation of the Predator model.
	m_D3D->GetWorldMatrix(worldMatrix);

	translateMatrix = XMMatrixTranslation(-3.0f, 0.9f, 10.0f);
	worldMatrix = XMMatrixScaling(0.1f, 0.1f, 0.1f);
	orbitMatrix = XMMatrixRotationY(rotation * 1);

	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, orbitMatrix);

	// Render the Predetor model.
	m_PredatorModel->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_PredatorModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
										m_PredatorModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
										m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}


	// Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}