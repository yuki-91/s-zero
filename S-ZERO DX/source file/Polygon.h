//-----------------------------------//
//----ポリゴン描画処理--[Polygon.h]--//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _POLYGON_H2_
#define _POLYGON_H2_

#include "d3d9.h"


#define ARRAYCOUNT(x) sizeof(x)/sizeof(x[0])

class CPolygon {
public:
	static bool PolygonInit2(void); //ポリゴンの初期処理
	static void PolygonUninit2(void);//ポリゴンの終了処理
	static void PolygonUpdate2(void);//ポリゴンの更新処理
	static void SetPolygonScale2(float cx, float cy, float sx, float sy);
	static void SetPolygonRotation2(float cx, float cy, float angle);
	static void PolygonDraw2(int texnum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tw, int th, int tcx, int tcy, int tcw, int tch, bool bAffine = false);//ポリゴンの描画処理
	static void CreateVertex(int texnum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tw, int th, int tcx, int tcy, int tcw, int tch);
	static void CreateVertexAffine(int texnum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tw, int th, int tcx, int tcy, int tcw, int tch);
private:
	static LPDIRECT3DDEVICE9 m_pDevice;
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;
	static float g_fAngle ;
	static float g_fRotationOffsetX;
	static float g_fRotationOffsetY;
	static float g_fScaleX;
	static float g_fScaleY;
	static float g_fScaleOffsetX;
	static float g_fScaleOffsetY;
	static float g_uv;
	static float g_fScale;
	static float g_fScaleAdd ;
};
#endif // _POLYGON_H_#pragma once
