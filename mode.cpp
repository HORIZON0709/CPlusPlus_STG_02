//================================================
//
//制作実践基礎[mode.h]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "mode.h"

#include "title.h"
#include "game.h"
#include "result.h"

//***************************
//静的メンバ変数
//***************************
CMode::MODE CMode::m_mode = TITLE;		//モード
CTitle* CMode::m_pTitle = nullptr;		//タイトル
CGame* CMode::m_pGame = nullptr;		//ゲーム
CResult* CMode::m_pResult = nullptr;	//リザルト

//================================================
//モードの設定
//================================================
void CMode::SetMode(const MODE &mode)
{
	m_mode = mode;
}

//================================================
//ゲーム情報を取得
//================================================
CGame* CMode::GetGame()
{
	return m_pGame;
}

//================================================
//コンストラクタ
//================================================
CMode::CMode()
{
}

//================================================
//デストラクタ
//================================================
CMode::~CMode()
{
}

//================================================
//初期化
//================================================
HRESULT CMode::Init()
{
	/* ゲーム */

	if (m_pGame == nullptr)
	{//NULLチェック
		m_pGame = new CGame;	//メモリの動的確保
	}

	if (FAILED(m_pGame->Init()))
	{//初期化処理が失敗した場合
		return E_FAIL;
	}

	return S_OK;
}

//================================================
//終了
//================================================
void CMode::Uninit()
{
	/* タイトル */

	if (m_pTitle != nullptr)
	{//NULLチェック
		m_pTitle->Uninit();	//終了
		delete m_pTitle;	//メモリの解放
		m_pTitle = nullptr;	//nullptrにする
	}

	/* ゲーム */

	if (m_pGame != nullptr)
	{//NULLチェック
		m_pGame->Uninit();	//終了
		delete m_pGame;		//メモリの解放
		m_pGame = nullptr;	//nullptrにする
	}

	/* リザルト */

	if (m_pResult != nullptr)
	{//NULLチェック
		m_pResult->Uninit();	//終了
		delete m_pResult;		//メモリの解放
		m_pResult = nullptr;	//nullptrにする
	}
}

//================================================
//更新
//================================================
void CMode::Update()
{
}

//================================================
//描画
//================================================
void CMode::Draw()
{
}