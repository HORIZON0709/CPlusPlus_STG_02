//================================================
//
//制作実践基礎[bg_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "bg_3D.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CBg3D::BG_WIDTH = CRenderer::SCREEN_WIDTH - 100.0f;		//横幅
const float CBg3D::BG_HEIGHT = CRenderer::SCREEN_HEIGHT - 50.0f;	//縦幅

//================================================
//生成
//================================================
CBg3D* CBg3D::Create()
{
	CBg3D* pBg3D = nullptr;	//ポインタ

	if (pBg3D != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pBg3D = new CBg3D;	//メモリの動的確保

	pBg3D->Init();	//初期化

	return pBg3D;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CBg3D::CBg3D()
{
	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::BG);
}

//================================================
//デストラクタ
//================================================
CBg3D::~CBg3D()
{
}

//================================================
//初期化
//================================================
HRESULT CBg3D::Init()
{
	CObject3D::Init();	//親クラス

	//サイズを設定
	D3DXVECTOR2 size = D3DXVECTOR2(BG_WIDTH, BG_HEIGHT);
	CObject3D::SetSize(size);

	//位置を設定
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.1f);
	CObject3D::SetPos(pos);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::TEXTURE_universe);

	return S_OK;
}

//================================================
//終了
//================================================
void CBg3D::Uninit()
{
	CObject3D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CBg3D::Update()
{
	CObject3D::Update();	//親クラス
}

//================================================
//描画
//================================================
void CBg3D::Draw()
{
	CObject3D::Draw();	//親クラス
}