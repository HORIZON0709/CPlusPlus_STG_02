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
#include "application.h"
#include "renderer.h"
#include "fade.h"
#include "object2D.h"
#include "object3D.h"

#include "camera.h"
#include "score.h"
#include "player_3D.h"
#include "enemy_curve.h"
#include "enemy_boss.h"
#include "bg_3D.h"

#include <assert.h>
#include <time.h>

//***************************
//�萔�̒�`
//***************************
const int CGame::INTERVAL_STRAIGHT = 120;		//�����G�̐����Ԋu
const int CGame::FADE_INTERVAL_PARTCHANGE = 60;	//�t�F�[�h�܂ł̊Ԋu(�p�[�g�؂�ւ���)
const int CGame::FADE_INTERVAL_GAMEOVER = 60;	//�t�F�[�h�܂ł̊Ԋu(�Q�[���I�[�o�[��)
const int CGame::FADE_INTERVAL_GAMECLEAR = 180;	//�t�F�[�h�܂ł̊Ԋu(�Q�[���N���A��)

//***************************
//�ÓI�����o�ϐ�
//***************************
CCamera* CGame::m_pCamera = nullptr;					//�J����
CScore* CGame::m_pScore = nullptr;						//�X�R�A
CPlayer3D* CGame::m_pPlayer3D = nullptr;				//�v���C���[(3D)
CEnemy3D* CGame::m_apEnemy3D[CEnemy3D::MAX_ENEMY] = {};	//�G(3D)
CBg3D* CGame::m_pBg3D = nullptr;						//�w�i(3D)

/*
	�Q�[���p�[�g�̔���
	false ---> �ʏ�p�[�g
	true ---> �{�X�p�[�g
*/
bool CGame::m_bGamePart = false;

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

	for (int i = 0; i < CObject::MAX_OBJECT; i++)
	{
		CObject* pObject = CObject::GetObjects(i);	//�I�u�W�F�N�g���̎擾

		if (pObject == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͖����ꍇ */

		CObject::OBJ_TYPE type = pObject->GetObjType();	//�I�u�W�F�N�g�̎�ނ̎擾

		if (type != CObject::OBJ_TYPE::ENEMY)
		{//�G�ł͖����ꍇ
			continue;
		}

		/* �G�̃I�u�W�F�N�g�������ꍇ */

		//nullptr�ɂ���
		CObject::SetObject(i, nullptr);
	}

	m_pCamera->Init();	//�J�����̏�����

	m_pBg3D->Init();	//�w�i(3D)�̏�����

	m_pPlayer3D->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//�����ʒu�ɖ߂�

	//***** �{�X�̐��� *****//

	if (m_apEnemy3D[0] != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* �ʏ�G���S�ĉ���ł��Ă����ꍇ */

	//�ʒu��ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3(CEnemyBoss::START_POS_X, CEnemyBoss::START_POS_Y, 0.0f);

	//�{�X�𐶐�����
	m_apEnemy3D[0] = CEnemy3D::Create(CEnemy3D::ENM_TYPE::BOSS, pos);

	m_bGamePart = true;	//�{�X�p�[�g�ɐ؂�ւ�

	//���]
	CApplication::GetFade()->Set(CFade::STATE::FADE_IN);
}

//================================================
//�Q�[���p�[�g�̎擾
//================================================
bool CGame::GetGamePart()
{
	return m_bGamePart;
}

//================================================
//�R���X�g���N�^
//================================================
CGame::CGame() : CMode(MODE::GAME),
m_nCntStraight(0),
m_nCntIntervalFade(0),
m_bFadeOut(false)
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
	srand((unsigned)time(NULL));	//�����_����q�̏�����

	m_bGamePart = false;	//�ʏ�p�[�g

	//�����o�ϐ��̏�����
	m_nCntStraight = 0;
	m_nCntIntervalFade = 0;
	m_bFadeOut = false;

	/* ���� */

	if (m_pCamera == nullptr)
	{//NULL�`�F�b�N
		m_pCamera = new CCamera;	//�J����
		m_pCamera->Init();			//������
	}

	m_pScore = CScore::Create();	//�X�R�A

	m_pBg3D = CBg3D::Create();	//�w�i(3D)

	m_pPlayer3D = CPlayer3D::Create();	//�v���C���[(3D)

	//���]
	CApplication::GetFade()->Set(CFade::STATE::FADE_IN);

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
	CObject::UpdateAll();	//�I�u�W�F�N�g

	if (m_pCamera != nullptr)
	{//NULL�`�F�b�N
		m_pCamera->Update();	//�J����
	}

	if (m_pPlayer3D->GetObjType() != CObject::OBJ_TYPE::PLAYER)
	{//�v���C���[�����S������
		m_nCntIntervalFade++;	//�J�E���g�A�b�v

		if (!m_bFadeOut && (m_nCntIntervalFade % FADE_INTERVAL_GAMEOVER == 0))
		{//�Ó]���Ă��Ȃ� & �J�E���g����萔�𒴂���
			//�Ó]
			CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);

			//�Ó]����
			m_bFadeOut = true;
		}

		if (m_bFadeOut && (CApplication::GetFade()->GetState() == CFade::STATE::NONE))
		{//�Ó]���� & ���݃t�F�[�h���Ă��Ȃ�
			Change(MODE::RESULT);	//���[�h�̐ݒ�
		}
	}

	if (m_bGamePart)
	{//�{�X�p�[�g�̏ꍇ
		UpdateBossPart();	//�{�X�p�[�g�̍X�V
		return;
	}

	/* �ʏ�p�[�g�̏ꍇ */

	UpdateNormalPart();	//�ʏ�p�[�g�̍X�V
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
//�����G�̐���
//================================================
void CGame::CreateEnemyStraight(const float fPosY)
{
	//�J�������̎擾
	D3DXMATRIX mtxCamera = m_pCamera->GetMatrixView();

	//�J�����̎��_�̈ʒu���擾
	D3DXVECTOR3 posV = m_pCamera->GetPosV();

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxCamera, posV.x, posV.y, posV.z);

	//�J�����̉�p�̉E�̌��E��ݒ�
	float fRimitRight = (mtxCamera._41 + (CRenderer::SCREEN_WIDTH * 0.5f));

	//�擪�����������ʒu��ݒ�
	float fPosFirst = (fRimitRight + 100.0f);

	int nNumCreate = 5;	//��x�ɐ������鐔

	for (int i = 0,nCnt = 0; i < CEnemy3D::MAX_ENEMY; i++)
	{
		if (nCnt == nNumCreate)
		{//�ݒ萔���S�Đ���������
			break;
		}

		/* �ݒ萔���S�Đ������Ă��Ȃ��ꍇ */

		if (m_apEnemy3D[i] != nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�̏ꍇ */

		//�ʒu��ݒ�
		D3DXVECTOR3 pos = D3DXVECTOR3(fPosFirst + (i * 100.0f), fPosY, 0.0f);

		//����
		m_apEnemy3D[i] = CEnemy3D::Create(CEnemy3D::ENM_TYPE::STRAIGHT, pos);

		nCnt++;	//����������J�E���g
	}
}

