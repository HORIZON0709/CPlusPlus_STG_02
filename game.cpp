//================================================
//
//制作実践基礎[game.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "game.h"
#include "object2D.h"
#include "object3D.h"

#include "camera.h"
#include "score.h"
#include "player_3D.h"
#include "enemy_curve.h"
#include "enemy_boss.h"
#include "bg_3D.h"

#include <assert.h>

//***************************
//静的メンバ変数
//***************************
CCamera* CGame::m_pCamera = nullptr;					//カメラ
CScore* CGame::m_pScore = nullptr;						//スコア
CPlayer3D* CGame::m_pPlayer3D = nullptr;				//プレイヤー(3D)
CEnemy3D* CGame::m_apEnemy3D[CEnemy3D::MAX_ENEMY] = {};	//敵(3D)
CBg3D* CGame::m_pBg3D = nullptr;						//背景(3D)
bool CGame::m_bGamePart = false;						//ゲームパート

//================================================
//カメラ情報を取得
//================================================
CCamera* CGame::GetCamera()
{
	return m_pCamera;
}

//================================================
//スコア情報を取得
//================================================
CScore* CGame::GetScore()
{
	return m_pScore;
}

//================================================
//プレイヤー(3D)情報を取得
//================================================
CPlayer3D* CGame::GetPlayer3D()
{
	return m_pPlayer3D;
}

//================================================
//敵(3D)情報を取得
//================================================
CEnemy3D* CGame::GetEnemy3D(const int nIdx)
{
	return m_apEnemy3D[nIdx];
}

//================================================
//背景(3D)情報を取得
//================================================
CBg3D* CGame::GetBg3D()
{
	return m_pBg3D;
}

//================================================
//コンストラクタ
//================================================
CGame::CGame() : CMode(MODE::GAME)
{
}

//================================================
//デストラクタ
//================================================
CGame::~CGame()
{
}

//================================================
//初期化
//================================================
HRESULT CGame::Init()
{
	m_bGamePart = false;	//通常パート

	/* 生成 */

	if (m_pCamera == nullptr)
	{//NULLチェック
		m_pCamera = new CCamera;	//カメラ
		m_pCamera->Init();			//初期化
	}

	m_pScore = CScore::Create();	//スコア

	m_pBg3D = CBg3D::Create();	//背景(3D)

	m_pPlayer3D = CPlayer3D::Create();	//プレイヤー(3D)

	for (int i = 0; i < CEnemy3D::NUM_ENEMY_CURVE; i++)
	{//カーブ敵
		if (m_apEnemy3D[i] != nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrの場合 */

		//位置を設定
		D3DXVECTOR3 pos = D3DXVECTOR3(CEnemyCurve::START_POS_X + (200.0f * i),
										(100.0f * i),
										0.0f);

		//生成
		m_apEnemy3D[i] = CEnemy3D::Create(CEnemy3D::ENM_TYPE::CURVE, pos);
	}

	return S_OK;
}

//================================================
//終了
//================================================
void CGame::Uninit()
{
	/* オブジェクト */

	CObject2D::ReleaseAll();	//全ての解放(2D)
	CObject3D::ReleaseAll();	//全ての解放(3D)

	/* カメラ */

	if (m_pCamera != nullptr)
	{//NULLチェック
		m_pCamera->Uninit();	//終了
		delete m_pCamera;		//メモリの解放
		m_pCamera = nullptr;	//nullptrにする
	}

	/* スコア */

	if (m_pScore != nullptr)
	{//NULLチェック
		m_pScore = nullptr;	//nullptrにする
	}

	/* 背景(3D) */

	if (m_pScore != nullptr)
	{//NULLチェック
		m_pBg3D = nullptr;	//nullptrにする
	}

	/* プレイヤー(3D) */
	if (m_pScore != nullptr)
	{//NULLチェック
		m_pPlayer3D = nullptr;	//nullptrにする
	}

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
}

//================================================
//更新
//================================================
void CGame::Update()
{
	if (m_pCamera != nullptr)
	{//NULLチェック
		m_pCamera->Update();	//カメラ
	}

	CObject::UpdateAll();	//オブジェクト

	if (m_pCamera->GetPosV().x == 500.0f)
	{
		ChangeGamePart();
	}
}

//================================================
//描画
//================================================
void CGame::Draw()
{
	//カメラの設定
	m_pCamera->Set();

	CObject::DrawAll();	//オブジェクト
}

//================================================
//ゲームパートの切り替え
//================================================
void CGame::ChangeGamePart()
{
	/* 通常敵を解放 */

	for (int i = 0; i < CEnemy3D::MAX_ENEMY; i++)
	{
		if (m_apEnemy3D[i] == nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		m_apEnemy3D[i] = nullptr;	//nullptrにする
	}

	m_pCamera->Init();	//カメラの初期化

	m_bGamePart = true;	//ボスパートに切り替え

	/* ボスの生成 */

	if (m_apEnemy3D[0] != nullptr)
	{//NULLチェック
		m_apEnemy3D[0] = nullptr;	//nullptrにする

		//位置を設定
		D3DXVECTOR3 pos = D3DXVECTOR3(CEnemyBoss::START_POS_X, CEnemyBoss::START_POS_Y, 0.0f);

		//ボスを生成する
		m_apEnemy3D[0] = CEnemy3D::Create(CEnemy3D::ENM_TYPE::BOSS, pos);
	}
}

//================================================
//ゲームパートの取得
//================================================
bool CGame::GetGamePart()
{
	return m_bGamePart;
}