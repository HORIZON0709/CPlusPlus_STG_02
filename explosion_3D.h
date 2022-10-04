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
	static const float EXPLOSION_SIZE;	//�T�C�Y
	static const int DIVIDE_TEX_U;		//�e�N�X�`���̕�����( U���� )

public: /* �ÓI�����o�֐� */
	static CExplosion3D* Create(D3DXVECTOR3 pos);	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CExplosion3D();
	~CExplosion3D() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �����o�ϐ� */
	int m_nCntAnim;		//�e�N�X�`���A�j���[�V�����p�J�E���g
	int m_nPtnAnim;		//�p�^�[���ԍ�
};
#endif