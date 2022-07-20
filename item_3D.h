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
public: /* 列挙型の定義 */
	enum TYPE	/* アイテムの種類 */
	{
		CHANGE_BUlLET_NORMAL = 0,	//通常弾に変化
		CHANGE_BUlLET_DOUBLE,		//二連弾に変化
		CHANGE_BUlLET_TRIPLE,		//三方向拡散弾に変化
		MAX,
		NONE
	};

private: /* 定数の定義 */
	static const int MAX_ITEM = 16;	//最大数
	static const float ITEM_SIZE;	//サイズ

public: /* 静的メンバ関数 */
	/*
		生成
		const D3DXVECTOR3 &pos ---> 生成する位置
		const CItem3D::TYPE type ---> どのタイプで生成するか
	*/
	static CItem3D* Create(const D3DXVECTOR3 &pos, const CItem3D::TYPE type);

public: /* コンストラクタ・デストラクタ */
	CItem3D();
	~CItem3D() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ変数 */
	CItem3D::TYPE m_type;	//種類
};
#endif