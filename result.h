//================================================
//
//������H��b[result.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//***************************
//�C���N���[�h
//***************************
#include "mode.h"

#include <d3dx9.h>

//***************************
//�O���錾
//***************************

//***************************
//���U���g�N���X�̒�`
//***************************
class CResult : public CMode
{/* CMode�̔h���N���X */
public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CResult();
	~CResult() override;

public: /* �����o�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private: /* �����o�ϐ� */
	
};
#endif