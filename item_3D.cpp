//================================================
//
//������H��b[item_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "item_3D.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CItem3D::ITEM_SIZE = 40.0f;	//�T�C�Y

//================================================
//����
//================================================
CItem3D* CItem3D::Create(const D3DXVECTOR3 &pos)
{
	CItem3D* pItem3D = nullptr;	//�|�C���^

	if (pItem3D != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pItem3D = new CItem3D;	//�������̓��I�m��

	pItem3D->Init();	//������

	pItem3D->SetPos(pos);	//�ʒu��ݒ�

	return pItem3D;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CItem3D::CItem3D()
{
	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::ITEM);
}

//================================================
//�f�X�g���N�^
//================================================
CItem3D::~CItem3D()
{
}

//================================================
//������
//================================================
HRESULT CItem3D::Init()
{
	CObject3D::Init();	//�e�N���X

	//�T�C�Y��ݒ�
	D3DXVECTOR2 size = D3DXVECTOR2(ITEM_SIZE, ITEM_SIZE);
	CObject3D::SetSize(size);

	//�F�̐ݒ�
	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	CObject3D::SetCol(col);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::item000);

	return S_OK;
}

//================================================
//�I��
//================================================
void CItem3D::Uninit()
{
	CObject3D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CItem3D::Update()
{
	CObject3D::Update();	//�e�N���X
}

//================================================
//�`��
//================================================
void CItem3D::Draw()
{
	CObject3D::Draw();	//�e�N���X
}