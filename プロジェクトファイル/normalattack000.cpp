////======================================
////
////	�ʏ�U������[normalattack000.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////�w�b�_�[�̃C���N���[�h
//#include "normalattack000.h"
//#include "normalattack001.h"
//#include "manager.h"
//#include "game.h"
//
////============================
////������
////============================
//HRESULT CNormalAttack000::Init()
//{
//	CContinuousAttack::Init();
//
//	return S_OK;
//}
//
////============================
////�L�����Z�����̏���
////============================
//void CNormalAttack000::Cancel()
//{
//	//���N���b�N��������
//	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
//	{
//		//���̍U���̐���
//		SetNextAction(new CNormalAttack001());
//
//		//�A�N�V�����̏I������
//		SetEndAction(true);
//	}
//}