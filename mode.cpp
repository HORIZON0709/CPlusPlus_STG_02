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
CMode::MODE CMode::m_mode = GAME;		//モード
CTitle* CMode::m_pTitle = nullptr;		//タイトル
CGame* CMode::m_pGame = nullptr;		//ゲーム
CResult* CMode::m_pResult = nullptr;	//リザルト

//================================================
//モードの設定
//================================================
void CMode::SetMode(const MODE &mode)
{
	switch (m_mode)
	{//変更前のモードを終了する
	case MODE::TITLE: /* タイトル */
		if (m_pTitle != nullptr)
		{//NULLチェック
			m_pTitle->Uninit();	//終了
			delete m_pTitle;	//メモリの解放
			m_pTitle = nullptr;	//nullptrにする
		}
		break;

	case MODE::GAME: /* ゲーム */
		if (m_pGame != nullptr)
		{//NULLチェック
			m_pGame->Uninit();	//終了
			delete m_pGame;		//メモリの解放
			m_pGame = nullptr;	//nullptrにする
		}
		break;

	case MODE::RESULT: /* リザルト */
		if (m_pResult != nullptr)
		{//NULLチェック
			m_pResult->Uninit();	//終了
			delete m_pResult;		//メモリの解放
			m_pResult = nullptr;	//nullptrにする
		}
		break;
	}

	m_mode = mode;	//モードを変更

	switch (m_mode)
	{//変更後のモードを初期化する
	case MODE::TITLE: /* タイトル */
		if (m_pTitle == nullptr)
		{//NULLチェック
			m_pTitle = new CTitle;	//メモリの動的確保
			m_pTitle->Init();		//初期化
		}
		break;

	case MODE::GAME: /* ゲーム */
		if (m_pGame == nullptr)
		{//NULLチェック
			m_pGame = new CGame;	//メモリの動的確保
			m_pGame->Init();		//初期化
		}
		break;

	case MODE::RESULT: /* リザルト */
		if (m_pResult == nullptr)
		{//NULLチェック
			m_pResult = new CResult;	//メモリの動的確保
			m_pResult->Init();			//初期化
		}
		break;
	}
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
	switch (m_mode)
	{
	case MODE::TITLE: /* タイトル */
		if (m_pTitle == nullptr)
		{//NULLチェック
			m_pTitle = new CTitle;	//メモリの動的確保
		}

		if (FAILED(m_pTitle->Init()))
		{//初期化処理が失敗した場合
			return E_FAIL;
		}
		break;

	case MODE::GAME: /* ゲーム */
		if (m_pGame == nullptr)
		{//NULLチェック
			m_pGame = new CGame;	//メモリの動的確保
		}

		if (FAILED(m_pGame->Init()))
		{//初期化処理が失敗した場合
			return E_FAIL;
		}
		break;

	case MODE::RESULT: /* リザルト */
		if (m_pResult == nullptr)
		{//NULLチェック
			m_pResult = new CResult;	//メモリの動的確保
		}

		if (FAILED(m_pResult->Init()))
		{//初期化処理が失敗した場合
			return E_FAIL;
		}
		break;
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