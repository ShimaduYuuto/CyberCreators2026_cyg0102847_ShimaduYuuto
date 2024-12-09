//======================================
//
//	�v���C���[�̏���[player.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "player.h"
#include "manager.h"
#include "game.h"
#include "modelparts.h"
#include "camera.h"
#include "state_player_normal.h"
#include "state_player_damage.h"
#include "state_player_knockback.h"
#include "battleareamanager.h"
#include "barriermanager.h"

//�ÓI�����o�̏�����
const float CPlayer::DAMAGE_IMPULSE = 10.0f;
const std::string CPlayer::FILEPATH = "data\\MODEL\\player001.x";

//============================
//�v���C���[�̃R���X�g���N�^
//============================
CPlayer::CPlayer(int nPriority) : CCharacter(nPriority),
	//m_pAction(),
	//m_pOrbit(nullptr),
	m_pLifeGauge(nullptr),
	m_pState(nullptr)
{
	m_pState = new CState_Player_Normal(this);
	SetType(TYPE_PLAYER);	//��ނ̐ݒ�
	SetCharacterType(CHARACTER_TYPE_PLAYER);
}

//============================
//�v���C���[�̃f�X�g���N�^
//============================
CPlayer::~CPlayer()
{
	
}

//============================
//�v���C���[�̏�����
//============================
HRESULT CPlayer::Init()
{
	//������
	CCharacter::Init();

	//�p�����[�^�̏�����
	CCharacter::SetRot({ 0.0f, 0.0f, 0.0f });
	CCharacter::SetPos({ 0.0f, 0.0f, 0.0f });
	CCharacter::SetGoalRot({ 0.0f, D3DX_PI, 0.0f });
	
	//���[�V�����̓ǂݍ���
	SetMotionInfo("data\\playermotion000.txt");

	//�Q�[�W�̐���
	if (m_pLifeGauge == nullptr)
	{
		m_pLifeGauge = CGauge_PlayerLife::Create(20);
	}

	//���̃��C�t�ݒ�
	SetLife(20);

	return S_OK;
}

//============================
//�v���C���[�̏I������
//============================
void CPlayer::Uninit()
{
	//������
	CCharacter::Uninit();

	//�Q�[�W�̏���
	if (m_pLifeGauge != nullptr)
	{
		m_pLifeGauge->Uninit();
		m_pLifeGauge = nullptr;
	}

	//��Ԃ̏���
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	SetOrbit(false);	//�O�Ղ̍폜
}

//============================
//�v���C���[�̍X�V
//============================
void CPlayer::Update()
{
	//���̏�Ԃ�����Ȃ�ύX
	if (m_pState->GetNextState() != nullptr)
	{
		//���̏�ԂɕύX
		CState_Player* pNext = m_pState->GetNextState();
		delete m_pState;
		m_pState = nullptr;

		//���
		m_pState = pNext;
	}

	//��Ԃɉ������X�V����
	if (m_pState != nullptr)
	{
		m_pState->Update(this);

		//���̏�Ԃ�����Ȃ�ύX
		if (m_pState->GetNextState() != nullptr)
		{
			//���̏�ԂɕύX
			CState_Player* pNext = m_pState->GetNextState();
			delete m_pState;
			m_pState = nullptr;

			//���
			m_pState = pNext;
		}
	}

	//���E�Ƃ̓����蔻��
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
	for (auto itr : pGame->GetBarrierManager()->GetList())
	{
		//���̓����蔻��
		if (GetPos().z + 30.0f >= itr->GetPos().z)
		{
			GetPos().z = itr->GetPos().z - 30.0f;
		}
	}

	//���ʏ����̍X�V
	CCharacter::Update();
}

//============================
//�_���[�W���̏���
//============================
bool CPlayer::SetDamage(int damage)
{
	//�_���[�W�̐ݒ�
	m_pState->SetDamage(this, damage);

	return true;
}

//============================
//�v���C���[�̕`��
//============================
void CPlayer::Draw()
{
	//�L�����N�^�[�N���X�̕`��
	CCharacter::Draw();
}

//============================
//�v���C���[�̃N���G�C�g
//============================
CPlayer* CPlayer::Create()
{
	//�|�C���^�p�̕ϐ�
	CPlayer* pPlayer;

	//�������̊m��
	pPlayer = new CPlayer;

	//������
	pPlayer->Init();

	return pPlayer;
}

//============================
//�d�͂̏���
//============================
D3DXVECTOR3 CPlayer::GravityMove(D3DXVECTOR3 move)
{
	//�󒆂ɂ���Ȃ�d�͂����Z
	if (!GetOnStand())
	{
		//�d�͂̉��Z
		move.y -= GRAVITY;
	}
	else
	{
		//���n���Ă��ė����Ă�����␳
		if (move.y < 0.0f)
		{
			move.y = 0.0f;
		}
	}

	return move;
}

