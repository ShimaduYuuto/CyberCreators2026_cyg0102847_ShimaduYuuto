//================================
//
//�G�̍s���܂Ƃ�[behavior_enemy.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy.h"
#include "manager.h"
#include "game.h"

const float CEnemyMove_Chase::VALUE_MOVE = 1.0f;

//====================================
//�ǂ���������
//====================================
void CEnemyAction_Chase::Action(CEnemy* enemy)
{
	//�Q�[���V�[���̃v���C���[�̈ʒu���擾
	CGame* pGame = nullptr;
	pGame = (CGame*)CManager::GetInstance()->GetScene();		//�Q�[���V�[���̎擾
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 Pos = enemy->GetPos();							//�����̈ʒu���擾

	//�v���C���[�Ƃ̊p�x���Z�o
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//�Ίp���̊p�x���Z�o

	//�p�x��ݒ�
	enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });

	//�����Ă�����
	if (enemy->CCharacter::GetOnStand())
	{
		//�����̌v�Z
		D3DXVECTOR3 fLengthPos = PlayerPos - Pos;
		float fLength = sqrtf(fLengthPos.x * fLengthPos.x + fLengthPos.z * fLengthPos.z);

		//���͈͓��ɓ�������U��
		if (fLength < 30.0f)
		{
			//���̃A�N�V�����Ɉڍs
			NextAction(enemy);
		}
		else
		{
			enemy->CCharacter::AddMove({ sinf(fAngle) * VALUE_MOVE, 0.0f, cosf(fAngle) * VALUE_MOVE });
			enemy->SetMotion(1);
		}
	}
	else
	{
		enemy->CCharacter::SetMove({ 0.0f, enemy->CCharacter::GetMove().y, 0.0f });
		enemy->SetMotion(3);
	}
}

//===========================
//�U���N���X
//===========================

//===============================
//�R���X�g���N�^
//===============================
CEnemyAction_Attack::CEnemyAction_Attack() : m_pAttack(nullptr), m_fAttackLength(0.0f)
{
	//�C���X�^���X�𐶐�
	if (m_pAttack == nullptr)
	{
		m_pAttack = new CAttack();
	}
}

//===============================
//�f�X�g���N�^
//===============================
CEnemyAction_Attack::~CEnemyAction_Attack()
{
	//�U���|�C���^�̊J��
	if (m_pAttack != nullptr)
	{
		delete m_pAttack;
		m_pAttack = nullptr;
	}
}

//===============================
//�U������
//===============================
void CEnemyAction_Attack::Action(CEnemy* enemy)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//�p�����[�^�̎擾
	bool bHit = m_pAttack->GetHit();
	float fCount = m_pAttack->GetActionCount();
	float fCollisionTime = m_pAttack->GetCollisionTime();
	float fEndTime = m_pAttack->GetEndTime();
	int nDamageValue = m_pAttack->GetDamageValue();

	//�����蔻����n�߂�J�E���g�ɂȂ�����
	if (fCount > fCollisionTime)
	{
		//�������Ă��Ȃ��Ȃ珈��
		if (!bHit)
		{
			//�ϐ��錾
			D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//�v���C���[�̈ʒu
			D3DXVECTOR3 AttackRot = enemy->GetRot();					//�U���̌���
			D3DXVECTOR3 AttackPos = enemy->GetPos();					//�U���̈ʒu

			//�U���̈ʒu���Z�o
			AttackPos += D3DXVECTOR3(sinf(AttackRot.y + D3DX_PI) * 20.0f, 0.0f, cosf(AttackRot.y + D3DX_PI) * 20.0f);

			//�������v�Z
			float fXZ = sqrtf((AttackPos.x - PlayerPos.x) * (AttackPos.x - PlayerPos.x) + (AttackPos.z - PlayerPos.z) * (AttackPos.z - PlayerPos.z)); //�������Z�o����
			float fXY = sqrtf((AttackPos.x - PlayerPos.x) * (AttackPos.x - PlayerPos.x) + (AttackPos.y - PlayerPos.y) * (AttackPos.y - PlayerPos.y)); //�������Z�o����
			float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//�������Z�o

			//�U���͈͓̔��Ȃ�
			if (fLength < m_fAttackLength)
			{
				//�v���C���[�Ƀ_���[�W��^����
				pGame->GetGamePlayer()->SetDamage(nDamageValue);
				bHit = true;
			}
		}
	}

	//�J�E���g�̍X�V
	fCount += pGame->GetTime()->GetValue(1.0f);

	//�p�����[�^�̐ݒ�
	m_pAttack->SetHit(bHit);
	m_pAttack->SetActionCount(fCount);
	m_pAttack->SetCollisionTime(fCollisionTime);
	m_pAttack->SetEndTime(fEndTime);
	m_pAttack->SetDamageValue(nDamageValue);

	//�J�E���g���I���l�ɂȂ������Ԃ̕ύX
	if (fEndTime < fCount)
	{
		NextAction(enemy);
	}
}

