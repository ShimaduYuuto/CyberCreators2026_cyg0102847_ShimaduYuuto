////======================================
////
////	�ʏ�U������[normalattack001.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////�w�b�_�[�̃C���N���[�h
//#include "normalattack001.h"
//#include "normalattack002.h"
//#include "manager.h"
//#include "game.h"
//#include "smash.h"
//
////============================
////������
////============================
//HRESULT CNormalAttack001::Init()
//{
//	//���[�V�����̐ݒ�
//	CCharacter* pPlayer = GetCharacter();
//	pPlayer->SetMotion(CPlayer::PLAYERMOTION_ACTION001);
//
//	CContinuousAttack::Init();
//
//	return S_OK;
//}
//
////============================
////�L�����Z�����̏���
////============================
//void CNormalAttack001::Cancel()
//{
//	//���N���b�N��������
//	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
//	{
//		//���̍U���̐���
//		SetNextAction(new CNormalAttack002());
//
//		//�A�N�V�����̏I������
//		SetEndAction(true);
//	}
//	else if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
//	{
//		//���̍U���̐���
//		SetNextAction(new CSmash());
//
//		//�A�N�V�����̏I������
//		SetEndAction(true);
//	}
//}