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

//***************************
//�萔�̒�`
//***************************
const float CCamera::CAMERA_MOVE = 20.0f;	//�ړ���

//================================================
//�R���X�g���N�^
//================================================
CCamera::CCamera():
	m_posV(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posR(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posVDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posRDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vecU(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	//�����o�ϐ��̃N���A
	memset(m_mtxProjection,0,sizeof(m_mtxProjection));
	memset(m_mtxView, 0, sizeof(m_mtxView));
}

//================================================
//�f�X�g���N�^
//================================================
CCamera::~CCamera()
{
}

//================================================
//������
//================================================
void CCamera::Init()
{
	//���_�E�����_�E������x�N�g����ݒ肷��
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�����̏�����
	m_rot = D3DXVECTOR3((-D3DX_PI * 0.1f), 0.0f, 0.0f);

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
	//�ړ�
	Move();

	//�����_
	m_posR.x = m_posV.x + sinf(m_rot.y);
	m_posR.z = m_posV.z + cosf(m_rot.y);
	m_posR.y = m_posV.y + tanf(m_rot.x);
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
//�ړ�
//================================================
void CCamera::Move()
{
	//�L�[�{�[�h���̎擾
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	/* �O�㍶�E */

	if (pKeyboard->GetPress(DIK_LEFT))
	{//���L�[
		/* �����ɉ����Ĉړ��ʂ����Z */

		if (pKeyboard->GetPress(DIK_UP))
		{//����
			m_posV.x += sinf(m_rot.y + (-D3DX_PI * 0.75f)) * CAMERA_MOVE;	//X��
			m_posV.y += cosf(m_rot.y + (-D3DX_PI * 0.75f)) * CAMERA_MOVE;	//Y��
		}
		else if (pKeyboard->GetPress(DIK_DOWN))
		{//����
			m_posV.x += sinf(m_rot.y + (-D3DX_PI * 0.25f)) * CAMERA_MOVE;	//X��
			m_posV.y += cosf(m_rot.y + (-D3DX_PI * 0.25f)) * CAMERA_MOVE;	//Y��
		}
		else
		{//��
			m_posV.x += sinf(m_rot.y + (-D3DX_PI * 0.5f)) * CAMERA_MOVE;	//X��
		}
	}
	else if (pKeyboard->GetPress(DIK_RIGHT))
	{//���L�[
		/* �����ɉ����Ĉړ��ʂ����Z */
		
		if (pKeyboard->GetPress(DIK_UP))
		{//�E��
			m_posV.x += sinf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;	//X��
			m_posV.y += cosf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;	//Y��
		}
		else if (pKeyboard->GetPress(DIK_DOWN))
		{//�E��
			m_posV.x += sinf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;	//X��
			m_posV.y += cosf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;	//Y��
		}
		else
		{//�E
			m_posV.x += sinf(m_rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;	//X��
		}
	}
	else if (pKeyboard->GetPress(DIK_UP))
	{//���L�[(��)
		/* �����ɉ����Ĉړ��ʂ����Z */
		m_posV.y += cosf(m_rot.y) * CAMERA_MOVE;	//Y��
	}
	else if (pKeyboard->GetPress(DIK_DOWN))
	{//���L�[(��)
		/* �����ɉ����Ĉړ��ʂ����Z */
		m_posV.y += cosf(-m_rot.y) * CAMERA_MOVE;	//Y��
	}
}

//================================================
//�p�x�̐��K��
//================================================
void CCamera::NormalizeAngle()
{
	/* Y�� */

	if (m_rot.y > D3DX_PI)
	{//��( 180��)�𒴂����ꍇ
		m_rot.y -= (D3DX_PI * 2.0f);
	}
	else if (m_rot.y < -D3DX_PI)
	{//-��( -180��)�𒴂����ꍇ
		m_rot.y += (D3DX_PI * 2.0f);
	}

	/* X�� */

	if (m_rot.x > D3DX_PI)
	{//��( 180��)�𒴂����ꍇ
		m_rot.x -= (D3DX_PI * 2.0f);
	}
	else if (m_rot.x < -D3DX_PI)
	{//-��( -180��)�𒴂����ꍇ
		m_rot.x += (D3DX_PI * 2.0f);
	}
}