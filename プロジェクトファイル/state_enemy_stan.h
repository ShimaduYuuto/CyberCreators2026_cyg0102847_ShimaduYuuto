//================================
//
//state_enemy_stan.cpp�ɕK�v�Ȑ錾[state_enemy_stan.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY_STAN_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_ENEMY_STAN_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_enemy.h"

//�X�^���X�e�[�g�N���X
class CState_Enemy_Stan : public CState_Enemy
{
public:

	//�����o�֐�
	CState_Enemy_Stan();					//�R���X�g���N�^
	CState_Enemy_Stan(CEnemy* enemy) {};	//�R���X�g���N�^
	~CState_Enemy_Stan() {};				//�f�X�g���N�^

	//��Ԃ��Ƃ̍X�V
	void UpdateState(CEnemy* enemy) override;	//��Ԃ̍X�V
};

#endif