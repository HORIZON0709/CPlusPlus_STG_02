//================================================
//
//������H��b[object3D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//***************************
//�C���N���[�h
//***************************
#include "object.h"
#include "texture.h"

//***************************
//�萔�̒�`
//***************************

/* ���_�t�H�[�}�b�g */
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//***************************
//�I�u�W�F�N�g�N���X�̒�`
//***************************
class CObject3D : public CObject
{/* CObject�̔h���N���X */
public: /* �\���̂̒�` */
	struct VERTEX_3D
	{//���_�f�[�^
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 nor;	//�@���x�N�g�� 
		D3DCOLOR col;		//�F
		D3DXVECTOR2 tex;	//�e�N�X�`�����W
	};

public: /* �ÓI�����o�֐� */
	static CObject3D* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CObject3D();
	~CObject3D() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

	/* Pos */
	void SetPos(const D3DXVECTOR3 &pos) override;	//�ʒu��ݒ�
	D3DXVECTOR3 GetPos() override;					//�ʒu���擾

	/* Size */
	void SetSize(const float &fSize) override;	//�T�C�Y��ݒ�
	float GetSize() override;					//�T�C�Y���擾

	/* Move */
	void SetMove(const D3DXVECTOR3 &move) override;	//�ړ��ʂ�ݒ�
	D3DXVECTOR3 GetMove() override;					//�ړ��ʂ��擾

public: /* �����o�֐� */
	void SetTexture(CTexture::TEXTURE texture);				//�e�N�X�`���̐ݒ�
	void SetTexUV(const int &nDivNum,const int &nPtnAnim);	//�e�N�X�`�����W�̐ݒ�(�A�j���[�V�����Ή�)

private: /* �����o�ϐ� */
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX	m_mtxWorld;				//���[���h�}�g���b�N�X
	CTexture::TEXTURE m_texture;		//�e�N�X�`���̗񋓌^

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	D3DXVECTOR3 m_move;	//�ړ���
	float m_fSize;		//�T�C�Y
};

#endif