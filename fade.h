//================================================
//
//������H��b[fade.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _FADE_H_
#define _FADE_H_

//***************************
//�C���N���[�h
//***************************
#include "object2D.h"

//***************************
//�w�i�N���X�̒�`
//***************************
class CFade
{/* ��{�N���X */
private: /* �萔�̒�` */
	static const float FADE_WIDTH;	//����
	static const float FADE_HEIGHT;	//�c��

public: /* �ÓI�����o�֐� */
	static CFade* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CFade();
	~CFade();

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init();	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

private: /* �����o�ϐ� */
	CObject2D* m_pPolygon;	//�t�F�[�h�p�|���S��
};
#endif