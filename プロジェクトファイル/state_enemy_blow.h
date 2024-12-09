//================================
//
//state_enemy_blow.cpp�ɕK�v�Ȑ錾[state_enemy_blow.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY_BLOW_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_ENEMY_BLOW_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_enemy.h"

//�u���[�X�e�[�g�N���X
class CState_Enemy_Blow : public CState_Enemy
{
public:

	//�萔
	static constexpr float VALUE_BLOW = 10.0f;	//������Ԓl

	//�����o�֐�
	CState_Enemy_Blow();					//�R���X�g���N�^
	CState_Enemy_Blow(CEnemy* enemy);		//�R���X�g���N�^
	~CState_Enemy_Blow() {};				//�f�X�g���N�^

	//��Ԃ��Ƃ̍X�V
	void UpdateState(CEnemy* enemy) override;	//��Ԃ̍X�V
};

#endif