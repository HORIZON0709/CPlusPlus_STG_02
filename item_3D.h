//================================================
//
//������H��b[item_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ITEM_3D_H_
#define _ITEM_3D_H_

//***************************
//�C���N���[�h
//***************************
#include "object3D.h"

//***************************
//�A�C�e���N���X�̒�`
//***************************
class CItem3D : public CObject3D
{/* Cobject3D�̔h���N���X */
private: /* �萔�̒�` */
	static const float ITEM_SIZE;	//�T�C�Y

public: /* �ÓI�����o�֐� */
	static CItem3D* Create(const D3DXVECTOR3 &pos);	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CItem3D();
	~CItem3D() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
};
#endif