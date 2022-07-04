//================================================
//
//������H��b[enemy_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ENEMY_3D_H_
#define _ENEMY_3D_H_

//***************************
//�C���N���[�h
//***************************
#include "object3D.h"

//***************************
//�G�N���X�̒�`
//***************************
class CEnemy3D : public CObject3D
{/* CObject3D�̔h���N���X */
private: /* �萔�̒�` */
	static const float ENEMY_SIZE;	//�T�C�Y

	static const int SHOT_INTERVAL = 20;	//�e�̘A�����˂̊Ԋu

public: /* �ÓI�����o�֐� */
	static CEnemy3D* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CEnemy3D();
	~CEnemy3D() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �����o�ϐ� */
	int m_nTimerInterval;	//�e�̘A�����˂̊Ԋu
};
#endif