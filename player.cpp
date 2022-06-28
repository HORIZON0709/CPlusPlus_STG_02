//================================================
//
//制作実践基礎[player.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "player.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CPlayer::PLAYER_SIZE = 100.0f;	//サイズ
const float CPlayer::MOVE_SPEED = 10.0f;	//移動速度

//================================================
//生成
//================================================
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = nullptr;	//ポインタ

	if (pPlayer != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pPlayer = new CPlayer;	//メモリの動的確保

	pPlayer->Init();	//初期化

	return pPlayer;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CPlayer::CPlayer()
{
	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::PLAYER);
}

//================================================
//デストラクタ
//================================================
CPlayer::~CPlayer()
{
}

//================================================
//初期化
//================================================
HRESULT CPlayer::Init()
{
	CObject2D::Init();	//親クラス

	//サイズを設定
	CObject2D::SetSize(PLAYER_SIZE);

	//位置を設定
	D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.5f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);
	CObject2D::SetPos(pos);

	// テクスチャの設定
	CObject2D::SetTexture(CTexture::TEXTURE_百鬼あやめ_8);

	return S_OK;
}

//================================================
//終了
//================================================
void CPlayer::Uninit()
{
	CObject2D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CPlayer::Update()
{
	CObject2D::Update();	//親クラス

	CInput* pInput = CInput::GetKey();		//キーボード情報を取得
	D3DXVECTOR3 pos = CObject2D::GetPos();	//位置情報を取得

	/* 移動 */

	if (pInput->Press(CInput::STANDARD_KEY::RIGHT))
	{//右
		pos.x += MOVE_SPEED;
	}
	else if (pInput->Press(CInput::STANDARD_KEY::LEFT))
	{//左
		pos.x -= MOVE_SPEED;
	}

	if (pInput->Press(CInput::STANDARD_KEY::UP))
	{//上
		pos.y -= MOVE_SPEED;
	}
	else if (pInput->Press(CInput::STANDARD_KEY::DOWN))
	{//下
		pos.y += MOVE_SPEED;
	}

	if (pInput->Trigger(CInput::STANDARD_KEY::SHOT))
	{//発射
		CBullet* pBullet = CBullet::Create(pos);	//弾の生成
	}

	CObject2D::SetPos(pos);	//位置を更新
}

//================================================
//描画
//================================================
void CPlayer::Draw()
{
	CObject2D::Draw();	//親クラス
}