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
#include "score.h"

#include "player_3D.h"
#include "enemy_3D.h"
#include "bg_3D.h"

#include <d3dx9.h>

//***************************
//ゲームクラスの定義
//***************************
class CGame
{/* 基本クラス */
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
	~CGame();

public: /* メンバ関数 */
	HRESULT Init();	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

private: /* 静的メンバ変数 */
	static CScore* m_pScore;							//スコア
	static CPlayer3D* m_pPlayer3D;						//プレイヤー(3D)
	static CEnemy3D* m_apEnemy3D[CEnemy3D::MAX_ENEMY];	//敵(3D)
	static CBg3D* m_pBg3D;								//背景(3D)
	
};
#endif