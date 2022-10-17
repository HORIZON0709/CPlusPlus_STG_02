//================================================
//
//制作実践基礎[enemy_curve.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "enemy_curve.h"
#include "application.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "fade.h"

#include "bullet_3D.h"
#include "item_3D.h"
#include "score.h"
#include "explosion_3D.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CEnemyCurve::START_POS_X = 1000.0f;	//初期位置( X )
const float CEnemyCurve::START_POS_Y = 100.0f;	//初期位置( Y )
const float CEnemyCurve::ENEMY_SIZE = 75.0f;	//サイズ
const float CEnemyCurve::CURVE_SIZE = 0.025f;	//カーブのサイズ
const float CEnemyCurve::MOVE_SPEED_X = 1.0f;	//移動スピード( X )
const float CEnemyCurve::MOVE_SPEED_Y = 5.0f;	//移動スピード( Y )

const int CEnemyCurve::SHOT_INTERVAL = 90;	//弾の連続発射の間隔
const int CEnemyCurve::NUM_SCORE = 10;		//獲得スコア量

//================================================
//コンストラクタ
//================================================
CEnemyCurve::CEnemyCurve():
	m_nTimerInterval(0),
	m_fCurve(0.0f),
	m_bInside(false)
{
	//敵の種類を設定
	CEnemy3D::SetEnmType(CEnemy3D::ENM_TYPE::CURVE);
}

//================================================
//デストラクタ
//================================================
CEnemyCurve::~CEnemyCurve()
{
}

//================================================
//初期化
//================================================
HRESULT CEnemyCurve::Init()
{
	CEnemy3D::Init();	//親クラス

	//移動量を設定
	D3DXVECTOR3 move = D3DXVECTOR3(-MOVE_SPEED_X, 0.0f, 0.0f);
	CObject3D::SetMove(move);

	//サイズを設定
	D3DXVECTOR3 size = D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f);
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
void CEnemyCurve::Uninit()
{
	CEnemy3D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CEnemyCurve::Update()
{
	if (CApplication::GetFade()->GetState() == CFade::STATE::FADE_OUT)
	{//暗転中
		return;
	}

	CEnemy3D::Update();	//親クラス

	//移動
	Move();

	//弾の発射
	Shot();

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
void CEnemyCurve::Draw()
{
	CEnemy3D::Draw();	//親クラス
}

//================================================
//死亡時の処理
//================================================
void CEnemyCurve::Death()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//位置を取得

	//アイテムの生成
	CItem3D::Create(pos, CItem3D::TYPE::CHANGE_BUlLET_DOUBLE);

	//爆発を生成
	CExplosion3D::Create(
		CObject3D::GetPos(),
		CObject3D::GetSize(),
		CTexture::TEXTURE::explosion001);

	//スコアを加算
	CGame::GetScore()->AddScore(NUM_SCORE);
}

//================================================
//移動
//================================================
void CEnemyCurve::Move()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();		//位置を取得
	D3DXVECTOR3 move = CObject3D::GetMove();	//移動量を取得

	//加算
	m_fCurve += CURVE_SIZE;

	//sinカーブ
	move.y = sinf(D3DX_PI * m_fCurve) * MOVE_SPEED_Y;

	//移動量を位置に加算
	pos += move;

	CObject3D::SetPos(pos);	//位置を設定
}

//================================================
//弾の発射
//================================================
void CEnemyCurve::Shot()
{
	m_nTimerInterval++;	//タイマーを進める

	if (m_nTimerInterval % SHOT_INTERVAL == 0)
	{//タイマーが一定時間になったら
		D3DXVECTOR3 posBullet = CObject3D::GetPos();				//位置を取得
		D3DXVECTOR3 moveBullet = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);	//弾の移動量を設定

		CBullet3D::Create(/* 弾の生成 */
			posBullet,					//位置
			moveBullet,					//移動量
			CObject::OBJ_TYPE::ENEMY,	//所有者
			CTexture::bullet004);		//テクスチャ
	}
}

//================================================
//画面右端を超えたかどうか
//================================================
void CEnemyCurve::OverRimitRight()
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
void CEnemyCurve::ReleaseOffScreen()
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