//================================================
//
//制作実践基礎[mode.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _MODE_H_
#define _MODE_H_

//***************************
//インクルード
//***************************
#include <d3dx9.h>

//***************************
//前方宣言
//***************************
class CGame;

//***************************
//モードクラスの定義
//***************************
class CMode
{/* 基本クラス */
public: /* 列挙型の定義 */
	enum MODE	//モードの種類
	{
		TITLE = 0,	//タイトル
		GAME,		//ゲーム
		RESULT,		//リザルト
		MAX
	};

public: /* 静的メンバ関数 */
	/*
		モードの設定
		MODE mode ---> モードの種類
	*/
	static void SetMode(MODE mode);

	//ゲーム情報の取得
	static CGame* GetGame();

public: /* コンストラクタ・デストラクタ */
	CMode();
	virtual ~CMode();

public: /* 仮想関数 */
	virtual HRESULT Init();	//初期化
	virtual void Uninit();	//終了
	virtual void Update();	//更新
	virtual void Draw();	//描画

private: /* 静的メンバ変数 */
	
	//********** ポインタ **********//

	//static CTitle* m_pTitle;	//タイトル
	static CGame* m_pGame;		//ゲーム
	//static CResult* m_pResult;	//リザルト
};
#endif