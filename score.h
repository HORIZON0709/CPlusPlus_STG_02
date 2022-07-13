//================================================
//
//������H��b[score.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//***************************
//�C���N���[�h
//***************************
#include "object.h"

//***************************
//�X�R�A�N���X�̒�`
//***************************
class CScore : public CObject
{/* CObject�̔h���N���X */
public: /* �ÓI�����o�֐� */
	static CScore* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CScore();
	~CScore();

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

public: /* �����o�֐� */
	void Set(const int &nScore);	//�Z�b�g
	void Add(const int &nValue);	//�X�R�A���Z
	int Get();				//�擾

private: /* �����o�ϐ� */
	//CNumber* m_apNumber[8];	//�������p��
	int m_nScore;				//�X�R�A
};


#endif