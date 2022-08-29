//================================================
//
//������H��b[mode.h]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "mode.h"

#include "title.h"
#include "game.h"
#include "result.h"

//***************************
//�ÓI�����o�ϐ�
//***************************
CMode::MODE CMode::m_mode = GAME;		//���[�h
CTitle* CMode::m_pTitle = nullptr;		//�^�C�g��
CGame* CMode::m_pGame = nullptr;		//�Q�[��
CResult* CMode::m_pResult = nullptr;	//���U���g

//================================================
//���[�h�̐ݒ�
//================================================
void CMode::SetMode(const MODE &mode)
{
	switch (m_mode)
	{//�ύX�O�̃��[�h���I������
	case MODE::TITLE: /* �^�C�g�� */
		if (m_pTitle != nullptr)
		{//NULL�`�F�b�N
			m_pTitle->Uninit();	//�I��
			delete m_pTitle;	//�������̉��
			m_pTitle = nullptr;	//nullptr�ɂ���
		}
		break;

	case MODE::GAME: /* �Q�[�� */
		if (m_pGame != nullptr)
		{//NULL�`�F�b�N
			m_pGame->Uninit();	//�I��
			delete m_pGame;		//�������̉��
			m_pGame = nullptr;	//nullptr�ɂ���
		}
		break;

	case MODE::RESULT: /* ���U���g */
		if (m_pResult != nullptr)
		{//NULL�`�F�b�N
			m_pResult->Uninit();	//�I��
			delete m_pResult;		//�������̉��
			m_pResult = nullptr;	//nullptr�ɂ���
		}
		break;
	}

	m_mode = mode;	//���[�h��ύX

	switch (m_mode)
	{//�ύX��̃��[�h������������
	case MODE::TITLE: /* �^�C�g�� */
		if (m_pTitle == nullptr)
		{//NULL�`�F�b�N
			m_pTitle = new CTitle;	//�������̓��I�m��
			m_pTitle->Init();		//������
		}
		break;

	case MODE::GAME: /* �Q�[�� */
		if (m_pGame == nullptr)
		{//NULL�`�F�b�N
			m_pGame = new CGame;	//�������̓��I�m��
			m_pGame->Init();		//������
		}
		break;

	case MODE::RESULT: /* ���U���g */
		if (m_pResult == nullptr)
		{//NULL�`�F�b�N
			m_pResult = new CResult;	//�������̓��I�m��
			m_pResult->Init();			//������
		}
		break;
	}
}

//================================================
//�Q�[�������擾
//================================================
CGame* CMode::GetGame()
{
	return m_pGame;
}

//================================================
//�R���X�g���N�^
//================================================
CMode::CMode()
{
}

//================================================
//�f�X�g���N�^
//================================================
CMode::~CMode()
{
}

//================================================
//������
//================================================
HRESULT CMode::Init()
{
	switch (m_mode)
	{
	case MODE::TITLE: /* �^�C�g�� */
		if (m_pTitle == nullptr)
		{//NULL�`�F�b�N
			m_pTitle = new CTitle;	//�������̓��I�m��
		}

		if (FAILED(m_pTitle->Init()))
		{//���������������s�����ꍇ
			return E_FAIL;
		}
		break;

	case MODE::GAME: /* �Q�[�� */
		if (m_pGame == nullptr)
		{//NULL�`�F�b�N
			m_pGame = new CGame;	//�������̓��I�m��
		}

		if (FAILED(m_pGame->Init()))
		{//���������������s�����ꍇ
			return E_FAIL;
		}
		break;

	case MODE::RESULT: /* ���U���g */
		if (m_pResult == nullptr)
		{//NULL�`�F�b�N
			m_pResult = new CResult;	//�������̓��I�m��
		}

		if (FAILED(m_pResult->Init()))
		{//���������������s�����ꍇ
			return E_FAIL;
		}
		break;
	}

	return S_OK;
}

//================================================
//�I��
//================================================
void CMode::Uninit()
{
	/* �^�C�g�� */

	if (m_pTitle != nullptr)
	{//NULL�`�F�b�N
		m_pTitle->Uninit();	//�I��
		delete m_pTitle;	//�������̉��
		m_pTitle = nullptr;	//nullptr�ɂ���
	}

	/* �Q�[�� */

	if (m_pGame != nullptr)
	{//NULL�`�F�b�N
		m_pGame->Uninit();	//�I��
		delete m_pGame;		//�������̉��
		m_pGame = nullptr;	//nullptr�ɂ���
	}

	/* ���U���g */

	if (m_pResult != nullptr)
	{//NULL�`�F�b�N
		m_pResult->Uninit();	//�I��
		delete m_pResult;		//�������̉��
		m_pResult = nullptr;	//nullptr�ɂ���
	}
}

//================================================
//�X�V
//================================================
void CMode::Update()
{
}

//================================================
//�`��
//================================================
void CMode::Draw()
{
}