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

#include <assert.h>

//***************************
//�ÓI�����o�ϐ�
//***************************
CScore* CGame::m_pScore = nullptr;						//�X�R�A
CPlayer3D* CGame::m_pPlayer3D = nullptr;				//�v���C���[(3D)
CEnemy3D* CGame::m_apEnemy3D[CEnemy3D::MAX_ENEMY] = {};	//�G(3D)
CBg3D* CGame::m_pBg3D = nullptr;						//�w�i(3D)

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
CGame::CGame()
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

	if (!m_bGamePart)
	{//�ʏ�p�[�g
		m_pScore = CScore::Create();	//�X�R�A

		m_pBg3D = CBg3D::Create();	//�w�i(3D)

		m_pPlayer3D = CPlayer3D::Create();	//�v���C���[(3D)

		for (int i = 0; i < CEnemy3D::NUM_ENEMY_CURVE; i++)
		{//�G(3D)
			if (m_apEnemy3D[i] != nullptr)
			{//NULL�`�F�b�N
				continue;
			}

			/* nullptr�̏ꍇ */

			//�ʒu��ݒ�
			D3DXVECTOR3 pos = D3DXVECTOR3(300.0f + (200.0f * i), (100.0f * i), 0.0f);

			//����
			m_apEnemy3D[i] = CEnemy3D::Create(CEnemy3D::ENM_TYPE::CURVE, pos);
		}
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

	/* �X�R�A */

	m_pScore = nullptr;	//nullptr�ɂ���

	/* �w�i(3D) */

	m_pBg3D = nullptr;	//nullptr�ɂ���

	/* �v���C���[(3D) */

	m_pPlayer3D = nullptr;	//nullptr�ɂ���

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
}

//================================================
//�`��
//================================================
void CGame::Draw()
{
}

//================================================
//�Q�[���p�[�g�̎擾
//================================================
bool CGame::GetGamePart()
{
	return m_bGamePart;
}