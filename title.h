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

//***************************
//�^�C�g���N���X�̒�`
//***************************
class CTitle : public CMode
{/* CMode�̔h���N���X */
public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CTitle();
	~CTitle() override;

public: /* �����o�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �����o�ϐ� */
	
};
#endif