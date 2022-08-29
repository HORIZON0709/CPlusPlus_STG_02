//================================================
//
//������H��b[bg.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _BG_H_
#define _BG_H_

//***************************
//�C���N���[�h
//***************************
#include "object2D.h"

//***************************
//�w�i�N���X�̒�`
//***************************
class CBg : public CObject2D
{/* CObject2D�̔h���N���X */
public: /* �萔�̒�` */
	static const float BG_WIDTH;	//����
	static const float BG_HEIGHT;	//�c��

public: /* �ÓI�����o�֐� */
	/*
		����
		CTexture::TEXTURE texture ---> �g�p����e�N�X�`��
	*/
	static CBg* Create(CTexture::TEXTURE texture);

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CBg();
	~CBg()override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
};
#endif