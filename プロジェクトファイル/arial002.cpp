////======================================
////
////	�ł��グ�U������[arial002.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////�w�b�_�[�̃C���N���[�h
//#include "arial002.h"
//#include "manager.h"
//#include "game.h"
//#include "manager.h"
//
////============================
////�R���X�g���N�^
////============================
//CArial002::CArial002()
//{
//
//}
//
////============================
////�f�X�g���N�^
////============================
//CArial002::~CArial002()
//{
//
//}
//
////============================
////������
////============================
//HRESULT CArial002::Init()
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
//	pPlayer->SetMotion(CPlayer::PLAYERMOTION_ARIAL002);
//
//	return S_OK;
//}
//
////============================
////�X�V
////============================
//void CArial002::Update()
//{
//	//�X�V����
//	CContinuousAttack::Update();
//}