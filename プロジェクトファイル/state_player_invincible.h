//================================
//
//state_player_invincible.cpp�ɕK�v�Ȑ錾[state_player_invincible.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_INVINCIBLE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_PLAYER_INVINCIBLE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_player.h"

//�X�e�[�g�N���X
class CState_Player_Invincible : public CState_Player
{
public:

	//�����o�֐�
	CState_Player_Invincible() {};					//�R���X�g���N�^
	CState_Player_Invincible(CPlayer* player)
	{
		//SetBehavior(new CPlayerBehavior(player));
	};	//�R���X�g���N�^
	~CState_Player_Invincible() {};					//�f�X�g���N�^
};

#endif