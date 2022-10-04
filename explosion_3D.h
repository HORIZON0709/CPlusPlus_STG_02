//================================================
//
//制作実践基礎[explosion_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _EXPLOSION_3D_H_
#define _EXPLOSION_3D_H_

//***************************
//インクルード
//***************************
#include "object3D.h"

//***************************
//爆発クラスの定義
//***************************
class CExplosion3D : public CObject3D
{/* CObject3Dの派生クラス */
private: /* 定数の定義 */
	static const float EXPLOSION_SIZE;	//サイズ
	static const int DIVIDE_TEX_U;		//テクスチャの分割数( U方向 )

public: /* 静的メンバ関数 */
	static CExplosion3D* Create(D3DXVECTOR3 pos);	//生成

public: /* コンストラクタ・デストラクタ */
	CExplosion3D();
	~CExplosion3D() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ変数 */
	int m_nCntAnim;		//テクスチャアニメーション用カウント
	int m_nPtnAnim;		//パターン番号
};
#endif