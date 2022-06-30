//================================================
//
//制作実践基礎[camera.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//***************************
//インクルード
//***************************
#include <d3dx9.h>

//***************************
//カメラクラスの定義
//***************************
class CCamera
{/* 基本クラス */
private: /* 定数の定義 */
	static const float CAMERA_MOVE;	//移動量
	static const float CAMERA_ROT;	//旋回量

public: /* コンストラクタ・デストラクタ */
	CCamera();
	~CCamera();

public: /* メンバ関数 */
	void Init();	//初期化
	void Uninit();	//終了
	void Update();	//更新
	void Set();		//設定
private:
	void Move();			//移動
	void Turn();			//旋回
	void NormalizeAngle();	//角度の正規化

private: /* メンバ変数 */
	D3DXVECTOR3 m_posV;		//現在の視点
	D3DXVECTOR3 m_posR;		//現在の注視点
	D3DXVECTOR3 m_posVDest;	//目的の視点
	D3DXVECTOR3 m_posRDest;	//目的の注視点
	D3DXVECTOR3 m_vecU;		//上方向ベクトル
	D3DXVECTOR3 m_rot;		//向き

	D3DXMATRIX m_mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;		//ビューマトリックス

	float m_fDistance;	//視点から注視点の距離
};

#endif