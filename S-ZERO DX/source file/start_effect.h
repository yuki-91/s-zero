//-----------------------------------//
//------îöî≠ï`âÊèàóù--[explosion.h]--//
//-----------------------------------//
//------Author:é¬ã{ óCãG-------------//
//-----------------------------------//
#ifndef _STARTEXPLOSION_H_
#define _STARTEXPLOSION_H_
#include "main.h"
#define START_EXPLOSION_MAX (300)

enum TEXTURE_ENUM6
{
	START_EXPLOSION_TEX_NULL = -1,
	START_EXPLOSION_TEX,
	START_EXPLOSION_TEX_MAX
};

typedef struct
{
	char fileName[256];
	int width;
	int height;

	float Xsize;
	float Ysize;

	int Xcount;

	int Acount;

}TEXTURE_START_EXPLOSION;

static const TEXTURE_START_EXPLOSION Texture_Start_effect[] =
{
	{ "data/texture/êÖ1.png",			960, 768, 192, 192, 5, 19 }
};

typedef struct
{
	bool bUse;

	int nAnimCount;

	int color;

	D3DXVECTOR3 pos;
}START_EXPLOSION;

class CStEffect {
public:
	static void InitStart_effect(void);
	static void UninitStart_effect(void);
	static void UpdateStart_effect(void);
	static void DrawStart_effect(void);
	static void CreateStart_effect(float x, float y, float z);
};
#endif 
