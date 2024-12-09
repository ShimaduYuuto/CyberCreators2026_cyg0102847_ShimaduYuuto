//================================
//
//state_player_normal.cpp�ɕK�v�Ȑ錾[state_player_normal.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_NORMAL_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_PLAYER_NORMAL_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_player.h"
//class CPlayerBehavior_Move;

//�m�[�}���X�e�[�g�N���X
class CState_Player_Normal : public CState_Player
{
public:

	//�����o�֐�
	CState_Player_Normal() {};					//�R���X�g���N�^
	CState_Player_Normal(CPlayer* player) 
	{
		SetBehavior(new CPlayerBehavior_Move(player));
	};	//�R���X�g���N�^
	~CState_Player_Normal() {};					//�f�X�g���N�^

	void UpdateState(CPlayer* player) override {};	//��Ԃ̍X�V
	void SetDamage(CPlayer* player, int damage) override;	//�_���[�W�̐ݒ�
};

#endif