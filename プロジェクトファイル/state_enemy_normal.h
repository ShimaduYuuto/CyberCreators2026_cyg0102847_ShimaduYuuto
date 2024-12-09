//================================
//
//state_enemy_normal.cpp�ɕK�v�Ȑ錾[state_enemy_normal.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY_NORMAL_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_ENEMY_NORMAL_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_enemy.h"

//�m�[�}���X�e�[�g�N���X
class CState_Enemy_Normal : public CState_Enemy
{
public:

	//�萔
	static const float MOVE_SPEED;		//�ړ���
	static const float GRAVITY_SPEED;	//�d�͂̋���
	static const float JUMP_SPEED;		//�W�����v�̑��x

	//�����o�֐�
	CState_Enemy_Normal() {};				//�R���X�g���N�^
	CState_Enemy_Normal(CEnemy* enemy);		//�R���X�g���N�^
	~CState_Enemy_Normal() {};				//�f�X�g���N�^

	//��Ԃ��Ƃ̍X�V
	void UpdateState(CEnemy* enemy) override;	//��Ԃ̍X�V

	//��Ԃ��Ƃ̍X�V
	void SetDamage(CEnemy* enemy, int damage) override { enemy->SetDamage(damage); }	//�_���[�W�̐ݒ�
};

#endif