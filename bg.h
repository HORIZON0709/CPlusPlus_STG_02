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
#include "object.h"

//***************************
//�O���錾
//***************************
class CObject2D;

//***************************
//�w�i�N���X�̒�`
//***************************
class CBg : public CObject
{/* Cobject�̔h���N���X */
public: /* �ÓI�����o�֐� */
	static CBg* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CBg();
	~CBg() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �ÓI�����o�ϐ� */
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_OBJECT];

private: /* �����o�ϐ� */
	CObject2D* m_apObject2D[MAX_OBJECT];
};


#endif