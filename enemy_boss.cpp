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
#include "fade.h"

#include "camera.h"
#include "explosion_3D.h"
#include "bullet_3D.h"
#include "score.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CEnemyBoss::START_POS_X = 0.0f;		//初期位置( X )
const float CEnemyBoss::START_POS_Y = 220.0f;	//初期位置( Y )

const float CEnemyBoss::ENEMY_SIZE = 270.0f;	//サイズ
const float CEnemyBoss::CURVE_SIZE = 0.003f;	//カーブの大きさ

const float CEnemyBoss::MOVE_SPEED_X = 4.0f;	//移動スピード( X )
const float CEnemyBoss::MOVE_SPEED_Y = 
{//移動スピード( Y )
	CGame::GetCamera()->SCROLL_SPEED * CGame::GetCamera()->MOVE_SPEED
};

const float CEnemyBoss::SHOT_SPEED = 3.0f;	//弾のスピード

const int CEnemyBoss::SHOT_INTERVAL = 120;	//弾の連続発射の間隔
const int CEnemyBoss::NUM_SCORE = 100;		//獲得スコア量
const int CEnemyBoss::NUM_BULLETS = 8;		//同時発射数
const int CEnemyBoss::MAX_LIFE = 30;		//体力の最大値

//================================================
//コンストラクタ
//================================================
CEnemyBoss::CEnemyBoss():
	m_fCurve(0.0f),
	m_nTimerInterval(0),
	m_nLife(0),
	m_nCnt(0),
	m_state(STATE::NONE)
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

	//メンバ変数の初期化
	m_fCurve = 0.0f;
	m_nTimerInterval = 0;
	m_nLife = MAX_LIFE;
	m_nCnt = 0;
	m_state = STATE::NORMAL;

	//サイズを設定
	D3DXVECTOR2 size = D3DXVECTOR2(ENEMY_SIZE, ENEMY_SIZE);
	CObject3D::SetSize(size);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::enemy002);

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
	if (CApplication::GetFade()->GetState() == CFade::STATE::FADE_OUT)
	{//暗転中
		return;
	}

	CEnemy3D::Update();	//親クラス
	
	//移動
	Move();

	//弾の発射
	Shot();

	//状態毎の処理
	State();
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
	//爆発を生成
	CExplosion3D::Create(CObject3D::GetPos(), CTexture::TEXTURE::explosion001);

	//スコアを加算
	CGame::GetScore()->AddScore(NUM_SCORE);
}

//================================================
//体力の減算
//================================================
void CEnemyBoss::SubLife(const int nDamage)
{
	//減算
	m_nLife -= nDamage;

	//ダメージ状態にする
	m_state = STATE::DAMAGE;
}

//================================================
//体力の取得
//================================================
int CEnemyBoss::GetLife()
{
	return m_nLife;
}

//================================================
//移動
//================================================
void CEnemyBoss::Move()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();		//位置を取得
	D3DXVECTOR3 move = CObject3D::GetMove();	//移動量を取得

	//加算
	m_fCurve += CURVE_SIZE;

	//sinカーブ
	move.x = cosf(D3DX_PI * m_fCurve) * MOVE_SPEED_X;

	//カメラに合わせてY軸を常時移動
	move.y = MOVE_SPEED_Y;

	//移動量を位置に加算
	pos += move;

	CObject3D::SetPos(pos);	//位置を設定
}

//================================================
//弾の発射
//================================================
void CEnemyBoss::Shot()
{
	m_nTimerInterval++;	//タイマーを進める

	if (m_nTimerInterval % SHOT_INTERVAL != 0)
	{//タイマーが一定時間経過していない場合
		return;
	}

	/* タイマーが一定時間経過した場合 */

	D3DXVECTOR3 pos = CObject3D::GetPos();	//位置を取得

	for (int i = 0; i < (NUM_BULLETS / 2); i++)
	{
		//移動量の設定
		float x = sinf(D3DX_PI * (1.0f / NUM_BULLETS) * i) * SHOT_SPEED;
		float y = cosf(D3DX_PI * (1.0f / NUM_BULLETS) * i) * SHOT_SPEED;

		/* 弾の生成 */

		//+方向
		CBullet3D::Create(pos,						//位置
						  D3DXVECTOR3(x, -y, 0.0f),	//移動量
						  CObject::OBJ_TYPE::ENEMY,	//所有者
						  CTexture::bullet005);		//テクスチャ

		//-方向
		CBullet3D::Create(pos,							//位置
						  D3DXVECTOR3(-x, -y, 0.0f),	//移動量
						  CObject::OBJ_TYPE::ENEMY,		//所有者
						  CTexture::bullet005);			//テクスチャ
	}
}

//================================================
//状態毎の処理
//================================================
void CEnemyBoss::State()
{
	switch (m_state)
	{
	case STATE::DAMAGE: /* ダメージ状態 */
	{
		D3DXCOLOR colRed = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//赤(ダメージ状態)
		D3DXCOLOR colNormal = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//白(元の状態)

		//色を赤にする
		CObject3D::SetCol(colRed);

		m_nCnt++;	//カウントアップ

		if (m_nCnt % 20 != 0)
		{
			break;
		}

		/* 一定数カウントしたら */

		//色を元に戻す
		CObject3D::SetCol(colNormal);

		//通常状態にする
		m_state = STATE::NONE;
		break;
	}
	case STATE::NONE: /* 上記以外 */
	case STATE::NORMAL:
	case STATE::MAX:
	default:
		break;
	}
}