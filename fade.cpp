//================================================
//
//制作実践基礎[fade.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "fade.h"
#include "renderer.h"

#include <assert.h>

//***************************
//定数の定義
//***************************
const float CFade::FADE_WIDTH = CRenderer::SCREEN_WIDTH;	//横幅
const float CFade::FADE_HEIGHT = CRenderer::SCREEN_HEIGHT;	//縦幅

//================================================
//生成
//================================================
CFade* CFade::Create()
{
	CFade* pFade = nullptr;	//ポインタ

	if (pFade != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pFade = new CFade;	//メモリの動的確保

	pFade->Init();	//初期化

	return pFade;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CFade::CFade() :
	m_state(STATE::NONE)
{
	//タイプの設定
	CObject::SetObjType(CObject::OBJ_TYPE::FADE);
}

//================================================
//デストラクタ
//================================================
CFade::~CFade()
{
}

//================================================
//初期化
//================================================
HRESULT CFade::Init()
{
	//メンバ変数の初期化
	m_state = STATE::NONE;

	//位置を設定
	D3DXVECTOR3 pos = D3DXVECTOR3(CRenderer::SCREEN_WIDTH * 0.5f,
								  CRenderer::SCREEN_HEIGHT * 0.5f,
								  0.0f);
	CObject2D::SetPos(pos);

	//サイズを設定
	D3DXVECTOR2 size = D3DXVECTOR2(FADE_WIDTH, FADE_HEIGHT);
	CObject2D::SetSize(size);

	//色を設定
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	CObject2D::SetCol(col);

	return S_OK;
}

//================================================
//終了
//================================================
void CFade::Uninit()
{
	CObject2D::Uninit();	//親クラス
}

//================================================
//更新
//================================================
void CFade::Update()
{
	CObject2D::Update();	//親クラス

	if (m_state == STATE::NONE)
	{//フェードしていない場合
		return;
	}

	/* フェードしているとき */

	D3DXCOLOR col = CObject2D::GetCol();	//色を取得

	if (m_state == STATE::FADE_IN)
	{//フェードイン( 不透明 ---> 透明 )
		col.a -= 0.01f;	//透明にしていく

		//色を設定
		CObject2D::SetCol(col);

		if (col.a <= 0.0f)
		{//完全に透明になったら
			col.a = 0.0f;			//0.0にする
			m_state = STATE::NONE;	//フェードしていない状態にする
		}
	}
	else if (m_state == STATE::FADE_OUT)
	{//フェードアウト( 透明 ---> 不透明 )
		col.a += 0.01f;	//不透明にしていく

		//色を設定
		CObject2D::SetCol(col);

		if (col.a >= 1.0f)
		{//完全に不透明になったら
			col.a = 1.0f;			//1.0にする
			m_state = STATE::NONE;	//フェードしていない状態にする
		}
	}
}

//================================================
//描画
//================================================
void CFade::Draw()
{
	CObject2D::Draw();	//親クラス
}

//================================================
//設定
//================================================
void CFade::Set(const STATE &state)
{
	m_state = state;	//フェード状態を設定
}