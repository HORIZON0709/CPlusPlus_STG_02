//================================================
//
//制作実践基礎[enemy_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "enemy_3D.h"
#include "enemy_straight.h"
#include "enemy_curve.h"
#include "enemy_boss.h"

#include <assert.h>

//================================================
//生成
//================================================
CEnemy3D* CEnemy3D::Create(const ENM_TYPE &type, const D3DXVECTOR3 &pos)
{
	CEnemy3D* pEnemy3D = nullptr;	//ポインタ

	if (pEnemy3D != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	switch (type)
	{
	case ENM_TYPE::STRAIGHT: /* 直線 */
		pEnemy3D = new CEnemyStraight;	//メモリの動的
		break;

	case ENM_TYPE::CURVE: /* sinカーブ */
		pEnemy3D = new CEnemyCurve;	//メモリの動的確保
		break;

	case ENM_TYPE::BOSS: /* ボス */
		pEnemy3D = new CEnemyBoss;	//メモリの動的確保
		break;

	default: /* それ以外 */
		assert(false);
		break;
	}

	pEnemy3D->Init();		//初期化
	pEnemy3D->SetPos(pos);	//位置を設定

	return pEnemy3D;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CEnemy3D::CEnemy3D():
	m_type(ENM_TYPE::NONE)
{
	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::ENEMY);
}

//================================================
//デストラクタ
//================================================
CEnemy3D::~CEnemy3D()
{
}

//================================================
//初期化
//================================================
HRESULT CEnemy3D::Init()
{
	CObject3D::Init();	//親クラス

	return S_OK;
}

//================================================
//終了
//================================================
void CEnemy3D::Uninit()
{
	CObject3D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CEnemy3D::Update()
{
	CObject3D::Update();	//親クラス
}

//================================================
//描画
//================================================
void CEnemy3D::Draw()
{
	CObject3D::Draw();	//親クラス
}

//================================================
//敵の種類を設定
//================================================
void CEnemy3D::SetEnmType(const ENM_TYPE &type)
{
	m_type = type;
}

//================================================
//敵の種類を取得
//================================================
CEnemy3D::ENM_TYPE CEnemy3D::GetEnmType()
{
	return m_type;
}