//================================
//
//behavior_enemy003.cpp�ɕK�v�Ȑ錾[behavior_enemy003.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY003_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BEHAVIOR_ENEMY003_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy.h"

//==========================
//�ҋ@
//==========================
class CEnemyAction_Standby003 : public CEnemyAction
{
public:

	//�R���X�g���N�^
	CEnemyAction_Standby003() {};
	CEnemyAction_Standby003(CEnemy* enemy) : m_nCoolTime(0)
	{
		enemy->SetMotion(0);
		m_nCoolTime = COOL_TIME;
	};

	//�萔
	static constexpr int COOL_TIME{ 90 };		//�N�[���^�C���̎���
	void Action(CEnemy* enemy) override;	//�A�N�V����

	//�U���A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override;

private:
	int m_nCoolTime;
};

//==========================
//�G�l�~�[003�̍U������
//==========================
class CEnemyAction_Attack003 : public CEnemyAction_Attack
{
public:

	//�R���X�g���N�^
	CEnemyAction_Attack003() {};
	CEnemyAction_Attack003(CEnemy* enemy)
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

	//�ҋ@�A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Standby003(enemy));
	}
};

//==========================
//�`���[�W�A�^�b�N
//==========================
class CEnemyAction_ChargeAttack : public CEnemyAction
{
public:

	static constexpr int CHARGE_TIME{ 80 };			//�`���[�W����
	static constexpr int END_TIME{ 200 };			//�I���̎���
	static constexpr float SPEED_MOVE{ 3.0f };		//�U���̈ړ����x

	//�R���X�g���N�^
	CEnemyAction_ChargeAttack() {};
	CEnemyAction_ChargeAttack(CEnemy* enemy) : m_nChargeCount(0)
	{
		//�ݒ�
		enemy->SetMotion(2);
	};

	//�f�X�g���N�^
	~CEnemyAction_ChargeAttack() {}

	void Action(CEnemy* enemy) override;	//�U��

	//�ҋ@�A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Standby003(enemy));
	}

private:
	int m_nChargeCount;		//�`���[�W�̃J�E���g
	float m_fAttackAngle;	//�ːi����
};

#endif