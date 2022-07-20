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
#include "application.h"
#include "renderer.h"
#include "explosion_3D.h"

#include "item_3D.h"

#include "camera.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CBullet3D::BULLET_SIZE = 30.0f;	//サイズ

//================================================
//生成
//================================================
CBullet3D* CBullet3D::Create(const D3DXVECTOR3 &pos,
							 const D3DXVECTOR3 &move,
							 const CObject::OBJ_TYPE &haveType)
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

	pBullet3D->SetMove(move);	//移動量を設定

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
	D3DXVECTOR2 size = D3DXVECTOR2(BULLET_SIZE, BULLET_SIZE);
	CObject3D::SetSize(size);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::bullet001);

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

	pos += move;	//位置を更新

	CObject3D::SetPos(pos);	//更新した位置を設定

	IsCollision();	//当たり判定

	float fLeft		= (pos.x - (BULLET_SIZE * 0.5f));	//左端
	float fRight	= (pos.x + (BULLET_SIZE * 0.5f));	//右端
	float fTop		= (pos.y + (BULLET_SIZE * 0.5f));	//上端
	float fBottom	= (pos.y - (BULLET_SIZE * 0.5f));	//下端

	//カメラ情報の取得
	D3DXMATRIX mtxCamera = CApplication::GetCamera()->GetMatrixView();
	
	//カメラの視点の位置を取得
	D3DXVECTOR3 posV = CApplication::GetCamera()->GetPosV();

	//位置を反映
	D3DXMatrixTranslation(&mtxCamera, posV.x, posV.y, posV.z);

	//移動制限を設定
	float fRimitTop		= (mtxCamera._42 + (CRenderer::SCREEN_HEIGHT * 0.5f));	//上
	float fRimitBottom	= (mtxCamera._42 - (CRenderer::SCREEN_HEIGHT * 0.5f));	//下
	float fRimitLeft	= (mtxCamera._41 - (CRenderer::SCREEN_WIDTH * 0.5f));	//左
	float fRimitRight	= (mtxCamera._41 + (CRenderer::SCREEN_WIDTH * 0.5f));	//右

	if ((fLeft < fRimitLeft) ||		//左端
		(fRight > fRimitRight) ||	//右端
		(fTop > fRimitTop) ||		//上端
		(fBottom < fRimitBottom))	//下端
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
void CBullet3D::IsCollision()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//位置設定用

	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject* pObjectTarget = GetObjects(i);	//対象の情報の取得

		if (pObjectTarget == nullptr || pObjectTarget == this)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		CObject::OBJ_TYPE typeTarget = pObjectTarget->GetObjType();	//タイプの取得

		if (!(((GetHaveType() == CObject::PLAYER) && (typeTarget == CObject::ENEMY)) || 
			((GetHaveType() == CObject::ENEMY) && (typeTarget == CObject::PLAYER))))
			/*
			『「所有者がプレイヤー　かつ　対象が敵」
			もしくは
			「所有者が敵　かつ　対象がプレイヤー」』
			ではない
			*/
		{
			continue;
		}

		/* 自身の判定用 */
		float fLeft		= (pos.x - (BULLET_SIZE * 0.5f));	//左端
		float fRight	= (pos.x + (BULLET_SIZE * 0.5f));	//右端
		float fTop		= (pos.y + (BULLET_SIZE * 0.5f));	//上端
		float fBottom	= (pos.y - (BULLET_SIZE * 0.5f));	//下端

		CObject3D* pObjTarget3D = (CObject3D*)pObjectTarget;	//CObject3D型にキャスト

		D3DXVECTOR3 posTarget = pObjTarget3D->GetPos();		//対象の位置を取得
		D3DXVECTOR2 sizeTarget = pObjTarget3D->GetSize();	//対象のサイズを取得

		/* 対象の判定用 */
		float fLeftTarget	= (posTarget.x - (sizeTarget.x * 0.5f));	//左端
		float fRightTarget	= (posTarget.x + (sizeTarget.x * 0.5f));	//右端
		float fTopTarget	= (posTarget.y + (sizeTarget.y * 0.5f));	//上端
		float fBottomTarget = (posTarget.y - (sizeTarget.y * 0.5f));	//下端

		if (fLeft < fRightTarget
			&& fRight > fLeftTarget
			&& fTop > fBottomTarget
			&& fBottom < fTopTarget)
		{//弾が対象の範囲内に来た場合
			CExplosion3D::Create(posTarget);	//爆発の生成

			pObjTarget3D->Release();	//対象の解放

			Release();	//自身の解放
			break;
		}
	}
}

//================================================
//所有者を設定
//================================================
void CBullet3D::SetHaveType(const CObject::OBJ_TYPE &haveType)
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