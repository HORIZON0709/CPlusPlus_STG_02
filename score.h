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
//�O���錾
//***************************
class CNumber;

//***************************
//�X�R�A�N���X�̒�`
//***************************
class CScore : public CObject
{/* CObject�̔h���N���X */
private: /* �萔�̒�` */
	static const int MAX_DIGIT = 8;	//�ő包��

public: /* �ÓI�����o�֐� */
	static CScore* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CScore();
	~CScore()override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

public: /* �����o�֐� */
	/*
		�X�R�A�̃Z�b�g
		const int &nScore ---> �X�R�A
	*/
	void SetScore(const int &nScore);

	/*
		�X�R�A���Z
		const int &nValue ---> ���Z����l
	*/
	void AddScore(const int &nValue);

	int GetCurrentScore();	//���݂̃X�R�A�̎擾

private: /* �����o�ϐ� */
	CNumber* m_apNumber[MAX_DIGIT];	//�������p��
	int m_nScore;					//�X�R�A
};
#endif