//================================================
//
//������H��b[fade.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "fade.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CFade::FADE_WIDTH = CRenderer::SCREEN_WIDTH;	//����
const float CFade::FADE_HEIGHT = CRenderer::SCREEN_HEIGHT;	//�c��

//================================================
//����
//================================================
CFade* CFade::Create()
{
	CFade* pFade = nullptr;	//�|�C���^

	if (pFade != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pFade = new CFade;	//�������̓��I�m��

	pFade->Init();	//������

	return pFade;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CFade::CFade()
{
	//�^�C�v�̐ݒ�
	//CObject::SetObjType(CObject::OBJ_TYPE::FADE);
}

//================================================
//�f�X�g���N�^
//================================================
CFade::~CFade()
{
}

//================================================
//������
//================================================
HRESULT CFade::Init()
{
	if (m_pPolygon != nullptr)
	{
		m_pPolygon = nullptr;
	}

	m_pPolygon = CObject2D::Create();

	//�T�C�Y��ݒ�
	D3DXVECTOR2 size = D3DXVECTOR2(FADE_WIDTH, FADE_HEIGHT);
	m_pPolygon->SetSize(size);

	//m_pPolygon->SetCol();

	return S_OK;
}

//================================================
//�I��
//================================================
void CFade::Uninit()
{
	//CObject2D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CFade::Update()
{
	//CObject3D::Update();	//�e�N���X
}

//================================================
//�`��
//================================================
void CFade::Draw()
{
	//CObject3D::Draw();	//�e�N���X
}