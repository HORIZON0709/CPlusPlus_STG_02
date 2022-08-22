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

#include "score.h"
#include "player_3D.h"
#include "enemy_3D.h"
#include "bg_3D.h"

#include <d3dx9.h>

//***************************
//ゲームクラスの定義
//***************************
class CGame : public CMode
{/* CModeの派生クラス */
public: /* 静的メンバ関数 */
	/* スコアの情報を取得 */
	static CScore* GetScore();

	/* プレイヤー(3D)の情報を取得 */
	static CPlayer3D* GetPlayer3D();

	/*
		敵(3D)の情報を取得
		const int nIdx ---> 何番目か
	*/
	static CEnemy3D* GetEnemy3D(const int nIdx);

	/* 背景(3D)の情報を取得 */
	static CBg3D* GetBg3D();

public: /* コンストラクタ・デストラクタ */
	CGame();
	~CGame() override;

public: /* メンバ関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;	//終了
	void Update() override;	//更新
	void Draw() override;	//描画

	bool GetGamePart();	//ゲームパートの取得

private: /* 静的メンバ変数 */
	static CScore* m_pScore;							//スコア
	static CPlayer3D* m_pPlayer3D;						//プレイヤー(3D)
	static CEnemy3D* m_apEnemy3D[CEnemy3D::MAX_ENEMY];	//敵(3D)
	static CBg3D* m_pBg3D;								//背景(3D)
	
private: /* メンバ変数 */
	/*
		ゲームパートの判別
		false ---> 通常パート
		true ---> ボスパート
	*/
	bool m_bGamePart;
};
#endif