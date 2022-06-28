//================================================
//
//������H��b[player.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "player.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CPlayer::PLAYER_SIZE = 100.0f;	//�T�C�Y
const float CPlayer::MOVE_SPEED = 10.0f;	//�ړ����x

//================================================
//����
//================================================
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = nullptr;	//�|�C���^

	if (pPlayer != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pPlayer = new CPlayer;	//�������̓��I�m��

	pPlayer->Init();	//������

	return pPlayer;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CPlayer::CPlayer()
{
	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::PLAYER);
}

//================================================
//�f�X�g���N�^
//================================================
CPlayer::~CPlayer()
{
}

//================================================
//������
//================================================
HRESULT CPlayer::Init()
{
	CObject2D::Init();	//�e�N���X

	//�T�C�Y��ݒ�
	CObject2D::SetSize(PLAYER_SIZE);

	//�ʒu��ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.5f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);
	CObject2D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_�S�S�����_8);

	return S_OK;
}

//================================================
//�I��
//================================================
void CPlayer::Uninit()
{
	CObject2D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CPlayer::Update()
{
	CObject2D::Update();	//�e�N���X

	CInput* pInput = CInput::GetKey();		//�L�[�{�[�h�����擾
	D3DXVECTOR3 pos = CObject2D::GetPos();	//�ʒu�����擾

	/* �ړ� */

	if (pInput->Press(CInput::STANDARD_KEY::RIGHT))
	{//�E
		pos.x += MOVE_SPEED;
	}
	else if (pInput->Press(CInput::STANDARD_KEY::LEFT))
	{//��
		pos.x -= MOVE_SPEED;
	}

	if (pInput->Press(CInput::STANDARD_KEY::UP))
	{//��
		pos.y -= MOVE_SPEED;
	}
	else if (pInput->Press(CInput::STANDARD_KEY::DOWN))
	{//��
		pos.y += MOVE_SPEED;
	}

	if (pInput->Trigger(CInput::STANDARD_KEY::SHOT))
	{//����
		CBullet* pBullet = CBullet::Create(pos);	//�e�̐���
	}

	CObject2D::SetPos(pos);	//�ʒu���X�V
}

//================================================
//�`��
//================================================
void CPlayer::Draw()
{
	CObject2D::Draw();	//�e�N���X
}