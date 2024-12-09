//================================
//
//state_player.cpp�ɕK�v�Ȑ錾[state_player.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_PLAYER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state.h"
#include "player.h"
#include "behavior_player.h"

//�O���錾
class CPlayer;
class CPlayerBehavior;

//�X�e�[�g�N���X
class CState_Player : public CState
{
public:

	//�����o�֐�
	CState_Player() : m_pBehavior(nullptr), m_pNextState(nullptr){};					//�R���X�g���N�^
	CState_Player(CPlayer* player) : m_pBehavior(nullptr), m_pNextState(nullptr) {};	//�R���X�g���N�^
	~CState_Player();																	//�f�X�g���N�^

	//��Ԃ��Ƃ̍X�V
	virtual void Update(CPlayer* player);					//�X�V
	virtual void SetDamage(CPlayer* player, int damage) {}		//�_���[�W�̐ݒ�

	//�A�N�V�����̃C���X�^���X
	void SetBehavior(CPlayerBehavior* behavior) { m_pBehavior = behavior; }	//�ݒ�
	CPlayerBehavior* GetBehavior() { return m_pBehavior; }					//�擾

	//���̏��
	void SetNextState(CState_Player* state) { if (m_pNextState == nullptr) { m_pNextState = state; } };	//�ݒ�
	CState_Player* GetNextState() { return m_pNextState; }												//�擾

private:

	//��ԂƃA�N�V�����̍X�V
	virtual void UpdateState(CPlayer* player);		//��Ԃ̍X�V
	void UpdateBehavior(CPlayer* player);			//�s���̍X�V

	//�C���X�^���X
	CPlayerBehavior* m_pBehavior;	//�s��
	CState_Player* m_pNextState;	//���̏��
};

#endif