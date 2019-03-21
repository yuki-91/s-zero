//-----------------------------------//
//-----ÉÇÅ[ÉhÉâÉìÉLÉìÉOèàóù-----------//
//--------[ranking.h]-------------//
//------Author:é¬ã{ óCãG-------------//
//-----------------------------------//
#ifndef _MODERANKING_H_
#define _MODERANKING_H_
#include"mode.h"
#include "score.h"

enum TEXTURE_RANK_ENUM
{
	TEXTURE_RANK_NULL = -1,
	TEXTURE_RANK1,
	TEXTURE_IN,
	TEXTURE_NOT,
	TEXTURE_RANK_MAX
};

typedef struct
{
	char fileName[256];
}TEXTURE_RANK;

static const TEXTURE_RANK g_aTexture_Rank[] =
{
	{ "data/texture/result.png" },
	{ "data/texture/new_record.png" },
	{ "data/texture/not_ranked.png" },
};

class CModeRanking :public CMode
{
private:
	static CScore *m_Score2;
	LPDIRECT3DDEVICE9  pDevice;
	static int wall_xy;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	//void GetScore(int score);

};
#endif 
