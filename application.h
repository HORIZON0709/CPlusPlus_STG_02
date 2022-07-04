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
class CPlayer3D;
class CEnemy3D;

//***************************
//�A�v���P�[�V�����N���X�̒�`
//***************************
class CApplication
{/* ��{�N���X */
public: /* �ÓI�����o�֐� */
	static CInputKeyboard* GetInputKeyboard();	//�L�[�{�[�h�����擾

	static CTexture* GetTexture();		//�e�N�X�`�������擾
	static CRenderer* GetRenderer();	//�����_���[�����擾
	static CCamera* GetCamera();		//�J���������擾

	static CPlayer* GetPlayer();	//�v���C���[�����擾
	static CEnemy* GetEnemy();		//�G�����擾

	static CPlayer3D* GetPlayer3D();	//�v���C���[(3D)�����擾
	static CEnemy3D* GetEnemy3D();		//�G(3D)�����擾

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CApplication();
	~CApplication();

public: /* �����o�֐� */
	HRESULT Init(HWND hWnd, BOOL bWindow,HINSTANCE hInstance);	//������

	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

private: /* �ÓI�����o�ϐ� */
	static CInput* m_pInput;					//�C���v�b�g�̃|�C���^
	static CInputKeyboard* m_pInputKeyboard;	//�L�[�{�[�h�̃|�C���^

	static CTexture* m_pTexture;	//�e�N�X�`���̃|�C���^
	static CRenderer* m_pRenderer;	//�����_���[�̃|�C���^
	static CCamera* m_pCamera;		//�J�����̃|�C���^

	static CPlayer* m_pPlayer;	//�v���C���[�̃|�C���^
	static CEnemy* m_pEnemy;	//�G�̃|�C���^

	static CPlayer3D* m_pPlayer3D;	//�v���C���[(3D)�̃|�C���^
	static CEnemy3D* m_pEnemy3D;	//�G(3D)�̃|�C���^
};

#endif