//================================================================
//�ȉ��̓o�b�N�A�b�v
//================================================================

//====================================
//�ړ�����
//====================================
void CEnemyMove_Chase::Move(CEnemy* enemy)
{
	//�Q�[���V�[���̃v���C���[�̈ʒu���擾
	CGame* pGame = nullptr;
	pGame = (CGame*)CManager::GetInstance()->GetScene();		//�Q�[���V�[���̎擾
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 Pos = enemy->GetPos();							//�����̈ʒu���擾

	//�v���C���[�Ƃ̊p�x���Z�o
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//�Ίp���̊p�x���Z�o

	//�p�x��ݒ�
	enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });

	//�����Ă�����
	if (enemy->CCharacter::GetOnStand())
	{
		enemy->CCharacter::AddMove({ sinf(fAngle) * VALUE_MOVE, 0.0f, cosf(fAngle) * VALUE_MOVE });
		enemy->SetMotion(1);
	}
	else
	{
		enemy->CCharacter::SetMove({ 0.0f, enemy->CCharacter::GetMove().y, 0.0f });
		enemy->SetMotion(3);
	}
}

//====================================
//�U������
//====================================
void CEnemyAttack::Attack(CEnemy* enemy)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//�p�����[�^�̎擾
	bool bHit = GetHit();
	float fCount = GetActionCount();
	float fCollisionTime = GetCollisionTime();
	float fEndTime = GetEndTime();
	int nDamageValue = GetDamageValue();

	//�����蔻����n�߂�J�E���g�ɂȂ�����
	if (fCount > fCollisionTime)
	{
		//�Q�[���V�[���Ȃ画��
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//�������Ă��Ȃ��Ȃ珈��
			if (!bHit)
			{
				//�ϐ��錾
				D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//�v���C���[�̈ʒu
				D3DXVECTOR3 AttackRot = enemy->GetRot();					//�U���̌���
				D3DXVECTOR3 AttackPos = enemy->GetPos();					//�U���̈ʒu

				//�U���̈ʒu���Z�o
				AttackPos += D3DXVECTOR3(sinf(AttackRot.y + D3DX_PI) * 20.0f, 0.0f, cosf(AttackRot.y + D3DX_PI) * 20.0f);

				//�������v�Z
				float fXZ = sqrtf((AttackPos.x - PlayerPos.x) * (AttackPos.x - PlayerPos.x) + (AttackPos.z - PlayerPos.z) * (AttackPos.z - PlayerPos.z)); //�������Z�o����
				float fXY = sqrtf((AttackPos.x - PlayerPos.x) * (AttackPos.x - PlayerPos.x) + (AttackPos.y - PlayerPos.y) * (AttackPos.y - PlayerPos.y)); //�������Z�o����
				float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//�������Z�o

				//�U���͈͓̔��Ȃ�
				if (fLength < m_fAttackLength)
				{
					//�v���C���[�Ƀ_���[�W��^����
					pGame->GetGamePlayer()->SetDamage(nDamageValue);
					bHit = true;
				}
			}
		}
	}

	//�J�E���g�̍X�V
	fCount += pGame->GetTime()->GetValue(1.0f);

	//�J�E���g���I���l�ɂȂ�����
	if (fEndTime < fCount)
	{
		//�A�N�V�����̏I������
		SetEndAction(true);
	}

	//�p�����[�^�̐ݒ�
	SetHit(bHit);
	SetActionCount(fCount);
	SetCollisionTime(fCollisionTime);
	SetEndTime(fEndTime);
	SetDamageValue(nDamageValue);
}