////======================================
////
////	�A�N�V��������[action_enemy001.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////�w�b�_�[�̃C���N���[�h
//#include "action_enemy001.h"
//#include "spawn_shield.h"
//#include "normalattack_enemy001.h"
//
////============================
////�R���X�g���N�^
////============================
//CAction_Enemy001::CAction_Enemy001() :
//	m_NextAction(ACTION_ENEMY001_NONE),
//	m_pCharacter(nullptr),
//	m_NowAction(ACTION_ENEMY001_NONE)
//{
//
//}
//
////============================
////�f�X�g���N�^
////============================
//CAction_Enemy001::~CAction_Enemy001()
//{
//
//}
//
////============================
////������
////============================
//HRESULT CAction_Enemy001::Init()
//{
//	CAction::Init();
//
//	return S_OK;
//}
//
////============================
////�X�V
////============================
//void CAction_Enemy001::Update()
//{
//	CAction::Update();
//}
//
////============================
////���̃A�N�V�����̐ݒ�
////============================
//void CAction_Enemy001::SetNextAction()
//{
//
//}
//
////============================
////�N���G�C�g
////============================
//CAction_Enemy001* CAction_Enemy001::Create(ACTION_ENEMY001 action_enemy001, CCharacter* character)
//{
//	//�|�C���^�p�̕ϐ�
//	CAction_Enemy001* pAction = nullptr;
//
//	//�A�N�V�����̎�ނɉ����ăN���X��ύX
//	switch (action_enemy001)
//	{
//	case ACTION_ENEMY001_NONE:	//�����Ȃ�
//		break;
//
//	case ACTION_ENEMY001_SPAWN_SHIELD:	//���̐���
//		pAction = new CSpawn_Shield;
//		break;
//
//	case ACTION_ENEMY001_ATTACK:		//�ʏ�U��
//		pAction = new CNormalAttack_Enemy001;
//		break;
//
//		//���݂̃A�N�V������ݒ�
//		pAction->m_NowAction = action_enemy001;
//	}
//
//	//�k���|�C���^�Ȃ�A�T�[�g��ʂ�
//	if (pAction == nullptr)
//	{
//		assert(true);
//	}
//
//	//�|�C���^���擾
//	pAction->m_pCharacter = character;
//
//	//������
//	pAction->Init();
//
//	return pAction;
//}