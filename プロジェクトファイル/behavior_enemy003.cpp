//================================
//
//�G�̍s���܂Ƃ�[behavior_enemy003.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy003.h"
#include "enemy003.h"
#include "game.h"
#include "manager.h"

//======================================================================
//�ҋ@
//======================================================================

//====================================
//�A�N�V����(�ҋ@)
//====================================
void CEnemyAction_Standby003::Action(CEnemy* enemy)
{
	//�N�[���^�C�����I������玟�̍s�����s��
	m_nCoolTime--;

	if (m_nCoolTime < 0)
	{
		//�U������
		SetNextAction(new CEnemyAction_ChargeAttack(enemy));
	}
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyAction_Standby003::NextAction(CEnemy* enemy)
{
	//�U����ݒ�
	SetNextAction(new CEnemyAction_Attack003(enemy));
}

//======================================================================
//�`���[�W�A�^�b�N
//======================================================================

//====================================
//�A�N�V����(�`���[�W�A�^�b�N)
//====================================
void CEnemyAction_ChargeAttack::Action(CEnemy* enemy)
{
	//�J�E���g�̍X�V
	m_nChargeCount++;

	//�J�E���g�����؂��Ă��Ȃ��Ȃ�X�V
	if (m_nChargeCount <= CHARGE_TIME)
	{
		CGame* pGame = nullptr;
		pGame = (CGame*)CManager::GetInstance()->GetScene();		//�Q�[���V�[���̎擾
		D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 Pos = enemy->GetPos();							//�����̈ʒu���擾

		//�v���C���[�Ƃ̊p�x���Z�o
		float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//�Ίp���̊p�x���Z�o

		//�p�x��ݒ�
		enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });

		//�`���[�W���I�������U��
		if (m_nChargeCount >= CHARGE_TIME)
		{
			//�U������ɂ���
			CEnemy003* pEnemy003 = (CEnemy003*)enemy;
			pEnemy003->SetAttacking(true);

			//�ړ��l�̐ݒ�
			enemy->SetMove({ sinf(fAngle) * SPEED_MOVE, 0.0f, cosf(fAngle) * SPEED_MOVE });
			m_fAttackAngle = fAngle;
		}
	}
	else
	{
		//�ړ��l�̐ݒ�
		enemy->SetMove({ sinf(m_fAttackAngle) * SPEED_MOVE, 0.0f, cosf(m_fAttackAngle) * SPEED_MOVE });

		//�I���̎��ԂɂȂ�����ҋ@
		if (m_nChargeCount > END_TIME)
		{
			//�U������̏I��
			CEnemy003* pEnemy003 = (CEnemy003*)enemy;
			pEnemy003->SetAttacking(false);

			SetNextAction(new CEnemyAction_Standby003(enemy));
		}
	}
	
}