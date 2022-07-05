//================================================
//
//制作実践基礎[bg_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _BG_3D_H_
#define _BG_3D_H_

//***************************
//インクルード
//***************************
#include "object3D.h"

//***************************
//背景クラスの定義
//***************************
class CBg3D : public CObject3D
{/* Cobject3Dの派生クラス */
public: /* 静的メンバ関数 */
	static CBg3D* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CBg3D();
	~CBg3D() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画
};
#endif