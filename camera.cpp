//============================================================================================================
//
//�~�c�P�e�l[camera.cpp]
//Author:Kishimoto Eiji
//
//============================================================================================================
#include "camera.h"
#include "input.h"
#include "player.h"

//============================================================================================================
//�}�N����`
//============================================================================================================
#define CAMERA_MOVE		(2.0f)		//�J�����̈ړ���
#define CAMERA_ROT		(0.05f)		//�J�����̐����

//============================================================================================================
//�X�^�e�B�b�N�ϐ��錾
//============================================================================================================
static Camera s_camera;		//�J�������
static bool bFollow;		//�Ǐ]��ON�EOFF

//============================================================================================================
//�v���g�^�C�v�錾
//============================================================================================================
static void CameraMove(void);
static void CameraReset(void);
static void AllDirections(void);
static void RiseAndFall(void);
static void Turning(void);
static void AngleNormalization(void);
static void CameraFollow(void);

//============================================================================================================
//�J�����̏���������
//============================================================================================================
void InitCamera(void)
{
	//���_�E�����_�E�������ݒ肷��
	s_camera.posV = D3DXVECTOR3(0.0f, 100.0f, -160.0f);
	s_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	s_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�����̏�����
	s_camera.rot = D3DXVECTOR3((-D3DX_PI * 0.1f), 0.0f, 0.0f);
	
	//���_���璍���_�̋����̐ݒ�
	float fX = (s_camera.posR.x - s_camera.posV.x);
	float fZ = (s_camera.posR.z - s_camera.posV.z);
	s_camera.fDistance	= sqrtf((fX * fX) + (fZ * fZ));		//�O�����ŋ������v�Z

	bFollow = true;		//�Ǐ]���Ȃ�
}

//============================================================================================================
//�J�����̏I������
//============================================================================================================
void UninitCamera(void)
{

}

//============================================================================================================
//�J�����̍X�V����
//============================================================================================================
void UpdateCamera(void)
{
	//�J�����̈ړ�
	CameraMove();

	if (GetKeyboardTrigger(DIK_F3))
	{
		bFollow = bFollow ? false : true;	//�Ǐ]�̐؂�ւ�
	}

	if (bFollow)
	{//�Ǐ]���[�hON
		//�J�����̒Ǐ]
		CameraFollow();
	}
}

//============================================================================================================
//�J�����̐ݒ菈��
//============================================================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&s_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&s_camera.mtxView,
					   &s_camera.posV,
					   &s_camera.posR,
					   &s_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &s_camera.mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&s_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&s_camera.mtxProjection,
								D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
								10.0f,
								3000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &s_camera.mtxProjection);
}

//============================================================================================================
//�J�����̈ړ�
//============================================================================================================
static void CameraMove(void)
{
#ifdef _DEBUG	//�f�o�b�O�̎�����

	//�J�����̃��Z�b�g
	CameraReset();

	//�O�㍶�E�̈ړ�
	AllDirections();
	
	//�㉺�̈ړ�
	RiseAndFall();

	//���_�E�����_�̐���
	Turning();

#endif
	//�p�x�̐��K��
	AngleNormalization();

	/*�� ���_�E�����_�̈ʒu���X�V ��*/

	if (GetKeyboardPress(DIK_Z) || GetKeyboardPress(DIK_C))
	{//���_�̐�������Ă���ꍇ�̂�
		//���_
		s_camera.posV.x = s_camera.posR.x - sinf(s_camera.rot.y) * s_camera.fDistance;
		s_camera.posV.z = s_camera.posR.z - cosf(s_camera.rot.y) * s_camera.fDistance;
	}

	//�����_
	s_camera.posR.x = s_camera.posV.x + sinf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posR.z = s_camera.posV.z + cosf(s_camera.rot.y) * s_camera.fDistance;
	s_camera.posR.y = s_camera.posV.y + tanf(s_camera.rot.x) * s_camera.fDistance;
}

