//================================================
//
//制作実践基礎[bullet.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//***************************
//インクルード
//***************************
#include "object2D.h"

//***************************
//弾クラスの定義
//***************************
class CBullet : public CObject2D
{/* CObject2Dの派生クラス */
private: /* 定数の定義 */
	static const float BULLET_SIZE;	//サイズ

public: /* 静的メンバ関数 */
	static CBullet* Create(D3DXVECTOR3 pos);	//生成

public: /* コンストラクタ・デストラクタ */
	CBullet();
	~CBullet() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画
	
public: /* メンバ関数 */
	void Collision();

private: /* メンバ変数 */
	D3DXVECTOR3 m_move;	//移動量
};
#endif