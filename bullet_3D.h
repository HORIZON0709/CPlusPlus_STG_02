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
public: /* 列挙型の定義 */
	enum TYPE	/* 弾の種類 */
	{
		NONE = -1,
		NORMAL = 0,	//通常弾
		DOUBLE,		//二連弾
		TRIPLE,		//三方向各散弾
		MAX
	};

private: /* 定数の定義 */
	static const float BULLET_SIZE;	//サイズ

public: /* 静的メンバ関数 */
	/*
		生成
		const D3DXVECTOR3 &pos ---> 位置
		const D3DXVECTOR3 &move ---> 移動量
		const CObject::OBJ_TYPE &haveType ---> 所有者
		const CTexture::TEXTURE &texture ---> テクスチャ
	*/
	static CBullet3D* Create(const D3DXVECTOR3 &pos,
							 const D3DXVECTOR3 &move,
							 const CObject::OBJ_TYPE &haveType,
							 const CTexture::TEXTURE &texture);

public: /* コンストラクタ・デストラクタ */
	CBullet3D();
	~CBullet3D() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ関数 */
	void IsCollision();			//当たり判定
	void ReleaseOffScreen();	//画面外に出たら解放する

public:	/* Set・Get系 */
	/*
		所有者を設定
		const CObject::OBJ_TYPE &haveType ---> 所有者
	*/
	void SetHaveType(const CObject::OBJ_TYPE &haveType);

	CObject::OBJ_TYPE GetHaveType();	//所有者を取得

private: /* メンバ変数 */
	CObject::OBJ_TYPE m_haveType;	//所有者
};
#endif