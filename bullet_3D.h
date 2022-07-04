//================================================
//
//������H��b[bullet_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _BULLET_3D_H_
#define _BULLET_3D_H_

//***************************
//�C���N���[�h
//***************************
#include "object3D.h"

//***************************
//�e�N���X�̒�`
//***************************
class CBullet3D : public CObject3D
{/* CObject3D�̔h���N���X */
private: /* �萔�̒�` */
	static const float BULLET_SIZE;	//�T�C�Y

public: /* �ÓI�����o�֐� */
	static CBullet3D* Create(D3DXVECTOR3 pos, CObject::OBJ_TYPE haveType);	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CBullet3D();
	~CBullet3D() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �����o�֐� */
	void Collision();

public:	/* Set�EGet�n */
	void SetHaveType(CObject::OBJ_TYPE haveType);
	CObject::OBJ_TYPE GetHaveType();

private: /* �����o�ϐ� */
	CObject::OBJ_TYPE m_haveType;	//���L��
};
#endif