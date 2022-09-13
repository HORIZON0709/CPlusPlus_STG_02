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
class CFade : public CObject2D
{/* CObject2D�̔h���N���X */
public: /* �񋓌^�̒�` */	
	enum STATE	//�t�F�[�h���
	{
		NONE = -1,		//�t�F�[�h���Ă��Ȃ�
		FADE_IN = 0,	//�t�F�[�h�C��
		FADE_OUT,		//�t�F�[�h�A�E�g
		MAX
	};

private: /* �萔�̒�` */
	static const float FADE_WIDTH;	//����
	static const float FADE_HEIGHT;	//�c��

public: /* �ÓI�����o�֐� */
	static CFade* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CFade();
	~CFade() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

public: /* �����o�֐� */
	/*
		�ݒ�
		const STATE &state ---> �t�F�[�h���
	*/
	void Set(const STATE &state);

private: /* �����o�ϐ� */
	STATE m_state;	//�t�F�[�h���
};
#endif