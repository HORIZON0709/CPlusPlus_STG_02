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
		int nScore ---> �X�R�A
	*/
	void SetScore(int nScore);

	/*
		�X�R�A���Z
		int nValue ---> ���Z����l
	*/
	void AddScore(int nValue);

	int GetCurrentScore();	//���݂̃X�R�A�̎擾
private:
	void ChangeTexUV();	//���݂̃X�R�A�ɉ������e�N�X�`�����W�̕ύX

private: /* �����o�ϐ� */
	CNumber* m_apNumber[MAX_DIGIT];	//�������p��
	int m_nScore;					//�X�R�A
};
#endif