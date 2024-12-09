////======================================
////
////	�ʏ�U������[normalattack.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////�w�b�_�[�̃C���N���[�h
//#include "normalattack.h"
//#include "normalattack000.h"
//#include "normalattack001.h"
//#include "normalattack002.h"
//#include "manager.h"
//#include "game.h"
//
////�萔
//const float CNormalAttack::VALUE_MOVE = 0.8f;
//
////============================
////�R���X�g���N�^
////============================
//CNormalAttack::CNormalAttack()
//{
//
//}
//
////============================
////�f�X�g���N�^
////============================
//CNormalAttack::~CNormalAttack()
//{
//	
//}
//
////============================
////������
////============================
//HRESULT CNormalAttack::Init()
//{
//	return S_OK;
//}
//
////============================
////�X�V
////============================
//void CNormalAttack::Update()
//{
//	//�X�V
//	CContinuousAttack::Update();
//
//	//�ړ��ʂ����Z���鎞��
//	if (GetCount() < END_MOVE)
//	{
//		//�Q�[���V�[���̎擾
//		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
//
//		//�ړ��ʂ����Z
//		D3DXVECTOR3 Move = pGame->GetGamePlayer()->GetMove();
//		D3DXVECTOR3 Rot = pGame->GetGamePlayer()->GetRot();
//
//		//�v�Z���ĉ��Z
//		Move += { sinf(Rot.y + D3DX_PI) * VALUE_MOVE, 0.0f, cosf(Rot.y + D3DX_PI) * VALUE_MOVE };
//		pGame->GetGamePlayer()->SetMove(Move);
//	}
//}
//
////============================
////�L�����Z�����̏���
////============================
//void CNormalAttack::Cancel()
//{
//	
//}