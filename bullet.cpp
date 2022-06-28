//================================================
//
//制作実践基礎[bullet.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "bullet.h"
#include "renderer.h"
#include "explosion.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CBullet::BULLET_SIZE = 50.0f;	//サイズ

//================================================
//生成
//================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos)
{
	CBullet* pBullet = nullptr;	//ポインタ

	if (pBullet != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pBullet = new CBullet;	//メモリの動的確保

	pBullet->Init();	//初期化

	pBullet->SetPos(pos);	//位置を設定

	return pBullet;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CBullet::CBullet():
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::BULLET);
}

//================================================
//デストラクタ
//================================================
CBullet::~CBullet()
{
}

//================================================
//初期化
//================================================
HRESULT CBullet::Init()
{
	CObject2D::Init();	//親クラス

	//サイズを設定
	CObject2D::SetSize(BULLET_SIZE);

	//移動量を設定
	m_move = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	// テクスチャの設定
	CObject2D::SetTexture(CTexture::TEXTURE_circle_sakura2);

	return S_OK;
}

//================================================
//終了
//================================================
void CBullet::Uninit()
{
	CObject2D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CBullet::Update()
{
	CObject2D::Update();	//親クラス

	D3DXVECTOR3 pos = CObject2D::GetPos();	//位置設定用

	pos.y -= m_move.y;	//位置を更新

	CObject2D::SetPos(pos);	//更新した位置を設定

	Collision();	//当たり判定

	if ((pos.x < 0) ||							//左端
		(pos.x > CRenderer::SCREEN_WIDTH) ||	//右端
		((pos.y - BULLET_SIZE * 0.5f) < 0) ||	//上端
		(pos.y > CRenderer::SCREEN_HEIGHT))		//下端
	{//指定した範囲から出たら
		//爆発の生成
		CExplosion* pExplosion = CExplosion::Create(pos);

		Release();	//解放
	}
}

//================================================
//描画
//================================================
void CBullet::Draw()
{
	CObject2D::Draw();	//親クラス
}

//================================================
//当たり判定
//================================================
void CBullet::Collision()
{
	D3DXVECTOR3 pos = CObject2D::GetPos();	//位置設定用

	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject* pObject = GetObjects(i);	//オブジェクト情報の取得

		if (pObject == nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		CObject::OBJ_TYPE type = pObject->GetObjType();	//タイプの取得

		if (type != CObject::OBJ_TYPE::ENEMY)
		{//「 タイプ：敵 」ではない場合
			continue;
		}

		/* 「 タイプ：敵 」の場合 */

		/* 自身の判定用 */
		float fLeft		= (pos.x - (BULLET_SIZE * 0.5f));	//左端
		float fRight	= (pos.x + (BULLET_SIZE * 0.5f));	//右端
		float fTop		= (pos.y - (BULLET_SIZE * 0.5f));	//上端
		float fBottom	= (pos.y + (BULLET_SIZE * 0.5f));	//下端

		D3DXVECTOR3 posTarget = pObject->GetPos();	//対象の位置を取得
		float fSizeTarget = pObject->GetSize();		//対象のサイズを取得

		/* 対象の判定用 */
		float fLeftTarget	= (posTarget.x - (fSizeTarget * 0.5f));	//左端
		float fRightTarget	= (posTarget.x + (fSizeTarget * 0.5f));	//右端
		float fTopTarget	= (posTarget.y - (fSizeTarget * 0.5f));	//上端
		float fBottomTarget	= (posTarget.y + (fSizeTarget * 0.5f));	//下端

		if (fLeft <= fRightTarget
			&& fRight >= fLeftTarget
			&& fTop <= fBottomTarget
			&& fBottom >= fTopTarget)
		{//弾が対象の範囲内に来た場合
			//爆発の生成
			CExplosion* pExplosion = CExplosion::Create(posTarget);
			
			pObject->Release();	//対象の解放
			break;
		}
	}
}