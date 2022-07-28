//================================================
//
//制作実践基礎[enemy_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ENEMY_3D_H_
#define _ENEMY_3D_H_

//***************************
//インクルード
//***************************
#include "object3D.h"

//***************************
//敵クラスの定義
//***************************
class CEnemy3D : public CObject3D
{/* CObject3Dの派生クラス */
public: /* 列挙型の定義 */
	enum ENM_TYPE /* 敵の種類 */
	{
		CURVE = 0,	//sinカーブ
		BOSS,		//ボス
		MAX,
		NONE
	};

public: /* 定数の定義 */
	static const int MAX_ENEMY = 16;	//敵の最大数

public: /* 静的メンバ関数 */
	/*
		生成
		const ENM_TYPE &type ---> 敵の種類
		const D3DXVECTOR3 &pos ---> 任意の位置
	*/
	static CEnemy3D* Create(const ENM_TYPE &type, const D3DXVECTOR3 &pos);

public: /* コンストラクタ・デストラクタ */
	CEnemy3D();
	~CEnemy3D() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

public: /* メンバ関数 */
	/*
		敵の種類を設定
		const ENM_TYPE &type ---> 任意の敵の種類
	*/
	void SetEnmType(const ENM_TYPE &type);

	/*
		敵の種類を取得
	*/
	ENM_TYPE GetEnmType();

private: /* メンバ変数 */
	ENM_TYPE m_type;	//種類
};
#endif