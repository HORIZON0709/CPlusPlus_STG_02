//================================================
//
//制作実践基礎[score.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "score.h"
#include "number.h"

#include <assert.h>

//================================================
//生成
//================================================
CScore* CScore::Create()
{
	CScore* pScore = nullptr;	//ポインタ

	if (pScore != nullptr)
	{//NULLチェック
		assert(false);
	}

	/* nullptrの場合 */

	pScore = new CScore;	//メモリの動的確保

	pScore->Init();	//初期化

	return pScore;	//動的確保したものを返す
}

//================================================
//コンストラクタ
//================================================
CScore::CScore():
	m_nScore(0)
{
	//メンバ変数のクリア
	memset(m_apNumber, 0, sizeof(m_apNumber));
}

//================================================
//デストラクタ
//================================================
CScore::~CScore()
{
}

//================================================
//初期化
//================================================
HRESULT CScore::Init()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		m_apNumber[i] = nullptr;	//nullptrにする

		if (m_apNumber[i] != nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrの場合 */

		m_apNumber[i] = CNumber::Create();	//メモリの動的確保

		m_apNumber[i]->Init();	//初期化

		//位置の設定
		D3DXVECTOR3 pos = D3DXVECTOR3(CNumber::POS_X, CNumber::POS_Y, 0.0f);
		m_apNumber[i]->SetPos(pos);

		//サイズの設定
		D3DXVECTOR2 size = D3DXVECTOR2(CNumber::NUMBER_WIDTH, CNumber::NUMBER_HEIGHT);
		m_apNumber[i]->SetSize(size);

		//テクスチャの設定
		m_apNumber[i]->SetTexture(CTexture::TEXTURE::number000);

		//テクスチャ座標の設定
		m_apNumber[i]->SetTexUV(CNumber::DIVIDE_TEX_U, 0);
	}

	return S_OK;
}

//================================================
//終了
//================================================
void CScore::Uninit()
{
}

//================================================
//更新
//================================================
void CScore::Update()
{
}

//================================================
//描画
//================================================
void CScore::Draw()
{
}

//================================================
//セット
//================================================
void CScore::SetScore(const int &nScore)
{
	m_nScore = nScore;
}

//================================================
//スコア加算
//================================================
void CScore::AddScore(const int &nValue)
{
	m_nScore += nValue;
}

//================================================
//現在のスコアの取得
//================================================
int CScore::GetCurrentScore()
{
	return m_nScore;
}