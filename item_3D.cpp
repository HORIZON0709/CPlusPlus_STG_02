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
#include "game.h"
#include "player_3D.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const int CItem3D::MAX_ITEM = 16;	//�ő吔

const float CItem3D::ITEM_SIZE = 40.0f;	//�T�C�Y

//================================================
//����
//================================================
CItem3D* CItem3D::Create(const D3DXVECTOR3 &pos, const CItem3D::TYPE type)
{
	CItem3D* pItem3D = nullptr;	//�|�C���^

	if (pItem3D != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pItem3D = new CItem3D;	//�������̓��I�m��

	pItem3D->Init();		//������
	pItem3D->SetPos(pos);	//�ʒu��ݒ�
	pItem3D->m_type = type;	//�^�C�v��ݒ�
	
	pItem3D->SetTexForEachItem();	//�A�C�e�����̃e�N�X�`���̐ݒ�

	return pItem3D;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CItem3D::CItem3D():
	m_type(CItem3D::TYPE::NONE)
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

	//�����o�ϐ��̏����ݒ�
	m_type = CItem3D::TYPE::NONE;

	//�T�C�Y��ݒ�
	D3DXVECTOR2 size = D3DXVECTOR2(ITEM_SIZE, ITEM_SIZE);
	CObject3D::SetSize(size);

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

	if (CObject3D::Collision(OBJ_TYPE::ITEM, OBJ_TYPE::PLAYER))
	{//�v���C���[�Ɠ���������
		CPlayer3D* pPlayer = CGame::GetPlayer3D();	//�v���C���[���̎擾

		//�v���C���[�ɁA���������A�C�e���̃^�C�v�𑗂�
		pPlayer->SetItem(m_type);

		Release();	//���g�̉��
	}
}

//================================================
//�`��
//================================================
void CItem3D::Draw()
{
	CObject3D::Draw();	//�e�N���X
}

//================================================
//�A�C�e�����̃e�N�X�`���̐ݒ�
//================================================
void CItem3D::SetTexForEachItem()
{
	switch (m_type)
	{
	case CHANGE_BUlLET_NORMAL: /* �ʏ�e�ɕύX */
		CObject3D::SetTexture(CTexture::item001);	// �e�N�X�`���̐ݒ�
		break;

	case CHANGE_BUlLET_DOUBLE: /* ��A�e�ɕύX */
		CObject3D::SetTexture(CTexture::item002);	// �e�N�X�`���̐ݒ�
		break;

	case CHANGE_BUlLET_TRIPLE: /* �O�A�e�U�e�ɕύX */
		CObject3D::SetTexture(CTexture::item003);	// �e�N�X�`���̐ݒ�
		break;

	default:
		break;
	}
}