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

#include "application.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "game.h"
#include "fade.h"

#include "explosion_3D.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CPlayer3D::PLAYER_SIZE = 60.0f;	//�T�C�Y
const float CPlayer3D::MOVE_SPEED = 8.0f;	//�ړ����x
const float CPlayer3D::SHOT_SPEED = 12.0f;	//�e���˂̑���

const int CPlayer3D::SHOT_INTERVAL = 30;	//�e�̘A�����˂̊Ԋu

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
CPlayer3D::CPlayer3D():
	m_nTimerInterval(0),
	m_getItem(CItem3D::TYPE::NONE),
	m_bulletType(CBullet3D::TYPE::NONE)
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

	//�����o�ϐ��̏����ݒ�
	m_getItem = CItem3D::TYPE::NONE;		//�����擾���Ă��Ȃ�
	m_bulletType = CBullet3D::TYPE::NORMAL;	//�ʏ�e

	//�ʒu��ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CObject3D::SetPos(pos);

	//�T�C�Y��ݒ�
	D3DXVECTOR3 size = D3DXVECTOR3(PLAYER_SIZE, PLAYER_SIZE, 0.0f);
	CObject3D::SetSize(size);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::player000);

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
	if (CApplication::GetFade()->GetState() == CFade::STATE::FADE_OUT)
	{//�Ó]��
		return;
	}

	CObject3D::Update();	//�e�N���X

	Move();	//�ړ�

	Shot();	//����

	if(CObject3D::Collision(OBJ_TYPE::PLAYER, OBJ_TYPE::ENEMY))
	{//�G�ƐڐG�����ꍇ
		//�����̐���
		CExplosion3D::Create(
			CObject3D::GetPos(),
			CObject3D::GetSize(),
			CTexture::TEXTURE::explosion001);

		Release();	//���
	}

	if (m_getItem != CItem3D::TYPE::NONE)
	{//�����A�C�e�����擾�����ꍇ
		//�����A�C�e�����̏���
		HaveItem();
	}
}

//================================================
//�`��
//================================================
void CPlayer3D::Draw()
{
	CObject3D::Draw();	//�e�N���X
}

//================================================
//�����A�C�e���̃Z�b�g
//================================================
void CPlayer3D::SetItem(const CItem3D::TYPE &item)
{
	m_getItem = item;
}

//================================================
//�����A�C�e���̎擾
//================================================
CItem3D::TYPE CPlayer3D::GetItem()
{
	return m_getItem;
}

//================================================
//�ړ�
//================================================
void CPlayer3D::Move()
{
	//�L�[�{�[�h���̎擾
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	D3DXVECTOR3 pos = CObject3D::GetPos();		//�ʒu���擾
	D3DXVECTOR3 move = CObject3D::GetMove();	//�ړ��ʂ��擾

	if (pKeyboard->GetPress(DIK_D))
	{//�E
		/* �ړ������ɉ����Ĉړ��ʂ𑝉� */

		if (pKeyboard->GetPress(DIK_W))
		{//�E��
			move.x += sinf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//X������
			move.y -= cosf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//Y������
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//�E��
			move.x += sinf(+D3DX_PI * 0.25f) * MOVE_SPEED;	//X������
			move.y -= cosf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//Y������
		}
		else
		{//�E
			move.x += sinf(+D3DX_PI * 0.5f) * MOVE_SPEED;	//X������
		}
	}
	else if (pKeyboard->GetPress(DIK_A))
	{//��
		/* �ړ������ɉ����Ĉړ��ʂ𑝉� */

		if (pKeyboard->GetPress(DIK_W))
		{//����
			move.x += sinf(-D3DX_PI * 0.75f) * MOVE_SPEED;	//X������
			move.y -= cosf(+D3DX_PI * 0.75f) * MOVE_SPEED;	//Y������
		}
		else if (pKeyboard->GetPress(DIK_S))
		{//����
			move.x += sinf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//X������
			move.y -= cosf(-D3DX_PI * 0.25f) * MOVE_SPEED;	//Y������
		}
		else
		{//��
			move.x += sinf(-D3DX_PI * 0.5f) * MOVE_SPEED;	//X������
		}
	}
	else if (pKeyboard->GetPress(DIK_W))
	{//��
		move.y -= cosf(+D3DX_PI * 1.0f) * MOVE_SPEED;	//Y������
	}
	else if (pKeyboard->GetPress(DIK_S))
	{//��
		move.y -= cosf(-D3DX_PI * 0.0f) * MOVE_SPEED;	//Y������
	}

	pos += move;	//�ʒu�Ɉړ��ʂ����Z

	/* ��ʊO�ւ̈ړ��h�~ */

	float fSizeHalf = (PLAYER_SIZE * 0.5f);	//�T�C�Y�̔���

	float fLeft		= (pos.x - fSizeHalf);	//���[
	float fRight	= (pos.x + fSizeHalf);	//�E�[
	float fTop		= (pos.y + fSizeHalf);	//��[
	float fBottom	= (pos.y - fSizeHalf);	//���[

	//�J�������̎擾
	D3DXMATRIX mtxCamera = CGame::GetCamera()->GetMatrixView();
	
	//�J�����̎��_�̈ʒu���擾
	D3DXVECTOR3 posV = CGame::GetCamera()->GetPosV();

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxCamera, posV.x, posV.y, posV.z);

	//�ړ�������ݒ�
	float fRimitTop		= (mtxCamera._42 + (CRenderer::SCREEN_HEIGHT * 0.5f));	//��
	float fRimitBottom	= (mtxCamera._42 - (CRenderer::SCREEN_HEIGHT * 0.5f));	//��
	float fRimitLeft	= (mtxCamera._41 - (CRenderer::SCREEN_WIDTH * 0.5f));	//��
	float fRimitRight	= (mtxCamera._41 + (CRenderer::SCREEN_WIDTH * 0.5f));	//�E

	if (fTop > fRimitTop)
	{//�ړ�����(��)
		pos.y = fRimitTop - fSizeHalf;
	}
	else if (fBottom < fRimitBottom)
	{//�ړ�����(��)
		pos.y = fRimitBottom + fSizeHalf;
	}

	if (fLeft < fRimitLeft)
	{//�ړ�����(��)
		pos.x = fRimitLeft + fSizeHalf;
	}
	else if (fRight > fRimitRight)
	{//�ړ�����(�E)
		pos.x = fRimitRight - fSizeHalf;
	}

	CObject3D::SetPos(pos);	//�ʒu���X�V
}

