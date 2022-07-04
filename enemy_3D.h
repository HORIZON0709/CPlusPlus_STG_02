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
private: /* 定数の定義 */
	static const float ENEMY_SIZE;	//サイズ

	static const int SHOT_INTERVAL = 20;	//弾の連続発射の間隔

public: /* 静的メンバ関数 */
	static CEnemy3D* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CEnemy3D();
	~CEnemy3D() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ変数 */
	int m_nTimerInterval;	//弾の連続発射の間隔
};
#endif