//================================================
//
//������H��b[enemy_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "enemy_3D.h"
#include "renderer.h"
#include "bullet_3D.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CEnemy3D::ENEMY_SIZE = 120.0f;	//�T�C�Y

//================================================
//����
//================================================
CEnemy3D* CEnemy3D::Create()
{
	CEnemy3D* pEnemy3D = nullptr;	//�|�C���^

	if (pEnemy3D != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pEnemy3D = new CEnemy3D;	//�������̓��I�m��

	pEnemy3D->Init();	//������

	//�ʒu��ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3((CRenderer::SCREEN_WIDTH * 0.8f), (CRenderer::SCREEN_HEIGHT * 0.5f), 0.0f);
	pEnemy3D->SetPos(pos);

	return pEnemy3D;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CEnemy3D::CEnemy3D():
	m_nTimerInterval(0)
{
	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::ENEMY);
}

//================================================
//�f�X�g���N�^
//================================================
CEnemy3D::~CEnemy3D()
{
}

//================================================
//������
//================================================
HRESULT CEnemy3D::Init()
{
	CObject3D::Init();	//�e�N���X

	//�T�C�Y��ݒ�
	CObject3D::SetSize(ENEMY_SIZE);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::TEXTURE_�S���Ⴄ);

	return S_OK;
}

//================================================
//�I��
//================================================
void CEnemy3D::Uninit()
{
	CObject3D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CEnemy3D::Update()
{
	CObject3D::Update();	//�e�N���X

	D3DXVECTOR3 pos = CObject3D::GetPos();	//�ʒu�����擾

	m_nTimerInterval++;	//�^�C�}�[��i�߂�

	if (m_nTimerInterval % SHOT_INTERVAL == 0)
	{//�^�C�}�[����莞�ԂɂȂ�����
		CBullet3D::Create(pos, CObject::OBJ_TYPE::ENEMY);	//�e�̐���
	}
}

//================================================
//�`��
//================================================
void CEnemy3D::Draw()
{
	CObject3D::Draw();	//�e�N���X
}