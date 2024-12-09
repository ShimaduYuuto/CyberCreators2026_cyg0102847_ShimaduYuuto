//================================
//
//��Ԃɉ��������������s[state_enemy_damage.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_enemy_normal.h"
#include "game.h"
#include "manager.h"

//====================================
//�R���X�g���N�^
//====================================
CState_Enemy_Normal::CState_Enemy_Normal(CEnemy* enemy)
{
	//�����A�N�V����
	enemy->SetEnableGravity(true);
}

//====================================
//��ԍX�V����
//====================================
void CState_Enemy_Normal::UpdateState(CEnemy* enemy)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//���̓G�Ƃ̓����蔻��
	EnemyCollision(enemy);

	//�e�M�~�b�N�Ƃ̓����蔻��
	for (auto& iter : pGame->GetGimmickManager()->GetList())
	{
		//�ʒu�̎擾
		D3DXVECTOR3 Pos = iter->GetCollision()->GetPos();
		D3DXVECTOR3 EnemyPos = enemy->GetCollision()->GetPos();

		//�������v�Z
		float fLength = sqrtf((EnemyPos.x - Pos.x) * (EnemyPos.x - Pos.x) + (EnemyPos.z - Pos.z) * (EnemyPos.z - Pos.z));
		float fTotalRadius = iter->GetCollision()->GetRadius() + enemy->GetCollision()->GetRadius();

		//�͈͓��̊m�F
		if (fLength < fTotalRadius)
		{
			//�M�̓�����Ȃ��ʒu�ɕ␳
			float fAngle = atan2f(Pos.x - EnemyPos.x, Pos.z - EnemyPos.z);//�Ίp���̊p�x���Z�o

			//�~�̓����ɕ␳
			enemy->SetPos(D3DXVECTOR3(sinf(fAngle + D3DX_PI) * fTotalRadius + Pos.x,
				enemy->GetPos().y,
				cosf(fAngle + D3DX_PI) * fTotalRadius + Pos.z));
		}
	}
}