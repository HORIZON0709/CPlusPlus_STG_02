//================================================
//
//������H��b[explosion_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _EXPLOSION_3D_H_
#define _EXPLOSION_3D_H_

//***************************
//�C���N���[�h
//***************************
#include "object3D.h"

//***************************
//�����N���X�̒�`
//***************************
class CExplosion3D : public CObject3D
{/* CObject3D�̔h���N���X */
private: /* �萔�̒�` */
	static const int ANIM_SPEED;	//�A�j���[�V�������x

public: /* �ÓI�����o�֐� */
	/*
		����
		const D3DXVECTOR3 &pos ---> �ʒu
		const D3DXVECTOR3 &size ---> �T�C�Y
		const CTexture::TEXTURE &texture ---> �e�N�X�`��
	*/
	static CExplosion3D* Create(
		const D3DXVECTOR3 &pos,
		const D3DXVECTOR3 &size,
		const CTexture::TEXTURE &texture);

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CExplosion3D();
	~CExplosion3D() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �ÓI�����o�ϐ� */
	static CTexture::TEXTURE m_tex;	//�e�N�X�`��

private: /* �����o�ϐ� */
	int m_nDivideTexU;	//�e�N�X�`���̕�����( U���� )
	int m_nDivideTexV;	//�e�N�X�`���̕�����( V���� )
	int m_nNumPtnAll;	//�e�N�X�`���̑��p�^�[����
	int m_nCntAnim;		//�e�N�X�`���A�j���[�V�����p�J�E���g
	int m_nPtnAnim;		//�p�^�[���ԍ�
};
#endif