//================================================
//
//制作実践基礎[explosion_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "explosion_3D.h"
#include "renderer.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CExplosion3D::EXPLOSION_SIZE = 60.0f;	//サイズ

const int CExplosion3D::DIVIDE_TEX_U = 5;	//テクスチャの分割数( U方向 )
const int CExplosion3D::DIVIDE_TEX_V = 8;	//テクスチャの分割数( V方向 )
const int CExplosion3D::ANIM_SPEED = 1;		//アニメーション速度

//テクスチャの総パターン数
const int CExplosion3D::NUM_PATTERN = (DIVIDE_TEX_U * DIVIDE_TEX_V);

//================================================
//生成
//================================================
CExplosion3D* CExplosion3D::Create(D3DXVECTOR3 pos)
{
	CExplosion3D* pExplosion3D = nullptr;	//ポインタ

	if (pExplosion3D != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pExplosion3D = new CExplosion3D;	//メモリの動的確保

	pExplosion3D->Init();	//初期化

	pExplosion3D->SetPos(pos);	//位置を設定

	return pExplosion3D;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CExplosion3D::CExplosion3D():
	m_nCntAnim(0),
	m_nPtnAnim(0)
{
	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::EXPLOSION);
}

//================================================
//デストラクタ
//================================================
CExplosion3D::~CExplosion3D()
{
}

//================================================
//初期化
//================================================
HRESULT CExplosion3D::Init()
{
	CObject3D::Init();	//親クラス

	//サイズを設定
	D3DXVECTOR2 size = D3DXVECTOR2(EXPLOSION_SIZE, EXPLOSION_SIZE);
	CObject3D::SetSize(size);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::explosion001);

	//テクスチャ座標の設定
	CObject3D::SetTexUV(DIVIDE_TEX_U, DIVIDE_TEX_V, 0);

	return S_OK;
}

//================================================
//終了
//================================================
void CExplosion3D::Uninit()
{
	CObject3D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CExplosion3D::Update()
{
	CObject3D::Update();	//親クラス

	m_nCntAnim++;	//カウントアップ

	if (m_nCntAnim % ANIM_SPEED == 0)
	{//一定間隔
		//パターン番号を更新する
		m_nPtnAnim = (m_nPtnAnim + 1) % NUM_PATTERN;

		//テクスチャ座標の設定
		CObject3D::SetTexUV(DIVIDE_TEX_U, DIVIDE_TEX_V, m_nPtnAnim);
	}

	if (m_nPtnAnim == (NUM_PATTERN - 1))
	{//アニメーションが終わったら
 		Release();	//解放
	}
}

//================================================
//描画
//================================================
void CExplosion3D::Draw()
{
	CObject3D::Draw();	//親クラス
}