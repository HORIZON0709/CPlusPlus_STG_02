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
#include "renderer.h"
#include "explosion_3D.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CBullet3D::BULLET_SIZE = 30.0f;	//�T�C�Y

//================================================
//����
//================================================
CBullet3D* CBullet3D::Create(D3DXVECTOR3 pos, CObject::OBJ_TYPE haveType)
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
	CObject3D::SetSize(BULLET_SIZE);

	//�ړ��ʂ�ݒ�
	D3DXVECTOR3 move = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	CObject3D::SetMove(move);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::TEXTURE_circle_sakura2);

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

	pos.x += move.x;
	//pos.y -= move.y;	//�ʒu���X�V

	CObject3D::SetPos(pos);	//�X�V�����ʒu��ݒ�

	Collision();	//�����蔻��

	float fLeft		= (pos.x - (BULLET_SIZE * 0.5f));	//���[
	float fRight	= (pos.x + (BULLET_SIZE * 0.5f));	//�E�[
	float fTop		= (pos.y + (BULLET_SIZE * 0.5f));	//��[
	float fBottom	= (pos.y - (BULLET_SIZE * 0.5f));	//���[]

	float fRimitHeight = (CRenderer::SCREEN_HEIGHT * 0.5f);	//����(�㉺)
	float fRimitWidth = (CRenderer::SCREEN_WIDTH * 0.25f);		//����(���E)

	if ((fLeft < -fRimitWidth) ||	//���[
		(fRight > fRimitWidth) ||	//�E�[
		(fTop > fRimitHeight) ||	//��[
		(fBottom < -fRimitHeight))	//���[
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
void CBullet3D::Collision()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//�ʒu�ݒ�p

	for (int i = 0; i < MAX_OBJECT; i++)
	{
		CObject* pObject = GetObjects(i);	//�I�u�W�F�N�g���̎擾

		if (pObject == nullptr || pObject == this)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		CObject::OBJ_TYPE type = pObject->GetObjType();	//�^�C�v�̎擾

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
		float fTop		= (pos.y + (BULLET_SIZE * 0.5f));	//��[
		float fBottom	= (pos.y - (BULLET_SIZE * 0.5f));	//���[

		D3DXVECTOR3 posTarget = pObject->GetPos();	//�Ώۂ̈ʒu���擾
		float fSizeTarget = pObject->GetSize();		//�Ώۂ̃T�C�Y���擾

		/* �Ώۂ̔���p */
		float fLeftTarget	= (posTarget.x - (fSizeTarget * 0.5f));	//���[
		float fRightTarget	= (posTarget.x + (fSizeTarget * 0.5f));	//�E�[
		float fTopTarget	= (posTarget.y + (fSizeTarget * 0.5f));	//��[
		float fBottomTarget = (posTarget.y - (fSizeTarget * 0.5f));	//���[

		if (fLeft <= fRightTarget
			&& fRight >= fLeftTarget
			&& fTop >= fBottomTarget
			&& fBottom <= fTopTarget)
		{//�e���Ώۂ͈͓̔��ɗ����ꍇ
			//�����̐���
			CExplosion3D::Create(posTarget);

			pObject->Release();	//�Ώۂ̉��

			Release();	//���g�̉��
			break;
		}
	}
}

//================================================
//���L�҂�ݒ�
//================================================
void CBullet3D::SetHaveType(CObject::OBJ_TYPE haveType)
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