//============================
//�ʒu�̍X�V
//============================
void CPlayer::UpdatePos()
{
	//�p�����[�^�̎擾
	D3DXVECTOR3 pos = CObject::GetPos();	//�ʒu

	//�O��̈ʒu��ۑ�
	GetOldPos() = pos;

	//�d�͂̏���
	if (GetEnableGravity())
	{
		GetMove() = GravityMove(GetMove());
	}

	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//�ړ��ʂ��ʒu�ɉ��Z
		pos += GetMove();

		//�G���A�̊m�F
		if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
		{
			//�ǂƂ̓����蔻��
			CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->GetWall()->GetHit(pos, GetSizeRadius());
		}

		//�����Ă��Ȃ��Ȃ�
		if (!GetOnStand())
		{
			//�n�ʂɐڂ��Ă�����
			if (pGame->GetGameField()->MeshCollision(pos))
			{
				//�����Ă��锻��
				SetOnStand(true);
			}
		}
		else
		{
			//�ʒu��␳
			pos = pGame->GetGameField()->ConvertMeshPos(pos);
		}

		//���̓����蔻��
		pos = pGame->GetGameField()->WidthCollision(pos);
	}

	//�ړ��ʂ�����
	GetMove().x += (0.0f - GetMove().x) * 0.5f;
	GetMove().z += (0.0f - GetMove().z) * 0.5f;

	//�p�����[�^�̐ݒ�
	CObject::SetPos(pos);	//�ʒu
}

//============================
//�O�Ղ̐ݒ�
//============================
void CPlayer::SetOrbit(bool set)
{
	//if (set) //true�Ȃ�
	//{
	//	//�O�Ղ��Ȃ��Ȃ�
	//	if (m_pOrbit == nullptr)
	//	{
	//		m_pOrbit = COrbit::Create();
	//	}
	//	
	//	//���f���p�[�c�̎擾
	//	CModelparts* pModelParts = GetModelParts(15);

	//	//�I�t�Z�b�g�ʒu�̐ݒ�
	//	D3DXVECTOR3 OffsetPos = { 0.0f, 70.0f, 0.0f };
	//	D3DXVec3TransformCoord(&OffsetPos, &OffsetPos, &pModelParts->GetMtx());

	//	//�O�Ղ̐ݒ�
	//	m_pOrbit->SetOrbit(pModelParts->GetWorldPos(), OffsetPos);
	//	m_pOrbit->SetOrbit(OffsetPos, pModelParts->GetWorldPos());
	//}
	//else //false�Ȃ�
	//{
	//	//�O�Ղ��Ȃ��Ȃ�
	//	if (m_pOrbit != nullptr)
	//	{
	//		//�I������
	//		m_pOrbit->Uninit();
	//		m_pOrbit = nullptr;
	//	}
	//}
}

//============================
//�m�b�N�o�b�N�̐ݒ�
//============================
void CPlayer::SetKnockBack(int time)
{
	SetMotion(PLAYERMOTION_KNOCKBACK);	//���[�V�����̐ݒ�

	//�m�b�N�o�b�N�̈ړ��ʂ�ݒ�
	D3DXVECTOR3 Rot = GetRot();
	D3DXVECTOR3 Move = GetMove();
	D3DXVECTOR3 AddMove = { sinf(Rot.y) * 10.0f, 0.0f, cosf(Rot.y) * 10.0f };

	//�ړ��ʂ̉��Z
	Move += AddMove;
	SetMove(Move);
	ChangeState(new CState_Player_Knockback(this));
}

//============================
//�X�e�[�g�̐ݒ�
//============================
void CPlayer::SetState(CState_Player* state)
{
	//�O�Ղ̍폜
	SetOrbit(false);	

	//��Ԃ̕ύX
	delete m_pState;
	m_pState = state;
}

//============================
//�A�N�V�����̐؂�ւ�
//============================
//CAction_Player* CPlayer::ChangeAction(CAction_Player* action)
//{
//	//null�`�F�b�N
//	if (m_pAction != nullptr)
//	{
//		delete m_pAction;
//		m_pAction = nullptr;
//	}
//
//	//�A�N�V�����̐ݒ�
//	m_pAction = action;
//	m_pAction->SetCharacter(this);
//	m_pAction->Init();
//
//	return m_pAction;
//}

//============================
//��Ԃ̕ύX
//============================
void CPlayer::ChangeState(CState_Player* state)
{
	//�`�F�b�N��ɊJ��
	if (m_pState == nullptr)
	{
		delete m_pState;
	}

	m_pState = state;
}