//================================================
//
//制作実践基礎[item_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ITEM_3D_H_
#define _ITEM_3D_H_

//***************************
//インクルード
//***************************
#include "object3D.h"

//***************************
//アイテムクラスの定義
//***************************
class CItem3D : public CObject3D
{/* Cobject3Dの派生クラス */
private: /* 定数の定義 */
	static const float ITEM_SIZE;	//サイズ

public: /* 静的メンバ関数 */
	static CItem3D* Create(const D3DXVECTOR3 &pos);	//生成

public: /* コンストラクタ・デストラクタ */
	CItem3D();
	~CItem3D() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画
};
#endif