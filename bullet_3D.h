//================================================
//
//制作実践基礎[bullet_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _BULLET_3D_H_
#define _BULLET_3D_H_

//***************************
//インクルード
//***************************
#include "object3D.h"

//***************************
//弾クラスの定義
//***************************
class CBullet3D : public CObject3D
{/* CObject3Dの派生クラス */
private: /* 定数の定義 */
	static const float BULLET_SIZE;	//サイズ

public: /* 静的メンバ関数 */
	/* 生成 */
	static CBullet3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, CObject::OBJ_TYPE haveType);

public: /* コンストラクタ・デストラクタ */
	CBullet3D();
	~CBullet3D() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ関数 */
	void IsCollision();

public:	/* Set・Get系 */
	void SetHaveType(CObject::OBJ_TYPE haveType);
	CObject::OBJ_TYPE GetHaveType();

private: /* メンバ変数 */
	CObject::OBJ_TYPE m_haveType;	//所有者
};
#endif