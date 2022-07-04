//================================================
//
//制作実践基礎[bg.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "bg.h"
#include "object2D.h"
#include "application.h"
#include "renderer.h"

//***************************
//静的メンバ変数
//***************************
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_OBJECT] = {};

//================================================
//生成
//================================================
CBg* CBg::Create()
{
	CBg* pBg = nullptr;	//ポインタ

	//if (pBg != nullptr)
	//{//NULLチェック
	//	assert(false);
	//}

	///* nullptrの場合 */

	//pBg = new CBg;	//メモリの動的確保

	//pBg->Init();	//初期化

	return pBg;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CBg::CBg()
{
	//メンバ変数のクリア
	memset(&m_apTexture[0], 0, sizeof(m_apTexture));
	memset(&m_apObject2D[0], 0, sizeof(m_apObject2D));
}

//================================================
//デストラクタ
//================================================
CBg::~CBg()
{
}

//================================================
//初期化
//================================================
HRESULT CBg::Init()
{
	////デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	////頂点バッファの生成
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//							D3DUSAGE_WRITEONLY,
	//							FVF_VERTEX_2D,
	//							D3DPOOL_MANAGED,
	//							&m_pVtxBuff,
	//							NULL);

	//VERTEX_2D *pVtx;	//頂点情報へのポインタ

	////頂点バッファをロックし、頂点情報へのポインタを取得
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////頂点情報を設定
	//pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////rhwの設定
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////頂点カラーの設定
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	////テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	////頂点バッファをアンロックする
	//m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//終了
//================================================
void CBg::Uninit()
{
	////頂点バッファの破棄
	//if (m_pVtxBuff != nullptr)
	//{
	//	m_pVtxBuff->Release();
	//	m_pVtxBuff = nullptr;
	//}

	////テクスチャの破棄
	//if (m_pTexture != nullptr)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = nullptr;
	//}
}

//================================================
//更新
//================================================
void CBg::Update()
{
	
}

//================================================
//描画
//================================================
void CBg::Draw()
{
	////デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	////頂点バッファをデータストリームに設定
	//pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	////頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//CTexture* pTexture = CApplication::GetTexture();	//テクスチャを取得

	////テクスチャの設定
	//pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	////ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
	//						0,					//描画する最初の頂点インデックス
	//						2);					//描画するプリミティブ数
}