////======================================
////
////	�ł��グ�U������[arial001.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////�w�b�_�[�̃C���N���[�h
//#include "arial001.h"
//#include "arial002.h"
//#include "manager.h"
//#include "game.h"
//#include "manager.h"
//
////============================
////�R���X�g���N�^
////============================
//CArial001::CArial001()
//{
//
//}
//
////============================
////�f�X�g���N�^
////============================
//CArial001::~CArial001()
//{
//
//}
//
////============================
////������
////============================
//HRESULT CArial001::Init()
//{
//	//������
//	CContinuousAttack::Init();
//
//	//�p�����[�^�̐ݒ�
//	CArial::SetCancelTime(START_CANCELTIME);	//�L�����Z��
//	CArial::SetEndTime(END_TIME);				//�I������
//	CArial::SetCollisionTime(START_COLLISION);	//�����蔻��
//
//	//���[�V�����̐ݒ�
//	CCharacter* pPlayer = GetCharacter();
//	pPlayer->SetMotion(CPlayer::PLAYERMOTION_ARIAL001);
//
//	return S_OK;
//}
//
////============================
////�X�V
////============================
//void CArial001::Update()
//{
//	//�X�V����
//	CContinuousAttack::Update();
//}
//
////============================
////�L�����Z�����̏���
////============================
//void CArial001::Cancel()
//{
//	//���N���b�N��������
//	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
//	{
//		//���̃A�N�V�����̐ݒ�
//		SetNextAction(new CArial002());
//
//		//�A�N�V�����̏I������
//		SetEndAction(true);
//	}
//}