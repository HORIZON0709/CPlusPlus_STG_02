//================================================
//
//������H��b[enemy_boss.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ENEMY_BOSS_H_
#define _ENEMY_BOSS_H_

//***************************
//�C���N���[�h
//***************************
#include "enemy_3D.h"

//***************************
//�G�N���X�̒�`
//***************************
class CEnemyBoss : public CEnemy3D
{/* CEnemy3D�̔h���N���X */
private: /* �萔�̒�` */
	static const float START_POS_X;		//�����ʒu( X )
	static const float START_POS_Y;		//�����ʒu( Y )
	static const float ENEMY_SIZE;		//�T�C�Y

	static const int SHOT_INTERVAL = 90;	//�e�̘A�����˂̊Ԋu
	static const int NUM_SCORE = 100;		//�l���X�R�A��

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CEnemyBoss();
	~CEnemyBoss() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

	void Death() override;	//���S���̏���

private: /* �����o�֐� */
	void Move();	//�ړ�

private: /* �����o�ϐ� */
	int m_nTimerInterval;	//�e�̘A�����˂̊Ԋu
};
#endif