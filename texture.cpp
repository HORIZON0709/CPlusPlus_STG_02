//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// Author : KIshimoto Eiji
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "renderer.h"
#include "texture.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const char* CTexture::s_FileName[] =
{// �e�N�X�`���̃p�X
	/* �v���C���[ */
	"data/TEXTURE/player000.jpg",	//���`���`�̗]����(��)

	/* �e */
	"data/TEXTURE/bullet000.png",	//���̃T�[�N��(��)
	"data/TEXTURE/bullet001.png",	//�X���b�N�̃A�C�R��(��)
	"data/TEXTURE/bullet002.png",	//�z�z�̒e(��)
	"data/TEXTURE/bullet003.png",	//�C�e(��)
	"data/TEXTURE/bullet004.png",	//�C�e(�ԍ�)
	"data/TEXTURE/bullet005.png",	//�΋�(�ԍ�)

	/* ���� */
	"data/TEXTURE/explosion000.png",	//�z�z�̔����A�j���[�V�����摜
	"data/TEXTURE/explosion001.png",	//�����A�j���[�V�����摜(������ : �c8 * ��5)
	"data/TEXTURE/explosion002.png",	//�����A�j���[�V�����摜(������ : �c10 * ��5)

	/* �G */
	"data/TEXTURE/enemy000.png",	//�S���Ⴄ�l�^�摜�̂��(��)
	"data/TEXTURE/enemy001.png",	//�z�z�̃J�j(��)
	"data/TEXTURE/enemy002.png",	//�{�X
	"data/TEXTURE/enemy003.png",	//��

	/* �w�i */
	"data/TEXTURE/bg000.jpeg",	//�������j�o�[�X(��)
	"data/TEXTURE/bg001.png",	//���w�i�F�^�C�g��
	"data/TEXTURE/bg003.png",	//���w�i�F���U���g

	/* �A�C�e�� */
	"data/TEXTURE/item000.png",	//�O�p�`(��)
	"data/TEXTURE/item001.png",	//�ʏ�e�ɕύX
	"data/TEXTURE/item002.png",	//��A�e�ɕύX
	"data/TEXTURE/item003.png",	//�O�A�e�U�e�ɕύX

	/* �i���o�[ */
	"data/TEXTURE/number000.png"	//0�`9�̐���(������)
};

static_assert(sizeof(CTexture::s_FileName) / sizeof(CTexture::s_FileName[0]) == CTexture::MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTexture::CTexture() :
	s_pTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CTexture::LoadAll()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	
	for (int i = 0; i < MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// �e�N�X�`���̓ǂݍ��݂�����Ă���
			continue;
		}

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CTexture::ReleaseAll(void)
{
	for (int i = 0; i < MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// �e�N�X�`���̉��
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTexture::Release(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < MAX);

	if (s_pTexture[inTexture] != NULL)
	{// �e�N�X�`���̉��
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = NULL;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE inTexture)
{
	if (inTexture == NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < MAX);

	// �ǂݍ���
	Load(inTexture);

	return s_pTexture[inTexture];
}
