////================================
////
////action_player.cpp�ɕK�v�Ȑ錾[action_player.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _ACTION_PLAYER_H_ //���̃}�N����`������Ă��Ȃ�������
//#define _ACTION_PLAYER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`
//
////�w�b�_�[�̃C���N���[�h
//#include "main.h"
//#include "action.h"
//#include "character.h"
//
////�A�N�V�����N���X
//class CAction_Player : public CAction
//{
//public:
//
//	//�����o�֐�
//	CAction_Player();			//�R���X�g���N�^
//	~CAction_Player() override;	//�f�X�g���N�^
//	HRESULT Init() override;	//������
//	void Update() override;		//�X�V
//
//	//�ݒ�Ǝ擾
//	void SetNextAction(CAction_Player* next);								//���̃A�N�V������ݒ�
//	CAction_Player* GetNextAction() { return m_pNextAction; }				//���̃A�N�V�������擾
//	void SetCharacter(CCharacter* character) { m_pCharacter = character; }	//�L�����N�^�[�̐ݒ�
//	CCharacter* GetCharacter() { return m_pCharacter; }						//�L�����N�^�[�̎擾
//
//private:
//	CAction_Player* m_pNextAction;	//���̃A�N�V����
//	CCharacter* m_pCharacter;		//�L�����N�^�[�̃|�C���^
//};
//
//#endif