//================================================
//
//������H��b[enemy.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//***************************
//�C���N���[�h
//***************************
#include "object2D.h"

//***************************
//�G�N���X�̒�`
//***************************
class CEnemy : public CObject2D
{/* CObject2D�̔h���N���X */
private: /* �萔�̒�` */
	static const float ENEMY_SIZE;	//�T�C�Y

public: /* �ÓI�����o�֐� */
	static CEnemy* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CEnemy();
	~CEnemy() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
};
#endif