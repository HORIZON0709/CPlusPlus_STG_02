//================================================
//
//������H��b[fade.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _FADE_H_
#define _FADE_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>

//***************************
//�萔�̒�`
//***************************
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);	//���_�t�H�[�}�b�g

//***************************
//�w�i�N���X�̒�`
//***************************
class CFade
{/* ��{�N���X */
public: /* �񋓌^�̒�` */	
	enum STATE	//�t�F�[�h���
	{
		NONE = -1,		//�t�F�[�h���Ă��Ȃ�
		FADE_IN = 0,	//�t�F�[�h�C��
		FADE_OUT,		//�t�F�[�h�A�E�g
		MAX
	};

private: /* �\���̂̒�` */
	struct VERTEX_2D
	{//���_�f�[�^
		D3DXVECTOR3 pos;	//�ʒu
		float rhw;			//�@��
		D3DCOLOR col;		//�F
		D3DXVECTOR2 tex;	//�e�N�X�`�����W
	};

public: /* �ÓI�����o�֐� */
	static CFade* Create();	//����

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CFade();
	~CFade();

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init();	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

public: /* �����o�֐� */
	/*
		�ݒ�
		const STATE &state ---> �t�F�[�h���
	*/
	void Set(const STATE &state);

private: /* �����o�ϐ� */
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	STATE m_state;	//�t�F�[�h���

	D3DXCOLOR m_col;	//�F
};
#endif