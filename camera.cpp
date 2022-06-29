//============================================================================================================
//
//ミツケテネ[camera.cpp]
//Author:Kishimoto Eiji
//
//============================================================================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//============================================================================================================
//マクロ定義
//============================================================================================================
#define CAMERA_MOVE		(2.0f)		//カメラの移動量
#define CAMERA_ROT		(0.05f)		//カメラの旋回量

//============================================================================================================
//スタティック変数宣言
//============================================================================================================
static Camera s_camera;		//カメラ情報
static bool bFollow;		//追従のON・OFF

//============================================================================================================
//プロトタイプ宣言
//============================================================================================================
static void CameraMove(void);
static void CameraReset(void);
static void AllDirections(void);
static void RiseAndFall(void);
static void Turning(void);
static void AngleNormalization(void);
static void CameraFollow(void);

//============================================================================================================
//カメラの初期化処理
//============================================================================================================
void InitCamera(void)
{
	//視点・注視点・上方向を設定する
	s_camera.posV = D3DXVECTOR3(0.0f, 100.0f, -160.0f);
	s_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	s_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//向きの初期化
	s_camera.rot = D3DXVECTOR3((-D3DX_PI * 0.1f), 0.0f, 0.0f);
	
	//視点から注視点の距離の設定
	float fX = (s_camera.posR.x - s_camera.posV.x);
	float fZ = (s_camera.posR.z - s_camera.posV.z);
	s_camera.fDistance	= sqrtf((fX * fX) + (fZ * fZ));		//三平方で距離を計算

	bFollow = true;		//追従しない
}

//============================================================================================================
//カメラの終了処理
//============================================================================================================
void UninitCamera(void)
{

}

//============================================================================================================
//カメラの更新処理
//============================================================================================================
void UpdateCamera(void)
{
	//カメラの移動
	CameraMove();

	if (GetKeyboardTrigger(DIK_F3))
	{
		bFollow = bFollow ? false : true;	//追従の切り替え
	}

	if (bFollow)
	{//追従モードON
		//カメラの追従
		CameraFollow();
	}
}

//============================================================================================================
//カメラの設定処理
//============================================================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&s_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&s_camera.mtxView,
					   &s_camera.posV,
					   &s_camera.posR,
					   &s_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &s_camera.mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&s_camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&s_camera.mtxProjection,
								D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
								10.0f,
								3000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &s_camera.mtxProjection);
}

//============================================================================================================
//カメラの移動
//============================================================================================================
static void CameraMove(void)
{
#ifdef _DEBUG	//デバッグの時だけ

	//カメラのリセット
	CameraReset();

	//前後左右の移動
	AllDirections();
	
	//上下の移動
	RiseAndFall();

	//視点・注視点の旋回
	Turning();

#endif
	//角度の正規化
	AngleNormalization();

	/*↓ 視点・注視点の位置を更新 ↓*/

	if (GetKeyboardPress(DIK_Z) || GetKeyboardPress(DIK_C))
	{//視点の旋回をしている場合のみ
		//視点
		s_camera.posV.x = s_camera.posR.x - sinf(s_camera.rot.y) * s_camera.fDistance;
		s_camera.posV.z = s_camera.posR.z - cosf(s_camera.rot.y) * s_camera.fDistance;
	}

	//注視点
	s_camera.posR.x = s_camera.posV.x + sinf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posR.z = s_camera.posV.z + cosf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posR.y = s_camera.posV.y + tanf(s_camera.rot.x) * s_camera.fDistance;
}

//============================================================================================================
//カメラの追従
//============================================================================================================
static void CameraFollow(void)
{
	Player *pP = GetPlayer();	//プレイヤー情報の取得
	Camera *pC = &s_camera;		//ポインタに変身

	/*↓ 目的の位置を設定 ↓*/

	//注視点
	pC->posRDest.x = pP->pos.x + sinf(pC->rot.y - pP->rot.y) * 300.0f;
	pC->posRDest.y = pP->pos.x - tanf(pP->rot.x - pP->rot.x) * 300.0f;
	pC->posRDest.z = pP->pos.z - cosf(pC->rot.y - pP->rot.y) * 300.0f;

	//視点
	pC->posVDest.x = pP->pos.x + sinf(pC->rot.y) * pC->fDistance;
	pC->posVDest.y = pP->pos.y - tanf(pC->rot.x) * pC->fDistance;
	pC->posVDest.z = pP->pos.z - cosf(pC->rot.y) * pC->fDistance;

	/*↓ 現在の位置を更新 ↓*/

	//注視点
	pC->posR.x += (pC->posRDest.x - pC->posR.x) * 0.1f;
	pC->posR.y += (pC->posRDest.y - pC->posR.y) * 0.01f;
	pC->posR.z += (pC->posRDest.z - pC->posR.z) * 0.1f;

	//視点
	pC->posV.x += (pC->posVDest.x - pC->posV.x) * 0.1f;
	pC->posV.y += (pC->posVDest.y - pC->posV.y) * 0.1f;
	pC->posV.z += (pC->posVDest.z - pC->posV.z) * 0.1f;
}

