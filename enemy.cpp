//================================================
//
//������H��b[enemy.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "enemy.h"
#include "renderer.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CEnemy::ENEMY_SIZE = 120.0f;	//�T�C�Y

//================================================
//����
//================================================
CEnemy* CEnemy::Create()
{
	CEnemy* pEnemy = nullptr;	//�|�C���^

	if (pEnemy != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pEnemy = new CEnemy;	//�������̓��I�m��

	pEnemy->Init();	//������

	D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.5f), (CRenderer::SCREEN_HEIGHT * 0.2f), 0.0f);
	pEnemy->SetPos(pos);	//�ʒu��ݒ�

	return pEnemy;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CEnemy::CEnemy()
{
	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::ENEMY);
}

//================================================
//�f�X�g���N�^
//================================================
CEnemy::~CEnemy()
{
}

//================================================
//������
//================================================
HRESULT CEnemy::Init()
{
	CObject2D::Init();	//�e�N���X

	//�T�C�Y��ݒ�
	CObject2D::SetSize(ENEMY_SIZE);

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_�S���Ⴄ);

	return S_OK;
}

//================================================
//�I��
//================================================
void CEnemy::Uninit()
{
	CObject2D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CEnemy::Update()
{
	CObject2D::Update();	//�e�N���X
}

//================================================
//�`��
//================================================
void CEnemy::Draw()
{
	CObject2D::Draw();	//�e�N���X
}