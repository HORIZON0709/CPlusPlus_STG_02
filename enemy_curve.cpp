//================================================
//
//������H��b[enemy_curve.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "enemy_curve.h"
#include "application.h"
#include "renderer.h"
#include "bullet_3D.h"
#include "item_3D.h"
#include "score.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CEnemyCurve::START_POS_X = 500.0f;	//�����ʒu( X )
const float CEnemyCurve::START_POS_Y = 0.0f;	//�����ʒu( Y )
const float CEnemyCurve::ENEMY_SIZE = 90.0f;	//�T�C�Y
const float CEnemyCurve::CURVE_SIZE = 0.1f;		//�J�[�u�̃T�C�Y
const float CEnemyCurve::MOVE_SPEED_X = 1.0f;	//�ړ��X�s�[�h( X )
const float CEnemyCurve::MOVE_SPEED_Y = 5.0f;	//�ړ��X�s�[�h( Y )

//================================================
//����
//================================================
CEnemyCurve* CEnemyCurve::Create()
{
	CEnemyCurve* pEnemyCurve = nullptr;	//�|�C���^

	if (pEnemyCurve != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pEnemyCurve = new CEnemyCurve;	//�������̓��I�m��

	pEnemyCurve->Init();	//������

	return pEnemyCurve;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CEnemyCurve::CEnemyCurve():
	m_nTimerInterval(0),
	m_fCurve(0.0f)
{
	//�G�̎�ނ�ݒ�
	CEnemy3D::SetEnmType(CEnemy3D::ENM_TYPE::CURVE);
}

//================================================
//�f�X�g���N�^
//================================================
CEnemyCurve::~CEnemyCurve()
{
}

//================================================
//������
//================================================
HRESULT CEnemyCurve::Init()
{
	CObject3D::Init();	//�e�N���X

	//�ʒu��ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3(START_POS_X, START_POS_Y, 0.0f);
	CObject3D::SetPos(pos);

	//�ړ��ʂ�ݒ�
	D3DXVECTOR3 move = D3DXVECTOR3(-MOVE_SPEED_X, 0.0f, 0.0f);
	CObject3D::SetMove(move);

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
void CEnemyCurve::Uninit()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//�ʒu���擾

	//�A�C�e���̐���
	CItem3D::Create(pos, CItem3D::TYPE::CHANGE_BUlLET_DOUBLE);

	//�X�R�A�����Z
	CApplication::GetScore()->AddScore(NUM_SCORE);

	CObject3D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CEnemyCurve::Update()
{
	CObject3D::Update();	//�e�N���X

	D3DXVECTOR3 pos = CObject3D::GetPos();		//�ʒu���擾
	D3DXVECTOR3 move = CObject3D::GetMove();	//�ړ��ʂ��擾

	//���Z
	m_fCurve += CURVE_SIZE;

	//sin�J�[�u
	move.y = sinf(D3DX_PI * m_fCurve) * MOVE_SPEED_Y;

	//�ړ��ʂ��ʒu�ɉ��Z
	pos += move;

	CObject3D::SetPos(pos);	//�ʒu��ݒ�

	m_nTimerInterval++;	//�^�C�}�[��i�߂�

	if (m_nTimerInterval % SHOT_INTERVAL == 0)
	{//�^�C�}�[����莞�ԂɂȂ�����
		D3DXVECTOR3 posBullet = CObject3D::GetPos();				//�ʒu���擾
		D3DXVECTOR3 moveBullet = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);	//�e�̈ړ��ʂ�ݒ�

		CBullet3D::Create(/* �e�̐��� */
			posBullet,					//�ʒu
			moveBullet,					//�ړ���
			CObject::OBJ_TYPE::ENEMY);	//���L��
	}
}

//================================================
//�`��
//================================================
void CEnemyCurve::Draw()
{
	CObject3D::Draw();	//�e�N���X
}