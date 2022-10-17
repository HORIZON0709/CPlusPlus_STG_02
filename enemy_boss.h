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
private: /* �񋓌^�̒�` */
	enum STATE	/* ��� */
	{
		NONE = -1,
		NORMAL = 0,	//�ʏ���
		DAMAGE,		//�_���[�W���
		MAX
	};

public: /* �萔�̒�` */
	static const float START_POS_X;		//�����ʒu( X )
	static const float START_POS_Y;		//�����ʒu( Y )
private:
	static const float ENEMY_SIZE;		//�T�C�Y
	static const float CURVE_SIZE;		//�J�[�u�̑傫��
	static const float MOVE_SPEED_X;	//�ړ��X�s�[�h( X )
	static const float MOVE_SPEED_Y;	//�ړ��X�s�[�h( Y )
	static const float SHOT_SPEED;		//�e�̃X�s�[�h

	static const int SHOT_INTERVAL;	//�e�̘A�����˂̊Ԋu
	static const int NUM_SCORE;		//�l���X�R�A��
	static const int NUM_BULLETS;	//�������ː�
	static const int MAX_LIFE;		//�̗͂̍ő�l

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CEnemyBoss();
	~CEnemyBoss() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
	void Death() override;		//���S���̏���

public: /* �����o�֐� */
	/*
		�̗͂̌��Z
		int nDamage ---> �_���[�W��
	*/
	void SubLife(int nDamage);

	int GetLife();	//�̗͂̎擾
private:
	void Move();	//�ړ�
	void Shot();	//�e�̔���
	void State();	//��Ԗ��̏���

private: /* �����o�ϐ� */
	float m_fCurve;			//�J�[�u�x��

	int m_nTimerInterval;	//�e�̘A�����˂̊Ԋu
	int m_nLife;			//�̗�
	int m_nCnt;				//�J�E���g

	STATE m_state;	//���
};
#endif