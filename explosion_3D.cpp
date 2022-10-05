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
#include "application.h"
#include "renderer.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CExplosion3D::EXPLOSION_SIZE = 120.0f;	//サイズ

const int CExplosion3D::ANIM_SPEED = 1;		//アニメーション速度

//***************************
//静的メンバ変数
//***************************
CTexture::TEXTURE CExplosion3D::m_tex = CTexture::TEXTURE::NONE;	//テクスチャ

//================================================
//生成
//================================================
CExplosion3D* CExplosion3D::Create(const D3DXVECTOR3 &pos, const CTexture::TEXTURE &texture)
{
	CExplosion3D* pExplosion3D = nullptr;	//ポインタ

	if (pExplosion3D != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pExplosion3D = new CExplosion3D;	//メモリの動的確保

	m_tex = texture;	//何のテクスチャかを保存

	pExplosion3D->Init();	//初期化

	pExplosion3D->SetPos(pos);	//位置を設定

	return pExplosion3D;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CExplosion3D::CExplosion3D():
	m_nDivideTexU(0),
	m_nDivideTexV(0),
	m_nNumPtnAll(0),
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

	//メンバ変数の初期化
	m_nCntAnim = 0;
	m_nPtnAnim = 0;

	//サイズを設定
	D3DXVECTOR2 size = D3DXVECTOR2(EXPLOSION_SIZE, EXPLOSION_SIZE);
	CObject3D::SetSize(size);

	//テクスチャの座標
	CObject3D::SetTexture(m_tex);

	if (m_tex == CTexture::TEXTURE::explosion001)
	{
		//分割数を設定
		m_nDivideTexU = 5;	//U方向
		m_nDivideTexV = 8;	//V方向
	}
	else if (m_tex == CTexture::TEXTURE::explosion002)
	{
		//分割数を設定
		m_nDivideTexU = 5;	//U方向
		m_nDivideTexV = 10;	//V方向
	}

	//総パターン数を設定
	m_nNumPtnAll = (m_nDivideTexU * m_nDivideTexV);

	//テクスチャ座標の設定
	CObject3D::SetTexUV(m_nDivideTexU, m_nDivideTexV, 0);

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
		m_nPtnAnim = (m_nPtnAnim + 1) % m_nNumPtnAll;

		//テクスチャ座標の設定
		CObject3D::SetTexUV(m_nDivideTexU, m_nDivideTexV, m_nPtnAnim);
	}

	if (m_nPtnAnim == (m_nNumPtnAll - 1))
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