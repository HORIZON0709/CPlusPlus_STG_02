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
#include "bullet_3D.h"
#include "item_3D.h"
#include "score.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CEnemyCurve::START_POS_X = 500.0f;	//初期位置( X )
const float CEnemyCurve::START_POS_Y = 0.0f;	//初期位置( Y )
const float CEnemyCurve::ENEMY_SIZE = 90.0f;	//サイズ
const float CEnemyCurve::CURVE_SIZE = 0.1f;		//カーブのサイズ
const float CEnemyCurve::MOVE_SPEED_X = 1.0f;	//移動スピード( X )
const float CEnemyCurve::MOVE_SPEED_Y = 5.0f;	//移動スピード( Y )

//================================================
//生成
//================================================
CEnemyCurve* CEnemyCurve::Create()
{
	CEnemyCurve* pEnemyCurve = nullptr;	//ポインタ

	if (pEnemyCurve != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pEnemyCurve = new CEnemyCurve;	//メモリの動的確保

	pEnemyCurve->Init();	//初期化

	return pEnemyCurve;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CEnemyCurve::CEnemyCurve():
	m_nTimerInterval(0),
	m_fCurve(0.0f)
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
	CObject3D::Init();	//親クラス

	//位置を設定
	D3DXVECTOR3 pos = D3DXVECTOR3(START_POS_X, START_POS_Y, 0.0f);
	CObject3D::SetPos(pos);

	//移動量を設定
	D3DXVECTOR3 move = D3DXVECTOR3(-MOVE_SPEED_X, 0.0f, 0.0f);
	CObject3D::SetMove(move);

	//サイズを設定
	D3DXVECTOR2 size = D3DXVECTOR2(ENEMY_SIZE, ENEMY_SIZE);
	CObject3D::SetSize(size);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::enemy000);

	return S_OK;
}

//================================================
//終了
//================================================
void CEnemyCurve::Uninit()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//位置を取得

	//アイテムの生成
	CItem3D::Create(pos, CItem3D::TYPE::CHANGE_BUlLET_DOUBLE);

	//スコアを加算
	CApplication::GetScore()->AddScore(NUM_SCORE);

	CObject3D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CEnemyCurve::Update()
{
	CObject3D::Update();	//親クラス

	D3DXVECTOR3 pos = CObject3D::GetPos();		//位置を取得
	D3DXVECTOR3 move = CObject3D::GetMove();	//移動量を取得

	//加算
	m_fCurve += CURVE_SIZE;

	//sinカーブ
	move.y = sinf(D3DX_PI * m_fCurve) * MOVE_SPEED_Y;

	//移動量を位置に加算
	pos += move;

	CObject3D::SetPos(pos);	//位置を設定

	m_nTimerInterval++;	//タイマーを進める

	if (m_nTimerInterval % SHOT_INTERVAL == 0)
	{//タイマーが一定時間になったら
		D3DXVECTOR3 posBullet = CObject3D::GetPos();				//位置を取得
		D3DXVECTOR3 moveBullet = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);	//弾の移動量を設定

		CBullet3D::Create(/* 弾の生成 */
			posBullet,					//位置
			moveBullet,					//移動量
			CObject::OBJ_TYPE::ENEMY);	//所有者
	}
}

//================================================
//描画
//================================================
void CEnemyCurve::Draw()
{
	CObject3D::Draw();	//親クラス
}