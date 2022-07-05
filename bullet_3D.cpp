//================================================
//
//制作実践基礎[bullet_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "bullet_3D.h"
#include "renderer.h"
#include "explosion_3D.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CBullet3D::BULLET_SIZE = 30.0f;	//サイズ

//================================================
//生成
//================================================
CBullet3D* CBullet3D::Create(D3DXVECTOR3 pos, CObject::OBJ_TYPE haveType)
{
	CBullet3D* pBullet3D = nullptr;	//ポインタ

	if (pBullet3D != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pBullet3D = new CBullet3D;	//メモリの動的確保

	pBullet3D->Init();	//初期化

	pBullet3D->SetPos(pos);	//位置を設定

	pBullet3D->SetHaveType(haveType);	//所有者を設定

	return pBullet3D;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CBullet3D::CBullet3D():
	m_haveType(CObject::OBJ_TYPE::NONE)
{
	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::BULLET);
}

//================================================
//デストラクタ
//================================================
CBullet3D::~CBullet3D()
{
}

//================================================
//初期化
//================================================
HRESULT CBullet3D::Init()
{
	CObject3D::Init();	//親クラス

	//サイズを設定
	CObject3D::SetSize(BULLET_SIZE);

	//移動量を設定
	D3DXVECTOR3 move = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	CObject3D::SetMove(move);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::TEXTURE_circle_sakura2);

	return S_OK;
}

//================================================
//終了
//================================================
void CBullet3D::Uninit()
{
	CObject3D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CBullet3D::Update()
{
	CObject3D::Update();	//親クラス

	D3DXVECTOR3 pos = CObject3D::GetPos();		//位置設定用
	D3DXVECTOR3 move = CObject3D::GetMove();	//移動量設定用

	pos.x += move.x;
	//pos.y -= move.y;	//位置を更新

	CObject3D::SetPos(pos);	//更新した位置を設定

	Collision();	//当たり判定

	float fLeft		= (pos.x - (BULLET_SIZE * 0.5f));	//左端
	float fRight	= (pos.x + (BULLET_SIZE * 0.5f));	//右端
	float fTop		= (pos.y + (BULLET_SIZE * 0.5f));	//上端
	float fBottom	= (pos.y - (BULLET_SIZE * 0.5f));	//下端]

	float fRimitHeight = (CRenderer::SCREEN_HEIGHT * 0.5f);	//制限(上下)
	float fRimitWidth = (CRenderer::SCREEN_WIDTH * 0.25f);		//制限(左右)

	if ((fLeft < -fRimitWidth) ||	//左端
		(fRight > fRimitWidth) ||	//右端
		(fTop > fRimitHeight) ||	//上端
		(fBottom < -fRimitHeight))	//下端
	{//指定した範囲から出たら
		//爆発の生成
		CExplosion3D::Create(pos);

		Release();	//解放
	}
}

//================================================
//描画
//================================================
void CBullet3D::Draw()
{
	CObject3D::Draw();	//親クラス
}

//================================================
//当たり判定
//================================================
void CBullet3D::Collision()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//位置設定用

	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject* pObject = GetObjects(i);	//オブジェクト情報の取得

		if (pObject == nullptr || pObject == this)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		CObject::OBJ_TYPE type = pObject->GetObjType();	//タイプの取得

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
		float fTop		= (pos.y + (BULLET_SIZE * 0.5f));	//上端
		float fBottom	= (pos.y - (BULLET_SIZE * 0.5f));	//下端

		D3DXVECTOR3 posTarget = pObject->GetPos();	//対象の位置を取得
		float fSizeTarget = pObject->GetSize();		//対象のサイズを取得

		/* 対象の判定用 */
		float fLeftTarget	= (posTarget.x - (fSizeTarget * 0.5f));	//左端
		float fRightTarget	= (posTarget.x + (fSizeTarget * 0.5f));	//右端
		float fTopTarget	= (posTarget.y + (fSizeTarget * 0.5f));	//上端
		float fBottomTarget = (posTarget.y - (fSizeTarget * 0.5f));	//下端

		if (fLeft <= fRightTarget
			&& fRight >= fLeftTarget
			&& fTop >= fBottomTarget
			&& fBottom <= fTopTarget)
		{//弾が対象の範囲内に来た場合
			//爆発の生成
			CExplosion3D::Create(posTarget);

			pObject->Release();	//対象の解放

			Release();	//自身の解放
			break;
		}
	}
}

//================================================
//所有者を設定
//================================================
void CBullet3D::SetHaveType(CObject::OBJ_TYPE haveType)
{
	m_haveType = haveType;
}

//================================================
//所有者を取得
//================================================
CObject::OBJ_TYPE CBullet3D::GetHaveType()
{
	return m_haveType;
}