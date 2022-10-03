//================================================
//
//������H��b[camera.cpp]
//Author:Kishimoto Eiji
//
//================================================
#include "camera.h"
#include "application.h"
#include "inputKeyboard.h"
#include "renderer.h"
#include "game.h"
#include "fade.h"

//***************************
//�萔�̒�`
//***************************
const float CCamera::SCROLL_SPEED = 0.1f;	//�X�N���[�����x
const float CCamera::MOVE_SPEED = 5.0f;		//�ړ����x

//================================================
//�R���X�g���N�^
//================================================
CCamera::CCamera():
	m_posV(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posR(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vecU(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	//�����o�ϐ��̃N���A
	memset(m_mtxProjection,0,sizeof(m_mtxProjection));
	memset(m_mtxView, 0, sizeof(m_mtxView));
}

//================================================
//�f�X�g���N�^
//================================================
CCamera::~CCamera()
{}

//================================================
//������
//================================================
void CCamera::Init()
{
	//�����o�ϐ��̏����ݒ�
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Set();	//�J�������Z�b�g
}

//================================================
//�I��
//================================================
void CCamera::Uninit()
{
}

//================================================
//�X�V
//================================================
void CCamera::Update()
{
	if (CApplication::GetFade()->GetState() == CFade::STATE::FADE_OUT)
	{//�Ó]��
		return;
	}

	if (!CGame::GetGamePart())
	{//�ʏ�p�[�g
		m_move.x = SCROLL_SPEED;	//X���̈ړ�
	}
	else
	{//�{�X�p�[�g
		m_move.y = SCROLL_SPEED;	//Y���̈ړ�
	}

#ifdef _DEBUG	//�f�o�b�O���̂�

	//�ړ�
	Move();

#endif

	if ((m_move.x == 0.0f) && (m_move.y == 0.0f))
	{//�ړ����Ă��Ȃ�������
		return;
	}

	/* �ړ����Ă����� */

	//�ړ��ʂɉ����Ĉʒu���X�V(���_)
	m_posV.x += m_move.x * MOVE_SPEED;	//X��
	m_posV.y += m_move.y * MOVE_SPEED;	//Y��

	//�ړ��ʂɉ����Ĉʒu���X�V(�����_)
	m_posR.x += m_move.x * MOVE_SPEED;	//X��
	m_posR.y += m_move.y * MOVE_SPEED;	//Y��

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʂ����Z�b�g
}

//================================================
//�ݒ�
//================================================
void CCamera::Set()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);  

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	/*D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(45.0f),
								(float)CRenderer::SCREEN_WIDTH / (float)CRenderer::SCREEN_HEIGHT,
								10.0f,
								3000.0f);*/

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
	D3DXMatrixOrthoLH(&m_mtxProjection,						//�v���W�F�N�V�����}�g���b�N�X
						(float)CRenderer::SCREEN_WIDTH,		//��
						(float)CRenderer::SCREEN_HEIGHT,	//����
						10.0f,								//�j�A
						3000.0f);							//�t�@�[

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//================================================
//�r���[�}�g���N�X�̎擾
//================================================
D3DXMATRIX CCamera::GetMatrixView()
{
	return m_mtxView;
}

//================================================
//���_�̈ʒu�̎擾
//================================================
D3DXVECTOR3 CCamera::GetPosV()
{
	return m_posV;
}

//================================================
//�ړ�
//================================================
void CCamera::Move()
{
	//�L�[�{�[�h���̎擾
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	/* �O�㍶�E */

	if (pKeyboard->GetPress(DIK_LEFT))
	{//���L�[
		/* �ړ������ɉ����� */

		if (pKeyboard->GetPress(DIK_UP))
		{//����
			m_move.x = -1.0f;	//X��
			m_move.y = +1.0f;	//Y��
		}
		else if (pKeyboard->GetPress(DIK_DOWN))
		{//����
			m_move.x = -1.0f;	//X��
			m_move.y = -1.0f;	//Y��
		}
		else
		{//��
			m_move.x = -1.0f;	//X��
		}
	}
	else if (pKeyboard->GetPress(DIK_RIGHT))
	{//���L�[
		/* �����ɉ����Ĉړ��ʂ����Z */
		
		if (pKeyboard->GetPress(DIK_UP))
		{//�E��
			m_move.x = +1.0f;	//X��
			m_move.y = +1.0f;	//Y��
		}
		else if (pKeyboard->GetPress(DIK_DOWN))
		{//�E��
			m_move.x = +1.0f;	//X��
			m_move.y = -1.0f;	//Y��
		}
		else
		{//�E
			m_move.x = +1.0f;	//X��
		}
	}
	else if (pKeyboard->GetPress(DIK_UP))
	{//���L�[(��)
		m_move.y = +1.0f;	//Y��
	}
	else if (pKeyboard->GetPress(DIK_DOWN))
	{//���L�[(��)
		m_move.y = -1.0f;	//Y��
	}
}