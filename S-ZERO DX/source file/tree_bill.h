//-----------------------------------//
//-----�؃r���{�[�h����--------------//
//----[tree_bill.h]----------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
#ifndef _TREEBILL_H_
#define _TREEBILL_H_
#define MAX_TREEBILLBOARD (159)	//�r���{�[�h�̌�
#define FVF_VERTEX_TREE (D3DFVF_XYZ|D3DFVF_DIFFUSE | D3DFVF_TEX1 )
enum TEXTURE_TREE_ENUM
{
	TEXTURE_TREE_NULL = -1,
	TEXTURE_TREE_1,
	TEXTURE_TREE_2,
	TEXTURE_TREE_3,
	TEXTURE_TREE_4,
	TEXTURE_TREE_5,
	TEXTURE_TREE_6,
	TEXTURE_TREE_7,
	TEXTURE_TREE_8,
	TEXTURE_TREE_9,
	TEXTURE_TREE_MAX
};
//-----------------------------------//
//-----�؃r���{�[�h����--------------//
//----[tree_bill.h]----------------//
//------Author:�{ �C�G-------------//
//-----------------------------------//
typedef struct
{
	char fileName[256];
}TEXTURE_TREE;

static const TEXTURE_TREE g_aTexture_t[] =
{
	{ "data/texture/tree001.png" },
	{ "data/texture/tree002.png" },
	{ "data/texture/tree003.png" },
	{ "data/texture/tree004.png" },
	{ "data/texture/tree005.png" },
	{ "data/texture/tree006.png" },
	{ "data/texture/weed001.png" },
	{ "data/texture/weed002.png" },
	{ "data/texture/weed003.png" }
};
class CTreeBill {
public:
	static bool InitTreeBill();
	static void UninitTreeBill();
	static void UpdateTreeBill();
	static void DrawTreeBill();
private:
	static LPDIRECT3DTEXTURE9 g_pTextures_bill[TEXTURE_TREE_MAX];	//�e�N�X�`���z��
	static D3DXMATRIX g_mtxWorld_TreeBill;		//���[���h�ϊ��s��
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer ;		// �o�[�e�b�N�X�o�b�t�@�̃|�C���^
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer ;		// �C���f�b�N�X�o�b�t�@�̃|�C���^
	static void VertexBuffer_Field();
	static void IndexBuffer_Field();
	static D3DXMATRIX g_viewInverse;
	static D3DXMATRIX g_Trans, g_Rotation;
	static D3DXVECTOR3 g_TransPos[MAX_TREEBILLBOARD];
	static int color[MAX_TREEBILLBOARD];
	static bool ememy[MAX_TREEBILLBOARD];
	static int Life[MAX_TREEBILLBOARD];
	static float  g_Rot3 ;
};
#endif 
