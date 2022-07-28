//================================================
//
//制作実践基礎[application.h]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "application.h"
#include "input.h"
#include "renderer.h"
#include "texture.h"
#include "camera.h"

#include "game.h"

//***************************
//静的メンバ変数
//***************************
CInput* CApplication::m_pInput = nullptr;					//インプット
CInputKeyboard* CApplication::m_pInputKeyboard = nullptr;	//キーボード

CTexture* CApplication::m_pTexture = nullptr;	//テクスチャ
CRenderer* CApplication::m_pRenderer = nullptr;	//レンダラー
CCamera* CApplication::m_pCamera = nullptr;		//カメラ

CGame* CApplication::m_pGame = nullptr;	//ゲーム

//================================================
//インプット情報を取得
//================================================
CInput* CApplication::GetInput()
{
	return m_pInput;
}

//================================================
//キーボード情報を取得
//================================================
CInputKeyboard* CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
}

//================================================
//テクスチャ情報を取得
//================================================
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//================================================
//レンダラー情報を取得
//================================================
CRenderer* CApplication::GetRenderer()
{
	return m_pRenderer;
}

//================================================
//カメラ情報を取得
//================================================
CCamera* CApplication::GetCamera()
{
	return m_pCamera;
}

//================================================
//ゲーム情報を取得
//================================================
CGame* CApplication::GetGame()
{
	return m_pGame;
}

//================================================
//コンストラクタ
//================================================
CApplication::CApplication()
{
}

//================================================
//デストラクタ
//================================================
CApplication::~CApplication()
{
}

//================================================
//初期化
//================================================
HRESULT CApplication::Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance)
{
	/* インプット */

	if (m_pInput == nullptr)
	{//NULLチェック
		m_pInput = CInput::Create();	//メモリの動的確保
	}

	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{//初期化処理が失敗した場合
		return E_FAIL;
	}

	/* キーボード */

	if (m_pInputKeyboard == nullptr)
	{//NULLチェック
		m_pInputKeyboard = new CInputKeyboard;	//メモリの動的確保
	}

	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//初期化処理が失敗した場合
		return E_FAIL;
	}

	/* テクスチャ */

	if (m_pTexture == nullptr)
	{//NULLチェック
		m_pTexture = new CTexture;	//メモリの動的確保
	}

	/* レンダラー */

	if (m_pRenderer == nullptr)
	{//NULLチェック
		m_pRenderer = new CRenderer;	//メモリの動的確保
	}

	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{//初期化処理が失敗した場合
		return E_FAIL;
	}

	/* カメラ */

	if (m_pCamera == nullptr)
	{//NULLチェック
		m_pCamera = new CCamera;	//メモリの動的確保
		m_pCamera->Init();			//初期化
	}

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
void CApplication::Uninit()
{
	/* ゲーム */

	if (m_pGame != nullptr)
	{//NULLチェック
		m_pGame->Uninit();	//終了
		delete m_pGame;		//メモリの解放
		m_pGame = nullptr;	//nullptrにする
	}

	/* カメラ */

	if (m_pCamera != nullptr)
	{//NULLチェック
		m_pCamera->Uninit();	//終了
		delete m_pCamera;		//メモリの解放
		m_pCamera = nullptr;	//nullptrにする
	}

	/* レンダラー */

	if (m_pRenderer != nullptr)
	{//NULLチェック
		m_pRenderer->Uninit();	//終了処理
		delete m_pRenderer;		//メモリの解放
		m_pRenderer = nullptr;	//nullptrにする
	}

	/* テクスチャ */

	if (m_pTexture != nullptr)
	{//NULLチェック
		m_pTexture->ReleaseAll();	//終了処理
		delete m_pTexture;			//メモリの解放
		m_pTexture = nullptr;		//nullptrにする
	}

	/* キーボード */

	if (m_pInputKeyboard != nullptr)
	{//NULLチェック
		m_pInputKeyboard->Uninit();	//終了処理
		delete m_pInputKeyboard;	//メモリの解放
		m_pInputKeyboard = nullptr;	//nullptrにする
	}

	/* インプット */

	m_pInput->Uninit();	//終了処理

}

//================================================
//更新
//================================================
void CApplication::Update()
{
	if (m_pInput != nullptr)
	{//NULLチェック
		m_pInput->Update();	//インプット
	}

	if (m_pInputKeyboard != nullptr)
	{//NULLチェック
		m_pInputKeyboard->Update();	//キーボード
	}

	if (m_pRenderer != nullptr)
	{//NULLチェック
		m_pRenderer->Update();	//レンダラー
	}

	if (m_pCamera != nullptr)
	{//NULLチェック
		m_pCamera->Update();	//カメラ
	}
}

//================================================
//描画
//================================================
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{//NULLチェック
		m_pRenderer->Draw();	//レンダラー
	}
}