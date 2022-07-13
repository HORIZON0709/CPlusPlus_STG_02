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
const float CBullet::BULLET_SIZE = 30.0f;	//サイズ

//================================================
//生成
//================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, CObject::OBJ_TYPE haveType)
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

	pBullet->SetHaveType(haveType);	//所有者を設定

	return pBullet;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CBullet::CBullet():
	m_haveType(CObject::OBJ_TYPE::NONE)
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
	D3DXVECTOR2 size = D3DXVECTOR2(BULLET_SIZE, BULLET_SIZE);
	CObject2D::SetSize(size);

	//移動量を設定
	D3DXVECTOR3 move = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	CObject2D::SetMove(move);

	// テクスチャの設定
	CObject2D::SetTexture(CTexture::bullet000);

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

	D3DXVECTOR3 pos = CObject2D::GetPos();		//位置設定用
	D3DXVECTOR3 move = CObject2D::GetMove();	//移動量設定用

	pos.x += move.x;
	//pos.y -= move.y;	//位置を更新

	CObject2D::SetPos(pos);	//更新した位置を設定

	Collision();	//当たり判定

	if ((pos.x < 0) ||							//左端
		(pos.x > CRenderer::SCREEN_WIDTH) ||	//右端
		((pos.y - BULLET_SIZE * 0.5f) < 0) ||	//上端
		(pos.y > CRenderer::SCREEN_HEIGHT))		//下端
	{//指定した範囲から出たら
		//爆発の生成
		CExplosion::Create(pos);

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
		CObject* pObjectTarget = GetObjects(i);	//対象の情報の取得

		if (pObjectTarget == nullptr || pObjectTarget == this)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		CObject::OBJ_TYPE type = pObjectTarget->GetObjType();	//タイプの取得

		if (!((GetHaveType() == CObject::PLAYER) && (type == CObject::ENEMY) || 
			(GetHaveType() == CObject::ENEMY) && (type == CObject::PLAYER)))
			/*
			「所有者がプレイヤー　かつ　対象が敵」ではない
			もしくは
			「所有者が敵　かつ　対象がプレイヤー」
			*/
		{
			continue;
		}

		/* 自身の判定用 */
		float fLeft		= (pos.x - (BULLET_SIZE * 0.5f));	//左端
		float fRight	= (pos.x + (BULLET_SIZE * 0.5f));	//右端
		float fTop		= (pos.y - (BULLET_SIZE * 0.5f));	//上端
		float fBottom	= (pos.y + (BULLET_SIZE * 0.5f));	//下端

		CObject2D* pObjTarget2D = (CObject2D*)pObjectTarget;	//CObject2D型にキャスト

		D3DXVECTOR3 posTarget = pObjTarget2D->GetPos();		//対象の位置を取得
		D3DXVECTOR2 sizeTarget = pObjTarget2D->GetSize();	//対象のサイズを取得

		/* 対象の判定用 */
		float fLeftTarget	= (posTarget.x - (sizeTarget.x * 0.5f));	//左端
		float fRightTarget	= (posTarget.x + (sizeTarget.x * 0.5f));	//右端
		float fTopTarget	= (posTarget.y - (sizeTarget.y * 0.5f));	//上端
		float fBottomTarget = (posTarget.y + (sizeTarget.y * 0.5f));	//下端

		if (fLeft <= fRightTarget
			&& fRight >= fLeftTarget
			&& fTop <= fBottomTarget
			&& fBottom >= fTopTarget)
		{//弾が対象の範囲内に来た場合
			CExplosion::Create(posTarget);	//爆発の生成

			pObjTarget2D->Release();	//対象の解放

			Release();	//自身の解放
			break;
		}
	}
}

//================================================
//所有者を設定
//================================================
void CBullet::SetHaveType(CObject::OBJ_TYPE haveType)
{
	m_haveType = haveType;
}

//================================================
//所有者を取得
//================================================
CObject::OBJ_TYPE CBullet::GetHaveType()
{
	return m_haveType;
}