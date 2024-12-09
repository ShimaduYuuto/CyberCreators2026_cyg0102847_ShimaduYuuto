//================================
//
//state_player_damage.cpp�ɕK�v�Ȑ錾[state_player_damage.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_DAMAGE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_PLAYER_DAMAGE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_player.h"

//�X�e�[�g�N���X
class CState_Player_Damage : public CState_Player
{
public:

	//�����o�֐�
	CState_Player_Damage() {};					//�R���X�g���N�^
	CState_Player_Damage(CPlayer* player)
	{
		SetEndTime(30);
	};	//�R���X�g���N�^
	~CState_Player_Damage() {};					//�f�X�g���N�^

	//��Ԃ��Ƃ̍X�V
	void UpdateState(CPlayer* player) override;				//��Ԃ̍X�V
	void SetDamage(CPlayer* player, int damage) override;	//�_���[�W�̐ݒ�
};

#endif