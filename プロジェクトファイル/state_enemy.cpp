//================================
//
//��Ԃɉ��������������s[state_enemy.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_enemy.h"
#include "game.h"
#include "manager.h"
#include "state_enemy_normal.h"

//====================================
//�f�X�g���N�^
//====================================
CState_Enemy::~CState_Enemy()
{
	//�A�N�V�����̔j��
	if (m_pAction != nullptr)
	{
		delete m_pAction;
		m_pAction = nullptr;
	}

	//���̏�Ԃ�j��
	if (m_pNextState != nullptr)
	{
		//delete m_pNextState;
		m_pNextState = nullptr;
	}
}

//====================================
//�X�V����
//====================================
void CState_Enemy::Update(CEnemy* enemy)
{
	//�A�N�V�����̍X�V
	UpdateAction(enemy);

	//��ԃJ�E���g�̍X�V
	UpdateState(enemy);
}

//====================================
//�A�N�V��������
//====================================
void CState_Enemy::UpdateAction(CEnemy*& enemy)
{
	//�A�N�V�����̍X�V
	if (m_pAction != nullptr)
	{
		//�h����̃A�N�V���������s
		m_pAction->Action(enemy);

		//���̃A�N�V����������Ȃ�ύX
		if (m_pAction->GetNextAction() != nullptr)
		{
			//���̃A�N�V�����ɕύX
			CEnemyAction* pNext = m_pAction->GetNextAction();
			delete m_pAction;
			m_pAction = nullptr;

			//���
			m_pAction = pNext;
		}
	}
}

//====================================
//��ԍX�V����
//====================================
void CState_Enemy::UpdateState(CEnemy* enemy)
{
	//�����o�ϐ��̎擾
	float fEndTime{ GetEndTime() };	//�I������
	float fCount{ GetStateCount() };//�J�E���g�̎擾

	//�J�E���g�A�b�v
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();	//�Q�[���V�[���̎擾
	fCount += pGame->GetTime()->GetValue<float>(1.0f);			//���Ԃɉ����ăJ�E���g�A�b�v

	//�J�E���g������؂������Ԃ�؂�ւ���
	if (fCount >= fEndTime)
	{
		//���̏�Ԃ�ݒ�
		if (m_pNextState == nullptr)
		{
			m_pNextState = new CState_Enemy_Normal();
		}
	}
}

//====================================
//�G�l�~�[���m�̓����蔻��
//====================================
void CState_Enemy::EnemyCollision(CEnemy* enemy)
{
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();	//�Q�[���V�[���̎擾
	CEnemyManager* pManager = pGame->GetEnemyManager();			//�G�l�~�[�}�l�[�W���[�̎擾

	//���̓G�Ƃ̓����蔻��
	for (auto& itr : pManager->GetList())
	{
		//�������g�Ȃ��΂�
		if (itr == enemy)
		{
			continue;
		}

		//�G�̈ʒu���擾
		D3DXVECTOR3 EnemyLength = itr->GetCollision()->GetPos() - enemy->GetCollision()->GetPos();

		//���̓G�Ƃ̋������Z�o
		float fXZ = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.z * EnemyLength.z);	//XZ�������Z�o����
		float fXY = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.y * EnemyLength.y);	//XY�������Z�o����
		float fLength = sqrtf(fXZ * fXZ + fXY * fXY);										//�������Z�o

		//�������Ă����玩���̈ʒu��͈͊O�ɂ���
		if (fLength < itr->GetCollision()->GetRadius() + enemy->GetCollision()->GetRadius())
		{
			//�v�Z�p�̕ϐ�
			D3DXVECTOR3 Pos = enemy->GetPos();

			//�p�x���Z�o���ĕ␳
			float fAngle = atan2f(EnemyLength.x, EnemyLength.z);

			//�~�̓����ɕ␳
			Pos.x = sinf(fAngle + D3DX_PI) * (itr->GetCollision()->GetRadius() + enemy->GetCollision()->GetRadius()) + itr->GetPos().x;
			Pos.z = cosf(fAngle + D3DX_PI) * (itr->GetCollision()->GetRadius() + enemy->GetCollision()->GetRadius()) + itr->GetPos().z;

			//�␳��̈ʒu��ݒ�
			enemy->SetPos(Pos);
		}
	}
}