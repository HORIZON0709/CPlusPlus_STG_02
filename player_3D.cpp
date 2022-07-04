//================================================
//
//制作実践基礎[player_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "player_3D.h"
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "bullet_3D.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CPlayer3D::PLAYER_SIZE = 150.0f;	//サイズ
const float CPlayer3D::MOVE_SPEED = 13.0f;		//移動速度

//================================================
//生成
//================================================
CPlayer3D* CPlayer3D::Create()
{
	CPlayer3D* pPlayer3D = nullptr;	//ポインタ

	if (pPlayer3D != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pPlayer3D = new CPlayer3D;	//メモリの動的確保

	pPlayer3D->Init();	//初期化

	return pPlayer3D;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CPlayer3D::CPlayer3D()/*:m_nTimerInterval(0)*/
{
	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::PLAYER);
}

//================================================
//デストラクタ
//================================================
CPlayer3D::~CPlayer3D()
{
}

//================================================
//初期化
//================================================
HRESULT CPlayer3D::Init()
{
	CObject3D::Init();	//親クラス

	//サイズを設定
	CObject3D::SetSize(PLAYER_SIZE);

	//位置を設定
	D3DXVECTOR3 pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	CObject3D::SetPos(pos);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::TEXTURE_百鬼あやめ_8);

	return S_OK;
}

//================================================
//終了
//================================================
void CPlayer3D::Uninit()
{
	CObject3D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CPlayer3D::Update()
{
	CObject3D::Update();	//親クラス

	Move();	//移動

	Shot();	//発射
}

//================================================
//描画
//================================================
void CPlayer3D::Draw()
{
	CObject3D::Draw();	//親クラス
}

//================================================
//移動
//================================================
void CPlayer3D::Move()
{
	//キーボード情報の取得
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	D3DXVECTOR3 pos = CObject3D::GetPos();		//位置を取得
	D3DXVECTOR3 move = CObject3D::GetMove();	//移動量を取得

	if (pKeyboard->GetPress(DIK_D))
	{//右
		/* 移動方向に応じて移動量を増加 */

		if (pKeyboard->GetPress(DIK_W))
		{//右上
			move.x += sinf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//X軸方向
			move.y -= cosf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//Y軸方向
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//右下
			move.x += sinf(+D3DX_PI * 0.25f) * MOVE_SPEED;	//X軸方向
			move.y -= cosf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//Y軸方向
		}
		else
		{//右
			move.x += sinf(+D3DX_PI * 0.5f) * MOVE_SPEED;	//X軸方向
		}
	}
	else if (pKeyboard->GetPress(DIK_A))
	{//左
		/* 移動方向に応じて移動量を増加 */

		if (pKeyboard->GetPress(DIK_W))
		{//左上
			move.x += sinf(-D3DX_PI * 0.75f) * MOVE_SPEED;	//X軸方向
			move.y -= cosf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//Y軸方向
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//左下
			move.x += sinf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//X軸方向
			move.y -= cosf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//Y軸方向
		}
		else
		{//左
			move.x += sinf(-D3DX_PI * 0.5f) * MOVE_SPEED;	//X軸方向
		}
	}
	else if (pKeyboard->GetPress(DIK_W))
	{//上
		move.y -= cosf(+D3DX_PI * 1.0f) * MOVE_SPEED;	//Y軸方向
	}
	else if (pKeyboard->GetPress(DIK_S))
	{//下
		move.y -= cosf(-D3DX_PI * 0.0f) * MOVE_SPEED;	//Y軸方向
	}

	pos += move;	//位置に移動量を加算

	/* 画面外への移動防止 */

	float fSizeHalf = (PLAYER_SIZE * 0.5f);	//サイズの半分

	float fLeft		= (pos.x - fSizeHalf);	//左端
	float fRight	= (pos.x + fSizeHalf);	//右端
	float fTop		= (pos.y + fSizeHalf);	//上端
	float fBottom	= (pos.y - fSizeHalf);	//下端

	float fRimitHeight = (CRenderer::SCREEN_HEIGHT * 0.3f);	//移動制限(上下)
	float fRimitWidth = (CRenderer::SCREEN_WIDTH * 0.278f);	//移動制限(左右)

	if (fTop > fRimitHeight)
	{//移動上限(上)
		pos.y = fRimitHeight - fSizeHalf;
	}
	else if (fBottom < -fRimitHeight)
	{//移動上限(下)
		pos.y = -fRimitHeight + fSizeHalf;
	}

	if (fLeft < -fRimitWidth)
	{//移動上限(左)
		pos.x = -fRimitWidth + fSizeHalf;
	}
	else if (fRight > fRimitWidth)
	{//移動上限(右)
		pos.x = fRimitWidth - fSizeHalf;
	}

	CObject3D::SetPos(pos);	//位置を更新
}

//================================================
//発射
//================================================
void CPlayer3D::Shot()
{
	CInput* pInput = CInput::GetKey();	//キーボード情報を取得

	D3DXVECTOR3 pos = CObject3D::GetPos();	//位置情報を取得

	if (pInput->Trigger(CInput::STANDARD_KEY::SHOT))
	{//単押し
		CBullet3D::Create(pos, CObject::OBJ_TYPE::PLAYER);	//弾の生成
	}
	else if (pInput->Press(CInput::STANDARD_KEY::SHOT))
	{//長押し(押しっぱなし)
		m_nTimerInterval++;	//タイマーを進める

		if (m_nTimerInterval % SHOT_INTERVAL != 0)
		{//間隔のタイマーが規定値に達していない
			return;
		}

		/* 間隔タイマーが規定値に達したら */

		CBullet3D::Create(pos,CObject::OBJ_TYPE::PLAYER);	//弾の生成
	}

	if (pInput->Release(CInput::STANDARD_KEY::SHOT))
	{//キーを離したら
		m_nTimerInterval = 0;	//タイマーをリセット
	}
}