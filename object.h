//================================================
//
//������H��b[object.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>

//***************************
//�I�u�W�F�N�g�N���X�̒�`
//***************************
class CObject
{/* ��{�N���X */
public: /* �񋓌^�̒�` */
	enum OBJ_TYPE
	{/* �I�u�W�F�N�g�̎�� */
		PLAYER = 0,	//�v���C���[
		ENEMY,		//�G
		BULLET,		//�e
		EXPLOSION,	//����
		BG,			//�w�i
		ITEM,		//�A�C�e��
		MAX,
		NONE
	};

public: /* �萔�̒�` */
	static const int MAX_OBJECT = 64;		//�|���S���̍ő吔
	//static const int MAX_NUM_PRIORITY = 5;	//�D�揇�ʂ̍ő吔

public: /* �ÓI�����o�֐� */
	static void ReleaseAll();	//�S�Ẳ��
	static void UpdateAll();	//�S�Ă̍X�V
	static void DrawAll();		//�S�Ă̕`��

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CObject();
	//explicit CObject(const int &nPriority = 3);	//�f�t�H���g����(�����ɒl��ݒ肵�Ȃ��ꍇ�́u3�v�ɂȂ�)
	virtual ~CObject();

public: /* �������z�֐� */
	virtual HRESULT Init() = 0;	//������
	virtual void Uninit() = 0;	//�I��
	virtual void Update() = 0;	//�X�V
	virtual void Draw() = 0;	//�`��

public: /* �����o�֐� */
	/*
		�I�u�W�F�N�g���̎擾
		const int &nIdx ---> �C���f�b�N�X��
	*/
	CObject* GetObjects(const int &nIdx);

	void Release();	//���

public:	/* ObjType */
	/*
		�^�C�v�̐ݒ�
		const OBJ_TYPE &type ---> �C�ӂ̃^�C�v
	*/
	void SetObjType(const OBJ_TYPE &type);

	/*
		�^�C�v�̎擾
	*/
	OBJ_TYPE GetObjType();

private: /* �ÓI�����o�ϐ� */
	static CObject* m_apObject[MAX_OBJECT];	//�|�C���^
	//static CObject* m_apObject[MAX_NUM_PRIORITY][MAX_OBJECT];	//�|�C���^(�D�揇�ʕt��)

	static int m_nNumAll;					//�ő吔
	
private: /* �����o�ϐ� */
	int m_nID;					//�i�[��̔ԍ�
	CObject::OBJ_TYPE objType;	//���
};

#endif