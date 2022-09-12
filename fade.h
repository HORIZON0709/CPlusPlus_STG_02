//================================================
//
//制作実践基礎[fade.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _FADE_H_
#define _FADE_H_

//***************************
//インクルード
//***************************
#include "object2D.h"

//***************************
//背景クラスの定義
//***************************
class CFade
{/* 基本クラス */
private: /* 定数の定義 */
	static const float FADE_WIDTH;	//横幅
	static const float FADE_HEIGHT;	//縦幅

public: /* 静的メンバ関数 */
	static CFade* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CFade();
	~CFade();

public: /* オーバーライド関数 */
	HRESULT Init();	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

private: /* メンバ変数 */
	CObject2D* m_pPolygon;	//フェード用ポリゴン
};
#endif