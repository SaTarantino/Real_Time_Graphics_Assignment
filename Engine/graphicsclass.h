////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "d3dclass.h"
#include "timerclass.h"
#include "shadermanagerclass.h"
#include "positionclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "modelclass.h"
#include "bumpmodelclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 10000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	//bool Render(float);
	//Xu
	bool HandleMovementInput(float);
	bool Render();

private:
	InputClass* m_Input;
	D3DClass* m_D3D;
	TimerClass* m_Timer;
	ShaderManagerClass* m_ShaderManager;
	PositionClass* m_Position;
	CameraClass* m_Camera;
	LightClass* m_Light;
	ModelClass* m_TerrainModel;
	ModelClass* m_SkyDomes;
	ModelClass* m_AirplaneModel;
	ModelClass* m_ControlTower;
	ModelClass* m_AirfieldModel;
	ModelClass* m_Drone;
	ModelClass* m_BigBuilding;
	ModelClass* m_PredatorModel;
};

#endif