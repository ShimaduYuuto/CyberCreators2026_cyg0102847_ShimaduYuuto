////======================================
////
////	�A�N�V��������[action_enemy000.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////�w�b�_�[�̃C���N���[�h
//#include "action_enemy000.h"
//#include "normalattack_enemy000.h"
//
////============================
////�R���X�g���N�^
////============================
//CAction_Enemy000::CAction_Enemy000() :
//	m_NextAction(ACTION_ENEMY000_NONE),
//	m_pCharacter(nullptr)
//{
//
//}
//
////============================
////�f�X�g���N�^
////============================
//CAction_Enemy000::~CAction_Enemy000()
//{
//
//}
//
////============================
////������
////============================
//HRESULT CAction_Enemy000::Init()
//{
//	CAction::Init();
//
//	return S_OK;
//}
//
////============================
////�X�V
////============================
//void CAction_Enemy000::Update()
//{
//	CAction::Update();
//}
//
////============================
////���̃A�N�V�����̐ݒ�
////============================
//void CAction_Enemy000::SetNextAction()
//{
//
//}
//
////============================
////�N���G�C�g
////============================
//CAction_Enemy000* CAction_Enemy000::Create(ACTION_ENEMY000 action_enemy000, CCharacter* character)
//{
//	//�|�C���^�p�̕ϐ�
//	CAction_Enemy000* pAction = nullptr;
//
//	//�A�N�V�����̎�ނɉ����ăN���X��ύX
//	switch (action_enemy000)
//	{
//	case ACTION_ENEMY000_NONE:	//�����Ȃ�
//		break;
//
//	case ACTION_ENEMY000_NORMALATTACK:	//�ʏ�U��
//		pAction = new CNormalAttack_Enemy000;
//		break;
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