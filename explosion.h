//================================================
//
//������H��b[explosion.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//***************************
//�C���N���[�h
//***************************
#include "object2D.h"

//***************************
//�����N���X�̒�`
//***************************
class CExplosion : public CObject2D
{/* CObject2D�̔h���N���X */
private: /* �萔�̒�` */
	static const float EXPLOSION_SIZE;	//�T�C�Y
	static const int DIVIDE_TEX_U = 8;	//�e�N�X�`���̕�����( U���� )

public: /* �ÓI�����o�֐� */
	static CExplosion* Create(D3DXVECTOR3 pos);	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CExplosion();
	~CExplosion() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �����o�ϐ� */
	int m_nCntAnim;
	int m_nPtnAnim;
};

#endif