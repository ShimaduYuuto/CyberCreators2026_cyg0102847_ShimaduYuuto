//================================
//
//behavior_enemy.cpp�ɕK�v�Ȑ錾[behavior_enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BEHAVIOR_ENEMY_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "behavior_character.h"
#include "enemy.h"

//�O���錾
class CEnemy;

//==========================
//�G�l�~�[�A�N�V�������N���X
//==========================
class CEnemyAction
{
public:

	//������
	CEnemyAction() : m_pNextAction(nullptr) {}
	~CEnemyAction() {}

	//�A�N�V�����̊��
	virtual void Action(CEnemy* enemy) {};	

	//���̃A�N�V����
	void SetNextAction(CEnemyAction* action) { m_pNextAction = action; }
	CEnemyAction* GetNextAction() { return m_pNextAction; }

	//���̃A�N�V�������m�肷��
	virtual void NextAction(CEnemy* enemy) {}	//���̊֐�

private:
	CEnemyAction* m_pNextAction;
};

//==========================
//�ǂ�������
//==========================
class CEnemyAction_Chase : public CEnemyAction
{
public:
	//�萔
	static constexpr float VALUE_MOVE = 1.0f;	//�ړ���

	void Action(CEnemy* enemy) override;	//�A�N�V����

	//���̍s�����m��
	virtual void NextAction(CEnemy* enemy) {};
};

//==========================
//�U��
//==========================
class CEnemyAction_Attack : public CEnemyAction
{
public:

	//�R���X�g���N�^�ƃf�X�g���N�^
	CEnemyAction_Attack();
	~CEnemyAction_Attack();

	//�U������
	void Action(CEnemy* enemy) override;

	//�U���̃C���X�^���X
	void SetAttackInstance(CAttack* attack) { m_pAttack = attack; }	//�ݒ�
	CAttack*& GetAttackInstanse() { return m_pAttack; }				//�擾

	//�U���̋���
	void SetAttackLength(float length) { m_fAttackLength = length; }	//�ݒ�
	float GetAttackLength() { return m_fAttackLength; }					//�擾

private:

	//��{�̍U���N���X�ƓG��p�ϐ�
	CAttack* m_pAttack;		//�U���̃C���X�^���X
	float m_fAttackLength;	//�U���̋���
};






//====================================================================
// �ȉ��̓o�b�N�A�b�v
//====================================================================

//==========================
//�ړ��X�g���e�W�[
//==========================
class CEnemyMove
{
public:
	virtual void Move(CEnemy* enemy) {};
};

//==========================
//�ǂ�������
//==========================
class CEnemyMove_Chase : public CEnemyMove
{
public:
	//�萔
	static const float VALUE_MOVE;

	void Move(CEnemy* enemy) override;
};

//==========================
//�G�l�~�[�̃A�^�b�N�X�g���e�W�[
//==========================
class CEnemyAttack : public CAttack
{
public:

	//�R���X�g���N�^
	CEnemyAttack() : m_fAttackLength(0.0f) {}

	//�U���̊��
	virtual void Attack(CEnemy* enemy);

	//�U���̋���
	void SetAttackLength(float length) { m_fAttackLength = length; }	//�ݒ�
	float GetAttackLength() { return m_fAttackLength; }

private:
	float m_fAttackLength;	//�U���̋���
};

#endif