//================================================
//�ʏ�p�[�g�̍X�V
//================================================
void CGame::UpdateNormalPart()
{
	if (m_bGamePart)
	{//�{�X�p�[�g�̏ꍇ
		return;
	}

	/* �ʏ�p�[�g�̏ꍇ */

	if (m_pCamera->GetPosV().x >= 500.0f)
	{//�J��������苗���܂Ői�񂾂�
		m_nCntIntervalFade++;	//�J�E���g�A�b�v

		if (!m_bFadeOut && (m_nCntIntervalFade >= FADE_INTERVAL_PARTCHANGE))
		{//�Ó]���Ă��Ȃ� & �J�E���g����萔�𒴂���
			//�Ó]
			CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);

			//�Ó]����
			m_bFadeOut = true;
		}
		
		if (m_bFadeOut && (CApplication::GetFade()->GetState() == CFade::STATE::NONE))
		{//�Ó]���� & ���݃t�F�[�h���Ă��Ȃ�
			//�Q�[���p�[�g�؂�ւ�
			ChangeGamePart();

			//�J�E���g��������(�{�X�p�[�g�ł͎g�p���Ȃ�)
			m_nCntStraight = 0;

			//���]����
			m_bFadeOut = false;
			return;
		}
	}

	if (m_pCamera->GetPosV().x < 450.0f)
	{//�J��������苗���̎�O�ɗ���܂�
		m_nCntStraight++;	//�J�E���g�A�b�v

		if (m_nCntStraight % INTERVAL_STRAIGHT != 0)
		{//���Ԋu�܂ŃJ�E���g���Ă��Ȃ�
			return;
		}
		
		/* ���Ԋu�܂ŃJ�E���g�����ꍇ */

		float aPosY[5] =
		{//�����_���Ő�������������(�ォ��)
			200.0f,
			100.0f,
			0.0f,
			-100.0f,
			-200.0f
		};

		int nRandam = rand() % 5;	//�����_��

		//�����G�̐���
		CreateEnemyStraight(aPosY[nRandam]);
	}
}

//================================================
//�{�X�p�[�g�̍X�V
//================================================
void CGame::UpdateBossPart()
{
	if (!m_bGamePart)
	{//�ʏ�p�[�g�̏ꍇ
		return;
	}

	/* �{�X�p�[�g�̏ꍇ */

	//�{�X�̌^�ɃL���X�g
	CEnemyBoss* pBoss = (CEnemyBoss*)m_apEnemy3D[0];

	//�{�X�̗̑͂��s�������ǂ���
	bool bBossAlive = (pBoss->GetLife() <= 0);

	if (!bBossAlive)
	{//�{�X������łȂ��ꍇ
		return;
	}

	/* �{�X�����񂾏ꍇ */

	m_nCntIntervalFade++;	//�J�E���g�A�b�v

	if (!m_bFadeOut && (m_nCntIntervalFade % FADE_INTERVAL_GAMECLEAR == 0))
	{//�Ó]���Ă��Ȃ� & �J�E���g����萔�𒴂���
		//�Ó]
		CApplication::GetFade()->Set(CFade::STATE::FADE_OUT);

		//�Ó]����
		m_bFadeOut = true;
	}

	if (m_bFadeOut && (CApplication::GetFade()->GetState() == CFade::STATE::NONE))
	{//�Ó]���� & ���݃t�F�[�h���Ă��Ȃ�
		Change(MODE::RESULT);	//���[�h�̐ݒ�
	}
}