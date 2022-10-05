//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// Author : KIshimoto Eiji
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CTexture
{
public: /* ��` */
	enum TEXTURE
	{
		NONE = -1,	//�g�p���Ȃ�

		/* �v���C���[ */
		player000 = 0,	//���`���`�̗]����(��)

		/* �e */
		bullet000,	//���̃T�[�N��(��)
		bullet001,	//�X���b�N�̃A�C�R��(��)
		bullet002,	//�z�z�̒e(��)
		bullet003,	//�C�e(��)
		bullet004,	//�C�e(�ԍ�)
		bullet005,	//�΋�(�ԍ�)

		/* ���� */
		explosion000,	//�z�z�̔����A�j���[�V�����摜(��)
		explosion001,	//�����A�j���[�V�����摜(������ : �c8 * ��5)
		explosion002,	//�����A�j���[�V�����摜(������ : �c10 * ��5)

		/* �G */
		enemy000,	//�S���Ⴄ�l�^�摜�̂��(��)
		enemy001,	//�z�z�̃J�j(��)
		enemy002,	//�{�X
		enemy003,	//��

		/* �w�i */
		bg000,	//�������j�o�[�X(��)
		bg001,	//���w�i�F�^�C�g��
		bg002,	//���w�i�F���U���g

		/* �A�C�e�� */
		item000,	//�O�p�`(��)
		item001,	//�ʏ�e�ɕύX(��)
		item002,	//��A�e�ɕύX(��)
		item003,	//�O�A�e�U�e�ɕύX(��)

		/* �i���o�[ */
		number000,	//0�`9�̐���(������)

		MAX
	};

	static const char* s_FileName[];	// �t�@�C���p�X

public:
	CTexture();		// �f�t�H���g�R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

public: /* �����o�֐� */
	void LoadAll();										// �S�Ă̓ǂݍ���
	void Load(TEXTURE inTexture);						// �w��̓ǂݍ���
	void ReleaseAll();									// �S�Ă̔j��
	void Release(TEXTURE inTexture);					// �w��̔j��
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// ���̎擾

private: /* �����o�ϐ� */
	LPDIRECT3DTEXTURE9 s_pTexture[MAX];	// �e�N�X�`���̏��
};

#endif // !_TEXTURE_H_
