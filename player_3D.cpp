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
#include "camera.h"
#include "input.h"

#include "explosion_3D.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CPlayer3D::PLAYER_SIZE = 150.0f;	//サイズ
const float CPlayer3D::MOVE_SPEED = 10.0f;		//移動速度

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
CPlayer3D::CPlayer3D():
	m_nTimerInterval(0),
	m_getItem(CItem3D::TYPE::NONE),
	m_bulletType(CBullet3D::TYPE::NONE)
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

	//メンバ変数の初期設定
	m_getItem = CItem3D::TYPE::NONE;		//何も取得していない
	m_bulletType = CBullet3D::TYPE::NORMAL;	//通常弾

	//サイズを設定
	D3DXVECTOR2 size = D3DXVECTOR2(PLAYER_SIZE, PLAYER_SIZE);
	CObject3D::SetSize(size);

	//位置を設定
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CObject3D::SetPos(pos);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::player000);

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

	if(CObject3D::Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ENEMY))
	{//敵と接触した場合
		//爆発の生成
		CExplosion3D::Create(CObject3D::GetPos());

		Release();	//解放
	}

	if (m_getItem != CItem3D::TYPE::NONE)
	{//何かアイテムを取得した場合
		//アイテム毎の処理
		ProcessingForEachItem();
	}
}

//================================================
//描画
//================================================
void CPlayer3D::Draw()
{
	CObject3D::Draw();	//親クラス
}

//================================================
//所持アイテムのセット
//================================================
void CPlayer3D::SetItem(const CItem3D::TYPE &item)
{
	m_getItem = item;
}

//================================================
//所持アイテムの取得
//================================================
CItem3D::TYPE CPlayer3D::GetItem()
{
	return m_getItem;
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

	//カメラ情報の取得
	D3DXMATRIX mtxCamera = CApplication::GetCamera()->GetMatrixView();
	
	//カメラの視点の位置を取得
	D3DXVECTOR3 posV = CApplication::GetCamera()->GetPosV();

	//位置を反映
	D3DXMatrixTranslation(&mtxCamera, posV.x, posV.y, posV.z);

	//移動制限を設定
	float fRimitTop		= (mtxCamera._42 + (CRenderer::SCREEN_HEIGHT * 0.5f));	//上
	float fRimitBottom	= (mtxCamera._42 - (CRenderer::SCREEN_HEIGHT * 0.5f));	//下
	float fRimitLeft	= (mtxCamera._41 - (CRenderer::SCREEN_WIDTH * 0.5f));	//左
	float fRimitRight	= (mtxCamera._41 + (CRenderer::SCREEN_WIDTH * 0.5f));	//右

	if (fTop > fRimitTop)
	{//移動制限(上)
		pos.y = fRimitTop - fSizeHalf;
	}
	else if (fBottom < fRimitBottom)
	{//移動制限(下)
		pos.y = fRimitBottom + fSizeHalf;
	}

	if (fLeft < fRimitLeft)
	{//移動制限(左)
		pos.x = fRimitLeft + fSizeHalf;
	}
	else if (fRight > fRimitRight)
	{//移動制限(右)
		pos.x = fRimitRight - fSizeHalf;
	}

	CObject3D::SetPos(pos);	//位置を更新
}

//================================================
//発射
//================================================
void CPlayer3D::Shot()
{
	CInput* pInput = CInput::GetKey();	//キーボード情報を取得

	if (pInput->Trigger(CInput::STANDARD_KEY::SHOT))
	{//単押し
		CreateBulletByType();	//タイプ別の弾の生成
	}
	else if (pInput->Press(CInput::STANDARD_KEY::SHOT))
	{//長押し(押しっぱなし)
		m_nTimerInterval++;	//タイマーを進める

		if (m_nTimerInterval % SHOT_INTERVAL != 0)
		{//間隔のタイマーが規定値に達していない
			return;
		}

		/* 間隔タイマーが規定値に達したら */

		CreateBulletByType();	//タイプ別の弾の生成
	}

	if (pInput->Release(CInput::STANDARD_KEY::SHOT))
	{//キーを離したら
		m_nTimerInterval = 0;	//タイマーをリセット
	}
}

//================================================
//タイプ別の弾の生成
//================================================
void CPlayer3D::CreateBulletByType()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//位置情報を取得

	D3DXVECTOR3 move;	//移動量設定用

	switch (m_bulletType)
	{/* 取得したアイテム毎の処理 */
	case CBullet3D::TYPE::NORMAL:	/* 通常弾 */

		//移動量設定(+X方向)
		move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

		//弾の生成
		CBullet3D::Create(pos, move, CObject::OBJ_TYPE::PLAYER);
		break;

	case CBullet3D::TYPE::DOUBLE:	/* 二連弾 */
		
		{
			//弾の位置を上下に少しずらす
			D3DXVECTOR3 posOver = pos + D3DXVECTOR3(0.0f, 5.0f, 0.0f);		//上側
			D3DXVECTOR3 posUnder = pos + D3DXVECTOR3(0.0f, -5.0f, 0.0f);	//下側

			//移動量設定(+X方向)
			move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

			//弾の生成
			CBullet3D::Create(posOver, move, CObject::OBJ_TYPE::PLAYER);	//上側
			CBullet3D::Create(posUnder, move, CObject::OBJ_TYPE::PLAYER);	//下側
		}
		break;

	case CBullet3D::TYPE::TRIPLE:	/* 三方向各散弾 */

		/* 斜め上方向 */

		move = D3DXVECTOR3(10.0f, 10.0f, 0.0f);	//移動量設定

		//弾の生成
		CBullet3D::Create(pos, move, CObject::OBJ_TYPE::PLAYER);
		

		/* 水平方向 */

		move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);	//移動量設定

		//弾の生成
		CBullet3D::Create(pos, move, CObject::OBJ_TYPE::PLAYER);
		

		/* 斜め下方向 */

		move = D3DXVECTOR3(10.0f, -10.0f, 0.0f);	//移動量設定

		//弾の生成
		CBullet3D::Create(pos, move, CObject::OBJ_TYPE::PLAYER);
		break;

	default: /* それ以外 */
		assert(false);
		break;
	}
}

//================================================
//アイテム毎の処理
//================================================
void CPlayer3D::ProcessingForEachItem()
{
	switch (m_getItem)
	{
	case CItem3D::TYPE::CHANGE_BUlLET_NORMAL: /* 弾変化(通常弾) */
		m_bulletType = CBullet3D::TYPE::NORMAL;	//弾のタイプを変更
		break;

	case CItem3D::TYPE::CHANGE_BUlLET_DOUBLE: /* 弾変化(二連弾) */
		m_bulletType = CBullet3D::TYPE::DOUBLE;	//弾のタイプを変更
		break;

	case CItem3D::TYPE::CHANGE_BUlLET_TRIPLE: /* 弾変化(三方向各散弾) */
		m_bulletType = CBullet3D::TYPE::TRIPLE;	//弾のタイプを変更
		break;

	default: /* それ以外 */
		break;
	}
}