//================================================
//
//������H��b[object2D.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//***************************
//�C���N���[�h
//***************************
#include "object.h"
#include "texture.h"

//***************************
//�I�u�W�F�N�g�N���X�̒�`
//***************************
class CObject2D : public CObject
{/* CObject�̔h���N���X */
public: /* �\���̂̒�` */
	struct VERTEX_2D
	{//���_�f�[�^
		D3DXVECTOR3 pos;	//�ʒu
		float rhw;			//�@��
		D3DCOLOR col;		//�F
		D3DXVECTOR2 tex;	//�e�N�X�`�����W
	};

protected: /* �萔�̒�` */
	static const float ROTATION_SPEED;	//��]�X�s�[�h

public: /* �ÓI�����o�֐� */
	static CObject2D* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CObject2D();
	~CObject2D() override;

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

public: /* �����o�֐� */
	void SetTexture(CTexture::TEXTURE texture);				//�e�N�X�`���̐ݒ�
	void SetTexUV(const int &nDivNum,const int &nPtnAnim);	//�e�N�X�`�����W�̐ݒ�(�A�j���[�V�����Ή�)

private: /* �����o�ϐ� */
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	CTexture::TEXTURE m_texture;		//�e�N�X�`���̗񋓌^

	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//����
	float m_fSize;		//�T�C�Y
};

#endif