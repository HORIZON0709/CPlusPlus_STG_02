//================================================
//
//制作実践基礎[player.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//***************************
//インクルード
//***************************
#include "object2D.h"

//***************************
//プレイヤークラスの定義
//***************************
class CPlayer : public CObject2D
{/* CObject2Dの派生クラス */
private: /* 定数の定義 */
	static const float PLAYER_SIZE;	//サイズ
	static const float MOVE_SPEED;	//移動速度

public: /* 静的メンバ関数 */
	static CPlayer* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CPlayer();
	~CPlayer() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画
};

#endif