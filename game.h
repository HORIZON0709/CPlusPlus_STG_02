//================================================
//
//������H��b[game.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _GAME_H_
#define _GAME_H_

//***************************
//�C���N���[�h
//***************************
#include "score.h"

#include "player_3D.h"
#include "enemy_3D.h"
#include "bg_3D.h"

#include <d3dx9.h>

//***************************
//�Q�[���N���X�̒�`
//***************************
class CGame
{/* ��{�N���X */
public: /* �ÓI�����o�֐� */
	/* �X�R�A�̏����擾 */
	static CScore* GetScore();

	/* �v���C���[(3D)�̏����擾 */
	static CPlayer3D* GetPlayer3D();

	/*
		�G(3D)�̏����擾
		const int nIdx ---> ���Ԗڂ�
	*/
	static CEnemy3D* GetEnemy3D(const int nIdx);

	/* �w�i(3D)�̏����擾 */
	static CBg3D* GetBg3D();

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CGame();
	~CGame();

public: /* �����o�֐� */
	HRESULT Init();	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

private: /* �ÓI�����o�ϐ� */
	static CScore* m_pScore;							//�X�R�A
	static CPlayer3D* m_pPlayer3D;						//�v���C���[(3D)
	static CEnemy3D* m_apEnemy3D[CEnemy3D::MAX_ENEMY];	//�G(3D)
	static CBg3D* m_pBg3D;								//�w�i(3D)
	
};
#endif