//================================
//
//state_enemy.cpp�ɕK�v�Ȑ錾[state_enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_ENEMY_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state.h"
#include "enemy.h"
#include "behavior_enemy.h"

//�O���錾
class CEnemy;
class CEnemyAction;

//�G�l�~�[�X�e�[�g�N���X
class CState_Enemy : public CState
{
public:

	//�����o�֐�
	CState_Enemy() : m_pAction(nullptr), m_pNextState(nullptr){};				//�R���X�g���N�^
	CState_Enemy(CEnemy* enemy) : m_pAction(nullptr), m_pNextState(nullptr) {};	//�R���X�g���N�^
	~CState_Enemy();															//�f�X�g���N�^

	//��Ԃ��Ƃ̍X�V
	void Update(CEnemy* enemy);

	//�G�l�~�[���m�̓����蔻��
	void EnemyCollision(CEnemy* enemy);

	//�_���[�W�̐ݒ�
	virtual void SetDamage(CEnemy* enemy, int damage) {}

	//�A�N�V�����̃C���X�^���X
	void SetAction(CEnemyAction* action) { m_pAction = action; }	//�ݒ�
	CEnemyAction* GetAction() { return m_pAction; }					//�擾

	//���̏��
	void SetNextState(CState_Enemy* state) { if (m_pNextState == nullptr) { m_pNextState = state; } };	//�ݒ�
	CState_Enemy* GetNextState() { return m_pNextState; }												//�擾

private:

	//��ԂƃA�N�V�����̍X�V
	virtual void UpdateState(CEnemy* enemy);				//��Ԃ̍X�V
	void UpdateAction(CEnemy*& enemy);						//�A�N�V�����̏���

	//�C���X�^���X
	CEnemyAction* m_pAction;	//�A�N�V����
	CState_Enemy* m_pNextState;	//���̏��
};

#endif