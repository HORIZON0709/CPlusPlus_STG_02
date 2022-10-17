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
	static const int ANIM_SPEED;	//アニメーション速度

public: /* 静的メンバ関数 */
	/*
		生成
		const D3DXVECTOR3 &pos ---> 位置
		const D3DXVECTOR3 &size ---> サイズ
		const CTexture::TEXTURE &texture ---> テクスチャ
	*/
	static CExplosion3D* Create(
		const D3DXVECTOR3 &pos,
		const D3DXVECTOR3 &size,
		const CTexture::TEXTURE &texture);

public: /* コンストラクタ・デストラクタ */
	CExplosion3D();
	~CExplosion3D() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* 静的メンバ変数 */
	static CTexture::TEXTURE m_tex;	//テクスチャ

private: /* メンバ変数 */
	int m_nDivideTexU;	//テクスチャの分割数( U方向 )
	int m_nDivideTexV;	//テクスチャの分割数( V方向 )
	int m_nNumPtnAll;	//テクスチャの総パターン数
	int m_nCntAnim;		//テクスチャアニメーション用カウント
	int m_nPtnAnim;		//パターン番号
};
#endif