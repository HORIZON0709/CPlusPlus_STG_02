//================================================
//
//������H��b[title.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "title.h"

#include "input.h"
#include "object2D.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CTitle::START_POS_X = 0.0f;		//�����ʒu( X )
const float CTitle::START_POS_Y = 150.0f;	//�����ʒu( Y )
const float CTitle::LOGO_WIDTH = 300.0f;	//���S�̕�
const float CTitle::LOGO_HEIGHT = 150.0f;	//���S�̍���

//***************************
//�ÓI�����o�ϐ�
//***************************
CObject2D* CTitle::m_pLogo = nullptr;	//�^�C�g�����S

//================================================
//�R���X�g���N�^
//================================================
CTitle::CTitle()
{
}

//================================================
//�f�X�g���N�^
//================================================
CTitle::~CTitle()
{
}

//================================================
//������
//================================================
HRESULT CTitle::Init()
{
	//����
	m_pLogo = CObject2D::Create();

	//�ʒu��ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 150.0f, 0.0f);
	m_pLogo->SetPos(pos);

	//�T�C�Y��ݒ�
	D3DXVECTOR2 size = D3DXVECTOR2(LOGO_WIDTH, LOGO_HEIGHT);
	m_pLogo->SetSize(size);

	return S_OK;
}

//================================================
//�I��
//================================================
void CTitle::Uninit()
{

}

//================================================
//�X�V
//================================================
void CTitle::Update()
{
	CInput* pInput = CInput::GetKey();	//�L�[�{�[�h�����擾

	if (pInput->Trigger(CInput::STANDARD_KEY::DECISION))
	{//����L�\
		SetMode(MODE::GAME);	//���[�h�̐ݒ�
	}
}

//================================================
//�`��
//================================================
void CTitle::Draw()
{
}