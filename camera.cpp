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
const float CCamera::CAMERA_MOVE = 2.0f;	//移動量
const float CCamera::CAMERA_ROT = 0.05f;	//旋回量

//================================================
//コンストラクタ
//================================================
CCamera::CCamera():
	m_posV(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posR(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posVDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posRDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vecU(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_fDistance(0.0f)
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
	//視点・注視点・上方向を設定する
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -160.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//向きの初期化
	m_rot = D3DXVECTOR3((-D3DX_PI * 0.1f), 0.0f, 0.0f);

	//視点から注視点の距離の設定
	float fX = (m_posR.x - m_posV.x);
	float fZ = (m_posR.z - m_posV.z);

	//三平方で距離を計算
	m_fDistance = sqrtf((fX * fX) + (fZ * fZ));
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

	//旋回
	Turn();

	//キーボード情報の取得
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	if (pKeyboard->GetPress(DIK_Z) || pKeyboard->GetPress(DIK_C))
	{//視点の旋回をしている場合のみ
		//視点
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}

	//注視点
	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	m_posR.y = m_posV.y + tanf(m_rot.x) * m_fDistance;
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
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(45.0f),
								(float)CRenderer::SCREEN_WIDTH / (float)CRenderer::SCREEN_HEIGHT,
								10.0f,
								3000.0f);

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
		/* 方向に応じて移動量を減算 */

		if (pKeyboard->GetPress(DIK_UP))
		{//左前
			m_posV.x -= sinf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;	//X軸
			m_posV.z -= cosf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;	//Z軸
		}
		else if (pKeyboard->GetPress(DIK_DOWN))
		{//左後ろ
			m_posV.x -= sinf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;	//X軸
			m_posV.z -= cosf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;	//Z軸
		}
		else
		{//左
			m_posV.x -= sinf(m_rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;	//X軸
			m_posV.z -= cosf(m_rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;	//Z軸
		}
	}
	else if (pKeyboard->GetPress(DIK_RIGHT))
	{//→キー
		/* 方向に応じて移動量を加算 */
		
		if (pKeyboard->GetPress(DIK_UP))
		{//右前
			m_posV.x += sinf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;	//X軸
			m_posV.z += cosf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;	//Z軸
		}
		else if (pKeyboard->GetPress(DIK_DOWN))
		{//右後ろ
			m_posV.x += sinf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;	//X軸
			m_posV.z += cosf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;	//Z軸
		}
		else
		{//右
			m_posV.x += sinf(m_rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;	//X軸
			m_posV.z += cosf(m_rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;	//Z軸
		}
	}
	else if (pKeyboard->GetPress(DIK_UP))
	{//↑キー(前)
		/* 方向に応じて移動量を加算 */
		m_posV.x += sinf(m_rot.y) * CAMERA_MOVE;	//X軸
		m_posV.z += cosf(m_rot.y) * CAMERA_MOVE;	//Z軸
	}
	else if (pKeyboard->GetPress(DIK_DOWN))
	{//↓キー(後)
		/* 方向に応じて移動量を減算 */
		m_posV.x -= sinf(m_rot.y) * CAMERA_MOVE;	//X軸
		m_posV.z -= cosf(m_rot.y) * CAMERA_MOVE;	//Z軸
	}

	/* 上下 */

	if (pKeyboard->GetPress(DIK_T))
	{//上昇( Tキー )
		m_posV.y += CAMERA_MOVE;	//移動量を加算( Y軸 )
	}
	else if (pKeyboard->GetPress(DIK_G))
	{//下降( Gキー )
		m_posV.y -= CAMERA_MOVE;	//移動量を減算( Y軸 )
	}
}

//================================================
//旋回
//================================================
void CCamera::Turn()
{
	//キーボード情報の取得
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	/* 左右([視点] or [注視点]) */

	if (pKeyboard->GetPress(DIK_Z) || pKeyboard->GetPress(DIK_Q))
	{//左回り( Zキー or Qキー )
		m_rot.y += CAMERA_ROT;	//旋回量を加算
	}
	else if (pKeyboard->GetPress(DIK_C) || pKeyboard->GetPress(DIK_E))
	{//右回り( Cキー or Eキー )
		m_rot.y -= CAMERA_ROT;	//旋回量を加算
	}

	/* 上下 */

	if (pKeyboard->GetPress(DIK_Y))
	{//上( Yキー )
		m_rot.x += (CAMERA_ROT * 0.2f);	//旋回量を加算
	}
	else if (pKeyboard->GetPress(DIK_H))
	{//下( Hキー )
		m_rot.x -= (CAMERA_ROT * 0.2f);	//旋回量を加算
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