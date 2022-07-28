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

#include "enemy_3D.h"

//***************************
//前方宣言
//***************************
class CInput;
class CInputKeyboard;
class CRenderer;
class CTexture;
class CCamera;

class CPlayer;
class CEnemy;
class CScore;

class CPlayer3D;
class CBg3D;

//***************************
//アプリケーションクラスの定義
//***************************
class CApplication
{/* 基本クラス */
public: /* 静的メンバ関数 */

	//********** 情報の取得 **********//

	static CInput* GetInput();					//インプット
	static CInputKeyboard* GetInputKeyboard();	//キーボード

	static CTexture* GetTexture();		//テクスチャ
	static CRenderer* GetRenderer();	//レンダラー
	static CCamera* GetCamera();		//カメラ

	static CPlayer* GetPlayer();	//プレイヤー
	static CEnemy* GetEnemy();		//敵
	static CScore* GetScore();		//スコア

	static CPlayer3D* GetPlayer3D();	//プレイヤー(3D)
	static CEnemy3D* GetEnemy3D(const int nIdx);		//敵(3D)
	static CBg3D* GetBg3D();			//背景(3D)

public: /* コンストラクタ・デストラクタ */
	CApplication();
	~CApplication();

public: /* メンバ関数 */
	HRESULT Init(HWND hWnd, BOOL bWindow,HINSTANCE hInstance);	//初期化

	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画

private: /* 静的メンバ変数 */
	
	//********** ポインタ **********//

	static CInput* m_pInput;					//インプット
	static CInputKeyboard* m_pInputKeyboard;	//キーボード

	static CTexture* m_pTexture;	//テクスチャ
	static CRenderer* m_pRenderer;	//レンダラー
	static CCamera* m_pCamera;		//カメラ

	static CPlayer* m_pPlayer;	//プレイヤー
	static CEnemy* m_pEnemy;	//敵
	static CScore* m_pScore;	//スコア

	static CPlayer3D* m_pPlayer3D;	//プレイヤー(3D)
	static CEnemy3D* m_apEnemy3D[CEnemy3D::MAX_ENEMY];	//敵(3D)
	static CBg3D* m_pBg3D;			//背景(3D)
};
#endif