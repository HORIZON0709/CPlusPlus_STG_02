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
#include "enemy_3D.h"

#include <d3dx9.h>

//***************************
//�O���錾
//***************************
class CCamera;
class CScore;
class CPlayer3D;
class CBg3D;

//***************************
//�Q�[���N���X�̒�`
//***************************
class CGame : public CMode
{/* CMode�̔h���N���X */
private: /* �萔�̒�` */
	static const int INTERVAL_STRAIGHT;			//�����G�̐����Ԋu
	static const int FADE_INTERVAL_PARTCHANGE;	//�t�F�[�h�܂ł̊Ԋu(�p�[�g�؂�ւ���)
	static const int FADE_INTERVAL_GAMEOVER;	//�t�F�[�h�܂ł̊Ԋu(�Q�[���I�[�o�[��)
	static const int FADE_INTERVAL_GAMECLEAR;	//�t�F�[�h�܂ł̊Ԋu(�Q�[���N���A��)

public: /* �ÓI�����o�֐� */
	static CCamera* GetCamera();		//�J�����̏����擾
	static CScore* GetScore();			//�X�R�A�̏����擾
	static CPlayer3D* GetPlayer3D();	//�v���C���[(3D)�̏����擾

	/*
		�G(3D)�̏����擾
		const int nIdx ---> ���Ԗڂ�
	*/
	static CEnemy3D* GetEnemy3D(const int nIdx);

	static CBg3D* GetBg3D();	//�w�i(3D)�̏����擾

	static void ChangeGamePart();	//�Q�[���p�[�g�̐؂�ւ�
	static bool GetGamePart();		//�Q�[���p�[�g�̎擾

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CGame();
	~CGame() override;

public: /* �I�[�o�[���C�h�֐� */
	HRESULT Init() override;	//������
	void Uninit() override;	//�I��
	void Update() override;	//�X�V
	void Draw() override;	//�`��

private: /* �����o�֐� */
	/*
		�����G�̐���
		const float fPosY ---> ��������ʒu( Y�� )
	*/
	void CreateEnemyStraight(const float fPosY);

	void UpdateNormalPart();	//�ʏ�p�[�g�̍X�V
	void UpdateBossPart();		//�{�X�p�[�g�̍X�V

private: /* �ÓI�����o�ϐ� */
	static CCamera* m_pCamera;							//�J����
	static CScore* m_pScore;							//�X�R�A
	static CPlayer3D* m_pPlayer3D;						//�v���C���[(3D)
	static CEnemy3D* m_apEnemy3D[CEnemy3D::MAX_ENEMY];	//�G(3D)
	static CBg3D* m_pBg3D;								//�w�i(3D)

	/*
		�Q�[���p�[�g�̔���
		false ---> �ʏ�p�[�g
		true ---> �{�X�p�[�g
	*/
	static bool m_bGamePart;

private: /* �����o�ϐ� */
	int m_nCntStraight;		//�����G�̐����Ԋu�J�E���g�p
	int m_nCntIntervalFade;	//�t�F�[�h����܂ł̊Ԋu�J�E���g�p

	bool m_bFadeOut;	//�Ó]�������ǂ���
};
#endif