//================================================
//
//������H��b[player_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PLAYER_3D_H_
#define _PLAYER_3D_H_

//***************************
//�C���N���[�h
//***************************
#include "object3D.h"

//***************************
//�v���C���[(3D)�N���X�̒�`
//***************************
class CPlayer3D : public CObject3D
{/* CObject2D�̔h���N���X */
private: /* �萔�̒�` */
	static const float PLAYER_SIZE;	//�T�C�Y
	static const float MOVE_SPEED;	//�ړ����x

	static const int SHOT_INTERVAL = 10;	//�e�̘A�����˂̊Ԋu

public: /* �ÓI�����o�֐� */
	static CPlayer3D* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CPlayer3D();
	~CPlayer3D() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �����o�֐� */
	void Move();	//�ړ�
	void Shot();	//����

private: /* �����o�ϐ� */
	int m_nTimerInterval;	//�e�̘A�����˂̊Ԋu
};

#endif