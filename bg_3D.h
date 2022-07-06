//================================================
//
//������H��b[bg_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _BG_3D_H_
#define _BG_3D_H_

//***************************
//�C���N���[�h
//***************************
#include "object3D.h"

//***************************
//�w�i�N���X�̒�`
//***************************
class CBg3D : public CObject3D
{/* Cobject3D�̔h���N���X */
private: /* �萔�̒�` */
	static const float BG_WIDTH;	//����
	static const float BG_HEIGHT;	//�c��

public: /* �ÓI�����o�֐� */
	static CBg3D* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CBg3D();
	~CBg3D() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
};
#endif