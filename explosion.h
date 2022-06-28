//================================================
//
//制作実践基礎[explosion.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//***************************
//インクルード
//***************************
#include "object2D.h"

//***************************
//爆発クラスの定義
//***************************
class CExplosion : public CObject2D
{/* CObject2Dの派生クラス */
private: /* 定数の定義 */
	static const float EXPLOSION_SIZE;	//サイズ
	static const int DIVIDE_TEX_U = 8;	//テクスチャの分割数( U方向 )

public: /* 静的メンバ関数 */
	static CExplosion* Create(D3DXVECTOR3 pos);	//生成

public: /* コンストラクタ・デストラクタ */
	CExplosion();
	~CExplosion() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ変数 */
	int m_nCntAnim;
	int m_nPtnAnim;
};

#endif