//============================================================================================================
//カメラのリセット
//============================================================================================================
static void CameraReset(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{//Enterキー
		//カメラの初期化処理
		InitCamera();
	}
}

//============================================================================================================
//前後左右の移動
//============================================================================================================
static void AllDirections(void)
{
	if (GetKeyboardPress(DIK_LEFT))
	{//←キー
		if (GetKeyboardPress(DIK_UP))
		{//左上
			s_camera.posV.x -= sinf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			s_camera.posV.z -= cosf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{//左下
			s_camera.posV.x -= sinf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			s_camera.posV.z -= cosf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else
		{//左
			s_camera.posV.x -= sinf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			s_camera.posV.z -= cosf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{//→キー
		if (GetKeyboardPress(DIK_UP))
		{//右上
			s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{//右下
			s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else
		{//右
			s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}
	}
	else if (GetKeyboardPress(DIK_UP))
	{//↑キー(前)
		s_camera.posV.x += sinf(s_camera.rot.y) * CAMERA_MOVE;
		s_camera.posV.z += cosf(s_camera.rot.y) * CAMERA_MOVE;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{//↓キー(後)
		s_camera.posV.x -= sinf(s_camera.rot.y) * CAMERA_MOVE;
		s_camera.posV.z -= cosf(s_camera.rot.y) * CAMERA_MOVE;
	}
}

//============================================================================================================
//上下の移動
//============================================================================================================
static void RiseAndFall(void)
{
	if (GetKeyboardPress(DIK_T))
	{//上昇
		s_camera.posV.y += CAMERA_MOVE;
	}
	else if (GetKeyboardPress(DIK_G))
	{//下降
		s_camera.posV.y -= CAMERA_MOVE;
	}
}

//============================================================================================================
//視点・注視点の旋回
//============================================================================================================
static void Turning(void)
{
	//左右([視点] or [注視点])
	if (GetKeyboardPress(DIK_Z) || GetKeyboardPress(DIK_Q))
	{//左回り
		s_camera.rot.y += CAMERA_ROT;
	}
	else if (GetKeyboardPress(DIK_C) || GetKeyboardPress(DIK_E))
	{//右回り
		s_camera.rot.y -= CAMERA_ROT;
	}

	//上下
	if (GetKeyboardPress(DIK_Y))
	{//上
		s_camera.rot.x += (CAMERA_ROT * 0.2f);
	}
	else if (GetKeyboardPress(DIK_H))
	{//下
		s_camera.rot.x -= (CAMERA_ROT * 0.2f);
	}
}

//============================================================================================================
//角度の正規化
//============================================================================================================
static void AngleNormalization(void)
{
	//Y軸
	if (s_camera.rot.y > D3DX_PI)
	{//π( 180°)を超えた場合
		s_camera.rot.y -= (D3DX_PI * 2.0f);
	}
	else if (s_camera.rot.y < -D3DX_PI)
	{//-π( -180°)を超えた場合
		s_camera.rot.y += (D3DX_PI * 2.0f);
	}

	//X軸
	if (s_camera.rot.x > D3DX_PI)
	{//π( 180°)を超えた場合
		s_camera.rot.x -= (D3DX_PI * 2.0f);
	}
	else if (s_camera.rot.x < -D3DX_PI)
	{//-π( -180°)を超えた場合
		s_camera.rot.x += (D3DX_PI * 2.0f);
	}
}

//============================================================================================================
//カメラの情報の取得
//============================================================================================================
Camera *GetCamera(void)
{
	return &s_camera;
}