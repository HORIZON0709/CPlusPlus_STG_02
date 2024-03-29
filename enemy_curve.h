//================================================
//
//制作実践基礎[enemy_curve.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ENEMY_CURVE_H_
#define _ENEMY_CURVE_H_

//***************************
//インクルード
//***************************
#include "enemy_3D.h"

//***************************
//敵クラスの定義
//***************************
class CEnemyCurve : public CEnemy3D
{/* CEnemy3Dの派生クラス */
public: /* 定数の定義 */
	static const float START_POS_X;		//初期位置( X )
	static const float START_POS_Y;		//初期位置( Y )
private:
	static const float ENEMY_SIZE;		//サイズ
	static const float CURVE_SIZE;		//カーブの大きさ
	static const float MOVE_SPEED_X;	//移動スピード( X )
	static const float MOVE_SPEED_Y;	//移動スピード( Y )

	static const int SHOT_INTERVAL;	//弾の連続発射の間隔
	static const int NUM_SCORE;		//獲得スコア量

public: /* コンストラクタ・デストラクタ */
	CEnemyCurve();
	~CEnemyCurve() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画
	void Death() override;		//死亡時の処理
	
private: /* メンバ関数 */
	void Move();				//移動
	void Shot();				//弾の発射
	void OverRimitRight();		//画面右端を超えたかどうか
	void ReleaseOffScreen();	//画面外に出たら解放する

private: /* メンバ変数 */
	int m_nTimerInterval;	//弾の連続発射の間隔
	float m_fCurve;			//カーブ度合

	/*
		画面内に入ってきたかどうか
		false ---> 画面外
		true ---> 画面内
	*/
	bool m_bInside;
};
#endif