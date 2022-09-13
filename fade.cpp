//================================================
//
//������H��b[fade.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "fade.h"
#include "renderer.h"

#include <assert.h>

//***************************
//�萔�̒�`
//***************************
const float CFade::FADE_WIDTH = CRenderer::SCREEN_WIDTH;	//����
const float CFade::FADE_HEIGHT = CRenderer::SCREEN_HEIGHT;	//�c��

//================================================
//����
//================================================
CFade* CFade::Create()
{
	CFade* pFade = nullptr;	//�|�C���^

	if (pFade != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pFade = new CFade;	//�������̓��I�m��

	pFade->Init();	//������

	return pFade;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CFade::CFade() :
	m_state(STATE::NONE)
{
	//�^�C�v�̐ݒ�
	CObject::SetObjType(CObject::OBJ_TYPE::FADE);
}

//================================================
//�f�X�g���N�^
//================================================
CFade::~CFade()
{
}

//================================================
//������
//================================================
HRESULT CFade::Init()
{
	//�����o�ϐ��̏�����
	m_state = STATE::NONE;

	//�ʒu��ݒ�
	D3DXVECTOR3 pos = D3DXVECTOR3(CRenderer::SCREEN_WIDTH * 0.5f,
								  CRenderer::SCREEN_HEIGHT * 0.5f,
								  0.0f);
	CObject2D::SetPos(pos);

	//�T�C�Y��ݒ�
	D3DXVECTOR2 size = D3DXVECTOR2(FADE_WIDTH, FADE_HEIGHT);
	CObject2D::SetSize(size);

	//�F��ݒ�
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	CObject2D::SetCol(col);

	return S_OK;
}

//================================================
//�I��
//================================================
void CFade::Uninit()
{
	CObject2D::Uninit();	//�e�N���X
}

//================================================
//�X�V
//================================================
void CFade::Update()
{
	CObject2D::Update();	//�e�N���X

	if (m_state == STATE::NONE)
	{//�t�F�[�h���Ă��Ȃ��ꍇ
		return;
	}

	/* �t�F�[�h���Ă���Ƃ� */

	D3DXCOLOR col = CObject2D::GetCol();	//�F���擾

	if (m_state == STATE::FADE_IN)
	{//�t�F�[�h�C��( �s���� ---> ���� )
		col.a -= 0.01f;	//�����ɂ��Ă���

		//�F��ݒ�
		CObject2D::SetCol(col);

		if (col.a <= 0.0f)
		{//���S�ɓ����ɂȂ�����
			col.a = 0.0f;			//0.0�ɂ���
			m_state = STATE::NONE;	//�t�F�[�h���Ă��Ȃ���Ԃɂ���
		}
	}
	else if (m_state == STATE::FADE_OUT)
	{//�t�F�[�h�A�E�g( ���� ---> �s���� )
		col.a += 0.01f;	//�s�����ɂ��Ă���

		//�F��ݒ�
		CObject2D::SetCol(col);

		if (col.a >= 1.0f)
		{//���S�ɕs�����ɂȂ�����
			col.a = 1.0f;			//1.0�ɂ���
			m_state = STATE::NONE;	//�t�F�[�h���Ă��Ȃ���Ԃɂ���
		}
	}
}

//================================================
//�`��
//================================================
void CFade::Draw()
{
	CObject2D::Draw();	//�e�N���X
}

//================================================
//�ݒ�
//================================================
void CFade::Set(const STATE &state)
{
	m_state = state;	//�t�F�[�h��Ԃ�ݒ�
}