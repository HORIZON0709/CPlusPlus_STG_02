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
class CFade : public CObject2D
{/* CObject2Dの派生クラス */
public: /* 列挙型の定義 */	
	enum STATE	//フェード状態
	{
		NONE = -1,		//フェードしていない
		FADE_IN = 0,	//フェードイン
		FADE_OUT,		//フェードアウト
		MAX
	};

private: /* 定数の定義 */
	static const float FADE_WIDTH;	//横幅
	static const float FADE_HEIGHT;	//縦幅

public: /* 静的メンバ関数 */
	static CFade* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CFade();
	~CFade() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

public: /* メンバ関数 */
	/*
		設定
		const STATE &state ---> フェード状態
	*/
	void Set(const STATE &state);

private: /* メンバ変数 */
	STATE m_state;	//フェード状態
};
#endif