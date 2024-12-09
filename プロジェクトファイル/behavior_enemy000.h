//================================
//
//behavior_enemy000.cpp�ɕK�v�Ȑ錾[behavior_enemy000.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY000_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BEHAVIOR_ENEMY000_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy.h"

//==========================
//�ǂ�������
//==========================
class CEnemyAction_Chase000 : public CEnemyAction_Chase
{
public:

	//�R���X�g���N�^
	CEnemyAction_Chase000() {};
	CEnemyAction_Chase000(CEnemy* enemy)
	{
		enemy->SetMotion(1);
	};

	//�萔
	static constexpr float VALUE_MOVE = 1.0f;	//�ړ���

	void Action(CEnemy* enemy) override
	{
		CEnemyAction_Chase::Action(enemy);
	};	//�A�N�V����

	//�U���A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override;
};

//==========================
//�G�l�~�[000�̍U������
//==========================
class CEnemyAction_Attack000 : public CEnemyAction_Attack
{
public:

	//�R���X�g���N�^
	CEnemyAction_Attack000() {};
	CEnemyAction_Attack000(CEnemy* enemy)
	{
		//�ݒ�
		GetAttackInstanse()->SetCollisionTime(65);
		GetAttackInstanse()->SetEndTime(100.0f);
		GetAttackInstanse()->SetDamageValue(1);
		SetAttackLength(30.0f);
		enemy->SetMotion(2);
	};

	void Action(CEnemy* enemy) override
	{
		CEnemyAction_Attack::Action(enemy);
	};	//�U��

	//�ǂ�������A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Chase000(enemy));
	}
};

//=======================================
//�ȉ��̓o�b�N�A�b�v
//=======================================

//==========================
//�G�l�~�[000�̃A�^�b�N�X�g���e�W�[
//==========================
class CEnemy000Attack : public CEnemyAttack
{
public:

	//�R���X�g���N�^
	CEnemy000Attack();
	CEnemy000Attack(CEnemy* enemy);

	//�p�����[�^�̐ݒ�
	void SetParam() override
	{
		//�ݒ�
		SetCollisionTime(65);
		SetEndTime(100.0f);
		SetDamageValue(1);
		SetAttackLength(30.0f);
	}
};

#endif