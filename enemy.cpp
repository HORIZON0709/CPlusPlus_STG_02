//================================================
//
//制作実践基礎[enemy.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "enemy.h"
#include "renderer.h"
#include "bullet.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CEnemy::ENEMY_SIZE = 120.0f;	//サイズ

//================================================
//生成
//================================================
CEnemy* CEnemy::Create()
{
	CEnemy* pEnemy = nullptr;	//ポインタ

	if (pEnemy != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pEnemy = new CEnemy;	//メモリの動的確保

	pEnemy->Init();	//初期化

	D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.8f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);
	pEnemy->SetPos(pos);	//位置を設定

	return pEnemy;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CEnemy::CEnemy():
	m_nTimerInterval(0)
{
	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::ENEMY);
}

//================================================
//デストラクタ
//================================================
CEnemy::~CEnemy()
{
}

//================================================
//初期化
//================================================
HRESULT CEnemy::Init()
{
	CObject2D::Init();	//親クラス

	//サイズを設定
	D3DXVECTOR2 size = D3DXVECTOR2(ENEMY_SIZE, ENEMY_SIZE);
	CObject2D::SetSize(size);

	// テクスチャの設定
	CObject2D::SetTexture(CTexture::enemy000);

	return S_OK;
}

//================================================
//終了
//================================================
void CEnemy::Uninit()
{
	CObject2D::Uninit();	//親クラス


}

//================================================
//更新
//================================================
void CEnemy::Update()
{
	CObject2D::Update();	//親クラス

	D3DXVECTOR3 pos = CObject2D::GetPos();	//位置情報を取得

	m_nTimerInterval++;	//タイマーを進める

	if (m_nTimerInterval % SHOT_INTERVAL == 0)
	{//タイマーが一定時間になったら
		CBullet::Create(pos, CObject::OBJ_TYPE::ENEMY);	//弾の生成
	}
}

//================================================
//描画
//================================================
void CEnemy::Draw()
{
	CObject2D::Draw();	//親クラス
}