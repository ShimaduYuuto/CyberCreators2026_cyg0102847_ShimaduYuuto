////======================================
////
////	�V�[���h�Đ�����[spawn_shield.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////�w�b�_�[�̃C���N���[�h
//#include "spawn_shield.h"
//#include "enemy000.h"
//#include "manager.h"
//#include "game.h"
//
////============================
////�R���X�g���N�^
////============================
//CSpawn_Shield::CSpawn_Shield() :
//	m_nEndCount(0)
//{
//
//}
//
////============================
////�f�X�g���N�^
////============================
//CSpawn_Shield::~CSpawn_Shield()
//{
//
//}
//
////============================
////������
////============================
//HRESULT CSpawn_Shield::Init()
//{
//	//�A�N�V�����̊J�n����
//	SetEndAction(false);
//	GetCharacter()->SetMotion(CEnemy000::ENEMY000MOTION_ACTION);
//
//	return S_OK;
//}
//
////============================
////�X�V
////============================
//void CSpawn_Shield::Update()
//{
//	//�����蔻����n�߂�J�E���g�ɂȂ�����
//	if (m_nEndCount > SPAWN_TIME)
//	{
//		//�Q�[���V�[���Ȃ画��
//		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
//		{
//			
//		}
//	}
//
//	//�J�E���g�̍X�V
//	m_nEndCount++;
//
//	//�J�E���g���I���l�ɂȂ�����
//	if (END_TIME < m_nEndCount)
//	{
//		//�A�N�V�����̏I������
//		SetEndAction(true);
//	}
//}