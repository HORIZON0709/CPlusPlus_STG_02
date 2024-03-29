//================================================
//
//制作実践基礎[game.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _GAME_H_
#define _GAME_H_

//***************************
//インクルード
//***************************
#include "mode.h"
#include "enemy_3D.h"

#include <d3dx9.h>

//***************************
//前方宣言
//***************************
class CCamera;
class CScore;
class CPlayer3D;
class CBg3D;

//***************************
//ゲームクラスの定義
//***************************
class CGame : public CMode
{/* CModeの派生クラス */
private: /* 定数の定義 */
	static const int INTERVAL_STRAIGHT;			//直線敵の生成間隔
	static const int FADE_INTERVAL_PARTCHANGE;	//フェードまでの間隔(パート切り替え時)
	static const int FADE_INTERVAL_GAMEOVER;	//フェードまでの間隔(ゲームオーバー時)
	static const int FADE_INTERVAL_GAMECLEAR;	//フェードまでの間隔(ゲームクリア時)

public: /* 静的メンバ関数 */
	static CCamera* GetCamera();		//カメラの情報を取得
	static CScore* GetScore();			//スコアの情報を取得
	static CPlayer3D* GetPlayer3D();	//プレイヤー(3D)の情報を取得

	/*
		敵(3D)の情報を取得
		int nIdx ---> 何番目か
	*/
	static CEnemy3D* GetEnemy3D(int nIdx);

	static CBg3D* GetBg3D();	//背景(3D)の情報を取得

	static void ChangeGamePart();	//ゲームパートの切り替え
	static bool GetGamePart();		//ゲームパートの取得

public: /* コンストラクタ・デストラクタ */
	CGame();
	~CGame() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;	//終了
	void Update() override;	//更新
	void Draw() override;	//描画

private: /* メンバ関数 */
	/*
		直線敵の生成
		float fPosY ---> 生成する位置( Y軸 )
	*/
	void CreateEnemyStraight(float fPosY);

	void UpdateNormalPart();	//通常パートの更新
	void UpdateBossPart();		//ボスパートの更新

private: /* 静的メンバ変数 */
	static CCamera* m_pCamera;							//カメラ
	static CScore* m_pScore;							//スコア
	static CPlayer3D* m_pPlayer3D;						//プレイヤー(3D)
	static CEnemy3D* m_apEnemy3D[CEnemy3D::MAX_ENEMY];	//敵(3D)
	static CBg3D* m_pBg3D;								//背景(3D)

	/*
		ゲームパートの判別
		false ---> 通常パート
		true ---> ボスパート
	*/
	static bool m_bGamePart;

private: /* メンバ変数 */
	int m_nCntStraight;		//直線敵の生成間隔カウント用
	int m_nCntIntervalFade;	//フェードするまでの間隔カウント用

	bool m_bFadeOut;	//暗転したかどうか
};
#endif