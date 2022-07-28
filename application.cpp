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

#include "player.h"
#include "enemy.h"
#include "score.h"

#include "player_3D.h"
#include "bg_3D.h"

#include "object2D.h"
#include "object3D.h"

//***************************
//�ÓI�����o�ϐ�
//***************************
CInput* CApplication::m_pInput = nullptr;					//�C���v�b�g
CInputKeyboard* CApplication::m_pInputKeyboard = nullptr;	//�L�[�{�[�h

CTexture* CApplication::m_pTexture = nullptr;	//�e�N�X�`��
CRenderer* CApplication::m_pRenderer = nullptr;	//�����_���[
CCamera* CApplication::m_pCamera = nullptr;		//�J����

CPlayer* CApplication::m_pPlayer = nullptr;	//�v���C���[
CEnemy* CApplication::m_pEnemy = nullptr;	//�G
CScore* CApplication::m_pScore = nullptr;	//�X�R�A

CPlayer3D* CApplication::m_pPlayer3D = nullptr;	//�v���C���[(3D)
CEnemy3D* CApplication::m_apEnemy3D[CEnemy3D::MAX_ENEMY] = {};	//�G(3D)
CBg3D* CApplication::m_pBg3D = nullptr;			//�w�i(3D)

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
//�X�R�A�����擾
//================================================
CScore* CApplication::GetScore()
{
	return m_pScore;
}

//================================================
//�v���C���[(3D)�����擾
//================================================
CPlayer3D* CApplication::GetPlayer3D()
{
	return m_pPlayer3D;
}

//================================================
//�G(3D)�����擾
//================================================
CEnemy3D* CApplication::GetEnemy3D(const int nIdx)
{
	return m_apEnemy3D[nIdx];
}

//================================================
//�w�i(3D)�����擾
//================================================
CBg3D* CApplication::GetBg3D()
{
	return m_pBg3D;
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

	/* �v���C���[ */

	//m_pPlayer = CPlayer::Create();	//����

	/* �G */

	//m_pEnemy = CEnemy::Create();	//����

	/* �X�R�A */

	m_pScore = CScore::Create();	//����

	/* �w�i(3D) */

	m_pBg3D = CBg3D::Create();	//����

	/* �v���C���[(3D) */

	m_pPlayer3D = CPlayer3D::Create();	//����

	/* �G(3D) */

	for (int i = 0; i < CEnemy3D::MAX_ENEMY; i++)
	{
		if (m_apEnemy3D[i] != nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�̏ꍇ */

		bool bNumEnemyCurve = ((i >= 0) && (i < 2));	//�J�[�u����G���ۂ�

		if (bNumEnemyCurve)
		{
			D3DXVECTOR3 pos = D3DXVECTOR3(300.0f + (200.0f * i),
										 (100.0f * i),
											0.0f);

			m_apEnemy3D[i] = CEnemy3D::Create(CEnemy3D::ENM_TYPE::CURVE, pos);	//����
		}
	}

	return S_OK;
}

//================================================
//�I��
//================================================
void CApplication::Uninit()
{
	/* �I�u�W�F�N�g */

	CObject2D::ReleaseAll();	//�S�Ẳ��(2D)
	CObject3D::ReleaseAll();	//�S�Ẳ��(3D)
	
	/* �v���C���[ */

	//m_pPlayer = nullptr;	//nullptr�ɂ���

	/* �G */

	//m_pEnemy = nullptr;	//nullptr�ɂ���

	/* �X�R�A */

	m_pScore = nullptr;	//nullptr�ɂ���

	/* �w�i(3D) */

	m_pBg3D = nullptr;	//nullptr�ɂ���

	/* �v���C���[(3D) */

	m_pPlayer3D = nullptr;	//nullptr�ɂ���

	/* �G(3D) */

	for (int i = 0; i < CEnemy3D::MAX_ENEMY; i++)
	{
		if (m_apEnemy3D[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		m_apEnemy3D[i] = nullptr;	//nullptr�ɂ���
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