//================================================
//
//������H��b[bullet_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "bullet_3D.h"
#include "application.h"
#include "renderer.h"
#include "explosion_3D.h"

#include "item_3D.h"

#include "camera.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CBullet3D::BULLET_SIZE = 30.0f;	//�T�C�Y

//================================================
//����
//================================================
CBullet3D* CBullet3D::Create(const D3DXVECTOR3 &pos,
							 const D3DXVECTOR3 &move,
							 const CObject::OBJ_TYPE &haveType)
{
	CBullet3D* pBullet3D = nullptr;	//�|�C���^

	if (pBullet3D != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pBullet3D = new CBullet3D;	//�������̓��I�m��

	pBullet3D->Init();	//������

	pBullet3D->SetPos(pos);	//�ʒu��ݒ�

	pBullet3D->SetMove(move);	//�ړ��ʂ�ݒ�

	pBullet3D->SetHaveType(haveType);	//���L�҂�ݒ�

	return pBullet3D;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CBullet3D::CBullet3D():
	m_haveType(CObject::OBJ_TYPE::NONE)
{
	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::BULLET);
}

//================================================
//�f�X�g���N�^
//================================================
CBullet3D::~CBullet3D()
{
}

//================================================
//������
//================================================
HRESULT CBullet3D::Init()
{
	CObject3D::Init();	//�e�N���X

	//�T�C�Y��ݒ�
	D3DXVECTOR2 size = D3DXVECTOR2(BULLET_SIZE, BULLET_SIZE);
	CObject3D::SetSize(size);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::bullet001);

	return S_OK;
}

//================================================
//�I��
//================================================
void CBullet3D::Uninit()
{
	CObject3D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CBullet3D::Update()
{
	CObject3D::Update();	//�e�N���X

	D3DXVECTOR3 pos = CObject3D::GetPos();		//�ʒu�ݒ�p
	D3DXVECTOR3 move = CObject3D::GetMove();	//�ړ��ʐݒ�p

	pos += move;	//�ʒu���X�V

	CObject3D::SetPos(pos);	//�X�V�����ʒu��ݒ�

	IsCollision();	//�����蔻��

	float fLeft		= (pos.x - (BULLET_SIZE * 0.5f));	//���[
	float fRight	= (pos.x + (BULLET_SIZE * 0.5f));	//�E�[
	float fTop		= (pos.y + (BULLET_SIZE * 0.5f));	//��[
	float fBottom	= (pos.y - (BULLET_SIZE * 0.5f));	//���[

	//�J�������̎擾
	D3DXMATRIX mtxCamera = CApplication::GetCamera()->GetMatrixView();
	
	//�J�����̎��_�̈ʒu���擾
	D3DXVECTOR3 posV = CApplication::GetCamera()->GetPosV();

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxCamera, posV.x, posV.y, posV.z);

	//�ړ�������ݒ�
	float fRimitTop		= (mtxCamera._42 + (CRenderer::SCREEN_HEIGHT * 0.5f));	//��
	float fRimitBottom	= (mtxCamera._42 - (CRenderer::SCREEN_HEIGHT * 0.5f));	//��
	float fRimitLeft	= (mtxCamera._41 - (CRenderer::SCREEN_WIDTH * 0.5f));	//��
	float fRimitRight	= (mtxCamera._41 + (CRenderer::SCREEN_WIDTH * 0.5f));	//�E

	if ((fLeft < fRimitLeft) ||		//���[
		(fRight > fRimitRight) ||	//�E�[
		(fTop > fRimitTop) ||		//��[
		(fBottom < fRimitBottom))	//���[
	{//�w�肵���͈͂���o����
		//�����̐���
		CExplosion3D::Create(pos);

		Release();	//���
	}
}

//================================================
//�`��
//================================================
void CBullet3D::Draw()
{
	CObject3D::Draw();	//�e�N���X
}

//================================================
//�����蔻��
//================================================
void CBullet3D::IsCollision()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//�ʒu�ݒ�p

	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject* pObjectTarget = GetObjects(i);	//�Ώۂ̏��̎擾

		if (pObjectTarget == nullptr || pObjectTarget == this)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		CObject::OBJ_TYPE typeTarget = pObjectTarget->GetObjType();	//�^�C�v�̎擾

		if (!(((GetHaveType() == CObject::PLAYER) && (typeTarget == CObject::ENEMY)) || 
			((GetHaveType() == CObject::ENEMY) && (typeTarget == CObject::PLAYER))))
			/*
			�w�u���L�҂��v���C���[�@���@�Ώۂ��G�v
			��������
			�u���L�҂��G�@���@�Ώۂ��v���C���[�v�x
			�ł͂Ȃ�
			*/
		{
			continue;
		}

		/* ���g�̔���p */
		float fLeft		= (pos.x - (BULLET_SIZE * 0.5f));	//���[
		float fRight	= (pos.x + (BULLET_SIZE * 0.5f));	//�E�[
		float fTop		= (pos.y + (BULLET_SIZE * 0.5f));	//��[
		float fBottom	= (pos.y - (BULLET_SIZE * 0.5f));	//���[

		CObject3D* pObjTarget3D = (CObject3D*)pObjectTarget;	//CObject3D�^�ɃL���X�g

		D3DXVECTOR3 posTarget = pObjTarget3D->GetPos();		//�Ώۂ̈ʒu���擾
		D3DXVECTOR2 sizeTarget = pObjTarget3D->GetSize();	//�Ώۂ̃T�C�Y���擾

		/* �Ώۂ̔���p */
		float fLeftTarget	= (posTarget.x - (sizeTarget.x * 0.5f));	//���[
		float fRightTarget	= (posTarget.x + (sizeTarget.x * 0.5f));	//�E�[
		float fTopTarget	= (posTarget.y + (sizeTarget.y * 0.5f));	//��[
		float fBottomTarget = (posTarget.y - (sizeTarget.y * 0.5f));	//���[

		if (fLeft < fRightTarget
			&& fRight > fLeftTarget
			&& fTop > fBottomTarget
			&& fBottom < fTopTarget)
		{//�e���Ώۂ͈͓̔��ɗ����ꍇ
			CExplosion3D::Create(posTarget);	//�����̐���

			pObjTarget3D->Release();	//�Ώۂ̉��

			Release();	//���g�̉��
			break;
		}
	}
}

//================================================
//���L�҂�ݒ�
//================================================
void CBullet3D::SetHaveType(const CObject::OBJ_TYPE &haveType)
{
	m_haveType = haveType;
}

//================================================
//���L�҂��擾
//================================================
CObject::OBJ_TYPE CBullet3D::GetHaveType()
{
	return m_haveType;
}