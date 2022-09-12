//================================================
//
//制作実践基礎[fade.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "fade.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CFade::FADE_WIDTH = CRenderer::SCREEN_WIDTH;	//横幅
const float CFade::FADE_HEIGHT = CRenderer::SCREEN_HEIGHT;	//縦幅

//================================================
//生成
//================================================
CFade* CFade::Create()
{
	CFade* pFade = nullptr;	//ポインタ

	if (pFade != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pFade = new CFade;	//メモリの動的確保

	pFade->Init();	//初期化

	return pFade;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CFade::CFade()
{
	//タイプの設定
	//CObject::SetObjType(CObject::OBJ_TYPE::FADE);
}

//================================================
//デストラクタ
//================================================
CFade::~CFade()
{
}

//================================================
//初期化
//================================================
HRESULT CFade::Init()
{
	if (m_pPolygon != nullptr)
	{
		m_pPolygon = nullptr;
	}

	m_pPolygon = CObject2D::Create();

	//サイズを設定
	D3DXVECTOR2 size = D3DXVECTOR2(FADE_WIDTH, FADE_HEIGHT);
	m_pPolygon->SetSize(size);

	//m_pPolygon->SetCol();

	return S_OK;
}

//================================================
//終了
//================================================
void CFade::Uninit()
{
	//CObject2D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CFade::Update()
{
	//CObject3D::Update();	//親クラス
}

//================================================
//描画
//================================================
void CFade::Draw()
{
	//CObject3D::Draw();	//親クラス
}