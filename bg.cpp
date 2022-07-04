//================================================
//
//������H��b[bg.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "bg.h"
#include "object2D.h"
#include "application.h"
#include "renderer.h"

//***************************
//�ÓI�����o�ϐ�
//***************************
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_OBJECT] = {};

//================================================
//����
//================================================
CBg* CBg::Create()
{
	CBg* pBg = nullptr;	//�|�C���^

	//if (pBg != nullptr)
	//{//NULL�`�F�b�N
	//	assert(false);
	//}

	///* nullptr�̏ꍇ */

	//pBg = new CBg;	//�������̓��I�m��

	//pBg->Init();	//������

	return pBg;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CBg::CBg()
{
	//�����o�ϐ��̃N���A
	memset(&m_apTexture[0], 0, sizeof(m_apTexture));
	memset(&m_apObject2D[0], 0, sizeof(m_apObject2D));
}

//================================================
//�f�X�g���N�^
//================================================
CBg::~CBg()
{
}

//================================================
//������
//================================================
HRESULT CBg::Init()
{
	////�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	////���_�o�b�t�@�̐���
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//							D3DUSAGE_WRITEONLY,
	//							FVF_VERTEX_2D,
	//							D3DPOOL_MANAGED,
	//							&m_pVtxBuff,
	//							NULL);

	//VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////���_����ݒ�
	//pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	////rhw�̐ݒ�
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////���_�J���[�̐ݒ�
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	////�e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	////���_�o�b�t�@���A�����b�N����
	//m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�I��
//================================================
void CBg::Uninit()
{
	////���_�o�b�t�@�̔j��
	//if (m_pVtxBuff != nullptr)
	//{
	//	m_pVtxBuff->Release();
	//	m_pVtxBuff = nullptr;
	//}

	////�e�N�X�`���̔j��
	//if (m_pTexture != nullptr)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = nullptr;
	//}
}

//================================================
//�X�V
//================================================
void CBg::Update()
{
	
}

//================================================
//�`��
//================================================
void CBg::Draw()
{
	////�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	////���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	////���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//CTexture* pTexture = CApplication::GetTexture();	//�e�N�X�`�����擾

	////�e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	////�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
	//						0,					//�`�悷��ŏ��̒��_�C���f�b�N�X
	//						2);					//�`�悷��v���~�e�B�u��
}