//================================================
//
//������H��b[title.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//***************************
//�C���N���[�h
//***************************
#include "mode.h"

#include <d3dx9.h>

//***************************
//�O���錾
//***************************
class CObject2D;
class CBg;

//***************************
//�^�C�g���N���X�̒�`
//***************************
class CTitle : public CMode
{/* CMode�̔h���N���X */
private: /* �萔�̒�` */
	static const float LOGO_WIDTH;	//���S�̕�
	static const float LOGO_HEIGHT;	//���S�̍���

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CTitle();
	~CTitle() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �ÓI�����o�ϐ� */
	static CBg* m_pBg;			//�w�i
	static CObject2D* m_pLogo;	//�^�C�g�����S

private: /* �����o�ϐ� */
	bool m_bFadeOut;	//�Ó]�������ǂ���
};
#endif