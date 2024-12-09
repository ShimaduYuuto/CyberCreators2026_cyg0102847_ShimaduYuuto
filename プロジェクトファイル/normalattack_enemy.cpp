////======================================
////
////	�ʏ�U������[normalattack_enemy000.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////�w�b�_�[�̃C���N���[�h
//#include "normalattack_enemy000.h"
//#include "enemy000.h"
//#include "manager.h"
//#include "game.h"
//
//const float CNormalAttack_Enemy000::ATTACK_RANGE = 30.0f;	//�U���͈̔�
//
////============================
////�R���X�g���N�^
////============================
//CNormalAttack_Enemy000::CNormalAttack_Enemy000() :
//	m_fEndCount(0.0f),
//	m_bHit(false)
//{
//
//}
//
////============================
////�f�X�g���N�^
////============================
//CNormalAttack_Enemy000::~CNormalAttack_Enemy000()
//{
//
//}
//
////============================
////������
////============================
//HRESULT CNormalAttack_Enemy000::Init()
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
//void CNormalAttack_Enemy000::Update()
//{
//	//�Q�[���V�[���̎擾
//	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
//
//	//�����蔻����n�߂�J�E���g�ɂȂ�����
//	if (m_fEndCount > START_COLLISION)
//	{
//		//�Q�[���V�[���Ȃ画��
//		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
//		{
//			//�������Ă��Ȃ��Ȃ珈��
//			if (!m_bHit)
//			{
//				//�ϐ��錾
//				D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//�v���C���[�̈ʒu
//				D3DXVECTOR3 AttackRot = GetCharacter()->GetRot();			//�U���̌���
//				D3DXVECTOR3 AttackPos = GetCharacter()->GetPos();			//�U���̈ʒu
//
//				//�U���̈ʒu���Z�o
//				AttackPos += D3DXVECTOR3(sinf(AttackRot.y + D3DX_PI) * 20.0f, 0.0f, cosf(AttackRot.y + D3DX_PI) * 20.0f);
//
//				//�������v�Z
//				float fXZ = sqrtf((AttackPos.x - PlayerPos.x) * (AttackPos.x - PlayerPos.x) + (AttackPos.z - PlayerPos.z) * (AttackPos.z - PlayerPos.z)); //�������Z�o����
//				float fXY = sqrtf((AttackPos.x - PlayerPos.x) * (AttackPos.x - PlayerPos.x) + (AttackPos.y - PlayerPos.y) * (AttackPos.y - PlayerPos.y)); //�������Z�o����
//				float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//�������Z�o
//
//				//�U���͈͓̔��Ȃ�
//				if (fLength < ATTACK_RANGE)
//				{
//					//�v���C���[�Ƀ_���[�W��^����
//					pGame->GetGamePlayer()->SetDamage(DAMAGE_VALUE);
//					m_bHit = true;
//				}
//			}
//		}
//	}
//
//	//�J�E���g�̍X�V
//	m_fEndCount += pGame->GetTime()->GetValue(1.0f);
//
//	//�J�E���g���I���l�ɂȂ�����
//	if (END_TIME < m_fEndCount)
//	{
//		//�A�N�V�����̏I������
//		SetEndAction(true);
//	}
//}