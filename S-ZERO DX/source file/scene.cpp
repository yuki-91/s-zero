//-----------------------------------//
//----------ÉVÅ[Éìèàóù---------------//
//----------[scene.cpp]--------------//
//------Author:é¬ã{ óCãG-------------//
//-----------------------------------//
#include "scene.h"
#define CSENE (10)
CScene *CScene::m_Scene[CSENE] = {NULL};

CScene::CScene() 
{
	for (int i = 0; i < CSENE; i++)
	{
		if (m_Scene[i] == NULL)
		{
			m_Scene[i] = this;
			break;
		}
	}
}

CScene::~CScene()
{
}

void CScene::Release()
{
	for (int i = 0; i < CSENE; i++)
	{
		if (m_Scene[i] == NULL)
		{
			Uninit();
			delete this;
			break;
		}
	}
}

void CScene::UpdateAll()
{
	for (int i = 0; i < CSENE; i++)
	{
		if (m_Scene[i] != NULL)
		{
			m_Scene[i]->Update();

		}
	}
}

void CScene::DrawAll()
{
	for (int i = 0; i < CSENE; i++)
	{
		if (m_Scene[i] != NULL)
		{
			m_Scene[i]->Draw();
		}
	}
}

void CScene::UninitAll()
{
	for (int i = 0; i < CSENE; i++)
	{
		if (m_Scene[i] != NULL)
		{
			m_Scene[i]->Uninit();
			m_Scene[i] = nullptr;
			delete m_Scene[i];
		}
	}
}

void CScene::SetPostion(D3DXVECTOR3 Pos)
{
	m_Position = Pos;
}