//================================================
//����
//================================================
void CPlayer3D::Shot()
{
	CInput* pInput = CInput::GetKey();	//�L�[�{�[�h�����擾

	if (pInput->Trigger(CInput::STANDARD_KEY::SHOT))
	{//�P����
		CreateBulletByType();	//�^�C�v�ʂ̒e�̐���
	}
	else if (pInput->Press(CInput::STANDARD_KEY::SHOT))
	{//������(�������ςȂ�)
		m_nTimerInterval++;	//�^�C�}�[��i�߂�

		if (m_nTimerInterval % SHOT_INTERVAL != 0)
		{//�Ԋu�̃^�C�}�[���K��l�ɒB���Ă��Ȃ�
			return;
		}

		/* �Ԋu�^�C�}�[���K��l�ɒB������ */

		CreateBulletByType();	//�^�C�v�ʂ̒e�̐���
	}

	if (pInput->Release(CInput::STANDARD_KEY::SHOT))
	{//�L�[�𗣂�����
		m_nTimerInterval = 0;	//�^�C�}�[�����Z�b�g
	}
}

//================================================
//�^�C�v�ʂ̒e�̐���
//================================================
void CPlayer3D::CreateBulletByType()
{
	switch (m_bulletType)
	{/* �擾�����A�C�e�����̏��� */
	case CBullet3D::TYPE::NORMAL:	/* �ʏ�e */
		SetNormalBullet();	//�ʏ�e�̐ݒ�
		break;

	case CBullet3D::TYPE::DOUBLE:	/* ��A�e */
		SetDoubleBullet();	//��A�e�̐ݒ�
		break;

	case CBullet3D::TYPE::TRIPLE:	/* �O�����e�U�e */
		SetTripleBullet();	//�O�A�e�U�e�̐ݒ�
		break;

	default: /* ����ȊO */
		assert(false);
		break;
	}
}

//================================================
//�ʏ�e�̐ݒ�
//================================================
void CPlayer3D::SetNormalBullet()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//�ʒu�����擾

	D3DXVECTOR3 move;	//�ړ��ʐݒ�p

	//�ړ��ʐݒ�(+X����)
	move = D3DXVECTOR3(SHOT_SPEED, 0.0f, 0.0f);

	if (CGame::GetGamePart())
	{//�{�X�p�[�g�̏ꍇ
		//�ړ��ʐݒ�(+Y����)
		move = D3DXVECTOR3(0.0f, SHOT_SPEED, 0.0f);
	}

	//�e�̐���
	CBullet3D::Create(pos, move, CObject::OBJ_TYPE::PLAYER, CTexture::bullet003);
}

