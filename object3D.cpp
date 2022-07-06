//================================================
//
//制作実践基礎[object3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "object3D.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//================================================
//生成
//================================================
CObject3D* CObject3D::Create()
{
	CObject3D* pObject3D = nullptr;	//ポインタ

	if (pObject3D != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pObject3D = new CObject3D;	//メモリの動的確保

	pObject3D->Init();	//初期化

	return pObject3D;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CObject3D::CObject3D() :
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_texture(CTexture::TEXTURE_NONE),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f,0.0f))
{
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
}

//================================================
//デストラクタ
//================================================
CObject3D::~CObject3D()
{
	/* 解放漏れの確認 */
	assert(m_pTexture == nullptr);
	assert(m_pVtxBuff == nullptr);
}

//================================================
//初期化
//================================================
HRESULT CObject3D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//メンバ変数の初期設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_texture = CTexture::TEXTURE_NONE;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_3D,
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//終了
//================================================
void CObject3D::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//================================================
//更新
//================================================
void CObject3D::Update()
{
	
}

//================================================
//描画
//================================================
void CObject3D::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ライトを切る
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	CTexture* pTexture = CApplication::GetTexture();	//テクスチャを取得

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
							0,					//描画する最初の頂点インデックス
							2);					//描画するプリミティブ数

	//テクスチャの設定
	pDevice->SetTexture(0, nullptr);
}

//================================================
//位置を設定
//================================================
void CObject3D::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

//================================================
//位置を取得
//================================================
D3DXVECTOR3 CObject3D::GetPos()
{
	return m_pos;
}

//================================================
//テクスチャの設定
//================================================
void CObject3D::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//================================================
//テクスチャ座標の設定(アニメーションに対応)
//================================================
void CObject3D::SetTexUV(const int &nDivNum, const int &nPtnAnim)
{
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

 	float fDivide = (1.0f / nDivNum);	//乗算用にfloatに変換

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(fDivide * nPtnAnim,		0.0f);
	pVtx[1].tex = D3DXVECTOR2(fDivide * (nPtnAnim + 1), 0.0f);
 	pVtx[2].tex = D3DXVECTOR2(fDivide * nPtnAnim,		1.0f);
	pVtx[3].tex = D3DXVECTOR2(fDivide * (nPtnAnim + 1), 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//サイズの設定
//================================================
void CObject3D::SetSize(const D3DXVECTOR2 &size)
{
	m_size = size;	//サイズを設定

	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fWidthHalf = (m_size.x * 0.5f);	//横幅の半分
	float fHeightHalf = (m_size.y * 0.5f);	//縦幅の半分

	//頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(-fWidthHalf, +fHeightHalf, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+fWidthHalf, +fHeightHalf, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fWidthHalf, -fHeightHalf, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+fWidthHalf, -fHeightHalf, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================================
//サイズの取得
//================================================
D3DXVECTOR2 CObject3D::GetSize()
{
	return m_size;
}

//================================================
//移動量の設定
//================================================
void CObject3D::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//================================================
//移動量の取得
//================================================
D3DXVECTOR3 CObject3D::GetMove()
{
	return m_move;
}