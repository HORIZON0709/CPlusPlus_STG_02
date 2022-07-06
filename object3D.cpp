//================================================
//
//������H��b[object3D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "object3D.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//================================================
//����
//================================================
CObject3D* CObject3D::Create()
{
	CObject3D* pObject3D = nullptr;	//�|�C���^

	if (pObject3D != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pObject3D = new CObject3D;	//�������̓��I�m��

	pObject3D->Init();	//������

	return pObject3D;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CObject3D::CObject3D() :
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_texture(CTexture::TEXTURE_NONE),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f,0.0f))
{
	memset(m_mtxWorld, 0, sizeof(m_mtxWorld));
}

//================================================
//�f�X�g���N�^
//================================================
CObject3D::~CObject3D()
{
	/* ����R��̊m�F */
	assert(m_pTexture == nullptr);
	assert(m_pVtxBuff == nullptr);
}

//================================================
//������
//================================================
HRESULT CObject3D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�����o�ϐ��̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_texture = CTexture::TEXTURE_NONE;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_3D,
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�I��
//================================================
void CObject3D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//================================================
//�X�V
//================================================
void CObject3D::Update()
{
	
}

//================================================
//�`��
//================================================
void CObject3D::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���C�g��؂�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	CTexture* pTexture = CApplication::GetTexture();	//�e�N�X�`�����擾

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
							0,					//�`�悷��ŏ��̒��_�C���f�b�N�X
							2);					//�`�悷��v���~�e�B�u��

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);
}

//================================================
//�ʒu��ݒ�
//================================================
void CObject3D::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}

//================================================
//�ʒu���擾
//================================================
D3DXVECTOR3 CObject3D::GetPos()
{
	return m_pos;
}

//================================================
//�e�N�X�`���̐ݒ�
//================================================
void CObject3D::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//================================================
//�e�N�X�`�����W�̐ݒ�(�A�j���[�V�����ɑΉ�)
//================================================
void CObject3D::SetTexUV(const int &nDivNum, const int &nPtnAnim)
{
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

 	float fDivide = (1.0f / nDivNum);	//��Z�p��float�ɕϊ�

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fDivide * nPtnAnim,		0.0f);
	pVtx[1].tex = D3DXVECTOR2(fDivide * (nPtnAnim + 1), 0.0f);
 	pVtx[2].tex = D3DXVECTOR2(fDivide * nPtnAnim,		1.0f);
	pVtx[3].tex = D3DXVECTOR2(fDivide * (nPtnAnim + 1), 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�T�C�Y�̐ݒ�
//================================================
void CObject3D::SetSize(const D3DXVECTOR2 &size)
{
	m_size = size;	//�T�C�Y��ݒ�

	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fWidthHalf = (m_size.x * 0.5f);	//�����̔���
	float fHeightHalf = (m_size.y * 0.5f);	//�c���̔���

	//���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(-fWidthHalf, +fHeightHalf, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+fWidthHalf, +fHeightHalf, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fWidthHalf, -fHeightHalf, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+fWidthHalf, -fHeightHalf, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�T�C�Y�̎擾
//================================================
D3DXVECTOR2 CObject3D::GetSize()
{
	return m_size;
}

//================================================
//�ړ��ʂ̐ݒ�
//================================================
void CObject3D::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//================================================
//�ړ��ʂ̎擾
//================================================
D3DXVECTOR3 CObject3D::GetMove()
{
	return m_move;
}