//================================================
//
//制作実践基礎[item_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "item_3D.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "player_3D.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const int CItem3D::MAX_ITEM = 16;	//最大数

const float CItem3D::ITEM_SIZE = 40.0f;	//サイズ

//================================================
//生成
//================================================
CItem3D* CItem3D::Create(const D3DXVECTOR3 &pos, const CItem3D::TYPE type)
{
	CItem3D* pItem3D = nullptr;	//ポインタ

	if (pItem3D != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pItem3D = new CItem3D;	//メモリの動的確保

	pItem3D->Init();		//初期化
	pItem3D->SetPos(pos);	//位置を設定
	pItem3D->m_type = type;	//タイプを設定
	
	pItem3D->SetTexForEachItem();	//アイテム毎のテクスチャの設定

	return pItem3D;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CItem3D::CItem3D():
	m_type(CItem3D::TYPE::NONE)
{
	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::ITEM);
}

//================================================
//デストラクタ
//================================================
CItem3D::~CItem3D()
{
}

//================================================
//初期化
//================================================
HRESULT CItem3D::Init()
{
	CObject3D::Init();	//親クラス

	//メンバ変数の初期設定
	m_type = CItem3D::TYPE::NONE;

	//サイズを設定
	D3DXVECTOR3 size = D3DXVECTOR3(ITEM_SIZE, ITEM_SIZE, 0.0f);
	CObject3D::SetSize(size);

	return S_OK;
}

//================================================
//終了
//================================================
void CItem3D::Uninit()
{
	CObject3D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CItem3D::Update()
{
	CObject3D::Update();	//親クラス

	if (CObject3D::Collision(OBJ_TYPE::ITEM, OBJ_TYPE::PLAYER))
	{//プレイヤーと当たったら
		CPlayer3D* pPlayer = CGame::GetPlayer3D();	//プレイヤー情報の取得

		//プレイヤーに、当たったアイテムのタイプを送る
		pPlayer->SetItem(m_type);

		Release();	//自身の解放
	}
}

//================================================
//描画
//================================================
void CItem3D::Draw()
{
	CObject3D::Draw();	//親クラス
}

//================================================
//アイテム毎のテクスチャの設定
//================================================
void CItem3D::SetTexForEachItem()
{
	switch (m_type)
	{
	case CHANGE_BUlLET_NORMAL: /* 通常弾に変更 */
		CObject3D::SetTexture(CTexture::item001);	// テクスチャの設定
		break;

	case CHANGE_BUlLET_DOUBLE: /* 二連弾に変更 */
		CObject3D::SetTexture(CTexture::item002);	// テクスチャの設定
		break;

	case CHANGE_BUlLET_TRIPLE: /* 三連各散弾に変更 */
		CObject3D::SetTexture(CTexture::item003);	// テクスチャの設定
		break;

	default:
		break;
	}
}