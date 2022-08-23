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

public: /* メンバ関数 */
	/*
		所持アイテムのセット
		const CItem3D::TYPE &item ---> 入手したアイテムのタイプ
	*/
	void SetItem(const CItem3D::TYPE &item);

	CItem3D::TYPE GetItem();	//所持アイテムの取得
private:
	void Move();					//移動
	void Shot();					//発射
	void CreateBulletByType();		//タイプ別の弾の生成
	void SetNormalBullet();			//通常弾の設定
	void SetDoubleBullet();			//二連弾の設定
	void SetTripleBullet();			//三方向各散弾の設定
	void ProcessingForEachItem();	//アイテム毎の処理

private: /* メンバ変数 */
	int m_nTimerInterval;			//弾の連続発射の間隔
	CItem3D::TYPE m_getItem;		//取得したアイテム
	CBullet3D::TYPE m_bulletType;	//弾のタイプ
};
#endif