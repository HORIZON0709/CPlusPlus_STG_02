//================================================
//
//������H��b[explosion.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "explosion.h"
#include "renderer.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CExplosion::EXPLOSION_SIZE = 60.0f;	//�T�C�Y

//================================================
//����
//================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion* pExplosion = nullptr;	//�|�C���^

	if (pExplosion != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pExplosion = new CExplosion;	//�������̓��I�m��

	pExplosion->Init();	//������

	pExplosion->SetPos(pos);	//�ʒu��ݒ�

	return pExplosion;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CExplosion::CExplosion():
	m_nCntAnim(0),
	m_nPtnAnim(0)
{
	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::EXPLOSION);
}

//================================================
//�f�X�g���N�^
//================================================
CExplosion::~CExplosion()
{
}

//================================================
//������
//================================================
HRESULT CExplosion::Init()
{
	CObject2D::Init();	//�e�N���X

	//�T�C�Y��ݒ�
	CObject2D::SetSize(EXPLOSION_SIZE);

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_explosion000);

	//�e�N�X�`�����W�̐ݒ�
	CObject2D::SetTexUV(DIVIDE_TEX_U, 0);

	return S_OK;
}

//================================================
//�I��
//================================================
void CExplosion::Uninit()
{
	CObject2D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CExplosion::Update()
{
	CObject2D::Update();	//�e�N���X

	m_nCntAnim++;	//�J�E���g�A�b�v

	if (m_nCntAnim % 5 == 0)
	{//���Ԋu
		//�p�^�[���ԍ����X�V����
		m_nPtnAnim = (m_nPtnAnim + 1) % DIVIDE_TEX_U;

		//�e�N�X�`�����W�̐ݒ�
		CObject2D::SetTexUV(DIVIDE_TEX_U, m_nPtnAnim);
	}

	if (m_nPtnAnim == (DIVIDE_TEX_U - 1))
	{//�A�j���[�V�������I�������
 		Release();	//���
	}
}

//================================================
//�`��
//================================================
void CExplosion::Draw()
{
	CObject2D::Draw();	//�e�N���X
}