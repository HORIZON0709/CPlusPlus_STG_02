//================================================
//
//制作実践基礎[enemy_boss.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "enemy_boss.h"
#include "application.h"
#include "renderer.h"
#include "game.h"

#include "bullet_3D.h"
#include "score.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CEnemyBoss::START_POS_X = 0.0f;		//初期位置( X )
const float CEnemyBoss::START_POS_Y = 100.0f;	//初期位置( Y )
const float CEnemyBoss::ENEMY_SIZE = 270.0f;	//サイズ

//================================================
//コンストラクタ
//================================================
CEnemyBoss::CEnemyBoss():
	m_nTimerInterval(0)
{
	//敵の種類を設定
	CEnemy3D::SetEnmType(CEnemy3D::ENM_TYPE::BOSS);
}

//================================================
//デストラクタ
//================================================
CEnemyBoss::~CEnemyBoss()
{
}

//================================================
//初期化
//================================================
HRESULT CEnemyBoss::Init()
{
	CEnemy3D::Init();	//親クラス

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
void CEnemyBoss::Uninit()
{
	CEnemy3D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CEnemyBoss::Update()
{
	CEnemy3D::Update();	//親クラス

	Move();	//移動

	m_nTimerInterval++;	//タイマーを進める

	if (m_nTimerInterval % SHOT_INTERVAL == 0)
	{//タイマーが一定時間になったら
		D3DXVECTOR3 posBullet = CObject3D::GetPos();				//位置を取得
		D3DXVECTOR3 moveBullet = D3DXVECTOR3(0.0f, -2.0f, 0.0f);	//弾の移動量を設定

		CBullet3D::Create(/* 弾の生成 */
			posBullet,					//位置
			moveBullet,					//移動量
			CObject::OBJ_TYPE::ENEMY);	//所有者
	}
}

//================================================
//描画
//================================================
void CEnemyBoss::Draw()
{
	CEnemy3D::Draw();	//親クラス
}

//================================================
//死亡時の処理
//================================================
void CEnemyBoss::Death()
{
	//スコアを加算
	CApplication::GetMode()->GetGame()->GetScore()->AddScore(NUM_SCORE);
}

//================================================
//移動
//================================================
void CEnemyBoss::Move()
{

}