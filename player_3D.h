//================================================
//
//制作実践基礎[player_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PLAYER_3D_H_
#define _PLAYER_3D_H_

//***************************
//インクルード
//***************************
#include "object3D.h"
#include "item_3D.h"
#include "bullet_3D.h"

//***************************
//プレイヤー(3D)クラスの定義
//***************************
class CPlayer3D : public CObject3D
{/* CObject3Dの派生クラス */
private: /* 定数の定義 */
	static const float PLAYER_SIZE;	//サイズ
	static const float MOVE_SPEED;	//移動速度

	static const int SHOT_INTERVAL = 10;	//弾の連続発射の間隔

public: /* 静的メンバ関数 */
	static CPlayer3D* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CPlayer3D();
	~CPlayer3D() override;

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

private: /* メンバ関数 */
	void Move();	//移動
	void Shot();	//発射

	/*
		タイプに応じた弾の生成
		const CItem3D::TYPE &getItem ---> 取得したアイテム
	*/
	void CreateBulletAccordingToType(const CItem3D::TYPE &getItem);

private: /* メンバ変数 */
	int m_nTimerInterval;		//弾の連続発射の間隔
	CItem3D::TYPE m_getItem;	//取得したアイテム
	CBullet3D::TYPE m_typeNow;	//現在の弾のタイプ
};
#endif