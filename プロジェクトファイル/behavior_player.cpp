//================================
//
//�v���C���[�̍s���܂Ƃ�[behavior_player.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "behavior_player.h"
#include "manager.h"
#include "game.h"
#include "gauge_slow.h"
#include "effect_hitattack.h"
#include "effect_runsmoke.h"

//�萔
const D3DXVECTOR3 CPlayerBehavior_Attack::POS_OFFSET{ 0.0f, 20.0f, 30.0f };

//================================================================
//�ړ�
//================================================================

//=========================
//�R���X�g���N�^
//=========================
CPlayerBehavior_Move::CPlayerBehavior_Move(CPlayer* player)
{
	player->SetEnableGravity(true);
}

//=========================
//�s��(�ړ�)
//=========================
void CPlayerBehavior_Move::Behavior(CPlayer* player)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 pos = player->GetPos();				//�ʒu�̎擾
	D3DXVECTOR3 goalrot = player->GetGoalRot();		//�ړI�̌����̎擾
	D3DXVECTOR3 move = player->GetMove();			//�ړ��ʂ̎擾

	//X�t�@�C���̓ǂݍ���
	CXfile* pCXfile = CManager::GetInstance()->GetXfile();

	//�W�����v
	if ((CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_SPACE) == true || CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A)) && player->GetOnStand())
	{//SPACE�������ꂽ�ꍇ
		move.y += JUMP_SPEED;
		player->SetOnStand(false);
		player->SetMotion(CPlayer::PLAYERMOTION_JUMP);
	}

	//�󒆂ɂ���Ȃ烂�[�V������ς���
	if(!player->GetOnStand())
	{
		//�W�����v�̃��[�V����
		player->SetMotion(CPlayer::PLAYERMOTION_JUMP);
	}

	//�ړ��ʂ̍X�V
	move += UpdateMove(player, goalrot);

	//�p�����[�^�̐ݒ�
	player->SetPos(pos);			//�ʒu
	player->SetGoalRot(goalrot);	//�ړI�̌���
	player->SetMove(move);			//�ړ���

	//�A�N�V��������
	Action(player);
}

