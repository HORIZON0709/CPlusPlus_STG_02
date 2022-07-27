//================================================
//
//������H��b[enemy_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ENEMY_3D_H_
#define _ENEMY_3D_H_

//***************************
//�C���N���[�h
//***************************
#include "object3D.h"

//***************************
//�G�N���X�̒�`
//***************************
class CEnemy3D : public CObject3D
{/* CObject3D�̔h���N���X */
public: /* �񋓌^�̒�` */
	enum ENM_TYPE /* �G�̎�� */
	{
		CURVE = 0,	//sin�J�[�u
		MAX,
		NONE
	};

public: /* �ÓI�����o�֐� */
	/*
		����
		const ENM_TYPE &type ---> �G�̎��
		const int nNum ---> ������
	*/
	static CEnemy3D* Create(const ENM_TYPE &type);

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CEnemy3D();
	~CEnemy3D() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

public: /* �����o�֐� */
	/*
		�G�̎�ނ�ݒ�
		const ENM_TYPE &type ---> �C�ӂ̓G�̎��
	*/
	void SetEnmType(const ENM_TYPE &type);

	/*
		�G�̎�ނ��擾
	*/
	ENM_TYPE GetEnmType();

private: /* �����o�ϐ� */
	ENM_TYPE m_type;	//���
};
#endif