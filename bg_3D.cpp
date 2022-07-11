//================================================
//
//������H��b[bg_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "bg_3D.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CBg3D::BG_WIDTH = CRenderer::SCREEN_WIDTH * 0.9f;	//����
const float CBg3D::BG_HEIGHT = CRenderer::SCREEN_HEIGHT * 0.9f;	//�c��

//================================================
//����
//================================================
CBg3D* CBg3D::Create()
{
	CBg3D* pBg3D = nullptr;	//�|�C���^

	if (pBg3D != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pBg3D = new CBg3D;	//�������̓��I�m��

	pBg3D->Init();	//������

	return pBg3D;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CBg3D::CBg3D()
{
	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::BG);
}

//================================================
//�f�X�g���N�^
//================================================
CBg3D::~CBg3D()
{
}

//================================================
//������
//================================================
HRESULT CBg3D::Init()
{
	CObject3D::Init();	//�e�N���X

	//�T�C�Y��ݒ�
	D3DXVECTOR2 size = D3DXVECTOR2(BG_WIDTH, BG_HEIGHT);
	CObject3D::SetSize(size);

	//�ʒu��ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.1f);
	CObject3D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::bg000);

	return S_OK;
}

//================================================
//�I��
//================================================
void CBg3D::Uninit()
{
	CObject3D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CBg3D::Update()
{
	CObject3D::Update();	//�e�N���X
}

//================================================
//�`��
//================================================
void CBg3D::Draw()
{
	CObject3D::Draw();	//�e�N���X
}