//========================
//�s���̍X�V
//========================
D3DXVECTOR3 CPlayerBehavior_Move::UpdateMove(CPlayer* player, D3DXVECTOR3& Rotgoal)
{
	//�Ԃ��p�̕ϐ�
	D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
	float fRotgoal = 0.0f;
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//���������̔���p
	bool bMove = false;

	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_A))
	{//A�L�[�������ꂽ�ꍇ
		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
		{
			move.x += sinf(D3DX_PI * -0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			move.z -= cosf(D3DX_PI * -0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * 0.75f + pCamera->GetRot().y;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
		{
			move.x += sinf(D3DX_PI * -0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			move.z -= cosf(D3DX_PI * -0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * 0.25f + pCamera->GetRot().y;
		}
		else
		{
			move.x += sinf(D3DX_PI * -0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			move.z += cosf(D3DX_PI * -0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = -(D3DX_PI * -0.5f - pCamera->GetRot().y);
		}

		bMove = true;	//����������
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_D))
	{//D�L�[�������ꂽ�ꍇ

		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
		{
			move.x += sinf(D3DX_PI * 0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			move.z -= cosf(D3DX_PI * 0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * -0.75f + pCamera->GetRot().y;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
		{
			move.x += sinf(D3DX_PI * 0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			move.z -= cosf(D3DX_PI * 0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * -0.25f + pCamera->GetRot().y;
		}
		else
		{
			move.x += sinf(D3DX_PI * 0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			move.z += cosf(D3DX_PI * 0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = -(D3DX_PI * 0.5f - pCamera->GetRot().y);
		}

		bMove = true;								//����������
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
	{//W�L�[�������ꂽ�ꍇ
		{
			move.z -= cosf(D3DX_PI + pCamera->GetRot().y) * MOVE_SPEED;
			move.x -= sinf(D3DX_PI + pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI + pCamera->GetRot().y;
		}

		bMove = true;								//����������
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
	{//S�L�[�������ꂽ�ꍇ
		{
			move.z -= cosf(pCamera->GetRot().y) * MOVE_SPEED;
			move.x -= sinf(pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = pCamera->GetRot().y;
		}

		bMove = true;								//����������
	}

	//���������̔���
	if (bMove && player->GetOnStand())
	{
		//���[�V�����̐ݒ�
		player->SetMotion(CPlayer::PLAYERMOTION_WALK);
	}
	else if (player->GetOnStand())	//�n�ʂɒ����Ă���Ȃ�
	{
		//���[�V�����̐ݒ�
		player->SetMotion(CPlayer::PLAYERMOTION_NORMAL);
	}

	//�ړ��ʂ�Ԃ�
	return move;
}

//============================
//�v���C���[�̃A�N�V��������
//============================
void CPlayerBehavior_Move::Action(CPlayer* player)
{
	//���V�t�g�Ń_�b�V����ݒ�
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		//�A�N�V���������Ă��Ȃ��Ȃ�
		if (GetNextBehavior() == nullptr)
		{
			//�Q�[���V�[���Ȃ画��
			if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
			{
				//�Q�[���V�[���̎擾
				CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

				//���b�N�I������̊m�F
				if (pGame->GetLockon() != nullptr)
				{
					if (pGame->GetLockon()->GetTarget() != nullptr)
					{
						////�^�[�Q�b�g�Ƀ_�b�V��
						//D3DXVECTOR3 TagPos = pGame->GetLockon()->GetTarget()->GetPos();
						//D3DXVECTOR3 Length = TagPos - player->GetPos();
						//float fLength = sqrtf((Length.x * Length.x) + (Length.z * Length.z));

						////�_�b�V�����~�܂�͈͂̊O�Ȃ�_�b�V��
						//if (fLength > CPlayerBehavior_Dash::STOP_LENGYH)
						//{
						//	//�_�b�V���𐶐�
						//	SetNextBehavior(new CPlayerBehavior_Dash(player));
						//}

						//�_�b�V���𐶐�
						SetNextBehavior(new CPlayerBehavior_Dash(player));
					}
				}
			}
			//�_�b�V���𐶐�
			//SetNextBehavior(new CPlayerBehavior_Dash(player));
		}
	}

	//�����Ă�����
	if (player->GetOnStand())
	{
		//�E�N���b�N��������
		if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
		{
			//�A�N�V���������Ă��Ȃ��Ȃ�
			if (GetNextBehavior() == nullptr)
			{
				//�X�}�b�V���A�N�V�����𐶐�
				SetNextBehavior(new CPlayerBehavior_Smash(player));
			}

		}
		else if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
		{

			//�A�N�V���������Ă��Ȃ��Ȃ�
			if (GetNextBehavior() == nullptr)
			{
				//���[�V�����̐ݒ�
				player->SetMotion(CPlayer::PLAYERMOTION_ACTION);

				//�ʏ�U���𐶐�
				SetNextBehavior(new CPlayerBehavior_NormalAttack000(player));
			}
		}
	}
	else //��
	{
		//���N���b�N��������
		if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
		{
			//�A�N�V���������Ă��Ȃ��Ȃ�
			if (GetNextBehavior() == nullptr)
			{
				//���[�V�����̐ݒ�
				player->SetMotion(CPlayer::PLAYERMOTION_ACTION);

				//�󒆍U���ɐ؂�ւ�
				SetNextBehavior(new CPlayerBehavior_Arial000(player));
			}
		}
		else if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
		{
			//�Q�[���V�[���Ȃ画��
			if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
			{
				//�Q�[���V�[���̎擾
				CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

				//���b�N�I���̐ݒ�
				pGame->SetLockon(true);
			}
		}
	}
}

//================================================================
//�_�b�V��
//================================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Dash::CPlayerBehavior_Dash(CPlayer* player)
{
	//���[�V�����̐ݒ������\��
	player->SetMotion(CPlayer::PLAYERMOTION_JUMP);
}

//============================
//�s��(�_�b�V��)
//============================
void CPlayerBehavior_Dash::Behavior(CPlayer* player)
{
	//�����Ă���ԃ_�b�V������
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		//�Ԃ��p�̕ϐ�
		D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };

		//�Q�[���V�[���Ȃ画��
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//�Q�[���V�[���̎擾
			CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

			//���b�N�I������̊m�F
			if (pGame->GetLockon() != nullptr)
			{
				if (pGame->GetLockon()->GetTarget() != nullptr)
				{
					//�^�[�Q�b�g�Ƀ_�b�V��
					D3DXVECTOR3 TagPos = pGame->GetLockon()->GetTarget()->GetPos();
					float fAngle = atan2f(TagPos.x - player->GetPos().x, TagPos.z - player->GetPos().z);
					move.x = sinf(fAngle) * DASH_SPEED;
					move.z = cosf(fAngle) * DASH_SPEED;

					//���b�N�I���̕��Ɍ�����
					player->SetGoalRot({ 0.0f, fAngle + D3DX_PI, 0.0f });

					//effect
					CEffect_RunSmoke::Create(player->GetPos());

					D3DXVECTOR3 Length = TagPos - player->GetPos();
					float fLength = sqrtf((Length.x * Length.x) + (Length.z * Length.z));

					if (fLength < STOP_LENGYH)
					{
						//�ړ���Ԃɂ���
						SetNextBehavior(new CPlayerBehavior_DashAttack000(player));
					}
				}
				
			}
		}
		else
		{
			//���݂̌����ɍ��킹�ă_�b�V��
			move.x = sinf(player->GetRot().y + D3DX_PI) * DASH_SPEED;
			move.z = cosf(player->GetRot().y + D3DX_PI) * DASH_SPEED;
		}

		//�ړ��ʂ̐ݒ�
		player->SetMove({ move.x , player->GetMove().y, move.z });
	}
	else if(CManager::GetInstance()->GetKeyboard()->GetRerease(DIK_LSHIFT)) //��������_�b�V�����I��
	{
		//�ړ���Ԃɂ���
		SetNextBehavior(new CPlayerBehavior_Move(player));
	}
}

//================================================================
//�U��
//================================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Attack::CPlayerBehavior_Attack() :
	m_fAttackLength(0.0f),
	m_HitEnemy(),
	m_nCancelStartTime(0),
	m_nCollisionlTime(0),
	m_nEndCount(0),
	m_nEndTime(0),
	m_OffsetPos({0.0f, 0.0f, 0.0f})
{
	//�p�����[�^�̐ݒ�
	SetEndTime(END_TIME);
	SetCollisionTime(START_COLLISION);
	SetCancelTime(START_CANCEL);
	SetAttackLength(ATTACK_LENGTH);
	SetOffsetPos(POS_OFFSET);
}

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Attack::CPlayerBehavior_Attack(CPlayer* player) :
	m_fAttackLength(0.0f),
	m_HitEnemy(),
	m_nCancelStartTime(0),
	m_nCollisionlTime(0),
	m_nEndCount(0),
	m_nEndTime(0)
{
	//�p�����[�^�̐ݒ�
	SetEndTime(END_TIME);
	SetCollisionTime(START_COLLISION);
	SetCancelTime(START_CANCEL);
	SetAttackLength(ATTACK_LENGTH);
	SetOffsetPos(POS_OFFSET);
}

//============================
//�U���s��
//============================
void CPlayerBehavior_Attack::Behavior(CPlayer* player)
{
	//�J�E���g�����ȏ�Ȃ�
	if (m_nEndCount > m_nCollisionlTime)
	{
		//�Q�[���V�[���Ȃ画��
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//�Q�[���V�[���̎擾
			CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

			//�U������̐���
			D3DXVECTOR3 AttackPos = player->GetPos();
			AttackPos += {sinf(player->GetRot().y + D3DX_PI) * m_OffsetPos.z, m_OffsetPos.y, cosf(player->GetRot().y + D3DX_PI)* m_OffsetPos.z};

			//�G�̎���
			for (auto& iter : pGame->GetEnemyManager()->GetList())
			{
				//����������
				bool bHit = false;

				//���łɓ������Ă��邩���m�F
				for (auto& HitEnemyiter : m_HitEnemy)
				{
					//���łɓ������Ă����甲����
					if (HitEnemyiter == iter)
					{
						bHit = true;	//���łɓ������Ă���
						break;
					}
				}

				//���łɓ������Ă������΂�
				if (bHit)
				{
					continue;
				}

				//�G�̈ʒu���擾
				D3DXVECTOR3 EnemyLength = iter->GetCollision()->GetPos() - AttackPos;

				float fXZ = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.z * EnemyLength.z); //XZ�������Z�o����
				float fXY = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.y * EnemyLength.y); //XY�������Z�o����
				float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//�������Z�o

				//�G�̔�����Ȃ�
				if (fLength < m_fAttackLength)
				{
					//�_���[�W����
					Damage(player, iter, 1);

					D3DXVECTOR3 Move = iter->CCharacter::GetMove();

					//�����Ă����班��������
					if (Move.y < 0.0f)
					{
						Move.y = 0.0f;
					}

					iter->CCharacter::SetMove(Move);

					//�G�̏���ۑ�
					m_HitEnemy.push_back(iter);
				}
			}

			//�e�Ƃ̓����蔻��
			for (auto& iter : pGame->GetEnemyBulletManager()->GetList())
			{
				//���ˍς݂͔�΂�
				if (iter->GetReflection() || !iter->GetShooting())
				{
					continue;
				}

				//�G�̈ʒu���擾
				D3DXVECTOR3 Length = iter->GetCollision()->GetPos() - AttackPos;

				float fXZ = sqrtf(Length.x * Length.x + Length.z * Length.z); //XZ�������Z�o����
				float fXY = sqrtf(Length.x * Length.x + Length.y * Length.y); //XY�������Z�o����
				float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//�������Z�o

				//�G�̔�����Ȃ�
				if (fLength < m_fAttackLength + iter->GetCollision()->GetRadius())
				{
					iter->Reflection();
				}
			}

			//�L�����Z���̃J�E���g�ȏ�ɂȂ�����
			if (m_nEndCount > m_nCancelStartTime)
			{
				//�L�����Z���̏���
				Cancel(player);
			}
		}
	}

	//�I�����ԂɂȂ�����s�����ړ��ɕύX
	if (m_nEndCount >= m_nEndTime)
	{
		if (GetNextBehavior() == nullptr)
		{
			//���̍s����ݒ�
			SetNextBehavior(new CPlayerBehavior_Move(player));
		}
	}

	//�J�E���g�̍X�V
	m_nEndCount++;
}

//============================
//�_���[�W��^���鏈��
//============================
void CPlayerBehavior_Attack::Damage(CPlayer* player, CEnemy* enemy, int damage)
{
	//�_���[�W
	if (enemy->SetDamage(damage, player->GetRot().y))
	{
		//�q�b�g���̏���
		CEffect_HitAttack::Create(enemy->GetCollision()->GetPos());
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_ATTACK);
	}
	else
	{
		enemy->DamageEffect(player);
	}
}

//============================
//�ʏ�U��
//============================
void CPlayerBehavior_NormalAttack::Behavior(CPlayer* player)
{
	//�ړ��ʂ����Z���鎞��
	if (GetCount() < END_MOVE)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//�ړ��ʂ����Z
		D3DXVECTOR3 Move = player->GetMove();
		D3DXVECTOR3 Rot = player->GetRot();

		//�v�Z���ĉ��Z
		Move += { sinf(Rot.y + D3DX_PI)* VALUE_MOVE, 0.0f, cosf(Rot.y + D3DX_PI)* VALUE_MOVE };
		pGame->GetGamePlayer()->SetMove(Move);
	}

	//�U���̏���
	CPlayerBehavior_Attack::Behavior(player);
}

//================================================================
//�ʏ�U��(1�i��)
//================================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_NormalAttack000::CPlayerBehavior_NormalAttack000(CPlayer* player)
{
	player->SetMotion(2);
}

//============================
//�L�����Z��
//============================
void CPlayerBehavior_NormalAttack000::Cancel(CPlayer* player)
{
	//���N���b�N��������
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
	{
		//���̍U���̐���
		SetNextBehavior(new CPlayerBehavior_NormalAttack001(player));
	}
}

//================================================================
//�ʏ�U��(2�i��)
//================================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_NormalAttack001::CPlayerBehavior_NormalAttack001(CPlayer* player)
{
	player->SetMotion(9);
}

//============================
//�L�����Z��
//============================
void CPlayerBehavior_NormalAttack001::Cancel(CPlayer* player)
{
	//���N���b�N��������
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
	{
		//���̍U���̐���
		SetNextBehavior(new CPlayerBehavior_NormalAttack002(player));
	}
	else if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
	{
		//���̍U���̐���
		SetNextBehavior(new CPlayerBehavior_Smash(player));
	}
}

//================================================================
//�ʏ�U��(3�i��)
//================================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_NormalAttack002::CPlayerBehavior_NormalAttack002(CPlayer* player) : m_bChargeEnd(false),m_fChargeRate(0.5f), m_fChargeAcceleration(0.0f)
{
	player->SetMotion(player->PLAYERMOTION_ATTACKCHARGE);

	//�p�����[�^�̐ݒ�
	SetEndTime(20);
	SetCollisionTime(5);
	SetCancelTime(25);
	SetAttackLength(ATTACK_LENGTH);
	SetOffsetPos(POS_OFFSET);
}

//============================
//�s��(�U��)
//============================
void CPlayerBehavior_NormalAttack002::Behavior(CPlayer* player)
{
	if (!m_bChargeEnd)
	{
		//�L�����Z���J�E���g�̉��Z
		if (m_nCancelCount < ACCEPT_CANCELTIME)
		{
			m_nCancelCount++;
		}

		//�}�b�N�X�܂Ń`���[�W
		if (m_fChargeRate < MAX_RATE)
		{
			m_fChargeAcceleration += ACCELERATION_VALUE;
			m_fChargeRate += m_fChargeAcceleration;
		}

		//�U���{�^���𗣂�����U��
		if (CManager::GetInstance()->GetMouse()->GetRerease(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
		{
			//�L�����Z�����Ԍ�ɗ�������`���[�W
			if (m_nCancelCount >= ACCEPT_CANCELTIME)
			{
				//�U�����[�V����
				player->SetMotion(player->PLAYERMOTION_CHARGEATTACK);

				//�`���[�W���I�������
				m_bChargeEnd = true;

				//�e�p�����[�^�̐ݒ�
				SetAttackLength(ATTACK_LENGTH * (m_fChargeRate * 0.01f));
				SetOffsetPos(D3DXVECTOR3(POS_OFFSET.x, POS_OFFSET.y, POS_OFFSET.z * (m_fChargeRate * 0.01f)));
			}
			else
			{
				//�U�����[�V����
				player->SetMotion(10);
			}

			//�`���[�W���I�������
			m_bChargeEnd = true;
		}
	}
	//�`���[�W���I����Ă�����U��
	else
	{
		//�ʏ�U��
		CPlayerBehavior_NormalAttack::Behavior(player);
	}
}

//============================
//�_���[�W��^���鏈��
//============================
void CPlayerBehavior_NormalAttack002::Damage(CPlayer* player, CEnemy* enemy, int damage)
{
	//�q�b�g������
	bool bHit = false;

	//�L�����Z���J�E���g�̉��Z
	if (m_nCancelCount < ACCEPT_CANCELTIME)
	{
		bHit = enemy->SetBlowDamage(damage, player->GetRot().y);
	}
	else
	{
		//�_���[�W
		bHit = enemy->SetBlowDamage(damage * 3, player->GetRot().y, m_fChargeRate * 0.5f);
	}

	//�q�b�g���̏���
	if (bHit)
	{
		CEffect_HitAttack::Create(enemy->GetCollision()->GetPos());
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_ATTACK);
	}
}

//=================================================
//�󒆍U��(1�i��)
//=================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Arial000::CPlayerBehavior_Arial000(CPlayer* player)
{
	player->SetMotion(4);
	player->SetEnableGravity(false);
	player->SetMove({ player->GetMove().x, 0.0f, player->GetMove().z });
}

//============================
//�L�����Z������
//============================
void CPlayerBehavior_Arial000::Cancel(CPlayer* player)
{
	//���N���b�N��������
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
	{
		//���̍U���̐���
		SetNextBehavior(new CPlayerBehavior_Arial001(player));
	}
}

//============================
//�s������(�U��)
//============================
void CPlayerBehavior_Arial000::Behavior(CPlayer* player)
{
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//�󒆍U��(2�i��)
//=================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Arial001::CPlayerBehavior_Arial001(CPlayer* player)
{
	player->SetMotion(5);
}

//============================
//�L�����Z������
//============================
void CPlayerBehavior_Arial001::Cancel(CPlayer* player)
{
	//���N���b�N��������
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
	{
		//���̍U���̐���
		SetNextBehavior(new CPlayerBehavior_Arial002(player));
	}
}

//============================
//�s������(�U��)
//============================
void CPlayerBehavior_Arial001::Behavior(CPlayer* player)
{
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//�󒆍U��(3�i��)
//=================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Arial002::CPlayerBehavior_Arial002(CPlayer* player)
{
	player->SetMotion(6);
}

//============================
//�s������(�U��)
//============================
void CPlayerBehavior_Arial002::Behavior(CPlayer* player)
{
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//�ł��グ�U��
//=================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Smash::CPlayerBehavior_Smash(CPlayer* player) :
	m_pImpact(nullptr),
	m_bAttack(false),
	m_bHit(false),
	m_nDelayCount(0),
	m_nSlowTime(0)
{
	m_pImpact = CImpactRange::Create(player->GetPos());
}						//�R���X�g���N�^

//============================
//�s������(�ł��グ�U��)
//============================
void CPlayerBehavior_Smash::Behavior(CPlayer* player)
{
	//�Q�[���V�[���̃v���C���[�̈ʒu���擾
	CGame* pGame = nullptr;
	pGame = (CGame*)CManager::GetInstance()->GetScene();	//�Q�[���V�[���̎擾
	D3DXVECTOR3 Pos = pGame->GetGamePlayer()->GetPos();		//�ʒu�̎擾

	//�U�������Ă��Ȃ�������
	if (!m_bAttack)
	{
		//�E�{�^���𗣂����瓖���蔻����m�F
		if (CManager::GetInstance()->GetMouse()->GetRerease(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
		{
			//�G�̎���
			for (auto& iter : pGame->GetEnemyManager()->GetList())
			{
				//�ʒu�̎擾
				D3DXVECTOR3 Pos = m_pImpact->GetPos();
				D3DXVECTOR3 EnemyPos = iter->GetPos();

				//�������v�Z
				float fLength = sqrtf((EnemyPos.x - Pos.x) * (EnemyPos.x - Pos.x) + (EnemyPos.z - Pos.z) * (EnemyPos.z - Pos.z));

				//�͈͓��̊m�F
				if (fLength < m_pImpact->GetSize().x * m_pImpact->GetRate() * 0.5f)
				{
					//������я���
					if (iter->SetBlowOff())
					{
						m_nSlowTime += ADD_SLOWTIME; //	�X���[���Ԃ̒ǉ�

						//�t���O���I�t�Ȃ�I���ɂ���
						if (!m_bHit)
						{
							m_bHit = true;
						}
					}
				}
			}

			//�C���p�N�g�͈̔͂�null�Ȃ�
			if (m_pImpact != nullptr)
			{
				//����
				m_pImpact->Uninit();
				m_pImpact = nullptr;
			}

			//�U��������I��
			m_bAttack = true;
			CManager::GetInstance()->GetCamera()->SetShake(15, 15);	//�q�b�g���J������h�炷
		}
	}

	//�U����������
	if (m_bAttack)
	{
		//�J�E���g�̉��Z
		m_nDelayCount++;

		//�x���̃J�E���g���w��l�ɂȂ�����
		if (m_nDelayCount >= DELAY_TIME)
		{
			//�������Ă�����J�E���g
			if (m_bHit)
			{
				//�x���̃J�E���g���w��l�ɂȂ�����
				if (m_nDelayCount >= DELAY_TIME)
				{
					//�Q�[���V�[���̃v���C���[�̈ʒu���擾
					CGame* pGame = nullptr;
					pGame = (CGame*)CManager::GetInstance()->GetScene();	//�Q�[���V�[���̎擾
					pGame->GetTime()->SetStateTimer(pGame->GetTime()->TIME_SLOW, m_nSlowTime);	//���Ԃ̏�Ԃ�ݒ�
					CGauge_Slow::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.05f, 0.0f), (float)m_nSlowTime);
				}
			}
			
			//�s�����ړ��ɕύX
			SetNextBehavior(new CPlayerBehavior_Move(player));
		}
	}

	//�C���p�N�g�͈̔͂�null�Ȃ�
	if (m_pImpact != nullptr)
	{
		//�ʒu�̍X�V
		m_pImpact->SetPos(Pos);
	}
}

//=================================================
//�_�b�V���U��(1�i��)
//=================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_DashAttack000::CPlayerBehavior_DashAttack000(CPlayer* player) : CPlayerBehavior_DashAttack(player)
{
	player->SetMotion(player->PLAYERMOTION_DASHATTACK000);
	player->SetEnableGravity(false);
	player->SetMove({ player->GetMove().x, 0.0f, player->GetMove().z });
}

//============================
//�L�����Z������
//============================
void CPlayerBehavior_DashAttack000::Cancel(CPlayer* player)
{
	//���N���b�N��������
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//���b�N�I������̊m�F
		if (pGame->GetLockon() != nullptr)
		{
			if (pGame->GetLockon()->GetTarget() != nullptr)
			{
				//���̍U���̐���
				SetNextBehavior(new CPlayerBehavior_DashAttack001(player));
			}
		}
	}
}

//============================
//�s������(�U��)
//============================
void CPlayerBehavior_DashAttack000::Behavior(CPlayer* player)
{
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//�_�b�V���U��(2�i��)
//=================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_DashAttack001::CPlayerBehavior_DashAttack001(CPlayer* player) : CPlayerBehavior_DashAttack(player)
{
	player->SetMotion(player->PLAYERMOTION_DASHATTACK001);
}

//============================
//�L�����Z������
//============================
void CPlayerBehavior_DashAttack001::Cancel(CPlayer* player)
{
	//���N���b�N��������
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//���b�N�I������̊m�F
		if (pGame->GetLockon() != nullptr)
		{
			if (pGame->GetLockon()->GetTarget() != nullptr)
			{
				//���̍U���̐���
				SetNextBehavior(new CPlayerBehavior_DashAttack000(player));
			}
		}
	}
}

//============================
//�s������(�U��)
//============================
void CPlayerBehavior_DashAttack001::Behavior(CPlayer* player)
{
	CPlayerBehavior_Attack::Behavior(player);
}