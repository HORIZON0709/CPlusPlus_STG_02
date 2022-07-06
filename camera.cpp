//================================================
//
//制作実践基礎[camera.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "camera.h"
#include "application.h"
#include "inputKeyboard.h"
#include "renderer.h"

//***************************
//定数の定義
//***************************
const float CCamera::CAMERA_MOVE = 20.0f;	//移動量

//================================================
//コンストラクタ
//================================================
CCamera::CCamera():
	m_posV(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posR(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posVDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posRDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vecU(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	//メンバ変数のクリア
	memset(m_mtxProjection,0,sizeof(m_mtxProjection));
	memset(m_mtxView, 0, sizeof(m_mtxView));
}

//================================================
//デストラクタ
//================================================
CCamera::~CCamera()
{
}

//================================================
//初期化
//================================================
void CCamera::Init()
{
	//視点・注視点・上方向ベクトルを設定する
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//向きの初期化
	m_rot = D3DXVECTOR3((-D3DX_PI * 0.1f), 0.0f, 0.0f);

	Set();	//カメラをセット
}

//================================================
//終了
//================================================
void CCamera::Uninit()
{
}

//================================================
//更新
//================================================
void CCamera::Update()
{
	//移動
	Move();

	//注視点
	m_posR.x = m_posV.x + sinf(m_rot.y);
	m_posR.z = m_posV.z + cosf(m_rot.y);
	m_posR.y = m_posV.y + tanf(m_rot.x);
}

//================================================
//設定
//================================================
void CCamera::Set()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//デバイスの取得

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	/*D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(45.0f),
								(float)CRenderer::SCREEN_WIDTH / (float)CRenderer::SCREEN_HEIGHT,
								10.0f,
								3000.0f);*/

	// プロジェクションマトリックスの作成(平行投影)
	D3DXMatrixOrthoLH(&m_mtxProjection,						//プロジェクションマトリックス
						(float)CRenderer::SCREEN_WIDTH,		//幅
						(float)CRenderer::SCREEN_HEIGHT,	//高さ
						10.0f,								//ニア
						3000.0f);							//ファー

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//================================================
//移動
//================================================
void CCamera::Move()
{
	//キーボード情報の取得
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	/* 前後左右 */

	if (pKeyboard->GetPress(DIK_LEFT))
	{//←キー
		/* 方向に応じて移動量を加算 */

		if (pKeyboard->GetPress(DIK_UP))
		{//左上
			m_posV.x += sinf(m_rot.y + (-D3DX_PI * 0.75f)) * CAMERA_MOVE;	//X軸
			m_posV.y += cosf(m_rot.y + (-D3DX_PI * 0.75f)) * CAMERA_MOVE;	//Y軸
		}
		else if (pKeyboard->GetPress(DIK_DOWN))
		{//左下
			m_posV.x += sinf(m_rot.y + (-D3DX_PI * 0.25f)) * CAMERA_MOVE;	//X軸
			m_posV.y += cosf(m_rot.y + (-D3DX_PI * 0.25f)) * CAMERA_MOVE;	//Y軸
		}
		else
		{//左
			m_posV.x += sinf(m_rot.y + (-D3DX_PI * 0.5f)) * CAMERA_MOVE;	//X軸
		}
	}
	else if (pKeyboard->GetPress(DIK_RIGHT))
	{//→キー
		/* 方向に応じて移動量を加算 */
		
		if (pKeyboard->GetPress(DIK_UP))
		{//右上
			m_posV.x += sinf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;	//X軸
			m_posV.y += cosf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;	//Y軸
		}
		else if (pKeyboard->GetPress(DIK_DOWN))
		{//右下
			m_posV.x += sinf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;	//X軸
			m_posV.y += cosf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;	//Y軸
		}
		else
		{//右
			m_posV.x += sinf(m_rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;	//X軸
		}
	}
	else if (pKeyboard->GetPress(DIK_UP))
	{//↑キー(上)
		/* 方向に応じて移動量を加算 */
		m_posV.y += cosf(m_rot.y) * CAMERA_MOVE;	//Y軸
	}
	else if (pKeyboard->GetPress(DIK_DOWN))
	{//↓キー(下)
		/* 方向に応じて移動量を減算 */
		m_posV.y += cosf(-m_rot.y) * CAMERA_MOVE;	//Y軸
	}
}

//================================================
//角度の正規化
//================================================
void CCamera::NormalizeAngle()
{
	/* Y軸 */

	if (m_rot.y > D3DX_PI)
	{//π( 180°)を超えた場合
		m_rot.y -= (D3DX_PI * 2.0f);
	}
	else if (m_rot.y < -D3DX_PI)
	{//-π( -180°)を超えた場合
		m_rot.y += (D3DX_PI * 2.0f);
	}

	/* X軸 */

	if (m_rot.x > D3DX_PI)
	{//π( 180°)を超えた場合
		m_rot.x -= (D3DX_PI * 2.0f);
	}
	else if (m_rot.x < -D3DX_PI)
	{//-π( -180°)を超えた場合
		m_rot.x += (D3DX_PI * 2.0f);
	}
}