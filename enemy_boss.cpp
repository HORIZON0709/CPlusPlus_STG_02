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
#include "fade.h"

#include "camera.h"
#include "explosion_3D.h"
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

const float CEnemyBoss::SHOT_SPEED = 3.0f;	//�e�̃X�s�[�h

const int CEnemyBoss::SHOT_INTERVAL = 120;	//�e�̘A�����˂̊Ԋu
const int CEnemyBoss::NUM_SCORE = 100;		//�l���X�R�A��
const int CEnemyBoss::NUM_BULLETS = 8;		//�������ː�
const int CEnemyBoss::MAX_LIFE = 30;		//�̗͂̍ő�l

//================================================
//�R���X�g���N�^
//================================================
CEnemyBoss::CEnemyBoss():
	m_fCurve(0.0f),
	m_nTimerInterval(0),
	m_nLife(0),
	m_nCnt(0),
	m_state(STATE::NONE)
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

	//�����o�ϐ��̏�����
	m_fCurve = 0.0f;
	m_nTimerInterval = 0;
	m_nLife = MAX_LIFE;
	m_nCnt = 0;
	m_state = STATE::NORMAL;

	//�T�C�Y��ݒ�
	D3DXVECTOR2 size = D3DXVECTOR2(ENEMY_SIZE, ENEMY_SIZE);
	CObject3D::SetSize(size);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::enemy002);

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
	if (CApplication::GetFade()->GetState() == CFade::STATE::FADE_OUT)
	{//�Ó]��
		return;
	}

	CEnemy3D::Update();	//�e�N���X
	
	//�ړ�
	Move();

	//�e�̔���
	Shot();

	//��Ԗ��̏���
	State();
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
	//�����𐶐�
	CExplosion3D::Create(CObject3D::GetPos(), CTexture::TEXTURE::explosion001);

	//�X�R�A�����Z
	CGame::GetScore()->AddScore(NUM_SCORE);
}

//================================================
//�̗͂̌��Z
//================================================
void CEnemyBoss::SubLife(const int nDamage)
{
	//���Z
	m_nLife -= nDamage;

	//�_���[�W��Ԃɂ���
	m_state = STATE::DAMAGE;
}

//================================================
//�̗͂̎擾
//================================================
int CEnemyBoss::GetLife()
{
	return m_nLife;
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

	if (m_nTimerInterval % SHOT_INTERVAL != 0)
	{//�^�C�}�[����莞�Ԍo�߂��Ă��Ȃ��ꍇ
		return;
	}

	/* �^�C�}�[����莞�Ԍo�߂����ꍇ */

	D3DXVECTOR3 pos = CObject3D::GetPos();	//�ʒu���擾

	for (int i = 0; i < (NUM_BULLETS / 2); i++)
	{
		//�ړ��ʂ̐ݒ�
		float x = sinf(D3DX_PI * (1.0f / NUM_BULLETS) * i) * SHOT_SPEED;
		float y = cosf(D3DX_PI * (1.0f / NUM_BULLETS) * i) * SHOT_SPEED;

		/* �e�̐��� */

		//+����
		CBullet3D::Create(pos,						//�ʒu
						  D3DXVECTOR3(x, -y, 0.0f),	//�ړ���
						  CObject::OBJ_TYPE::ENEMY,	//���L��
						  CTexture::bullet005);		//�e�N�X�`��

		//-����
		CBullet3D::Create(pos,							//�ʒu
						  D3DXVECTOR3(-x, -y, 0.0f),	//�ړ���
						  CObject::OBJ_TYPE::ENEMY,		//���L��
						  CTexture::bullet005);			//�e�N�X�`��
	}
}

//================================================
//��Ԗ��̏���
//================================================
void CEnemyBoss::State()
{
	switch (m_state)
	{
	case STATE::DAMAGE: /* �_���[�W��� */
	{
		D3DXCOLOR colRed = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);		//��(�_���[�W���)
		D3DXCOLOR colNormal = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//��(���̏��)

		//�F��Ԃɂ���
		CObject3D::SetCol(colRed);

		m_nCnt++;	//�J�E���g�A�b�v

		if (m_nCnt % 20 != 0)
		{
			break;
		}

		/* ��萔�J�E���g������ */

		//�F�����ɖ߂�
		CObject3D::SetCol(colNormal);

		//�ʏ��Ԃɂ���
		m_state = STATE::NONE;
		break;
	}
	case STATE::NONE: /* ��L�ȊO */
	case STATE::NORMAL:
	case STATE::MAX:
	default:
		break;
	}
}