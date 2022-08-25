//================================================
//
//制作実践基礎[title.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "title.h"

#include "input.h"

#include <assert.h>

//***************************
//静的メンバ変数
//***************************

//================================================
//コンストラクタ
//================================================
CTitle::CTitle()
{
}

//================================================
//デストラクタ
//================================================
CTitle::~CTitle()
{
}

//================================================
//初期化
//================================================
HRESULT CTitle::Init()
{
	return S_OK;
}

//================================================
//終了
//================================================
void CTitle::Uninit()
{

}

//================================================
//更新
//================================================
void CTitle::Update()
{
	CInput* pInput = CInput::GetKey();	//キーボード情報を取得

	if (pInput->Trigger(CInput::STANDARD_KEY::DECISION))
	{//決定キ―
		SetMode(MODE::GAME);	//モードの設定
	}
}

//================================================
//描画
//================================================
void CTitle::Draw()
{
}