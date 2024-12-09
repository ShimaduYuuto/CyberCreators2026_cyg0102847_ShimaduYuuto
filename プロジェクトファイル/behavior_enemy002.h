//================================
//
//behavior_enemy002.cpp�ɕK�v�Ȑ錾[behavior_enemy002.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY002_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BEHAVIOR_ENEMY002_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy.h"
#include "enemybullet.h"
#include "effect_chargeshot.h"

//==========================
//�ǂ�������
//==========================
class CEnemyAction_Standby : public CEnemyAction
{
public:

	//�R���X�g���N�^
	CEnemyAction_Standby() {};
	CEnemyAction_Standby(CEnemy* enemy) : m_nCoolTime(0)
	{
		enemy->SetMotion(0);
		m_nCoolTime = COOL_TIME;
	};

	//�萔
	static constexpr int COOL_TIME{90};		//�N�[���^�C���̎���
	void Action(CEnemy* enemy) override;	//�A�N�V����

	//�U���A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override;

private:
	int m_nCoolTime;
};

//==========================
//�G�l�~�[002�̍U������
//==========================
class CEnemyAction_Attack002 : public CEnemyAction_Attack
{
public:

	//�R���X�g���N�^
	CEnemyAction_Attack002() {};
	CEnemyAction_Attack002(CEnemy* enemy)
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
		SetNextAction(new CEnemyAction_Standby(enemy));
	}
};

//==========================
//�`���[�W�V���b�g
//==========================
class CEnemyAction_ChargeShot : public CEnemyAction
{
public:

	static constexpr int CHARGE_TIME{ 230 };		//�`���[�W����
	static constexpr int CREATE_BULLET_TIME{ 50 };	//�e�̐�������
	static constexpr int END_TIME{ 300 };			//�A�N�V�����I������
	static constexpr float ADD_SCALE_VALUE{ 0.03f };//�X�P�[���̉��Z��

	//�R���X�g���N�^
	CEnemyAction_ChargeShot() {};
	CEnemyAction_ChargeShot(CEnemy* enemy) : m_nChargeCount(0), m_pBullet(nullptr), m_pEffect(nullptr)
	{
		//�ݒ�
		enemy->SetMotion(4);
	};

	//�f�X�g���N�^
	~CEnemyAction_ChargeShot()
	{
		if (m_pBullet != nullptr)
		{
			m_pBullet = nullptr;
		}
	}

	void Action(CEnemy* enemy) override;	//�U��

	//�ҋ@�A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Standby(enemy));
	}

private:
	int m_nChargeCount;				//�`���[�W�̃J�E���g
	CEnemyBullet* m_pBullet;		//�e�̃|�C���^
	CEffect_ChargeShot* m_pEffect;	//�G�t�F�N�g�̃|�C���^
};

//==========================
//�G�l�~�[002�̉��o
//==========================
class CEnemyAction_Direction : public CEnemyAction
{
public:

	static constexpr int DIRECTION_TIME{ 300 };	//���o�̎���

	//�R���X�g���N�^
	CEnemyAction_Direction() {};
	CEnemyAction_Direction(CEnemy* enemy);

	void Action(CEnemy* enemy) override;	//���o

	//�ǂ�������A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Standby(enemy));
	}

private:
	int m_nCount;	//�J�E���g�p
};

#endif