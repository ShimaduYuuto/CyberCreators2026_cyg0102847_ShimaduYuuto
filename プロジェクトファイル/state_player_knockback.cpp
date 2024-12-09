//================================
//
//��Ԃɉ��������������s[state_player_knockback.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_player_knockback.h"
#include "state_player_normal.h"
#include "state_player_damage.h"

//====================================
//��Ԃ̍X�V
//====================================
void CState_Player_Knockback::UpdateState(CPlayer* player)
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
		if (GetNextState() == nullptr)
		{
			//�ʏ��ԂɈڍs
			SetNextState(new CState_Player_Normal(player));
		}
	}

	//��Ԃ̐ݒ�
	SetStateCount(fCount);
}

//========================
//�_���[�W�̐ݒ�
//========================
void CState_Player_Knockback::SetDamage(CPlayer* player, int damage)
{
	//���S�t���O�������Ă����甲����
	if (player->GetDeath())
	{
		return;
	}

	//�_���[�W���󂯂�
	player->CCharacter::SetDamage(damage);
	player->SetMotion(8);											//���[�V�����̐ݒ�
	SetNextState(new CState_Player_Damage(player));					//�X�e�[�g�̐ݒ�

	//�m�b�N�o�b�N�̈ړ��ʂ�ݒ�
	D3DXVECTOR3 Rot = player->GetRot();
	D3DXVECTOR3 Move = player->GetMove();
	D3DXVECTOR3 AddMove = { sinf(Rot.y) * 10.0f, 0.0f, cosf(Rot.y) * 10.0f };

	//�ړ��ʂ̉��Z
	Move += AddMove;
	player->SetMove(Move);

	//�C���X�^���X�̎擾
	CGauge_PlayerLife* pGauge = player->GetLifeGauge();

	//�̗̓Q�[�W�ɔ��f
	if (pGauge != nullptr)
	{
		//�Q�[�W�ɔ��f
		pGauge->GetGauge()->AddGauge(-(float)damage);
	}

	player->SetLifeGauge(pGauge);
}