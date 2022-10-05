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
#include "application.h"
#include "renderer.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CExplosion3D::EXPLOSION_SIZE = 120.0f;	//�T�C�Y

const int CExplosion3D::ANIM_SPEED = 1;		//�A�j���[�V�������x

//***************************
//�ÓI�����o�ϐ�
//***************************
CTexture::TEXTURE CExplosion3D::m_tex = CTexture::TEXTURE::NONE;	//�e�N�X�`��

//================================================
//����
//================================================
CExplosion3D* CExplosion3D::Create(const D3DXVECTOR3 &pos, const CTexture::TEXTURE &texture)
{
	CExplosion3D* pExplosion3D = nullptr;	//�|�C���^

	if (pExplosion3D != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pExplosion3D = new CExplosion3D;	//�������̓��I�m��

	m_tex = texture;	//���̃e�N�X�`������ۑ�

	pExplosion3D->Init();	//������

	pExplosion3D->SetPos(pos);	//�ʒu��ݒ�

	return pExplosion3D;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CExplosion3D::CExplosion3D():
	m_nDivideTexU(0),
	m_nDivideTexV(0),
	m_nNumPtnAll(0),
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

	//�����o�ϐ��̏�����
	m_nCntAnim = 0;
	m_nPtnAnim = 0;

	//�T�C�Y��ݒ�
	D3DXVECTOR2 size = D3DXVECTOR2(EXPLOSION_SIZE, EXPLOSION_SIZE);
	CObject3D::SetSize(size);

	//�e�N�X�`���̍��W
	CObject3D::SetTexture(m_tex);

	if (m_tex == CTexture::TEXTURE::explosion001)
	{
		//��������ݒ�
		m_nDivideTexU = 5;	//U����
		m_nDivideTexV = 8;	//V����
	}
	else if (m_tex == CTexture::TEXTURE::explosion002)
	{
		//��������ݒ�
		m_nDivideTexU = 5;	//U����
		m_nDivideTexV = 10;	//V����
	}

	//���p�^�[������ݒ�
	m_nNumPtnAll = (m_nDivideTexU * m_nDivideTexV);

	//�e�N�X�`�����W�̐ݒ�
	CObject3D::SetTexUV(m_nDivideTexU, m_nDivideTexV, 0);

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

	if (m_nCntAnim % ANIM_SPEED == 0)
	{//���Ԋu
		//�p�^�[���ԍ����X�V����
		m_nPtnAnim = (m_nPtnAnim + 1) % m_nNumPtnAll;

		//�e�N�X�`�����W�̐ݒ�
		CObject3D::SetTexUV(m_nDivideTexU, m_nDivideTexV, m_nPtnAnim);
	}

	if (m_nPtnAnim == (m_nNumPtnAll - 1))
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