//================================================
//
//������H��b[player.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//***************************
//�C���N���[�h
//***************************
#include "object2D.h"

//***************************
//�v���C���[�N���X�̒�`
//***************************
class CPlayer : public CObject2D
{/* CObject2D�̔h���N���X */
private: /* �萔�̒�` */
	static const float PLAYER_SIZE;	//�T�C�Y
	static const float MOVE_SPEED;	//�ړ����x

public: /* �ÓI�����o�֐� */
	static CPlayer* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CPlayer();
	~CPlayer() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
};

#endif