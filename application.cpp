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

#include "player.h"
#include "enemy.h"
#include "score.h"

#include "player_3D.h"
#include "bg_3D.h"

#include "object2D.h"
#include "object3D.h"

//***************************
//静的メンバ変数
//***************************
CInput* CApplication::m_pInput = nullptr;					//インプット
CInputKeyboard* CApplication::m_pInputKeyboard = nullptr;	//キーボード

CTexture* CApplication::m_pTexture = nullptr;	//テクスチャ
CRenderer* CApplication::m_pRenderer = nullptr;	//レンダラー
CCamera* CApplication::m_pCamera = nullptr;		//カメラ

CPlayer* CApplication::m_pPlayer = nullptr;	//プレイヤー
CEnemy* CApplication::m_pEnemy = nullptr;	//敵
CScore* CApplication::m_pScore = nullptr;	//スコア

CPlayer3D* CApplication::m_pPlayer3D = nullptr;	//プレイヤー(3D)
CEnemy3D* CApplication::m_apEnemy3D[CEnemy3D::MAX_ENEMY] = {};	//敵(3D)
CBg3D* CApplication::m_pBg3D = nullptr;			//背景(3D)

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
//プレイヤー情報を取得
//================================================
CPlayer* CApplication::GetPlayer()
{
	return m_pPlayer;
}

//================================================
//敵情報を取得
//================================================
CEnemy* CApplication::GetEnemy()
{
	return m_pEnemy;
}

//================================================
//スコア情報を取得
//================================================
CScore* CApplication::GetScore()
{
	return m_pScore;
}

//================================================
//プレイヤー(3D)情報を取得
//================================================
CPlayer3D* CApplication::GetPlayer3D()
{
	return m_pPlayer3D;
}

//================================================
//敵(3D)情報を取得
//================================================
CEnemy3D* CApplication::GetEnemy3D(const int nIdx)
{
	return m_apEnemy3D[nIdx];
}

//================================================
//背景(3D)情報を取得
//================================================
CBg3D* CApplication::GetBg3D()
{
	return m_pBg3D;
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

	/* プレイヤー */

	//m_pPlayer = CPlayer::Create();	//生成

	/* 敵 */

	//m_pEnemy = CEnemy::Create();	//生成

	/* スコア */

	m_pScore = CScore::Create();	//生成

	/* 背景(3D) */

	m_pBg3D = CBg3D::Create();	//生成

	/* プレイヤー(3D) */

	m_pPlayer3D = CPlayer3D::Create();	//生成

	/* 敵(3D) */

	for (int i = 0; i < CEnemy3D::MAX_ENEMY; i++)
	{
		if (m_apEnemy3D[i] != nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrの場合 */

		bool bNumEnemyCurve = ((i >= 0) && (i < 2));	//カーブする敵か否か

		if (bNumEnemyCurve)
		{
			D3DXVECTOR3 pos = D3DXVECTOR3(300.0f + (200.0f * i),
										 (100.0f * i),
											0.0f);

			m_apEnemy3D[i] = CEnemy3D::Create(CEnemy3D::ENM_TYPE::CURVE, pos);	//生成
		}
	}

	return S_OK;
}

//================================================
//終了
//================================================
void CApplication::Uninit()
{
	/* オブジェクト */

	CObject2D::ReleaseAll();	//全ての解放(2D)
	CObject3D::ReleaseAll();	//全ての解放(3D)
	
	/* プレイヤー */

	//m_pPlayer = nullptr;	//nullptrにする

	/* 敵 */

	//m_pEnemy = nullptr;	//nullptrにする

	/* スコア */

	m_pScore = nullptr;	//nullptrにする

	/* 背景(3D) */

	m_pBg3D = nullptr;	//nullptrにする

	/* プレイヤー(3D) */

	m_pPlayer3D = nullptr;	//nullptrにする

	/* 敵(3D) */

	for (int i = 0; i < CEnemy3D::MAX_ENEMY; i++)
	{
		if (m_apEnemy3D[i] == nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		m_apEnemy3D[i] = nullptr;	//nullptrにする
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