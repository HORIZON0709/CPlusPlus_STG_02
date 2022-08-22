//================================================
//
//������H��b[mode.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _MODE_H_
#define _MODE_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>

//***************************
//�O���錾
//***************************
class CGame;

//***************************
//���[�h�N���X�̒�`
//***************************
class CMode
{/* ��{�N���X */
public: /* �񋓌^�̒�` */
	enum MODE	//���[�h�̎��
	{
		TITLE = 0,	//�^�C�g��
		GAME,		//�Q�[��
		RESULT,		//���U���g
		MAX
	};

public: /* �ÓI�����o�֐� */
	/*
		���[�h�̐ݒ�
		MODE mode ---> ���[�h�̎��
	*/
	static void SetMode(MODE mode);

	//�Q�[�����̎擾
	static CGame* GetGame();

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CMode();
	virtual ~CMode();

public: /* ���z�֐� */
	virtual HRESULT Init();	//������
	virtual void Uninit();	//�I��
	virtual void Update();	//�X�V
	virtual void Draw();	//�`��

private: /* �ÓI�����o�ϐ� */
	
	//********** �|�C���^ **********//

	//static CTitle* m_pTitle;	//�^�C�g��
	static CGame* m_pGame;		//�Q�[��
	//static CResult* m_pResult;	//���U���g
};
#endif