//================================================
//
//������H��b[game.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "game.h"
#include "object2D.h"
#include "object3D.h"

#include "camera.h"
#include "score.h"
#include "player_3D.h"
#include "enemy_curve.h"
#include "enemy_boss.h"
#include "bg_3D.h"

#include <assert.h>

//***************************
//�ÓI�����o�ϐ�
//***************************
CCamera* CGame::m_pCamera = nullptr;					//�J����
CScore* CGame::m_pScore = nullptr;						//�X�R�A
CPlayer3D* CGame::m_pPlayer3D = nullptr;				//�v���C���[(3D)
CEnemy3D* CGame::m_apEnemy3D[CEnemy3D::MAX_ENEMY] = {};	//�G(3D)
CBg3D* CGame::m_pBg3D = nullptr;						//�w�i(3D)
bool CGame::m_bGamePart = false;						//�Q�[���p�[�g

//================================================
//�J���������擾
//================================================
CCamera* CGame::GetCamera()
{
	return m_pCamera;
}

//================================================
//�X�R�A�����擾
//================================================
CScore* CGame::GetScore()
{
	return m_pScore;
}

//================================================
//�v���C���[(3D)�����擾
//================================================
CPlayer3D* CGame::GetPlayer3D()
{
	return m_pPlayer3D;
}

//================================================
//�G(3D)�����擾
//================================================
CEnemy3D* CGame::GetEnemy3D(const int nIdx)
{
	return m_apEnemy3D[nIdx];
}

//================================================
//�w�i(3D)�����擾
//================================================
CBg3D* CGame::GetBg3D()
{
	return m_pBg3D;
}

//================================================
//�R���X�g���N�^
//================================================
CGame::CGame() : CMode(MODE::GAME)
{
}

//================================================
//�f�X�g���N�^
//================================================
CGame::~CGame()
{
}

//================================================
//������
//================================================
HRESULT CGame::Init()
{
	m_bGamePart = false;	//�ʏ�p�[�g

	/* ���� */

	if (m_pCamera == nullptr)
	{//NULL�`�F�b�N
		m_pCamera = new CCamera;	//�J����
		m_pCamera->Init();			//������
	}

	m_pScore = CScore::Create();	//�X�R�A

	m_pBg3D = CBg3D::Create();	//�w�i(3D)

	m_pPlayer3D = CPlayer3D::Create();	//�v���C���[(3D)

	for (int i = 0; i < CEnemy3D::NUM_ENEMY_CURVE; i++)
	{//�J�[�u�G
		if (m_apEnemy3D[i] != nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�̏ꍇ */

		//�ʒu��ݒ�
		D3DXVECTOR3 pos = D3DXVECTOR3(CEnemyCurve::START_POS_X + (200.0f * i),
										(100.0f * i),
										0.0f);

		//����
		m_apEnemy3D[i] = CEnemy3D::Create(CEnemy3D::ENM_TYPE::CURVE, pos);
	}

	return S_OK;
}

//================================================
//�I��
//================================================
void CGame::Uninit()
{
	/* �I�u�W�F�N�g */

	CObject2D::ReleaseAll();	//�S�Ẳ��(2D)
	CObject3D::ReleaseAll();	//�S�Ẳ��(3D)

	/* �J���� */

	if (m_pCamera != nullptr)
	{//NULL�`�F�b�N
		m_pCamera->Uninit();	//�I��
		delete m_pCamera;		//�������̉��
		m_pCamera = nullptr;	//nullptr�ɂ���
	}

	/* �X�R�A */

	if (m_pScore != nullptr)
	{//NULL�`�F�b�N
		m_pScore = nullptr;	//nullptr�ɂ���
	}

	/* �w�i(3D) */

	if (m_pScore != nullptr)
	{//NULL�`�F�b�N
		m_pBg3D = nullptr;	//nullptr�ɂ���
	}

	/* �v���C���[(3D) */
	if (m_pScore != nullptr)
	{//NULL�`�F�b�N
		m_pPlayer3D = nullptr;	//nullptr�ɂ���
	}

	/* �G(3D) */

	for (int i = 0; i < CEnemy3D::MAX_ENEMY; i++)
	{
		if (m_apEnemy3D[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		m_apEnemy3D[i] = nullptr;	//nullptr�ɂ���
	}
}

//================================================
//�X�V
//================================================
void CGame::Update()
{
	if (m_pCamera != nullptr)
	{//NULL�`�F�b�N
		m_pCamera->Update();	//�J����
	}

	CObject::UpdateAll();	//�I�u�W�F�N�g

	if (m_pCamera->GetPosV().x == 500.0f)
	{
		ChangeGamePart();
	}
}

//================================================
//�`��
//================================================
void CGame::Draw()
{
	//�J�����̐ݒ�
	m_pCamera->Set();

	CObject::DrawAll();	//�I�u�W�F�N�g
}

//================================================
//�Q�[���p�[�g�̐؂�ւ�
//================================================
void CGame::ChangeGamePart()
{
	/* �ʏ�G����� */

	for (int i = 0; i < CEnemy3D::MAX_ENEMY; i++)
	{
		if (m_apEnemy3D[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		m_apEnemy3D[i] = nullptr;	//nullptr�ɂ���
	}

	m_pCamera->Init();	//�J�����̏�����

	m_bGamePart = true;	//�{�X�p�[�g�ɐ؂�ւ�

	/* �{�X�̐��� */

	if (m_apEnemy3D[0] != nullptr)
	{//NULL�`�F�b�N
		m_apEnemy3D[0] = nullptr;	//nullptr�ɂ���

		//�ʒu��ݒ�
		D3DXVECTOR3 pos = D3DXVECTOR3(CEnemyBoss::START_POS_X, CEnemyBoss::START_POS_Y, 0.0f);

		//�{�X�𐶐�����
		m_apEnemy3D[0] = CEnemy3D::Create(CEnemy3D::ENM_TYPE::BOSS, pos);
	}
}

//================================================
//�Q�[���p�[�g�̎擾
//================================================
bool CGame::GetGamePart()
{
	return m_bGamePart;
}