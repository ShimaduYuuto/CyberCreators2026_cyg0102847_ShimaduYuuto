////================================
////
////action_enemy.cpp�ɕK�v�Ȑ錾[action_enemy.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _ACTION_ENEMY_H_ //���̃}�N����`������Ă��Ȃ�������
//#define _ACTION_ENEMY_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`
//
////�w�b�_�[�̃C���N���[�h
//#include "main.h"
//#include "action.h"
//#include "character.h"
//
////�O���錾
//class CEnemy;
//
////�A�N�V�����N���X
//class CAction_Enemy : public CAction
//{
//public:
//
//	//�����o�֐�
//	CAction_Enemy() : m_NextAction(nullptr) {}		//�R���X�g���N�^
//	~CAction_Enemy() override {};					//�f�X�g���N�^
//	void Update(CEnemy* enemy);						//�X�V
//
//	//�p�����[�^�[�̎擾�Ɛݒ�
//	void SetNextAction(CAction_Enemy* next) { m_NextAction = next; }	//���̃A�N�V�����̐ݒ�
//	CAction_Enemy* GetNextAction() { return m_NextAction; }				//���̃A�N�V�����̎擾
//
//private:
//
//	CAction_Enemy* m_NextAction;	//���̃A�N�V����
//};
//
//#endif