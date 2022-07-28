//================================================
//
//制作実践基礎[enemy_curve.h]
//Author:Kishimoto Eiji Danian
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
	static const int MAX_ENEMY_CURVE = 8;	//カーブ敵の最大数
private:
	static const float START_POS_X;		//初期位置( X )
	static const float START_POS_Y;		//初期位置( Y )
	static const float ENEMY_SIZE;		//サイズ
	static const float CURVE_SIZE;		//カーブの大きさ
	static const float MOVE_SPEED_X;	//移動スピード( X )
	static const float MOVE_SPEED_Y;	//移動スピード( Y )

	static const int SHOT_INTERVAL = 90;	//弾の連続発射の間隔
	static const int NUM_SCORE = 10;		//獲得スコア量

public: /* コンストラクタ・デストラクタ */
	CEnemyCurve();
	~CEnemyCurve() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ変数 */
	int m_nTimerInterval;	//弾の連続発射の間隔
	float m_fCurve;			//カーブの具合
};
#endif