//================================================
//
//������H��b[camera.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>

//***************************
//�J�����N���X�̒�`
//***************************
class CCamera
{/* ��{�N���X */
private: /* �萔�̒�` */
	static const float CAMERA_MOVE;	//�ړ���
	static const float CAMERA_ROT;	//�����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CCamera();
	~CCamera();

public: /* �����o�֐� */
	void Init();	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Set();		//�ݒ�
private:
	void Move();			//�ړ�
	void Turn();			//����
	void NormalizeAngle();	//�p�x�̐��K��

private: /* �����o�ϐ� */
	D3DXVECTOR3 m_posV;		//���݂̎��_
	D3DXVECTOR3 m_posR;		//���݂̒����_
	D3DXVECTOR3 m_posVDest;	//�ړI�̎��_
	D3DXVECTOR3 m_posRDest;	//�ړI�̒����_
	D3DXVECTOR3 m_vecU;		//������x�N�g��
	D3DXVECTOR3 m_rot;		//����

	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X

	float m_fDistance;	//���_���璍���_�̋���
};

#endif