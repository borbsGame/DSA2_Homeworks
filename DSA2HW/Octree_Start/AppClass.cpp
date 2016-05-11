#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Sandbox"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
	//m_pSystem->SetWindowResolution(RESOLUTIONS::HD_1280X720);
	//m_pSystem->SetWindowFullscreen(); //Sets the window to be fullscreen
	//m_pSystem->SetWindowBorderless(true); //Sets the window to not have borders
}

void AppClass::InitVariables(void)
{
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What Im looking at
		REAXISY);//What is up

	optimizationSwitch = false;

	m_pBOMngr = MyBOManager::GetInstance();

	//Load a model onto the Mesh manager
	for (uint i = 0; i < 50; i++)
	{
		String sName = "Creeper" + std::to_string(i);
		vector3 v3Position = glm::sphericalRand(10.0f);
		m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", sName, false, glm::translate(v3Position + vector3(5.0f,0,0)));
		m_pBOMngr->AddObject(sName);
	}

	m_pOctreeHead = new MyOctant();
	m_pOctreeHead->Subdivide();

	/*
	for (int i = 0; i < 8; i++)
	{
		m_pOctreeHead->m_pChildren[i].Subdivide();
	}
	*/

}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
	
	//Set the model matrix for the first model to be the arcball
	m_pMeshMngr->SetModelMatrix(ToMatrix4(m_qArcBall), 0);
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	if (optimizationSwitch)
	{
		m_pMeshMngr->Print("OPTIMIZED\n");
		for (int i = 0; i < 8; i++)
		{
			m_pOctreeHead->m_pChildren[i].Display();
		}
	}
	else
	{
		m_pMeshMngr->Print("BRUTE FORCE\n");

		m_pBOMngr->Update();
	}
	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("Selection: ");
	m_pMeshMngr->PrintLine(m_pMeshMngr->GetInstanceGroupName(m_selection.first, m_selection.second), REYELLOW);
	
	m_pMeshMngr->Print("FPS: ");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ResetRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	/*m_pOctreeHead->DestroyOctant();
	SafeDelete(m_pOctreeHead);*/
	if (m_pOctreeHead != nullptr)
	{
		delete m_pOctreeHead;
		m_pOctreeHead = nullptr;
	}
	super::Release(); //release the memory of the inherited fields
}