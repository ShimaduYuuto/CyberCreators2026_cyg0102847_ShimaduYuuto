//================================
//
//state_player_knockback.cpp�ɕK�v�Ȑ錾[state_player_knockback.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_KNOCKBACK_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_PLAYER_KNOCKBACK_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_player.h"

//�X�e�[�g�N���X
class CState_Player_Knockback : public CState_Player
{
public:

	//�m�b�N�o�b�N�̎���
	static const int TIME_KNOCKBACK = 30;

	//�����o�֐�
	CState_Player_Knockback() : m_nKnockbackCount(TIME_KNOCKBACK){};					//�R���X�g���N�^
	CState_Player_Knockback(CPlayer* player) : m_nKnockbackCount(TIME_KNOCKBACK)
	{
		SetBehavior(new CPlayerBehavior(player));
		SetEndTime(TIME_KNOCKBACK);
	};	//�R���X�g���N�^
	~CState_Player_Knockback() {};	//�f�X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CPlayer* player) override;	
	void SetDamage(CPlayer* player, int damage) override;	//�_���[�W�̐ݒ�
private:
	int m_nKnockbackCount;
};

#endif