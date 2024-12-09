//================================
//
//�G�̍s���܂Ƃ�[behavior_enemy002.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy002.h"
#include "enemy002.h"
#include "enemybullet.h"
#include "game.h"
#include "manager.h"

//======================================================================
//�ҋ@
//======================================================================

//====================================
//�A�N�V����(�ҋ@)
//====================================
void CEnemyAction_Standby::Action(CEnemy* enemy)
{
	//�N�[���^�C�����I������玟�̍s�����s��
	m_nCoolTime--;

	if (m_nCoolTime < 0)
	{
		//�U������
		SetNextAction(new CEnemyAction_ChargeShot(enemy));
	}
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyAction_Standby::NextAction(CEnemy* enemy)
{
	//�U����ݒ�
	SetNextAction(new CEnemyAction_Attack002(enemy));
}

//======================================================================
//�`���[�W�V���b�g
//======================================================================

//====================================
//�A�N�V����(�`���[�W�V���b�g)
//====================================
void CEnemyAction_ChargeShot::Action(CEnemy* enemy)
{
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

		//�J�E���g�̍X�V
		m_nChargeCount++;

		//�e�̐������ԂɂȂ����琶��
		if (m_nChargeCount > CREATE_BULLET_TIME)
		{
			//�e�̐���
			if (m_pBullet == nullptr)
			{
				m_pBullet = CEnemyBullet::Create(enemy->GetCollision()->GetPos(), { 0.0f, 0.0f, 0.0f });
				m_pEffect = CEffect_ChargeShot::Create(enemy->GetCollision()->GetPos());
			}
		}

		//�e�������ς݂Ȃ�
		if (m_pBullet != nullptr)
		{
			//�X�P�[����傫������
			m_pBullet->AddSizeRate(ADD_SCALE_VALUE);
			m_pBullet->SetPos({ enemy->GetCollision()->GetPos().x + sinf(fAngle) * 20.0f * m_pBullet->GetSizeRate() , enemy->GetCollision()->GetPos().y, enemy->GetCollision()->GetPos().z + cosf(fAngle) * 20.0f * m_pBullet->GetSizeRate() });

			//�`���[�W���Ԃ��I�����甭��
			if (m_nChargeCount > CHARGE_TIME)
			{
				//�����Ă�������Ɍ���
				m_pBullet->SetMove({ sinf(fAngle) * 3.0f, 0.0f, cosf(fAngle) * 3.0f });
				m_pBullet->SetShooting(true);

				//�G�t�F�N�g�̔j��
				if (m_pEffect != nullptr)
				{
					m_pEffect->Uninit();
					m_pEffect = nullptr;
				}	
			}
		}
	}

	//�I���̎��ԂɂȂ�����ҋ@�A�N�V����
	if (m_nChargeCount > END_TIME)
	{
		SetNextAction(new CEnemyAction_Standby(enemy));
	}

	//�������Ă��������
	if (m_pBullet != nullptr)
	{
		if (m_pBullet->GetDeath())
		{
			m_pBullet = nullptr;
			SetNextAction(new CEnemyAction_Standby(enemy));
		}
	}
}

//======================================================================
//�o�ꉉ�o
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyAction_Direction::CEnemyAction_Direction(CEnemy* enemy) :
	m_nCount(0)
{
	enemy->SetMotion(6);
}

//====================================
//�A�N�V����(���o)
//====================================
void CEnemyAction_Direction::Action(CEnemy* enemy)
{
	//���o�̎��Ԃ��I�������s���J�n
	m_nCount++;

	if (m_nCount > DIRECTION_TIME)
	{
		NextAction(enemy);
	}
}