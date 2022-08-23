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
#include "item_3D.h"
#include "bullet_3D.h"

//***************************
//�v���C���[(3D)�N���X�̒�`
//***************************
class CPlayer3D : public CObject3D
{/* CObject3D�̔h���N���X */
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

public: /* �����o�֐� */
	/*
		�����A�C�e���̃Z�b�g
		const CItem3D::TYPE &item ---> ���肵���A�C�e���̃^�C�v
	*/
	void SetItem(const CItem3D::TYPE &item);

	CItem3D::TYPE GetItem();	//�����A�C�e���̎擾
private:
	void Move();					//�ړ�
	void Shot();					//����
	void CreateBulletByType();		//�^�C�v�ʂ̒e�̐���
	void SetNormalBullet();			//�ʏ�e�̐ݒ�
	void SetDoubleBullet();			//��A�e�̐ݒ�
	void SetTripleBullet();			//�O�����e�U�e�̐ݒ�
	void ProcessingForEachItem();	//�A�C�e�����̏���

private: /* �����o�ϐ� */
	int m_nTimerInterval;			//�e�̘A�����˂̊Ԋu
	CItem3D::TYPE m_getItem;		//�擾�����A�C�e��
	CBullet3D::TYPE m_bulletType;	//�e�̃^�C�v
};
#endif