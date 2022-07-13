//================================================
//
//制作実践基礎[score.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//***************************
//インクルード
//***************************
#include "object.h"

//***************************
//スコアクラスの定義
//***************************
class CScore : public CObject
{/* CObjectの派生クラス */
public: /* 静的メンバ関数 */
	static CScore* Create();	//生成

public: /* コンストラクタ・デストラクタ */
	CScore();
	~CScore();

public: /* オーバーライド関数 */
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

public: /* メンバ関数 */
	void Set(const int &nScore);	//セット
	void Add(const int &nValue);	//スコア加算
	int Get();				//取得

private: /* メンバ変数 */
	//CNumber* m_apNumber[8];	//桁数分用意
	int m_nScore;				//スコア
};


#endif