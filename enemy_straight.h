//================================================
//
//������H��b[enemy_straight.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ENEMY_STRAIGHT_H_
#define _ENEMY_STRAIGHT_H_

//***************************
//�C���N���[�h
//***************************
#include "enemy_3D.h"

//***************************
//�G�N���X�̒�`
//***************************
class CEnemyStraight : public CEnemy3D
{/* CEnemy3D�̔h���N���X */
public: /* �萔�̒�` */
	static const float START_POS_X;		//�����ʒu( X )
	static const float START_POS_Y;		//�����ʒu( Y )
private:
	static const float ENEMY_SIZE;		//�T�C�Y
	static const float MOVE_SPEED_X;	//�ړ��X�s�[�h( X )

	static const int NUM_SCORE = 10;		//�l���X�R�A��

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CEnemyStraight();
	~CEnemyStraight() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
	void Death() override;		//���S���̏���
	
private: /* �����o�֐� */
	void Move();				//�ړ�
	void OverRimitRight();		//��ʉE�[�𒴂������ǂ���
	void ReleaseOffScreen();	//��ʊO�ɏo����������

private: /* �����o�ϐ� */
	/*
		��ʓ��ɓ����Ă������ǂ���
		false ---> ��ʊO
		true ---> ��ʓ�
	*/
	bool m_bInside;
};
#endif