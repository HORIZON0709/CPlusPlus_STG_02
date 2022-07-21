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

		m_apNumber[i]->Init();	//������

		//�ʒu�̐ݒ�
		D3DXVECTOR3 pos = D3DXVECTOR3(CNumber::POS_X, CNumber::POS_Y, 0.0f);
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
void CScore::SetScore(const int &nScore)
{
	m_nScore = nScore;
}

//================================================
//�X�R�A���Z
//================================================
void CScore::AddScore(const int &nValue)
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