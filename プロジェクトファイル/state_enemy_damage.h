//================================
//
//state_enemy_normal.cpp�ɕK�v�Ȑ錾[state_enemy_normal.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY_DAMAGE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_ENEMY_DAMAGE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_enemy.h"

//�_���[�W�X�e�[�g�N���X
class CState_Enemy_Damage : public CState_Enemy
{
public:

	//�����o�֐�
	CState_Enemy_Damage();					//�R���X�g���N�^
	CState_Enemy_Damage(CEnemy* enemy) {};	//�R���X�g���N�^
	~CState_Enemy_Damage() {};				//�f�X�g���N�^

	//��Ԃ��Ƃ̍X�V
	void UpdateState(CEnemy* enemy) override;	//��Ԃ̍X�V
};

#endif