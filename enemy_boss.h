//================================================
//
//制作実践基礎[enemy_boss.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ENEMY_BOSS_H_
#define _ENEMY_BOSS_H_

//***************************
//インクルード
//***************************
#include "enemy_3D.h"

//***************************
//敵クラスの定義
//***************************
class CEnemyBoss : public CEnemy3D
{/* CEnemy3Dの派生クラス */
private: /* 定数の定義 */
	static const float START_POS_X;		//初期位置( X )
	static const float START_POS_Y;		//初期位置( Y )
	static const float ENEMY_SIZE;		//サイズ

	static const int SHOT_INTERVAL = 90;	//弾の連続発射の間隔
	static const int NUM_SCORE = 100;		//獲得スコア量

public: /* コンストラクタ・デストラクタ */
	CEnemyBoss();
	~CEnemyBoss() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

	void Death() override;	//死亡時の処理

private: /* メンバ関数 */
	void Move();	//移動

private: /* メンバ変数 */
	int m_nTimerInterval;	//弾の連続発射の間隔
};
#endif