//============================================================================================================
//�J�����̒Ǐ]
//============================================================================================================
static void CameraFollow(void)
{
	Player *pP = GetPlayer();	//�v���C���[���̎擾
	Camera *pC = &s_camera;		//�|�C���^�ɕϐg

	/*�� �ړI�̈ʒu��ݒ� ��*/

	//�����_
	pC->posRDest.x = pP->pos.x + sinf(pC->rot.y - pP->rot.y) * 300.0f;
	pC->posRDest.y = pP->pos.x - tanf(pP->rot.x - pP->rot.x) * 300.0f;
	pC->posRDest.z = pP->pos.z - cosf(pC->rot.y - pP->rot.y) * 300.0f;

	//���_
	pC->posVDest.x = pP->pos.x + sinf(pC->rot.y) * pC->fDistance;
	pC->posVDest.y = pP->pos.y - tanf(pC->rot.x) * pC->fDistance;
	pC->posVDest.z = pP->pos.z - cosf(pC->rot.y) * pC->fDistance;

	/*�� ���݂̈ʒu���X�V ��*/

	//�����_
	pC->posR.x += (pC->posRDest.x - pC->posR.x) * 0.1f;
	pC->posR.y += (pC->posRDest.y - pC->posR.y) * 0.01f;
	pC->posR.z += (pC->posRDest.z - pC->posR.z) * 0.1f;

	//���_
	pC->posV.x += (pC->posVDest.x - pC->posV.x) * 0.1f;
	pC->posV.y += (pC->posVDest.y - pC->posV.y) * 0.1f;
	pC->posV.z += (pC->posVDest.z - pC->posV.z) * 0.1f;
}

//============================================================================================================
//�J�����̃��Z�b�g
//============================================================================================================
static void CameraReset(void)
{
	if (GetKeyboardTrigger(DIK_RETURN))
	{//Enter�L�[
		//�J�����̏���������
		InitCamera();
	}
}

//============================================================================================================
//�O�㍶�E�̈ړ�
//============================================================================================================
static void AllDirections(void)
{
	if (GetKeyboardPress(DIK_LEFT))
	{//���L�[
		if (GetKeyboardPress(DIK_UP))
		{//����
			s_camera.posV.x -= sinf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			s_camera.posV.z -= cosf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{//����
			s_camera.posV.x -= sinf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			s_camera.posV.z -= cosf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else
		{//��
			s_camera.posV.x -= sinf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			s_camera.posV.z -= cosf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{//���L�[
		if (GetKeyboardPress(DIK_UP))
		{//�E��
			s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN))
		{//�E��
			s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else
		{//�E
			s_camera.posV.x += sinf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			s_camera.posV.z += cosf(s_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}
	}
	else if (GetKeyboardPress(DIK_UP))
	{//���L�[(�O)
		s_camera.posV.x += sinf(s_camera.rot.y) * CAMERA_MOVE;
		s_camera.posV.z += cosf(s_camera.rot.y) * CAMERA_MOVE;
	}
	else if (GetKeyboardPress(DIK_DOWN))
	{//���L�[(��)
		s_camera.posV.x -= sinf(s_camera.rot.y) * CAMERA_MOVE;
		s_camera.posV.z -= cosf(s_camera.rot.y) * CAMERA_MOVE;
	}
}

//============================================================================================================
//�㉺�̈ړ�
//============================================================================================================
static void RiseAndFall(void)
{
	if (GetKeyboardPress(DIK_T))
	{//�㏸
		s_camera.posV.y += CAMERA_MOVE;
	}
	else if (GetKeyboardPress(DIK_G))
	{//���~
		s_camera.posV.y -= CAMERA_MOVE;
	}
}

//============================================================================================================
//���_�E�����_�̐���
//============================================================================================================
static void Turning(void)
{
	//���E([���_] or [�����_])
	if (GetKeyboardPress(DIK_Z) || GetKeyboardPress(DIK_Q))
	{//�����
		s_camera.rot.y += CAMERA_ROT;
	}
	else if (GetKeyboardPress(DIK_C) || GetKeyboardPress(DIK_E))
	{//�E���
		s_camera.rot.y -= CAMERA_ROT;
	}

	//�㉺
	if (GetKeyboardPress(DIK_Y))
	{//��
		s_camera.rot.x += (CAMERA_ROT * 0.2f);
	}
	else if (GetKeyboardPress(DIK_H))
	{//��
		s_camera.rot.x -= (CAMERA_ROT * 0.2f);
	}
}

//============================================================================================================
//�p�x�̐��K��
//============================================================================================================
static void AngleNormalization(void)
{
	//Y��
	if (s_camera.rot.y > D3DX_PI)
	{//��( 180��)�𒴂����ꍇ
		s_camera.rot.y -= (D3DX_PI * 2.0f);
	}
	else if (s_camera.rot.y < -D3DX_PI)
	{//-��( -180��)�𒴂����ꍇ
		s_camera.rot.y += (D3DX_PI * 2.0f);
	}

	//X��
	if (s_camera.rot.x > D3DX_PI)
	{//��( 180��)�𒴂����ꍇ
		s_camera.rot.x -= (D3DX_PI * 2.0f);
	}
	else if (s_camera.rot.x < -D3DX_PI)
	{//-��( -180��)�𒴂����ꍇ
		s_camera.rot.x += (D3DX_PI * 2.0f);
	}
}

//============================================================================================================
//�J�����̏��̎擾
//============================================================================================================
Camera *GetCamera(void)
{
	return &s_camera;
}