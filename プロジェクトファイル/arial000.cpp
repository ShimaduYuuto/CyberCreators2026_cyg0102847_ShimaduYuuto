////======================================
////
////	�ł��グ�U������[arial000.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////�w�b�_�[�̃C���N���[�h
//#include "arial000.h"
//#include "arial001.h"
//#include "player.h"
//#include "manager.h"
//
////============================
////�R���X�g���N�^
////============================
//CArial000::CArial000()
//{
//
//}
//
////============================
////�f�X�g���N�^
////============================
//CArial000::~CArial000()
//{
//
//}
//
////============================
////������
////============================
//HRESULT CArial000::Init()
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
//	pPlayer->SetMotion(CPlayer::PLAYERMOTION_ARIAL000);
//
//	return S_OK;
//}
//
////============================
////�X�V
////============================
//void CArial000::Update()
//{
//	//�X�V����
//	CContinuousAttack::Update();
//}
//
////============================
////�L�����Z�����̏���
////============================
//void CArial000::Cancel()
//{
//	//���N���b�N��������
//	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
//	{
//		SetNextAction(new CArial001());
//
//		//�A�N�V�����̏I������
//		SetEndAction(true);
//	}
//}