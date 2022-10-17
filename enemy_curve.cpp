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
#include "camera.h"
#include "game.h"
#include "fade.h"

#include "bullet_3D.h"
#include "item_3D.h"
#include "score.h"
#include "explosion_3D.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CEnemyCurve::START_POS_X = 1000.0f;	//�����ʒu( X )
const float CEnemyCurve::START_POS_Y = 100.0f;	//�����ʒu( Y )
const float CEnemyCurve::ENEMY_SIZE = 75.0f;	//�T�C�Y
const float CEnemyCurve::CURVE_SIZE = 0.025f;	//�J�[�u�̃T�C�Y
const float CEnemyCurve::MOVE_SPEED_X = 1.0f;	//�ړ��X�s�[�h( X )
const float CEnemyCurve::MOVE_SPEED_Y = 5.0f;	//�ړ��X�s�[�h( Y )

const int CEnemyCurve::SHOT_INTERVAL = 90;	//�e�̘A�����˂̊Ԋu
const int CEnemyCurve::NUM_SCORE = 10;		//�l���X�R�A��

//================================================
//�R���X�g���N�^
//================================================
CEnemyCurve::CEnemyCurve():
	m_nTimerInterval(0),
	m_fCurve(0.0f),
	m_bInside(false)
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
	CEnemy3D::Init();	//�e�N���X

	//�ړ��ʂ�ݒ�
	D3DXVECTOR3 move = D3DXVECTOR3(-MOVE_SPEED_X, 0.0f, 0.0f);
	CObject3D::SetMove(move);

	//�T�C�Y��ݒ�
	D3DXVECTOR3 size = D3DXVECTOR3(ENEMY_SIZE, ENEMY_SIZE, 0.0f);
	CObject3D::SetSize(size);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::enemy000);

	//�����ʒu����ʊO�ł���
	m_bInside = false;

	return S_OK;
}

//================================================
//�I��
//================================================
void CEnemyCurve::Uninit()
{
	CEnemy3D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CEnemyCurve::Update()
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
void CEnemyCurve::Draw()
{
	CEnemy3D::Draw();	//�e�N���X
}

//================================================
//���S���̏���
//================================================
void CEnemyCurve::Death()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();	//�ʒu���擾

	//�A�C�e���̐���
	CItem3D::Create(pos, CItem3D::TYPE::CHANGE_BUlLET_DOUBLE);

	//�����𐶐�
	CExplosion3D::Create(
		CObject3D::GetPos(),
		CObject3D::GetSize(),
		CTexture::TEXTURE::explosion001);

	//�X�R�A�����Z
	CGame::GetScore()->AddScore(NUM_SCORE);
}

//================================================
//�ړ�
//================================================
void CEnemyCurve::Move()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();		//�ʒu���擾
	D3DXVECTOR3 move = CObject3D::GetMove();	//�ړ��ʂ��擾

	//���Z
	m_fCurve += CURVE_SIZE;

	//sin�J�[�u
	move.y = sinf(D3DX_PI * m_fCurve) * MOVE_SPEED_Y;

	//�ړ��ʂ��ʒu�ɉ��Z
	pos += move;

	CObject3D::SetPos(pos);	//�ʒu��ݒ�
}

//================================================
//�e�̔���
//================================================
void CEnemyCurve::Shot()
{
	m_nTimerInterval++;	//�^�C�}�[��i�߂�

	if (m_nTimerInterval % SHOT_INTERVAL == 0)
	{//�^�C�}�[����莞�ԂɂȂ�����
		D3DXVECTOR3 posBullet = CObject3D::GetPos();				//�ʒu���擾
		D3DXVECTOR3 moveBullet = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);	//�e�̈ړ��ʂ�ݒ�

		CBullet3D::Create(/* �e�̐��� */
			posBullet,					//�ʒu
			moveBullet,					//�ړ���
			CObject::OBJ_TYPE::ENEMY,	//���L��
			CTexture::bullet004);		//�e�N�X�`��
	}
}

//================================================
//��ʉE�[�𒴂������ǂ���
//================================================
void CEnemyCurve::OverRimitRight()
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
void CEnemyCurve::ReleaseOffScreen()
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