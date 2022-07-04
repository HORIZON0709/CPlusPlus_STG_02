//================================================
//
//制作実践基礎[bg.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _BG_H_
#define _BG_H_

//***************************
//インクルード
//***************************
#include "object.h"

//***************************
//前方宣言
//***************************
class CObject2D;

//***************************
//背景クラスの定義
//***************************
class CBg : public CObject
{/* Cobjectの派生クラス */
public: /* 静的メンバ関数 */
	static CBg* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CBg();
	~CBg() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* 静的メンバ変数 */
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_OBJECT];

private: /* メンバ変数 */
	CObject2D* m_apObject2D[MAX_OBJECT];
};


#endif