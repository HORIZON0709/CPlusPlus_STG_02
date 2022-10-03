//================================================
//
//制作実践基礎[enemy_straight.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "enemy_straight.h"
#include "application.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "fade.h"

#include "score.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CEnemyStraight::START_POS_X = 1000.0f;	//初期位置( X )
const float CEnemyStraight::START_POS_Y = 100.0f;	//初期位置( Y )
const float CEnemyStraight::ENEMY_SIZE = 75.0f;		//サイズ
const float CEnemyStraight::MOVE_SPEED_X = 2.0f;	//移動スピード( X )

//================================================
//コンストラクタ
//================================================
CEnemyStraight::CEnemyStraight():
	m_bInside(false)
{
	//敵の種類を設定
	CEnemy3D::SetEnmType(CEnemy3D::ENM_TYPE::STRAIGHT);
}

//================================================
//デストラクタ
//================================================
CEnemyStraight::~CEnemyStraight()
{
}

//================================================
//初期化
//================================================
HRESULT CEnemyStraight::Init()
{
	CEnemy3D::Init();	//親クラス

	//移動量を設定
	D3DXVECTOR3 move = D3DXVECTOR3(-MOVE_SPEED_X, 0.0f, 0.0f);
	CObject3D::SetMove(move);

	//サイズを設定
	D3DXVECTOR2 size = D3DXVECTOR2(ENEMY_SIZE, ENEMY_SIZE);
	CObject3D::SetSize(size);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::enemy000);

	//初期位置が画面外である
	m_bInside = false;

	return S_OK;
}

//================================================
//終了
//================================================
void CEnemyStraight::Uninit()
{
	CEnemy3D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CEnemyStraight::Update()
{
	if (CApplication::GetFade()->GetState() == CFade::STATE::FADE_OUT)
	{//暗転中
		return;
	}

	CEnemy3D::Update();	//親クラス

	//移動
	Move();

	if (!m_bInside)
	{//画面内に入ってきていない場合
		OverRimitRight();	//画面右端を超えたかどうか
		return;
	}

	/* 画面内に入ってきた場合 */

	//画面外に出たら解放する
	ReleaseOffScreen();
}

//================================================
//描画
//================================================
void CEnemyStraight::Draw()
{
	CEnemy3D::Draw();	//親クラス
}

//================================================
//死亡時の処理
//================================================
void CEnemyStraight::Death()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//位置を取得

	//スコアを加算
	CGame::GetScore()->AddScore(NUM_SCORE);
}

//================================================
//移動
//================================================
void CEnemyStraight::Move()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();		//位置を取得
	
	//移動量を位置に加算
	pos += CObject3D::GetMove();

	CObject3D::SetPos(pos);	//位置を設定
}

//================================================
//画面右端を超えたかどうか
//================================================
void CEnemyStraight::OverRimitRight()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//位置を取得

	float fSizeHalf = (ENEMY_SIZE * 0.5f);	//サイズの半分
	float fLeft		= (pos.x - fSizeHalf);	//左端

	//カメラ情報の取得
	D3DXMATRIX mtxCamera = CGame::GetCamera()->GetMatrixView();
	
	//カメラの視点の位置を取得
	D3DXVECTOR3 posV = CGame::GetCamera()->GetPosV();

	//位置を反映
	D3DXMatrixTranslation(&mtxCamera, posV.x, posV.y, posV.z);

	//カメラの画角の右の限界を設定
	float fRimitRight	= (mtxCamera._41 + (CRenderer::SCREEN_WIDTH * 0.5f));	//右

	//画面右端を超えたかどうか
	bool bOverRimitRight = (fLeft < fRimitRight);

	if (bOverRimitRight)
	{//画面右端を超えた場合
		m_bInside = true;	//画面内にいる
	}
}

//================================================
//画面外に出たら解放する
//================================================
void CEnemyStraight::ReleaseOffScreen()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//位置を取得

	float fSizeHalf = (ENEMY_SIZE * 0.5f);	//サイズの半分
	float fLeft		= (pos.x - fSizeHalf);	//左端
	float fRight	= (pos.x + fSizeHalf);	//右端

	//カメラ情報の取得
	D3DXMATRIX mtxCamera = CGame::GetCamera()->GetMatrixView();
	
	//カメラの視点の位置を取得
	D3DXVECTOR3 posV = CGame::GetCamera()->GetPosV();

	//位置を反映
	D3DXMatrixTranslation(&mtxCamera, posV.x, posV.y, posV.z);

	//カメラの画角の左右の限界を設定
	float fRimitLeft	= (mtxCamera._41 - (CRenderer::SCREEN_WIDTH * 0.5f));	//左
	float fRimitRight	= (mtxCamera._41 + (CRenderer::SCREEN_WIDTH * 0.5f));	//右

	//左右にフレームアウトしたかどうか
	bool bFrameOutOnLeft	= (fRight < fRimitLeft);	//左側に
	bool bFrameOutOnRight	= (fLeft > fRimitRight);	//右側に

	if (bFrameOutOnLeft || bFrameOutOnRight)
	{//画角から完全に出たら
		Release();	//自身の解放
	}
}