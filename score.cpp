//================================================
//
//������H��b[score.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "score.h"
#include "number.h"

#include "application.h"
#include "input.h"

#include <math.h>
#include <assert.h>

//================================================
//����
//================================================
CScore* CScore::Create()
{
	CScore* pScore = nullptr;	//�|�C���^

	if (pScore != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pScore = new CScore;	//�������̓��I�m��

	pScore->Init();	//������

	return pScore;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CScore::CScore():
	m_nScore(0)
{
	//�����o�ϐ��̃N���A
	memset(m_apNumber, 0, sizeof(m_apNumber));

	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::SCORE);
}

//================================================
//�f�X�g���N�^
//================================================
CScore::~CScore()
{
}

//================================================
//������
//================================================
HRESULT CScore::Init()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		m_apNumber[i] = nullptr;	//nullptr�ɂ���

		if (m_apNumber[i] != nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�̏ꍇ */

		m_apNumber[i] = CNumber::Create();	//�������̓��I�m��

		//�ʒu�̐ݒ�
		D3DXVECTOR3 pos = D3DXVECTOR3((CNumber::POS_X - (i * CNumber::NUMBER_WIDTH)),
									  CNumber::POS_Y,
									  0.0f);
		m_apNumber[i]->SetPos(pos);

		//�T�C�Y�̐ݒ�
		D3DXVECTOR2 size = D3DXVECTOR2(CNumber::NUMBER_WIDTH, CNumber::NUMBER_HEIGHT);
		m_apNumber[i]->SetSize(size);

		//�e�N�X�`���̐ݒ�
		m_apNumber[i]->SetTexture(CTexture::TEXTURE::number000);

		//�e�N�X�`�����W�̐ݒ�
		m_apNumber[i]->SetTexUV(CNumber::DIVIDE_TEX_U, 0);
	}

	return S_OK;
}

//================================================
//�I��
//================================================
void CScore::Uninit()
{
}

//================================================
//�X�V
//================================================
void CScore::Update()
{
	/* �f�o�b�O�p */

	//�L�[�{�[�h���̎擾
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	if (pKeyboard->GetTrigger(DIK_P))
	{//P�L�[����
		AddScore(123);
	}
	
	//���݂̃X�R�A�ɉ������e�N�X�`�����W�̕ύX
	ChangeTexUV();
}

//================================================
//�`��
//================================================
void CScore::Draw()
{
}

//================================================
//�Z�b�g
//================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//================================================
//�X�R�A���Z
//================================================
void CScore::AddScore(const int nValue)
{
	m_nScore += nValue;
}

//================================================
//���݂̃X�R�A�̎擾
//================================================
int CScore::GetCurrentScore()
{
	return m_nScore;
}

//================================================
//���݂̃X�R�A�ɉ������e�N�X�`�����W�̕ύX
//================================================
void CScore::ChangeTexUV()
{
	int nSaveScore = m_nScore;	//���݂̃X�R�A���擾�A�ۑ�

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		//��̈ʂ��珇�ɒl�����Ă���
		int nNum = (nSaveScore % 10);

		if ((nNum < 0) || (nNum > 9))
		{//0�`9�̒l( 1�� )�ł͂Ȃ��ꍇ
			continue;
		}

		/* 0�`9�̒l( 1�� )�̏ꍇ */

		//�e�N�X�`�����W�̐ݒ�
		m_apNumber[i]->SetTexUV(CNumber::DIVIDE_TEX_U, nNum);

		nSaveScore /= 10;	//�v�Z�����ʂ��珜�O���Ă���
	}
}