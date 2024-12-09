//================================
//
//��Ԃɉ��������������s[state_player.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_player.h"
#include "state_player_normal.h"

//====================================
//�f�X�g���N�^
//====================================
CState_Player::~CState_Player()
{
	//�s���C���X�^���X�̔j��
	if (m_pBehavior != nullptr)
	{
		delete m_pBehavior;
		m_pBehavior = nullptr;
	}

	//���̏�Ԃ̃C���X�^���X��j��
	/*if (m_pNextState != nullptr)
	{
		delete m_pNextState;
		m_pNextState = nullptr;
	}*/
}

//====================================
//�ړ�����
//====================================
//void CState_Player::Move(CPlayer* player)
//{
//	//�ړ��̍X�V
//	player->CCharacter::Update();
//}

//====================================
//��Ԃɉ������X�V����
//====================================
void CState_Player::Update(CPlayer* player)
{
	//�A�N�V�����̍X�V
	UpdateBehavior(player);

	//��ԃJ�E���g�̍X�V
	UpdateState(player);
}

//====================================
//�s���̍X�V
//====================================
void CState_Player::UpdateBehavior(CPlayer* player)
{
	//�A�N�V�����̍X�V
	if (m_pBehavior != nullptr)
	{
		//�h����̃A�N�V���������s
		m_pBehavior->Behavior(player);

		//���̃A�N�V����������Ȃ�ύX
		if (m_pBehavior->GetNextBehavior() != nullptr)
		{
			//���̃A�N�V�����ɕύX
			CPlayerBehavior* pNext = m_pBehavior->GetNextBehavior();
			delete m_pBehavior;
			m_pBehavior = nullptr;

			//���
			m_pBehavior = pNext;
		}
	}
}

//====================================
//��ԍX�V����
//====================================
void CState_Player::UpdateState(CPlayer* player)
{
	//�����o�ϐ��̎擾
	float fEndTime{ GetEndTime() };	//�I������
	float fCount{ GetStateCount() };//�J�E���g�̎擾

	//�J�E���g�A�b�v
	fCount++;

	//�J�E���g������؂������Ԃ�؂�ւ���
	if (fCount >= fEndTime)
	{
		//���̏�Ԃ�ݒ�
		if (m_pNextState == nullptr)
		{
			//�ʏ��ԂɈڍs
			m_pNextState = new CState_Player_Normal(player);
		}
	}
}