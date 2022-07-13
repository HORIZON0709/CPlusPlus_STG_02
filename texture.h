//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CTexture
{
public: /* 定義 */
	enum TEXTURE
	{
		/* プレイヤー */
		player000 = 0,	//モチモチの余さん

		/* 弾 */
		bullet000,	//桜のサークル
		bullet001,	//スラックのアイコン

		/* 爆発 */
		explosion000,	//配布の爆発アニメーション画像

		/* 敵 */
		enemy000,	//全部違うネタ画像のやつ

		/* 背景 */
		bg000,	//何かユニバース

		/* アイテム */
		item000,	//三角形

		MAX,
		NONE,	//使用しない
	};

	static const char* s_FileName[];	// ファイルパス

public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public: /* メンバ関数 */
	void LoadAll();										// 全ての読み込み
	void Load(TEXTURE inTexture);						// 指定の読み込み
	void ReleaseAll();									// 全ての破棄
	void Release(TEXTURE inTexture);					// 指定の破棄
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// 情報の取得

private: /* メンバ変数 */
	LPDIRECT3DTEXTURE9 s_pTexture[MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_
