//================================
//
//behavior_enemy001.cpp�ɕK�v�Ȑ錾[behavior_enemy001.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY001_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BEHAVIOR_ENEMY001_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy.h"

//==========================
//�ǂ�������
//==========================
class CEnemyAction_Chase001 : public CEnemyAction_Chase
{
public:

	//�R���X�g���N�^
	CEnemyAction_Chase001() {};
	CEnemyAction_Chase001(CEnemy* enemy);

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
//�G�l�~�[001�̍U������
//==========================
class CEnemyAction_Attack001 : public CEnemyAction_Attack
{
public:

	//�R���X�g���N�^
	CEnemyAction_Attack001() {};
	CEnemyAction_Attack001(CEnemy* enemy);

	void Action(CEnemy* enemy) override
	{
		CEnemyAction_Attack::Action(enemy);
	};	//�U��

	//�ǂ�������A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Chase001(enemy));
	}
};

#endif