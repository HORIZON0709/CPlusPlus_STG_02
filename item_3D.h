//================================================
//
//������H��b[item_3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _ITEM_3D_H_
#define _ITEM_3D_H_

//***************************
//�C���N���[�h
//***************************
#include "object3D.h"

//***************************
//�A�C�e���N���X�̒�`
//***************************
class CItem3D : public CObject3D
{/* Cobject3D�̔h���N���X */
public: /* �񋓌^�̒�` */
	enum TYPE	/* �A�C�e���̎�� */
	{
		CHANGE_BUlLET_NORMAL = 0,	//�ʏ�e�ɕω�
		CHANGE_BUlLET_DOUBLE,		//��A�e�ɕω�
		CHANGE_BUlLET_TRIPLE,		//�O�����g�U�e�ɕω�
		MAX,
		NONE
	};

private: /* �萔�̒�` */
	static const float ITEM_SIZE;	//�T�C�Y

public: /* �ÓI�����o�֐� */
	static CItem3D* Create(const D3DXVECTOR3 &pos);	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CItem3D();
	~CItem3D() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
};
#endif