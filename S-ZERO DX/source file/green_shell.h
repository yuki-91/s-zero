#pragma once


#ifndef _BULLET_H_
#define _BULLET_H_

#define BULLET_MAX		(50)
#define BULLET_LIFE		(50)

typedef struct
{
	bool bUse;			//�g�p

	D3DXVECTOR3 vPos;	//�ʒu

	D3DXVECTOR3 vDir;	//����

	int color;			//�F

	int nLife;			//�g���Ă��鎞�ԁE����

}BULLET;

enum TEXTURE_ENUM_BULLET
{
	TEXTURE_BULLET_NULL = -1,
	TEXTURE_BULLET_TAMA_BLUE,
	TEXTURE_BULLET_TAMA_RED,
	TEXTURE_BULLET_TAMA_GREEN,
	TEXTURE_BULLET_SHADOW,
	TEXTURE_BULLET_MAX
};

typedef struct
{
	char fileName[256];
}TEXTURE_BULLET;

static const TEXTURE_BULLET g_aTexture_Bullet[] =
{
	{ "data/texture/03830a7e38159ea2093564140a50b928.png" },
	{ "data/texture/03830a7e38159ea2093564140a50b928.png" },
	{ "data/texture/03830a7e38159ea2093564140a50b928.png" },
	{ "data/texture/shadow000.jpg" },

};


//-------------------------------------------------------------------
//�@�v���g�^�C�v�錾
//-------------------------------------------------------------------

bool InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void CreateBullet(float radian, int color);
void DestroyBullet(int num);

void CreateBulletShadow();

D3DXVECTOR3 GetBulletPos(int num);

int *GetBulletColor(int BulletNumber);

bool *GetBulletUse(int b);

D3DXVECTOR3 *StockColor();

#endif // !_BULLET_H_



