//================================
//
//state_enemy_stick.cpp�ɕK�v�Ȑ錾[state_enemy_stick.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY_STICK_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_ENEMY_STICK_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_enemy.h"

//�X�e�B�b�N�X�e�[�g�N���X
class CState_Enemy_Stick : public CState_Enemy
{
public:

	//�����o�֐�
	CState_Enemy_Stick();					//�R���X�g���N�^
	CState_Enemy_Stick(CEnemy* enemy);		//�R���X�g���N�^
	~CState_Enemy_Stick() {};				//�f�X�g���N�^

	//��Ԃ��Ƃ̍X�V
	void UpdateState(CEnemy* enemy) override;	//��Ԃ̍X�V
};

#endif