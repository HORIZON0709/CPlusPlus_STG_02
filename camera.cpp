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
const float CCamera::CAMERA_MOVE = 2.0f;	//�ړ���
const float CCamera::CAMERA_ROT = 0.05f;	//�����

//================================================
//�R���X�g���N�^
//================================================
CCamera::CCamera():
	m_posV(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posR(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posVDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posRDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vecU(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_fDistance(0.0f)
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
	//���_�E�����_�E�������ݒ肷��
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -160.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�����̏�����
	m_rot = D3DXVECTOR3((-D3DX_PI * 0.1f), 0.0f, 0.0f);

	//���_���璍���_�̋����̐ݒ�
	float fX = (m_posR.x - m_posV.x);
	float fZ = (m_posR.z - m_posV.z);

	//�O�����ŋ������v�Z
	m_fDistance = sqrtf((fX * fX) + (fZ * fZ));
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

	//����
	Turn();

	//�L�[�{�[�h���̎擾
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	if (pKeyboard->GetPress(DIK_Z) || pKeyboard->GetPress(DIK_C))
	{//���_�̐�������Ă���ꍇ�̂�
		//���_
		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}

	//�����_
	m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
	m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	m_posR.y = m_posV.y + tanf(m_rot.x) * m_fDistance;
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
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(45.0f),
								(float)CRenderer::SCREEN_WIDTH / (float)CRenderer::SCREEN_HEIGHT,
								10.0f,
								3000.0f);

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
		{//���O
			m_posV.x -= sinf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;	//X��
			m_posV.z -= cosf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;	//Z��
		}
		else if (pKeyboard->GetPress(DIK_DOWN))
		{//�����
			m_posV.x -= sinf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;	//X��
			m_posV.z -= cosf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;	//Z��
		}
		else
		{//��
			m_posV.x -= sinf(m_rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;	//X��
			m_posV.z -= cosf(m_rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;	//Z��
		}
	}
	else if (pKeyboard->GetPress(DIK_RIGHT))
	{//���L�[
		/* �����ɉ����Ĉړ��ʂ����Z */
		
		if (pKeyboard->GetPress(DIK_UP))
		{//�E�O
			m_posV.x += sinf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;	//X��
			m_posV.z += cosf(m_rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;	//Z��
		}
		else if (pKeyboard->GetPress(DIK_DOWN))
		{//�E���
			m_posV.x += sinf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;	//X��
			m_posV.z += cosf(m_rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;	//Z��
		}
		else
		{//�E
			m_posV.x += sinf(m_rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;	//X��
			m_posV.z += cosf(m_rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;	//Z��
		}
	}
	else if (pKeyboard->GetPress(DIK_UP))
	{//���L�[(�O)
		/* �����ɉ����Ĉړ��ʂ����Z */
		m_posV.x += sinf(m_rot.y) * CAMERA_MOVE;	//X��
		m_posV.z += cosf(m_rot.y) * CAMERA_MOVE;	//Z��
	}
	else if (pKeyboard->GetPress(DIK_DOWN))
	{//���L�[(��)
		/* �����ɉ����Ĉړ��ʂ����Z */
		m_posV.x -= sinf(m_rot.y) * CAMERA_MOVE;	//X��
		m_posV.z -= cosf(m_rot.y) * CAMERA_MOVE;	//Z��
	}

	/* �㉺ */

	if (pKeyboard->GetPress(DIK_T))
	{//�㏸( T�L�[ )
		m_posV.y += CAMERA_MOVE;	//�ړ��ʂ����Z( Y�� )
	}
	else if (pKeyboard->GetPress(DIK_G))
	{//���~( G�L�[ )
		m_posV.y -= CAMERA_MOVE;	//�ړ��ʂ����Z( Y�� )
	}
}

//================================================
//����
//================================================
void CCamera::Turn()
{
	//�L�[�{�[�h���̎擾
	CInputKeyboard* pKeyboard = CApplication::GetInputKeyboard();

	/* ���E([���_] or [�����_]) */

	if (pKeyboard->GetPress(DIK_Z) || pKeyboard->GetPress(DIK_Q))
	{//�����( Z�L�[ or Q�L�[ )
		m_rot.y += CAMERA_ROT;	//����ʂ����Z
	}
	else if (pKeyboard->GetPress(DIK_C) || pKeyboard->GetPress(DIK_E))
	{//�E���( C�L�[ or E�L�[ )
		m_rot.y -= CAMERA_ROT;	//����ʂ����Z
	}

	/* �㉺ */

	if (pKeyboard->GetPress(DIK_Y))
	{//��( Y�L�[ )
		m_rot.x += (CAMERA_ROT * 0.2f);	//����ʂ����Z
	}
	else if (pKeyboard->GetPress(DIK_H))
	{//��( H�L�[ )
		m_rot.x -= (CAMERA_ROT * 0.2f);	//����ʂ����Z
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