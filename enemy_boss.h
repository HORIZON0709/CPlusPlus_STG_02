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
public: /* 定数の定義 */
	static const float START_POS_X;		//初期位置( X )
	static const float START_POS_Y;		//初期位置( Y )
private:
	static const float ENEMY_SIZE;		//サイズ
	static const float CURVE_SIZE;		//カーブの大きさ
	static const float MOVE_SPEED_X;	//移動スピード( X )
	static const float MOVE_SPEED_Y;	//移動スピード( Y )
	static const float SHOT_SPEED;		//弾のスピード

	static const int SHOT_INTERVAL = 120;	//弾の連続発射の間隔
	static const int NUM_SCORE = 100;		//獲得スコア量
	static const int NUM_BULLETS = 8;		//同時発射数
	static const int MAX_LIFE = 30;			//体力の最大値

public: /* コンストラクタ・デストラクタ */
	CEnemyBoss();
	~CEnemyBoss() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画
	void Death() override;		//死亡時の処理

public: /* メンバ関数 */
	/*
		体力の減算
		const int nDamage ---> ダメージ量
	*/
	void SubLife(const int nDamage);

	int GetLife();	//体力の取得
private:
	void Move();	//移動
	void Shot();	//弾の発射

private: /* メンバ変数 */
	float m_fCurve;			//カーブ度合

	int m_nTimerInterval;	//弾の連続発射の間隔
	int m_nLife;			//体力
};
#endif