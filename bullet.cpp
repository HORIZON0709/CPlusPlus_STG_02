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
const float CBullet::BULLET_SIZE = 50.0f;	//�T�C�Y

//================================================
//����
//================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos)
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

	return pBullet;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CBullet::CBullet():
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
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
	CObject2D::SetSize(BULLET_SIZE);

	//�ړ��ʂ�ݒ�
	m_move = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_circle_sakura2);

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

	D3DXVECTOR3 pos = CObject2D::GetPos();	//�ʒu�ݒ�p

	pos.y -= m_move.y;	//�ʒu���X�V

	CObject2D::SetPos(pos);	//�X�V�����ʒu��ݒ�

	Collision();	//�����蔻��

	if ((pos.x < 0) ||							//���[
		(pos.x > CRenderer::SCREEN_WIDTH) ||	//�E�[
		((pos.y - BULLET_SIZE * 0.5f) < 0) ||	//��[
		(pos.y > CRenderer::SCREEN_HEIGHT))		//���[
	{//�w�肵���͈͂���o����
		//�����̐���
		CExplosion* pExplosion = CExplosion::Create(pos);

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
		CObject* pObject = GetObjects(i);	//�I�u�W�F�N�g���̎擾

		if (pObject == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		CObject::OBJ_TYPE type = pObject->GetObjType();	//�^�C�v�̎擾

		if (type != CObject::OBJ_TYPE::ENEMY)
		{//�u �^�C�v�F�G �v�ł͂Ȃ��ꍇ
			continue;
		}

		/* �u �^�C�v�F�G �v�̏ꍇ */

		/* ���g�̔���p */
		float fLeft		= (pos.x - (BULLET_SIZE * 0.5f));	//���[
		float fRight	= (pos.x + (BULLET_SIZE * 0.5f));	//�E�[
		float fTop		= (pos.y - (BULLET_SIZE * 0.5f));	//��[
		float fBottom	= (pos.y + (BULLET_SIZE * 0.5f));	//���[

		D3DXVECTOR3 posTarget = pObject->GetPos();	//�Ώۂ̈ʒu���擾
		float fSizeTarget = pObject->GetSize();		//�Ώۂ̃T�C�Y���擾

		/* �Ώۂ̔���p */
		float fLeftTarget	= (posTarget.x - (fSizeTarget * 0.5f));	//���[
		float fRightTarget	= (posTarget.x + (fSizeTarget * 0.5f));	//�E�[
		float fTopTarget	= (posTarget.y - (fSizeTarget * 0.5f));	//��[
		float fBottomTarget	= (posTarget.y + (fSizeTarget * 0.5f));	//���[

		if (fLeft <= fRightTarget
			&& fRight >= fLeftTarget
			&& fTop <= fBottomTarget
			&& fBottom >= fTopTarget)
		{//�e���Ώۂ͈͓̔��ɗ����ꍇ
			//�����̐���
			CExplosion* pExplosion = CExplosion::Create(posTarget);
			
			pObject->Release();	//�Ώۂ̉��
			break;
		}
	}
}