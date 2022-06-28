//================================================
//
//������H��b[application.h]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "application.h"
#include "input.h"
#include "renderer.h"
#include "texture.h"
#include "player.h"
#include "enemy.h"

#include "object2D.h"

//***************************
//�ÓI�����o�ϐ�
//***************************
CInput* CApplication::m_pInput = nullptr;					//�C���v�b�g
CInputKeyboard* CApplication::m_pInputKeyboard = nullptr;	//�L�[�{�[�h

CRenderer* CApplication::m_pRenderer = nullptr;	//�����_���[
CTexture* CApplication::m_pTexture = nullptr;	//�e�N�X�`��

CPlayer* CApplication::m_pPlayer = nullptr;	//�v���C���[
CEnemy* CApplication::m_pEnemy = nullptr;	//�G

//================================================
//�L�[�{�[�h�����擾
//================================================
CInputKeyboard* CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
}

//================================================
//�����_���[�����擾
//================================================
CRenderer* CApplication::GetRenderer()
{
	return m_pRenderer;
}

//================================================
// �e�N�X�`�������擾
//================================================
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//================================================
//�v���C���[�����擾
//================================================
CPlayer* CApplication::GetPlayer()
{
	return m_pPlayer;
}

//================================================
//�G�����擾
//================================================
CEnemy* CApplication::GetEnemy()
{
	return m_pEnemy;
}

//================================================
//�R���X�g���N�^
//================================================
CApplication::CApplication()
{
}

//================================================
//�f�X�g���N�^
//================================================
CApplication::~CApplication()
{
}

//================================================
//������
//================================================
HRESULT CApplication::Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance)
{
	/* �C���v�b�g */

	if (m_pInput == nullptr)
	{//NULL�`�F�b�N
		m_pInput = CInput::Create();	//�������̓��I�m��
	}

	if (FAILED(m_pInput->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	/* �����_���[ */

	if (m_pRenderer == nullptr)
	{//NULL�`�F�b�N
		m_pRenderer = new CRenderer;	//�������̓��I�m��
	}

	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	/* �e�N�X�`�� */

	if (m_pTexture == nullptr)
	{//NULL�`�F�b�N
		m_pTexture = new CTexture;	//�������̓��I�m��
	}

	/* �v���C���[ */

	m_pPlayer = CPlayer::Create();	//����

	/* �G */

	m_pEnemy = CEnemy::Create();	//����

	return S_OK;
}

//================================================
//�I��
//================================================
void CApplication::Uninit()
{
	/* �I�u�W�F�N�g */

	CObject2D::ReleaseAll();	//�S�Ẳ��
	
	/* �v���C���[ */

	m_pPlayer = nullptr;	//nullptr�ɂ���

	/* �G */

	m_pEnemy = nullptr;	//nullptr�ɂ���

	/* �e�N�X�`�� */

	if (m_pTexture != nullptr)
	{//NULL�`�F�b�N
		m_pTexture->ReleaseAll();	//�I������
		delete m_pTexture;			//�������̉��
		m_pTexture = nullptr;		//nullptr�ɂ���
	}

	/* �L�[�{�[�h */

	if (m_pInputKeyboard != nullptr)
	{//NULL�`�F�b�N
		m_pInputKeyboard->Uninit();	//�I������
		delete m_pInputKeyboard;	//�������̉��
		m_pInputKeyboard = nullptr;	//nullptr�ɂ���
	}

	/* �C���v�b�g */

	m_pInput->Uninit();	//�I������

	/* �����_���[ */

	if (m_pRenderer != nullptr)
	{//NULL�`�F�b�N
		m_pRenderer->Uninit();	//�I������
		delete m_pRenderer;		//�������̉��
		m_pRenderer = nullptr;	//nullptr�ɂ���
	}
}

//================================================
//�X�V
//================================================
void CApplication::Update()
{
	if (m_pInput != nullptr)
	{//NULL�`�F�b�N
		m_pInput->Update();	//�L�[�{�[�h
	}

	if (m_pInputKeyboard != nullptr)
	{//NULL�`�F�b�N
		m_pInputKeyboard->Update();	//�L�[�{�[�h
	}

	if (m_pRenderer != nullptr)
	{//NULL�`�F�b�N
		m_pRenderer->Update();	//�����_���[
	}
}

//================================================
//�`��
//================================================
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{//NULL�`�F�b�N
		m_pRenderer->Draw();	//�����_���[
	}
}