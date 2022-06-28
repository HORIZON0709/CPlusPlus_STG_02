//================================================
//
//制作実践基礎[application.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//***************************
//インクルード
//***************************
#include <d3dx9.h>

//***************************
//前方宣言
//***************************
class CInput;
class CInputKeyboard;
class CRenderer;
class CTexture;
class CPlayer;
class CEnemy;

//***************************
//アプリケーションクラスの定義
//***************************
class CApplication
{/* 基本クラス */
public: /* 静的メンバ関数 */
	static CInputKeyboard* GetInputKeyboard();	//キーボード情報を取得

	static CRenderer* GetRenderer();	//レンダラー情報を取得
	static CTexture* GetTexture();		//テクスチャ情報を取得

	static CPlayer* GetPlayer();	//プレイヤー情報を取得
	static CEnemy* GetEnemy();		//敵情報を取得

public: /* コンストラクタ・デストラクタ */
	CApplication();
	~CApplication();

public: /* メンバ関数 */
	HRESULT Init(HWND hWnd, BOOL bWindow,HINSTANCE hInstance);	//初期化

	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

private: /* 静的メンバ変数 */
	static CInput* m_pInput;					//インプットのポインタ
	static CInputKeyboard* m_pInputKeyboard;	//キーボードのポインタ

	static CRenderer* m_pRenderer;	//レンダラーのポインタ
	static CTexture* m_pTexture;	//テクスチャのポインタ

	static CPlayer* m_pPlayer;	//プレイヤーのポインタ
	static CEnemy* m_pEnemy;	//敵のポインタ
};

#endif