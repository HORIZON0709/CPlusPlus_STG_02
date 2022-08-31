//================================================
//
//������H��b[enemy_boss.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "enemy_boss.h"
#include "application.h"
#include "renderer.h"
#include "game.h"

#include "camera.h"
#include "bullet_3D.h"
#include "score.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CEnemyBoss::START_POS_X = 0.0f;		//�����ʒu( X )
const float CEnemyBoss::START_POS_Y = 220.0f;	//�����ʒu( Y )

const float CEnemyBoss::ENEMY_SIZE = 270.0f;	//�T�C�Y
const float CEnemyBoss::CURVE_SIZE = 0.003f;	//�J�[�u�̑傫��

const float CEnemyBoss::MOVE_SPEED_X = 4.0f;	//�ړ��X�s�[�h( X )
const float CEnemyBoss::MOVE_SPEED_Y = 
{//�ړ��X�s�[�h( Y )
	CGame::GetCamera()->SCROLL_SPEED * CGame::GetCamera()->MOVE_SPEED
};

const float CEnemyBoss::SHOT_SPEED = -4.0f;	//�e�̃X�s�[�h

//================================================
//�R���X�g���N�^
//================================================
CEnemyBoss::CEnemyBoss():
	m_nTimerInterval(0)
{
	//�G�̎�ނ�ݒ�
	CEnemy3D::SetEnmType(CEnemy3D::ENM_TYPE::BOSS);
}

//================================================
//�f�X�g���N�^
//================================================
CEnemyBoss::~CEnemyBoss()
{
}

//================================================
//������
//================================================
HRESULT CEnemyBoss::Init()
{
	CEnemy3D::Init();	//�e�N���X

	//�T�C�Y��ݒ�
	D3DXVECTOR2 size = D3DXVECTOR2(ENEMY_SIZE, ENEMY_SIZE);
	CObject3D::SetSize(size);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::enemy000);

	return S_OK;
}

//================================================
//�I��
//================================================
void CEnemyBoss::Uninit()
{
	CEnemy3D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CEnemyBoss::Update()
{
	CEnemy3D::Update();	//�e�N���X

	//�ړ�
	Move();

	//�e�̔���
	Shot();
}

//================================================
//�`��
//================================================
void CEnemyBoss::Draw()
{
	CEnemy3D::Draw();	//�e�N���X
}

//================================================
//���S���̏���
//================================================
void CEnemyBoss::Death()
{
	//�X�R�A�����Z
	CGame::GetScore()->AddScore(NUM_SCORE);
}

//================================================
//�ړ�
//================================================
void CEnemyBoss::Move()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();		//�ʒu���擾
	D3DXVECTOR3 move = CObject3D::GetMove();	//�ړ��ʂ��擾

	//���Z
	m_fCurve += CURVE_SIZE;

	//sin�J�[�u
	move.x = cosf(D3DX_PI * m_fCurve) * MOVE_SPEED_X;

	//�J�����ɍ��킹��Y�����펞�ړ�
	move.y = MOVE_SPEED_Y;

	//�ړ��ʂ��ʒu�ɉ��Z
	pos += move;

	CObject3D::SetPos(pos);	//�ʒu��ݒ�
}

//================================================
//�e�̔���
//================================================
void CEnemyBoss::Shot()
{
	m_nTimerInterval++;	//�^�C�}�[��i�߂�

	if (m_nTimerInterval % SHOT_INTERVAL == 0)
	{//�^�C�}�[����莞�ԂɂȂ�����
		D3DXVECTOR3 posBullet = CObject3D::GetPos();					//�ʒu���擾
		D3DXVECTOR3 moveBullet = D3DXVECTOR3(0.0f, SHOT_SPEED, 0.0f);	//�e�̈ړ��ʂ�ݒ�

		CBullet3D::Create(/* �e�̐��� */
			posBullet,					//�ʒu
			moveBullet,					//�ړ���
			CObject::OBJ_TYPE::ENEMY);	//���L��
	}
}