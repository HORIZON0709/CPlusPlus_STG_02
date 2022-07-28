//================================================
//
//������H��b[enemy_curve.h]
//Author:Kishimoto Eiji Danian
//
//================================================
#ifndef _ENEMY_CURVE_H_
#define _ENEMY_CURVE_H_

//***************************
//�C���N���[�h
//***************************
#include "enemy_3D.h"

//***************************
//�G�N���X�̒�`
//***************************
class CEnemyCurve : public CEnemy3D
{/* CEnemy3D�̔h���N���X */
public: /* �萔�̒�` */
	static const int MAX_ENEMY_CURVE = 8;	//�J�[�u�G�̍ő吔
private:
	static const float START_POS_X;		//�����ʒu( X )
	static const float START_POS_Y;		//�����ʒu( Y )
	static const float ENEMY_SIZE;		//�T�C�Y
	static const float CURVE_SIZE;		//�J�[�u�̑傫��
	static const float MOVE_SPEED_X;	//�ړ��X�s�[�h( X )
	static const float MOVE_SPEED_Y;	//�ړ��X�s�[�h( Y )

	static const int SHOT_INTERVAL = 90;	//�e�̘A�����˂̊Ԋu
	static const int NUM_SCORE = 10;		//�l���X�R�A��

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CEnemyCurve();
	~CEnemyCurve() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �����o�ϐ� */
	int m_nTimerInterval;	//�e�̘A�����˂̊Ԋu
	float m_fCurve;			//�J�[�u�̋
};
#endif