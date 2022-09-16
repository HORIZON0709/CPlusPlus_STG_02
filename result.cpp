//================================================
//
//������H��b[result.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "result.h"

#include "application.h"
#include "fade.h"
#include "input.h"
#include "object2D.h"
#include "bg.h"

#include <assert.h>

//***************************
//�ÓI�����o�ϐ�
//***************************
CBg* CResult::m_pBg = nullptr;	//�w�i

//================================================
//�R���X�g���N�^
//================================================
CResult::CResult() : CMode(MODE::RESULT),
m_bFadeOut(false)
{
}

//================================================
//�f�X�g���N�^
//================================================
CResult::~CResult()
{
}

//================================================
//������
//================================================
HRESULT CResult::Init()
{
	//�����o�ϐ��̏�����
	m_bFadeOut = false;

	/* �w�i */

	//����
	m_pBg = CBg::Create();

	//�e�N�X�`���̐ݒ�
	m_pBg->SetTexture(CTexture::bg002);

	//�e�N�X�`�����W�̐ݒ�
	m_pBg->SetTexUV(1, 0);

	//���]
	CApplication::GetFade()->Set(CFade::STATE::FADE_IN);

	return S_OK;
}

//================================================
//�I��
//================================================
void CResult::Uninit()
{
	/* �I�u�W�F�N�g */

	CObject2D::ReleaseAll();	//�S�Ẳ��(2D)

	/* �w�i */

	if (m_pBg != nullptr)
	{//NULL�`�F�b�N
		m_pBg = nullptr;	//nullptr�ɂ���
	}
}

//================================================
//�X�V
//================================================
void CResult::Update()
{
	CObject::UpdateAll();	//�I�u�W�F�N�g

	CInput* pInput = CInput::GetKey();	//�L�[�{�[�h�����擾

	if (pInput->Trigger(CInput::STANDARD_KEY::DECISION))
	{//����L�\
		CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);	//�Ó]
		m_bFadeOut = true;	//�Ó]����
	}

	if (m_bFadeOut && (CApplication::GetFade()->GetState() == CFade::STATE::NONE))
	{//�t�F�[�h���I����ĈÓ]���̏ꍇ
		Change(MODE::TITLE);	//���[�h�̐ݒ�
	}
}

//================================================
//�`��
//================================================
void CResult::Draw()
{
	CObject::DrawAll();	//�I�u�W�F�N�g
}