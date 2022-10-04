//================================================
//
//������H��b[enemy_straight.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "enemy_straight.h"
#include "application.h"
#include "renderer.h"
#include "camera.h"
#include "game.h"
#include "fade.h"

#include "score.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CEnemyStraight::START_POS_X = 1000.0f;	//�����ʒu( X )
const float CEnemyStraight::START_POS_Y = 100.0f;	//�����ʒu( Y )
const float CEnemyStraight::ENEMY_SIZE = 75.0f;		//�T�C�Y
const float CEnemyStraight::MOVE_SPEED_X = 2.0f;	//�ړ��X�s�[�h( X )

const int CEnemyStraight::NUM_SCORE = 10;	//�l���X�R�A��
const int CEnemyStraight::DIVIDE_TEX_U = 4;	//�e�N�X�`���̕�����( U���� )
const int CEnemyStraight::ANIM_SPEED = 10;	//�A�j���[�V�������x

//================================================
//�R���X�g���N�^
//================================================
CEnemyStraight::CEnemyStraight():
	m_bInside(false),
	m_nCntAnim(0),
	m_nPtnAnim(0)
{
	//�G�̎�ނ�ݒ�
	CEnemy3D::SetEnmType(CEnemy3D::ENM_TYPE::STRAIGHT);
}

//================================================
//�f�X�g���N�^
//================================================
CEnemyStraight::~CEnemyStraight()
{
}

//================================================
//������
//================================================
HRESULT CEnemyStraight::Init()
{
	CEnemy3D::Init();	//�e�N���X

	//�����o�ϐ��̏�����
	m_nCntAnim = 0;
	m_nPtnAnim = 0;

	//�ړ��ʂ�ݒ�
	D3DXVECTOR3 move = D3DXVECTOR3(-MOVE_SPEED_X, 0.0f, 0.0f);
	CObject3D::SetMove(move);

	//�T�C�Y��ݒ�
	D3DXVECTOR2 size = D3DXVECTOR2(ENEMY_SIZE, ENEMY_SIZE);
	CObject3D::SetSize(size);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::enemy003);

	//UV���W�̐ݒ�
	CObject3D::SetTexUV(DIVIDE_TEX_U, 1, 0);

	//�����ʒu����ʊO�ł���
	m_bInside = false;

	return S_OK;
}

//================================================
//�I��
//================================================
void CEnemyStraight::Uninit()
{
	CEnemy3D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CEnemyStraight::Update()
{
	if (CApplication::GetFade()->GetState() == CFade::STATE::FADE_OUT)
	{//�Ó]��
		return;
	}

	CEnemy3D::Update();	//�e�N���X

	//�ړ�
	Move();

	//�e�N�X�`���A�j���[�V����
	TexAnim();

	if (!m_bInside)
	{//��ʓ��ɓ����Ă��Ă��Ȃ��ꍇ
		OverRimitRight();	//��ʉE�[�𒴂������ǂ���
		return;
	}

	/* ��ʓ��ɓ����Ă����ꍇ */

	//��ʊO�ɏo����������
	ReleaseOffScreen();
}

//================================================
//�`��
//================================================
void CEnemyStraight::Draw()
{
	CEnemy3D::Draw();	//�e�N���X
}

//================================================
//���S���̏���
//================================================
void CEnemyStraight::Death()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//�ʒu���擾

	//�X�R�A�����Z
	CGame::GetScore()->AddScore(NUM_SCORE);
}

//================================================
//�ړ�
//================================================
void CEnemyStraight::Move()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();		//�ʒu���擾
	
	//�ړ��ʂ��ʒu�ɉ��Z
	pos += CObject3D::GetMove();

	CObject3D::SetPos(pos);	//�ʒu��ݒ�
}

//================================================
//�e�N�X�`���A�j���[�V����
//================================================
void CEnemyStraight::TexAnim()
{
	m_nCntAnim++;	//�J�E���g�A�b�v

	if (m_nCntAnim % ANIM_SPEED == 0)
	{//��萔�J�E���g������
		//�p�^�[���ԍ����X�V����
		m_nPtnAnim = (m_nPtnAnim + 1) % DIVIDE_TEX_U;

		//UV���W�̐ݒ�
		CObject3D::SetTexUV(DIVIDE_TEX_U, 1, m_nPtnAnim);
	}
}

//================================================
//��ʉE�[�𒴂������ǂ���
//================================================
void CEnemyStraight::OverRimitRight()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//�ʒu���擾

	float fSizeHalf = (ENEMY_SIZE * 0.5f);	//�T�C�Y�̔���
	float fLeft		= (pos.x - fSizeHalf);	//���[

	//�J�������̎擾
	D3DXMATRIX mtxCamera = CGame::GetCamera()->GetMatrixView();
	
	//�J�����̎��_�̈ʒu���擾
	D3DXVECTOR3 posV = CGame::GetCamera()->GetPosV();

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxCamera, posV.x, posV.y, posV.z);

	//�J�����̉�p�̉E�̌��E��ݒ�
	float fRimitRight	= (mtxCamera._41 + (CRenderer::SCREEN_WIDTH * 0.5f));	//�E

	//��ʉE�[�𒴂������ǂ���
	bool bOverRimitRight = (fLeft < fRimitRight);

	if (bOverRimitRight)
	{//��ʉE�[�𒴂����ꍇ
		m_bInside = true;	//��ʓ��ɂ���
	}
}

//================================================
//��ʊO�ɏo����������
//================================================
void CEnemyStraight::ReleaseOffScreen()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//�ʒu���擾

	float fSizeHalf = (ENEMY_SIZE * 0.5f);	//�T�C�Y�̔���
	float fLeft		= (pos.x - fSizeHalf);	//���[
	float fRight	= (pos.x + fSizeHalf);	//�E�[

	//�J�������̎擾
	D3DXMATRIX mtxCamera = CGame::GetCamera()->GetMatrixView();
	
	//�J�����̎��_�̈ʒu���擾
	D3DXVECTOR3 posV = CGame::GetCamera()->GetPosV();

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxCamera, posV.x, posV.y, posV.z);

	//�J�����̉�p�̍��E�̌��E��ݒ�
	float fRimitLeft	= (mtxCamera._41 - (CRenderer::SCREEN_WIDTH * 0.5f));	//��
	float fRimitRight	= (mtxCamera._41 + (CRenderer::SCREEN_WIDTH * 0.5f));	//�E

	//���E�Ƀt���[���A�E�g�������ǂ���
	bool bFrameOutOnLeft	= (fRight < fRimitLeft);	//������
	bool bFrameOutOnRight	= (fLeft > fRimitRight);	//�E����

	if (bFrameOutOnLeft || bFrameOutOnRight)
	{//��p���犮�S�ɏo����
		Release();	//���g�̉��
	}
}