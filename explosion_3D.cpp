//================================================
//
//������H��b[explosion_3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "explosion_3D.h"
#include "renderer.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CExplosion3D::EXPLOSION_SIZE = 60.0f;	//�T�C�Y

//================================================
//����
//================================================
CExplosion3D* CExplosion3D::Create(D3DXVECTOR3 pos)
{
	CExplosion3D* pExplosion3D = nullptr;	//�|�C���^

	if (pExplosion3D != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pExplosion3D = new CExplosion3D;	//�������̓��I�m��

	pExplosion3D->Init();	//������

	pExplosion3D->SetPos(pos);	//�ʒu��ݒ�

	return pExplosion3D;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CExplosion3D::CExplosion3D():
	m_nCntAnim(0),
	m_nPtnAnim(0)
{
	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::EXPLOSION);
}

//================================================
//�f�X�g���N�^
//================================================
CExplosion3D::~CExplosion3D()
{
}

//================================================
//������
//================================================
HRESULT CExplosion3D::Init()
{
	CObject3D::Init();	//�e�N���X

	//�T�C�Y��ݒ�
	D3DXVECTOR2 size = D3DXVECTOR2(EXPLOSION_SIZE, EXPLOSION_SIZE);
	CObject3D::SetSize(size);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::explosion000);

	//�e�N�X�`�����W�̐ݒ�
	CObject3D::SetTexUV(DIVIDE_TEX_U, 0);

	return S_OK;
}

//================================================
//�I��
//================================================
void CExplosion3D::Uninit()
{
	CObject3D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CExplosion3D::Update()
{
	CObject3D::Update();	//�e�N���X

	m_nCntAnim++;	//�J�E���g�A�b�v

	if (m_nCntAnim % 5 == 0)
	{//���Ԋu
		//�p�^�[���ԍ����X�V����
		m_nPtnAnim = (m_nPtnAnim + 1) % DIVIDE_TEX_U;

		//�e�N�X�`�����W�̐ݒ�
		CObject3D::SetTexUV(DIVIDE_TEX_U, m_nPtnAnim);
	}

	if (m_nPtnAnim == (DIVIDE_TEX_U - 1))
	{//�A�j���[�V�������I�������
 		Release();	//���
	}
}

//================================================
//�`��
//================================================
void CExplosion3D::Draw()
{
	CObject3D::Draw();	//�e�N���X
}