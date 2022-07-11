//================================================
//
//制作実践基礎[enemy_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "enemy_3D.h"
#include "renderer.h"
#include "bullet_3D.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CEnemy3D::ENEMY_SIZE = 90.0f;	//サイズ

//================================================
//生成
//================================================
CEnemy3D* CEnemy3D::Create()
{
	CEnemy3D* pEnemy3D = nullptr;	//ポインタ

	if (pEnemy3D != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pEnemy3D = new CEnemy3D;	//メモリの動的確保

	pEnemy3D->Init();	//初期化

	//位置を設定
	D3DXVECTOR3 pos = D3DXVECTOR3(200.0f, 0.0f, 0.0f);
	pEnemy3D->SetPos(pos);

	return pEnemy3D;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CEnemy3D::CEnemy3D():
	m_nTimerInterval(0)
{
	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::ENEMY);
}

//================================================
//デストラクタ
//================================================
CEnemy3D::~CEnemy3D()
{
}

//================================================
//初期化
//================================================
HRESULT CEnemy3D::Init()
{
	CObject3D::Init();	//親クラス

	//サイズを設定
	D3DXVECTOR2 size = D3DXVECTOR2(ENEMY_SIZE, ENEMY_SIZE);
	CObject3D::SetSize(size);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::TEXTURE_全部違う);

	return S_OK;
}

//================================================
//終了
//================================================
void CEnemy3D::Uninit()
{
	CObject3D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CEnemy3D::Update()
{
	CObject3D::Update();	//親クラス

	D3DXVECTOR3 pos = CObject3D::GetPos();	//位置情報を取得

	m_nTimerInterval++;	//タイマーを進める

	if (m_nTimerInterval % SHOT_INTERVAL == 0)
	{//タイマーが一定時間になったら
		D3DXVECTOR3 move = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);	//移動量設定用

		CBullet3D::Create(pos, move, CObject::OBJ_TYPE::ENEMY);	//弾の生成
	}
}

//================================================
//描画
//================================================
void CEnemy3D::Draw()
{
	CObject3D::Draw();	//親クラス
}