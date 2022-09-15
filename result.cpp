//================================================
//
//制作実践基礎[result.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "result.h"

#include "application.h"
#include "fade.h"
#include "input.h"
#include "object2D.h"
#include "bg.h"

#include <assert.h>

//***************************
//静的メンバ変数
//***************************
CBg* CResult::m_pBg = nullptr;	//背景

//================================================
//コンストラクタ
//================================================
CResult::CResult() : CMode(MODE::RESULT)
{
}

//================================================
//デストラクタ
//================================================
CResult::~CResult()
{
}

//================================================
//初期化
//================================================
HRESULT CResult::Init()
{
	/* 背景 */

	//生成
	m_pBg = CBg::Create();

	//テクスチャの設定
	m_pBg->SetTexture(CTexture::bg002);

	//テクスチャ座標の設定
	m_pBg->SetTexUV(1, 0);

	//明転
	CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);

	return S_OK;
}

//================================================
//終了
//================================================
void CResult::Uninit()
{
	/* オブジェクト */

	CObject2D::ReleaseAll();	//全ての解放(2D)

	/* 背景 */

	if (m_pBg != nullptr)
	{//NULLチェック
		m_pBg = nullptr;	//nullptrにする
	}
}

//================================================
//更新
//================================================
void CResult::Update()
{
	CObject::UpdateAll();	//オブジェクト

	CInput* pInput = CInput::GetKey();	//キーボード情報を取得

	if (pInput->Trigger(CInput::STANDARD_KEY::DECISION))
	{//決定キ―
		CApplication::GetFade()->Set(CFade::STATE::FADE_IN);	//暗転

		Change(MODE::TITLE);	//モードの設定
	}
}

//================================================
//描画
//================================================
void CResult::Draw()
{
	CObject::DrawAll();	//オブジェクト
}