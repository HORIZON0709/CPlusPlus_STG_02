//================================================
//
//������H��b[bullet.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "bullet.h"
#include "renderer.h"
#include "explosion.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CBullet::BULLET_SIZE = 30.0f;	//�T�C�Y

//================================================
//����
//================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, CObject::OBJ_TYPE haveType)
{
	CBullet* pBullet = nullptr;	//�|�C���^

	if (pBullet != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pBullet = new CBullet;	//�������̓��I�m��

	pBullet->Init();	//������

	pBullet->SetPos(pos);	//�ʒu��ݒ�

	pBullet->SetHaveType(haveType);	//���L�҂�ݒ�

	return pBullet;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CBullet::CBullet():
	m_haveType(CObject::OBJ_TYPE::NONE)
{
	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::BULLET);
}

//================================================
//�f�X�g���N�^
//================================================
CBullet::~CBullet()
{
}

//================================================
//������
//================================================
HRESULT CBullet::Init()
{
	CObject2D::Init();	//�e�N���X

	//�T�C�Y��ݒ�
	D3DXVECTOR2 size = D3DXVECTOR2(BULLET_SIZE, BULLET_SIZE);
	CObject2D::SetSize(size);

	//�ړ��ʂ�ݒ�
	D3DXVECTOR3 move = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	CObject2D::SetMove(move);

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::bullet000);

	return S_OK;
}

//================================================
//�I��
//================================================
void CBullet::Uninit()
{
	CObject2D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CBullet::Update()
{
	CObject2D::Update();	//�e�N���X

	D3DXVECTOR3 pos = CObject2D::GetPos();		//�ʒu�ݒ�p
	D3DXVECTOR3 move = CObject2D::GetMove();	//�ړ��ʐݒ�p

	pos.x += move.x;
	//pos.y -= move.y;	//�ʒu���X�V

	CObject2D::SetPos(pos);	//�X�V�����ʒu��ݒ�

	Collision();	//�����蔻��

	if ((pos.x < 0) ||							//���[
		(pos.x > CRenderer::SCREEN_WIDTH) ||	//�E�[
		((pos.y - BULLET_SIZE * 0.5f) < 0) ||	//��[
		(pos.y > CRenderer::SCREEN_HEIGHT))		//���[
	{//�w�肵���͈͂���o����
		//�����̐���
		CExplosion::Create(pos);

		Release();	//���
	}
}

//================================================
//�`��
//================================================
void CBullet::Draw()
{
	CObject2D::Draw();	//�e�N���X
}

//================================================
//�����蔻��
//================================================
void CBullet::Collision()
{
	D3DXVECTOR3 pos = CObject2D::GetPos();	//�ʒu�ݒ�p

	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject* pObjectTarget = GetObjects(i);	//�Ώۂ̏��̎擾

		if (pObjectTarget == nullptr || pObjectTarget == this)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		CObject::OBJ_TYPE type = pObjectTarget->GetObjType();	//�^�C�v�̎擾

		if (!((GetHaveType() == CObject::PLAYER) && (type == CObject::ENEMY) || 
			(GetHaveType() == CObject::ENEMY) && (type == CObject::PLAYER)))
			/*
			�u���L�҂��v���C���[�@���@�Ώۂ��G�v�ł͂Ȃ�
			��������
			�u���L�҂��G�@���@�Ώۂ��v���C���[�v
			*/
		{
			continue;
		}

		/* ���g�̔���p */
		float fLeft		= (pos.x - (BULLET_SIZE * 0.5f));	//���[
		float fRight	= (pos.x + (BULLET_SIZE * 0.5f));	//�E�[
		float fTop		= (pos.y - (BULLET_SIZE * 0.5f));	//��[
		float fBottom	= (pos.y + (BULLET_SIZE * 0.5f));	//���[

		CObject2D* pObjTarget2D = (CObject2D*)pObjectTarget;	//CObject2D�^�ɃL���X�g

		D3DXVECTOR3 posTarget = pObjTarget2D->GetPos();		//�Ώۂ̈ʒu���擾
		D3DXVECTOR2 sizeTarget = pObjTarget2D->GetSize();	//�Ώۂ̃T�C�Y���擾

		/* �Ώۂ̔���p */
		float fLeftTarget	= (posTarget.x - (sizeTarget.x * 0.5f));	//���[
		float fRightTarget	= (posTarget.x + (sizeTarget.x * 0.5f));	//�E�[
		float fTopTarget	= (posTarget.y - (sizeTarget.y * 0.5f));	//��[
		float fBottomTarget = (posTarget.y + (sizeTarget.y * 0.5f));	//���[

		if (fLeft <= fRightTarget
			&& fRight >= fLeftTarget
			&& fTop <= fBottomTarget
			&& fBottom >= fTopTarget)
		{//�e���Ώۂ͈͓̔��ɗ����ꍇ
			CExplosion::Create(posTarget);	//�����̐���

			pObjTarget2D->Release();	//�Ώۂ̉��

			Release();	//���g�̉��
			break;
		}
	}
}

//================================================
//���L�҂�ݒ�
//================================================
void CBullet::SetHaveType(CObject::OBJ_TYPE haveType)
{
	m_haveType = haveType;
}

//================================================
//���L�҂��擾
//================================================
CObject::OBJ_TYPE CBullet::GetHaveType()
{
	return m_haveType;
}