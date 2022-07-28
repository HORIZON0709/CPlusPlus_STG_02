//================================================
//
//������H��b[application.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>

#include "enemy_3D.h"

//***************************
//�O���錾
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
//�A�v���P�[�V�����N���X�̒�`
//***************************
class CApplication
{/* ��{�N���X */
public: /* �ÓI�����o�֐� */

	//********** ���̎擾 **********//

	static CInput* GetInput();					//�C���v�b�g
	static CInputKeyboard* GetInputKeyboard();	//�L�[�{�[�h

	static CTexture* GetTexture();		//�e�N�X�`��
	static CRenderer* GetRenderer();	//�����_���[
	static CCamera* GetCamera();		//�J����

	static CPlayer* GetPlayer();	//�v���C���[
	static CEnemy* GetEnemy();		//�G
	static CScore* GetScore();		//�X�R�A

	static CPlayer3D* GetPlayer3D();	//�v���C���[(3D)
	static CEnemy3D* GetEnemy3D(const int nIdx);		//�G(3D)
	static CBg3D* GetBg3D();			//�w�i(3D)

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CApplication();
	~CApplication();

public: /* �����o�֐� */
	HRESULT Init(HWND hWnd, BOOL bWindow,HINSTANCE hInstance);	//������

	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

private: /* �ÓI�����o�ϐ� */
	
	//********** �|�C���^ **********//

	static CInput* m_pInput;					//�C���v�b�g
	static CInputKeyboard* m_pInputKeyboard;	//�L�[�{�[�h

	static CTexture* m_pTexture;	//�e�N�X�`��
	static CRenderer* m_pRenderer;	//�����_���[
	static CCamera* m_pCamera;		//�J����

	static CPlayer* m_pPlayer;	//�v���C���[
	static CEnemy* m_pEnemy;	//�G
	static CScore* m_pScore;	//�X�R�A

	static CPlayer3D* m_pPlayer3D;	//�v���C���[(3D)
	static CEnemy3D* m_apEnemy3D[CEnemy3D::MAX_ENEMY];	//�G(3D)
	static CBg3D* m_pBg3D;			//�w�i(3D)
};
#endif