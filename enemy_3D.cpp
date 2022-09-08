//================================================
//
//������H��b[enemy_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "enemy_3D.h"
#include "enemy_straight.h"
#include "enemy_curve.h"
#include "enemy_boss.h"

#include <assert.h>

//================================================
//����
//================================================
CEnemy3D* CEnemy3D::Create(const ENM_TYPE &type, const D3DXVECTOR3 &pos)
{
	CEnemy3D* pEnemy3D = nullptr;	//�|�C���^

	if (pEnemy3D != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	switch (type)
	{
	case ENM_TYPE::STRAIGHT: /* ���� */
		pEnemy3D = new CEnemyStraight;	//�������̓��I
		break;

	case ENM_TYPE::CURVE: /* sin�J�[�u */
		pEnemy3D = new CEnemyCurve;	//�������̓��I�m��
		break;

	case ENM_TYPE::BOSS: /* �{�X */
		pEnemy3D = new CEnemyBoss;	//�������̓��I�m��
		break;

	default: /* ����ȊO */
		assert(false);
		break;
	}

	pEnemy3D->Init();		//������
	pEnemy3D->SetPos(pos);	//�ʒu��ݒ�

	return pEnemy3D;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CEnemy3D::CEnemy3D():
	m_type(ENM_TYPE::NONE)
{
	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::ENEMY);
}

//================================================
//�f�X�g���N�^
//================================================
CEnemy3D::~CEnemy3D()
{
}

//================================================
//������
//================================================
HRESULT CEnemy3D::Init()
{
	CObject3D::Init();	//�e�N���X

	return S_OK;
}

//================================================
//�I��
//================================================
void CEnemy3D::Uninit()
{
	CObject3D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CEnemy3D::Update()
{
	CObject3D::Update();	//�e�N���X
}

//================================================
//�`��
//================================================
void CEnemy3D::Draw()
{
	CObject3D::Draw();	//�e�N���X
}

//================================================
//�G�̎�ނ�ݒ�
//================================================
void CEnemy3D::SetEnmType(const ENM_TYPE &type)
{
	m_type = type;
}

//================================================
//�G�̎�ނ��擾
//================================================
CEnemy3D::ENM_TYPE CEnemy3D::GetEnmType()
{
	return m_type;
}