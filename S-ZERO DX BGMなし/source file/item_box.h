//-----------------------------------//
//---アイテムボックス-[item_box.cpp]-//
//-----------------------------------//
//------Author:篠宮 佑季-------------//
//-----------------------------------//
#ifndef _ITEMBOX_H_
#define _ITEMBOX_H_
#define MAX_ITEMBOX (20)	//ビルボードの個数

enum TEXTURE_ITEM_ENUM
{
	TEXTURE_ITEM_NULL = -1,
	TEXTURE_ITEM_BOX,
	TEXTURE_ITEM_MAX
};

typedef struct
{
	char fileName[256];
}TEXTURE_ITEM;

static const TEXTURE_ITEM g_aTexture_i[] =
{
	{ "data/texture/hatena.png" }
};
class CItem {
public:
	static bool InitItem();
	static void UninitItem();
	static void UpdateItem();
	static void DrawItem();
	static bool GetItem(); 
	static bool GetItem2();
	static bool GetBGM();
private:
	static LPDIRECT3DTEXTURE9 g_pTextures_bill[TEXTURE_ITEM_MAX];	//テクスチャ配列
	static D3DXMATRIX g_mtxWorld_Item;		//ワールド変換行列
	static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;		// バーテックスバッファのポインタ
	static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer;		// インデックスバッファのポインタ
	static void VertexBuffer_Field();
	static void IndexBuffer_Field();
	static D3DXMATRIX g_viewInverse;
	static D3DXMATRIX g_Trans, g_Rotation;
	static D3DXVECTOR3 g_TransPosI[MAX_ITEMBOX];
	static int color[MAX_ITEMBOX];
	static bool ememy[MAX_ITEMBOX];
	static int Life[MAX_ITEMBOX];
	static float  g_Rot4;
	static bool b_item;
	static bool b_item2;
	static bool b_item_BGM;
};
#endif 