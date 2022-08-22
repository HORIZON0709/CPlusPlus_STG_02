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
#include "mode.h"

#include "score.h"
#include "player_3D.h"
#include "enemy_3D.h"
#include "bg_3D.h"

#include <d3dx9.h>

//***************************
//�Q�[���N���X�̒�`
//***************************
class CGame : public CMode
{/* CMode�̔h���N���X */
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
	~CGame() override;

public: /* �����o�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;	//�I��
	void Update() override;	//�X�V
	void Draw() override;	//�`��

	bool GetGamePart();	//�Q�[���p�[�g�̎擾

private: /* �ÓI�����o�ϐ� */
	static CScore* m_pScore;							//�X�R�A
	static CPlayer3D* m_pPlayer3D;						//�v���C���[(3D)
	static CEnemy3D* m_apEnemy3D[CEnemy3D::MAX_ENEMY];	//�G(3D)
	static CBg3D* m_pBg3D;								//�w�i(3D)
	
private: /* �����o�ϐ� */
	/*
		�Q�[���p�[�g�̔���
		false ---> �ʏ�p�[�g
		true ---> �{�X�p�[�g
	*/
	bool m_bGamePart;
};
#endif