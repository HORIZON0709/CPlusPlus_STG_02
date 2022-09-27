//================================================
//
//������H��b[object.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "object.h"
#include "renderer.h"

//***************************
//�ÓI�����o�ϐ�
//***************************
CObject* CObject::m_apObject[MAX_OBJECT] = {};	//�|�C���^
int CObject::m_nNumAll = 0;						//�ő吔

//================================================
//�S�Ẳ��
//================================================
void CObject::ReleaseAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		m_apObject[i]->Release();	//���
	}
}

//================================================
//�S�Ă̍X�V
//================================================
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		m_apObject[i]->Update();	//�X�V
	}
}

//================================================
//�S�Ă̕`��
//================================================
void CObject::DrawAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		m_apObject[i]->Draw();	//�`��
	}
}

//================================================
//�I�u�W�F�N�g���̎擾
//================================================
CObject* CObject::GetObjects(const int &nIdx)
{
	return m_apObject[nIdx];
}

//================================================
//�I�u�W�F�N�g���̐ݒ�
//================================================
void CObject::SetObject(const int &nIdx, void* pObject)
{
	m_apObject[nIdx] = (CObject*)pObject;
}

//================================================
//�R���X�g���N�^
//================================================
CObject::CObject()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] != nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�̏ꍇ */

		m_apObject[i] = this;	//���g�̃|�C���^��Ԃ�

		m_nID = i;	//�����̔ԍ���ݒ�

		m_nNumAll++;	//���𑝂₷
		break;
	}
}

//================================================
//�R���X�g���N�^(�f�t�H���g����ver.)
//================================================
//CObject::CObject(const int &nPriority /* = 3 */)
//{
//	for (int i = 0; i < MAX_OBJECT; i++)
//	{
//		if (m_apObject[nPriority][i] != nullptr)
//		{//NULL�`�F�b�N
//			continue;
//		}
//
//		/* nullptr�̏ꍇ */
//
//
//	}
//}

//================================================
//�f�X�g���N�^
//================================================
CObject::~CObject()
{
}

//================================================
//���
//================================================
void CObject::Release()
{
	if (m_apObject[m_nID] == nullptr)
	{//NULL�`�F�b�N
		return;
	}

	/* nullptr�ł͂Ȃ��ꍇ */

	int nID = m_nID;	//�ԍ���ۑ�

	m_apObject[nID]->Uninit();	//�I��
	delete m_apObject[nID];		//�������̉��
	m_apObject[nID] = nullptr;	//nullptr�ɂ���

	m_nNumAll--;	//�������炷
}

//================================================
//�^�C�v�̐ݒ�
//================================================
void CObject::SetObjType(const CObject::OBJ_TYPE &type)
{
	objType = type;
}

//================================================
//�^�C�v�̎擾
//================================================
CObject::OBJ_TYPE CObject::GetObjType()
{
	return objType;
}