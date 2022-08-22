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
#include "camera.h"

#include "mode.h"

//***************************
//�ÓI�����o�ϐ�
//***************************
CInput* CApplication::m_pInput = nullptr;					//�C���v�b�g
CInputKeyboard* CApplication::m_pInputKeyboard = nullptr;	//�L�[�{�[�h

CTexture* CApplication::m_pTexture = nullptr;	//�e�N�X�`��
CRenderer* CApplication::m_pRenderer = nullptr;	//�����_���[
CCamera* CApplication::m_pCamera = nullptr;		//�J����

CMode* CApplication::m_pMode = nullptr;	//���[�h

//================================================
//�C���v�b�g�����擾
//================================================
CInput* CApplication::GetInput()
{
	return m_pInput;
}

//================================================
//�L�[�{�[�h�����擾
//================================================
CInputKeyboard* CApplication::GetInputKeyboard()
{
	return m_pInputKeyboard;
}

//================================================
//�e�N�X�`�������擾
//================================================
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//================================================
//�����_���[�����擾
//================================================
CRenderer* CApplication::GetRenderer()
{
	return m_pRenderer;
}

//================================================
//�J���������擾
//================================================
CCamera* CApplication::GetCamera()
{
	return m_pCamera;
}

//================================================
//���[�h�����擾
//================================================
CMode* CApplication::GetMode()
{
	return m_pMode;
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

	/* �L�[�{�[�h */

	if (m_pInputKeyboard == nullptr)
	{//NULL�`�F�b�N
		m_pInputKeyboard = new CInputKeyboard;	//�������̓��I�m��
	}

	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	/* �e�N�X�`�� */

	if (m_pTexture == nullptr)
	{//NULL�`�F�b�N
		m_pTexture = new CTexture;	//�������̓��I�m��
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

	/* �J���� */

	if (m_pCamera == nullptr)
	{//NULL�`�F�b�N
		m_pCamera = new CCamera;	//�������̓��I�m��
		m_pCamera->Init();			//������
	}

	/* ���[�h */

	if (m_pMode == nullptr)
	{//NULL�`�F�b�N
		m_pMode = new CMode;	//�������̓��I�m��
	}

	if (FAILED(m_pMode->Init()))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	return S_OK;
}

//================================================
//�I��
//================================================
void CApplication::Uninit()
{
	/* ���[�h */

	if (m_pMode != nullptr)
	{//NULL�`�F�b�N
		m_pMode->Uninit();	//�I��
		delete m_pMode;		//�������̉��
		m_pMode = nullptr;	//nullptr�ɂ���
	}

	/* �J���� */

	if (m_pCamera != nullptr)
	{//NULL�`�F�b�N
		m_pCamera->Uninit();	//�I��
		delete m_pCamera;		//�������̉��
		m_pCamera = nullptr;	//nullptr�ɂ���
	}

	/* �����_���[ */

	if (m_pRenderer != nullptr)
	{//NULL�`�F�b�N
		m_pRenderer->Uninit();	//�I������
		delete m_pRenderer;		//�������̉��
		m_pRenderer = nullptr;	//nullptr�ɂ���
	}

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

}

//================================================
//�X�V
//================================================
void CApplication::Update()
{
	if (m_pInput != nullptr)
	{//NULL�`�F�b�N
		m_pInput->Update();	//�C���v�b�g
	}

	if (m_pInputKeyboard != nullptr)
	{//NULL�`�F�b�N
		m_pInputKeyboard->Update();	//�L�[�{�[�h
	}

	if (m_pRenderer != nullptr)
	{//NULL�`�F�b�N
		m_pRenderer->Update();	//�����_���[
	}

	if (m_pCamera != nullptr)
	{//NULL�`�F�b�N
		m_pCamera->Update();	//�J����
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