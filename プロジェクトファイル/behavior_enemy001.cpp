//================================
//
//�G�̍s���܂Ƃ�[behavior_enemy001.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy001.h"
#include "enemy001.h"

//======================================================================
//�ǂ�������
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyAction_Chase001::CEnemyAction_Chase001(CEnemy* enemy)
{
	//���[�V�����̐ݒ�
	enemy->SetMotion(1);
	CEnemy001* enemy001 = (CEnemy001*)enemy;
	enemy001->SetDamageJudge(false);
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyAction_Chase001::NextAction(CEnemy* enemy)
{
	//�U����ݒ�
	SetNextAction(new CEnemyAction_Attack001(enemy));
}

//======================================================================
//�U��
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyAction_Attack001::CEnemyAction_Attack001(CEnemy* enemy)
{
	//�ݒ�
	GetAttackInstanse()->SetCollisionTime(45);
	GetAttackInstanse()->SetEndTime(100.0f);
	GetAttackInstanse()->SetDamageValue(1);
	SetAttackLength(50.0f);

	enemy->SetMotion(5);
	CEnemy001* enemy001 = (CEnemy001*)enemy;
	enemy001->SetDamageJudge(true);
}