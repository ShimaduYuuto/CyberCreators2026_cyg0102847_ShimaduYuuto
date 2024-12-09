//======================================
//
//	�G�l�~�[�̏���[enemy.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "enemy.h"
#include "manager.h"
#include "game.h"
#include "enemy000.h"
#include "enemy001.h"
#include "enemy002.h"
#include "enemy003.h"
#include "state_enemy_damage.h"
#include "battleareamanager.h"

//============================
//�G�l�~�[�̃R���X�g���N�^
//============================
CEnemy::CEnemy(int nPriority) : 
	CCharacter(nPriority), m_Collision(),
	m_EnemyType(),
	m_pState(nullptr)
{
	//�G�̎�ނ�ݒ�
	m_EnemyType = ENEMYTYPE_ENEMY000;
	SetType(TYPE_ENEMY);	//�G�̎��

	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//�}�l�[�W���[�ɓo�^
		pGame->GetEnemyManager()->Regist(this);

		//�����蔻��̐���
		if (m_Collision == nullptr)
		{
			m_Collision = CCollision::Create(GetSizeRadius(), D3DXVECTOR3(0.0f, 30.0f, 0.0f));
		}
	}
}

//============================
//�G�l�~�[�̃f�X�g���N�^
//============================
CEnemy::~CEnemy()
{
	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//�}�l�[�W���[����폜
		pGame->GetEnemyManager()->Erase(this);

		if (pGame->GetLockon() != nullptr)
		{
			pGame->GetLockon()->Erase(this);
		}
	}

	//�G�̐������炷
	if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
	{
		CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->DecrementEnemyNum();
	}

	//�����蔻��̏���
	if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}
}

//============================
//�G�l�~�[�̏�����
//============================
HRESULT CEnemy::Init()
{
	//������
	CCharacter::Init();

	return S_OK;
}

//============================
//�G�l�~�[�̏I������
//============================
void CEnemy::Uninit()
{
	//���S�t���O�������Ă����甲����
	if (GetDeath())
	{
		return;
	}

	//������
	CCharacter::Uninit();
}

//============================
//�G�l�~�[�̍X�V
//============================
void CEnemy::Update()
{
	//��Ԃɉ������X�V����
	if (m_pState != nullptr)
	{
		m_pState->Update(this);

		//���̃A�N�V����������Ȃ�ύX
		if (m_pState->GetNextState() != nullptr)
		{
			//���̃A�N�V�����ɕύX
			CState_Enemy* pNext = m_pState->GetNextState();
			delete m_pState;
			m_pState = nullptr;

			//���
			m_pState = pNext;
		}
	}

	//���ʏ����̍X�V
	CCharacter::Update();

	//�����蔻��̈ʒu�̍X�V
	m_Collision->Update(GetPos());
}

//============================
//�G�l�~�[�̕`��
//============================
void CEnemy::Draw()
{
	
}

//============================
//�G�l�~�[�̃N���G�C�g
//============================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	//��ނɉ����ē��I�m��
	CEnemy* pEnemy = nullptr;

	switch (type)
	{
	case ENEMYTYPE_ENEMY000:	//�ʏ�̓G

		//�G�̃������m��
		pEnemy = new CEnemy000;
		break;

	case ENEMYTYPE_ENEMY001:	//�������̓G

	//�G�̃������m��
		pEnemy = new CEnemy001;
		break;

	case ENEMYTYPE_ENEMY002:	//�{�X�̓G

	//�G�̃������m��
		pEnemy = new CEnemy002;
		break;

	case ENEMYTYPE_ENEMY003:	//�ːi�̓G

	//�G�̃������m��
		pEnemy = new CEnemy003;
		break;
	}

	//������
	pEnemy->Init();

	//�ʒu�̐ݒ�
	pEnemy->SetPos(pos);

	//�ݒ肵������Ԃ�
	return pEnemy;
}

//============================
//�_���[�W�̐ݒ�
//============================
bool CEnemy::SetDamage(int damage)
{
	//�U�����~�߂�
	//SetMotion(0);

	//�_���[�W�̐ݒ�
	CCharacter::SetDamage(damage);

	return true;
}

//============================
//�_���[�W�̐ݒ�
//============================
bool CEnemy::SetDamage(int damage, float rotY)
{
	//�m�b�N�o�b�N�̐ݒ�
	D3DXVECTOR3 Move = {sinf(rotY + D3DX_PI) * VALUE_KNOCKBACK, 0.0f, cosf(rotY + D3DX_PI) * VALUE_KNOCKBACK };

	//�ړ��ʂ�ݒ�
	CCharacter::AddMove(Move);

	//�_���[�W�̐ݒ�
	CEnemy::SetDamage(damage);

	return true;
}

//============================
//������΂��ă_���[�W�̐ݒ�
//============================
bool CEnemy::SetBlowDamage(int damage, float rotY)
{
	//�������Ȃ��琁����΂�
	AddMove(D3DXVECTOR3(0.0f, 7.0f, 0.0f));
	D3DXVECTOR3 Blow = { sinf(rotY + D3DX_PI) * VALUE_BLOWOFF, 0.0f, cosf(rotY + D3DX_PI) * VALUE_BLOWOFF };
	SetBlowValue(Blow);
	SetOnStand(false);
	CEnemy::SetDamage(damage, rotY);

	//������я�ԂɕύX
	ChangeState(new CState_Enemy_Blow(this));

	return true;
}

//============================
//������΂��ă_���[�W�̐ݒ�
//============================
bool CEnemy::SetBlowDamage(int damage, float rotY, float value)
{
	//�������Ȃ��琁����΂�
	AddMove(D3DXVECTOR3(0.0f, 7.0f, 0.0f));
	D3DXVECTOR3 Blow = { sinf(rotY + D3DX_PI) * value, 0.0f, cosf(rotY + D3DX_PI) * value };
	SetBlowValue(Blow);
	SetOnStand(false);
	SetDamage(damage, rotY);

	//������я�ԂɕύX
	ChangeState(new CState_Enemy_Blow(this));

	return true;
}

//============================
//������я���
//============================
bool CEnemy::SetBlowOff()
{
	//������ԏ���
	CCharacter::SetMove(D3DXVECTOR3(0.0f, VALUE_BLOWOFF, 0.0f));	//�ړ��ʂ̐ݒ�
	SetOnStand(false);												//�����Ă��Ȃ���Ԃɐݒ�
	SetEnableGravity(true);											//�d�͂��󂯂�

	return true;
}

//============================
//��Ԃ̕ύX
//============================
void CEnemy::ChangeState(CState_Enemy* state)
{
	//�`�F�b�N��ɊJ��
	if (m_pState != nullptr)
	{
		delete m_pState;
	}
	
	m_pState = state;
}