//-----------------------------------//
//----------シーン処理---------------//
//----------[scene.h]--------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"
#include <d3d9.h>
#include <d3dx9.h> 

class CScene
{
protected:
	D3DXVECTOR3 m_Position;
	LPDIRECT3DDEVICE9 m_Device;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DTEXTURE9 m_Texture;
private:
	static CScene *m_Scene[10];
public:
	CScene();
	virtual ~CScene();
	virtual void Init() {};//仮想関数
	virtual void Uninit() = 0;//純粋仮想関数
	virtual void Update() = 0;
	virtual void Draw() = 0;
	void Release();
	static void UpdateAll();
	static void DrawAll();
	static void UninitAll();
	void SetPostion(D3DXVECTOR3 Pos);
	
};
#endif 
