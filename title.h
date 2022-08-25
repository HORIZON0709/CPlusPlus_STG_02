//================================================
//
//制作実践基礎[title.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//***************************
//インクルード
//***************************
#include "mode.h"

#include <d3dx9.h>

//***************************
//前方宣言
//***************************

//***************************
//タイトルクラスの定義
//***************************
class CTitle : public CMode
{/* CModeの派生クラス */
public: /* コンストラクタ・デストラクタ */
	CTitle();
	~CTitle() override;

public: /* メンバ関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ変数 */
	
};
#endif