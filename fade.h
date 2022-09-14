//================================================
//
//制作実践基礎[fade.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _FADE_H_
#define _FADE_H_

//***************************
//インクルード
//***************************
#include <d3dx9.h>

//***************************
//定数の定義
//***************************
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);	//頂点フォーマット

//***************************
//背景クラスの定義
//***************************
class CFade
{/* 基本クラス */
public: /* 列挙型の定義 */	
	enum STATE	//フェード状態
	{
		NONE = -1,		//フェードしていない
		FADE_IN = 0,	//フェードイン
		FADE_OUT,		//フェードアウト
		MAX
	};

private: /* 構造体の定義 */
	struct VERTEX_2D
	{//頂点データ
		D3DXVECTOR3 pos;	//位置
		float rhw;			//法線
		D3DCOLOR col;		//色
		D3DXVECTOR2 tex;	//テクスチャ座標
	};

public: /* 静的メンバ関数 */
	static CFade* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CFade();
	~CFade();

public: /* オーバーライド関数 */
	HRESULT Init();	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

public: /* メンバ関数 */
	/*
		設定
		const STATE &state ---> フェード状態
	*/
	void Set(const STATE &state);

private: /* メンバ変数 */
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ

	STATE m_state;	//フェード状態

	D3DXCOLOR m_col;	//色
};
#endif