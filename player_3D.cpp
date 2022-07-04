//================================================
//
//������H��b[player_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "player_3D.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CPlayer3D::PLAYER_SIZE = 200.0f;	//�T�C�Y
const float CPlayer3D::MOVE_SPEED = 13.0f;		//�ړ����x

//================================================
//����
//================================================
CPlayer3D* CPlayer3D::Create()
{
	CPlayer3D* pPlayer3D = nullptr;	//�|�C���^

	if (pPlayer3D != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pPlayer3D = new CPlayer3D;	//�������̓��I�m��

	pPlayer3D->Init();	//������

	return pPlayer3D;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CPlayer3D::CPlayer3D()/*:m_nTimerInterval(0)*/
{
	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::PLAYER);
}

//================================================
//�f�X�g���N�^
//================================================
CPlayer3D::~CPlayer3D()
{
}

//================================================
//������
//================================================
HRESULT CPlayer3D::Init()
{
	CObject3D::Init();	//�e�N���X

	//�T�C�Y��ݒ�
	CObject3D::SetSize(PLAYER_SIZE);

	//�ʒu��ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CObject3D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::TEXTURE_�S�S�����_8);

	return S_OK;
}

//================================================
//�I��
//================================================
void CPlayer3D::Uninit()
{
	CObject3D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CPlayer3D::Update()
{
	CObject3D::Update();	//�e�N���X

	//Move();	//�ړ�

	//Shot();	//����
}

//================================================
//�`��
//================================================
void CPlayer3D::Draw()
{
	CObject3D::Draw();	//�e�N���X
}

//================================================
//�ړ�
//================================================
void CPlayer3D::Move()
{
	CInput* pInput = CInput::GetKey();	//�L�[�{�[�h�����擾

	D3DXVECTOR3 pos = CObject3D::GetPos();		//�ʒu���擾
	D3DXVECTOR3 move = CObject3D::GetMove();	//�ړ��ʂ��擾

	if (pInput->Press(CInput::STANDARD_KEY::RIGHT))
	{//�E
		/* �ړ������ɉ����Ĉړ��ʂ𑝉� */

		if (pInput->Press(CInput::STANDARD_KEY::UP))
		{//�E��
			move.x += sinf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//X������
			move.y += cosf(-D3DX_PI * 0.75f) * MOVE_SPEED;	//Y������
		}
		else if (pInput->Press(CInput::STANDARD_KEY::DOWN))
		{//�E��
			move.x += sinf(+D3DX_PI * 0.25f) * MOVE_SPEED;	//X������
			move.y += cosf(+D3DX_PI * 0.25f) * MOVE_SPEED;	//Y������
		}
		else
		{//�E
			move.x += sinf(+D3DX_PI * 0.5f) * MOVE_SPEED;	//X������
		}
	}
	else if (pInput->Press(CInput::STANDARD_KEY::LEFT))
	{//��
		/* �ړ������ɉ����Ĉړ��ʂ𑝉� */

		if (pInput->Press(CInput::STANDARD_KEY::UP))
		{//����
			move.x += sinf(-D3DX_PI * 0.75f) * MOVE_SPEED;	//X������
			move.y += cosf(-D3DX_PI * 0.75f) * MOVE_SPEED;	//Y������
		}
		else if (pInput->Press(CInput::STANDARD_KEY::DOWN))
		{//����
			move.x += sinf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//X������
			move.y += cosf(+D3DX_PI * 0.25f) * MOVE_SPEED;	//Y������
		}
		else
		{//��
			move.x += sinf(-D3DX_PI * 0.5f) * MOVE_SPEED;	//X������
		}
	}
	else if (pInput->Press(CInput::STANDARD_KEY::UP))
	{//��
		move.y += cosf(-D3DX_PI * 1.0f) * MOVE_SPEED;	//Y������
	}
	else if (pInput->Press(CInput::STANDARD_KEY::DOWN))
	{//��
		move.y += cosf(+D3DX_PI * 0.0f) * MOVE_SPEED;	//Y������
	}

	pos += move;	//�ʒu�Ɉړ��ʂ����Z

	/* ��ʊO�ւ̈ړ��h�~ */

	float fSizeHalf = (PLAYER_SIZE * 0.5f);	//�T�C�Y�̔���

	float fLeft		= (pos.x - fSizeHalf);	//���[
	float fRight	= (pos.x + fSizeHalf);	//�E�[
	float fTop		= (pos.y - fSizeHalf);	//��[
	float fBottom	= (pos.y + fSizeHalf);	//���[

	if (fTop <= 0.0f)
	{//�ړ����(��)
		pos.y = 0.0f + fSizeHalf;
	}

	if (fBottom >= CRenderer::SCREEN_HEIGHT)
	{//�ړ����(��)
		pos.y = CRenderer::SCREEN_HEIGHT - fSizeHalf;
	}

	if (fLeft <= 0.0f)
	{//�ړ����(��)
		pos.x = 0.0f + fSizeHalf;
	}

	if (fRight >= CRenderer::SCREEN_WIDTH)
	{//�ړ����(�E)
		pos.x = CRenderer::SCREEN_WIDTH - fSizeHalf;
	}

	CObject3D::SetPos(pos);	//�ʒu���X�V
}

//================================================
//����
//================================================
//void CPlayer3D::Shot()
//{
//	CInput* pInput = CInput::GetKey();	//�L�[�{�[�h�����擾
//
//	D3DXVECTOR3 pos = CObject2D::GetPos();	//�ʒu�����擾
//
//	if (pInput->Trigger(CInput::STANDARD_KEY::SHOT))
//	{//�P����
//		CBullet::Create(pos, CObject::OBJ_TYPE::PLAYER);	//�e�̐���
//	}
//	else if (pInput->Press(CInput::STANDARD_KEY::SHOT))
//	{//������(�������ςȂ�)
//		m_nTimerInterval++;	//�^�C�}�[��i�߂�
//
//		if (m_nTimerInterval % SHOT_INTERVAL != 0)
//		{//�Ԋu�̃^�C�}�[���K��l�ɒB���Ă��Ȃ�
//			return;
//		}
//
//		/* �Ԋu�^�C�}�[���K��l�ɒB������ */
//
//		CBullet::Create(pos,CObject::OBJ_TYPE::PLAYER);	//�e�̐���
//	}
//
//	if (pInput->Release(CInput::STANDARD_KEY::SHOT))
//	{//�L�[�𗣂�����
//		m_nTimerInterval = 0;	//�^�C�}�[�����Z�b�g
//	}
//}