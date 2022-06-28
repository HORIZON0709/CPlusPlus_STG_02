//================================================
//
//制作実践基礎[explosion.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "explosion.h"
#include "renderer.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CExplosion::EXPLOSION_SIZE = 60.0f;	//サイズ

//================================================
//生成
//================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion* pExplosion = nullptr;	//ポインタ

	if (pExplosion != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pExplosion = new CExplosion;	//メモリの動的確保

	pExplosion->Init();	//初期化

	pExplosion->SetPos(pos);	//位置を設定

	return pExplosion;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CExplosion::CExplosion():
	m_nCntAnim(0),
	m_nPtnAnim(0)
{
	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::EXPLOSION);
}

//================================================
//デストラクタ
//================================================
CExplosion::~CExplosion()
{
}

//================================================
//初期化
//================================================
HRESULT CExplosion::Init()
{
	CObject2D::Init();	//親クラス

	//サイズを設定
	CObject2D::SetSize(EXPLOSION_SIZE);

	// テクスチャの設定
	CObject2D::SetTexture(CTexture::TEXTURE_explosion000);

	//テクスチャ座標の設定
	CObject2D::SetTexUV(DIVIDE_TEX_U, 0);

	return S_OK;
}

//================================================
//終了
//================================================
void CExplosion::Uninit()
{
	CObject2D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CExplosion::Update()
{
	CObject2D::Update();	//親クラス

	m_nCntAnim++;	//カウントアップ

	if (m_nCntAnim % 5 == 0)
	{//一定間隔
		//パターン番号を更新する
		m_nPtnAnim = (m_nPtnAnim + 1) % DIVIDE_TEX_U;

		//テクスチャ座標の設定
		CObject2D::SetTexUV(DIVIDE_TEX_U, m_nPtnAnim);
	}

	if (m_nPtnAnim == (DIVIDE_TEX_U - 1))
	{//アニメーションが終わったら
 		Release();	//解放
	}
}

//================================================
//描画
//================================================
void CExplosion::Draw()
{
	CObject2D::Draw();	//親クラス
}