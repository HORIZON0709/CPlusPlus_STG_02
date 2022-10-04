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

	static const int NUM_SCORE;		//�l���X�R�A��
	static const int DIVIDE_TEX_U;	//�e�N�X�`���̕�����( U���� )
	static const int ANIM_SPEED;	//�A�j���[�V�������x

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
	void TexAnim();				//�e�N�X�`���A�j���[�V����
	void OverRimitRight();		//��ʉE�[�𒴂������ǂ���
	void ReleaseOffScreen();	//��ʊO�ɏo����������

private: /* �����o�ϐ� */
	/*
		��ʓ��ɓ����Ă������ǂ���
		false ---> ��ʊO
		true ---> ��ʓ�
	*/
	bool m_bInside;

	int m_nCntAnim;	//�A�j���[�V�����J�E���g
	int m_nPtnAnim;	//�p�^�[���ԍ�
};
#endif