//================================================
//��A�e�̐ݒ�
//================================================
void CPlayer3D::SetDoubleBullet()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//�ʒu�����擾

	D3DXVECTOR3 move;	//�ړ��ʐݒ�p

	if (CGame::GetGamePart())
	{//�{�X�p�[�g�̏ꍇ
		//�e�̈ʒu�����E�ɏ������炷
		D3DXVECTOR3 posLeft = pos + D3DXVECTOR3(10.0f, 0.0f, 0.0f);		//��
		D3DXVECTOR3 posRight = pos + D3DXVECTOR3(-10.0f, 0.0f, 0.0f);	//�E

		//�ړ��ʐݒ�(+Y����)
		move = D3DXVECTOR3(0.0f, SHOT_SPEED, 0.0f);

		//�e�̐���
		CBullet3D::Create(posLeft, move, CObject::OBJ_TYPE::PLAYER, CTexture::bullet003);	//��
		CBullet3D::Create(posRight, move, CObject::OBJ_TYPE::PLAYER, CTexture::bullet003);	//�E
		return;
	}

	/* �ʏ�p�[�g�̏ꍇ */

	//�e�̈ʒu���㉺�ɏ������炷
	D3DXVECTOR3 posOver = pos + D3DXVECTOR3(0.0f, SHOT_SPEED, 0.0f);	//��
	D3DXVECTOR3 posUnder = pos + D3DXVECTOR3(0.0f, -SHOT_SPEED, 0.0f);	//��

	//�ړ��ʐݒ�(+X����)
	move = D3DXVECTOR3(SHOT_SPEED, 0.0f, 0.0f);

	//�e�̐���
	CBullet3D::Create(posOver, move, CObject::OBJ_TYPE::PLAYER, CTexture::bullet003);	//��
	CBullet3D::Create(posUnder, move, CObject::OBJ_TYPE::PLAYER, CTexture::bullet003);	//��
}

//================================================
//�O�A�g�U�e�̐ݒ�
//================================================
void CPlayer3D::SetTripleBullet()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//�ʒu�����擾

	D3DXVECTOR3 move;	//�ړ��ʐݒ�p
	
	/*************************** 1�e�� ***************************/

	if (CGame::GetGamePart())
	{//�{�X�p�[�g�̏ꍇ
		move = D3DXVECTOR3(-SHOT_SPEED, SHOT_SPEED, 0.0f);	//���΂�
	}

	move = D3DXVECTOR3(SHOT_SPEED, SHOT_SPEED, 0.0f);	//�΂ߏ�

	//�e�̐���
	CBullet3D::Create(pos, move, CObject::OBJ_TYPE::PLAYER, CTexture::bullet003);

	/*************************** 2�e�� ***************************/

	if (CGame::GetGamePart())
	{//�{�X�p�[�g�̏ꍇ
		move = D3DXVECTOR3(0.0f, SHOT_SPEED, 0.0f);	//+Y����
	}

	move = D3DXVECTOR3(SHOT_SPEED, 0.0f, 0.0f);	//����

	//�e�̐���
	CBullet3D::Create(pos, move, CObject::OBJ_TYPE::PLAYER, CTexture::bullet003);

	/*************************** 3�e�� ***************************/

	move = D3DXVECTOR3(SHOT_SPEED, -SHOT_SPEED, 0.0f);	//�΂߉�

	if (CGame::GetGamePart())
	{//�{�X�p�[�g�̏ꍇ
		move = D3DXVECTOR3(SHOT_SPEED, SHOT_SPEED, 0.0f);	//�E�΂�
	}

	//�e�̐���
	CBullet3D::Create(pos, move, CObject::OBJ_TYPE::PLAYER, CTexture::bullet003);
}

//================================================
//�����A�C�e�����̏���
//================================================
void CPlayer3D::HaveItem()
{
	switch (m_getItem)
	{//�^�C�v��ύX
	case CItem3D::TYPE::CHANGE_BUlLET_NORMAL: /* �ʏ�e */
		m_bulletType = CBullet3D::TYPE::NORMAL;
		break;

	case CItem3D::TYPE::CHANGE_BUlLET_DOUBLE: /* ��A�e */
		m_bulletType = CBullet3D::TYPE::DOUBLE;
		break;

	case CItem3D::TYPE::CHANGE_BUlLET_TRIPLE: /* �O�����e�U�e */
		m_bulletType = CBullet3D::TYPE::TRIPLE;
		break;

	default: /* ����ȊO */
		break;
	}
}