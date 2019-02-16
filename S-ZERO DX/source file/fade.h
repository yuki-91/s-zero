//-----------------------------------//
//------ÉtÉFÅ[Éhèàóù [Fade.h]------//
//-----------------------------------//
//------Author:é¬ã{ óCãG-------------//
//-----------------------------------//
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"

class CFade {
public:
	static void InitFade();
	static void UninitFade();
	static void CreateFade(int count, bool out, bool pose);
private:
	static LPDIRECT3DTEXTURE9 g_Textures_Fade;
	static LPDIRECT3DTEXTURE9 g_Textures_Pose;
	static LPDIRECT3DTEXTURE9 g_Textures_Back;
	static int g_nFramecount;
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;

};
#endif