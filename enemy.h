//================================================
//
//制作実践基礎[enemy.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//***************************
//インクルード
//***************************
#include "object2D.h"

//***************************
//敵クラスの定義
//***************************
class CEnemy : public CObject2D
{/* CObject2Dの派生クラス */
private: /* 定数の定義 */
	static const float ENEMY_SIZE;	//サイズ

public: /* 静的メンバ関数 */
	static CEnemy* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CEnemy();
	~CEnemy() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画
};
#endif