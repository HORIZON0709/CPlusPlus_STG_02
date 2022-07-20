//================================================
//
//制作実践基礎[object2D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//***************************
//インクルード
//***************************
#include "object.h"
#include "texture.h"

//***************************
//定数の定義
//***************************
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);	//頂点フォーマット

//***************************
//オブジェクトクラスの定義
//***************************
class CObject2D : public CObject
{/* CObjectの派生クラス */
public: /* 構造体の定義 */
	struct VERTEX_2D
	{//頂点データ
		D3DXVECTOR3 pos;	//位置
		float rhw;			//法線
		D3DCOLOR col;		//色
		D3DXVECTOR2 tex;	//テクスチャ座標
	};

public: /* 静的メンバ関数 */
	static CObject2D* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CObject2D();
	~CObject2D() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

public: /* Pos */
	/*
		位置を設定
		const D3DXVECTOR3 &pos ---> 任意の位置
	*/
	void SetPos(const D3DXVECTOR3 &pos);

	/*
		位置を取得
	*/
	D3DXVECTOR3 GetPos();

public: /* Size */
	/*
		サイズを設定
		const D3DXVECTOR2 &size ---> 任意のサイズ
	*/
	void SetSize(const D3DXVECTOR2 &size);

	/*
		サイズを取得
	*/
	D3DXVECTOR2 GetSize();

public: /* Move */
	/*
		移動量を設定
		const D3DXVECTOR3 &move ---> 任意の移動量
	*/
	void SetMove(const D3DXVECTOR3 &move);

	/*
		移動量を取得
	*/
	D3DXVECTOR3 GetMove();

public: /* Texture */
	/*
		テクスチャの設定
		CTexture::TEXTURE texture ---> 任意のテクスチャ
	*/
	void SetTexture(CTexture::TEXTURE texture);

	/*
		テクスチャ座標の設定(アニメーション対応)
		const int &nDivNum ---> テクスチャの分割数
		const int &nPtnAnim ---> アニメーションパターン数
		(単体画像の場合は「1,0」を送る。)
	*/
	void SetTexUV(const int &nDivNum,const int &nPtnAnim);

private: /* メンバ変数 */
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	CTexture::TEXTURE m_texture;		//テクスチャの列挙型

	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//向き
	D3DXVECTOR3 m_move;	//移動量
	D3DXVECTOR2 m_size;	//サイズ
};

#endif