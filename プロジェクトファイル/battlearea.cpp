//======================================
//
//	�o�g���G���A�̏���[battlearea.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "battlearea.h"
#include "manager.h"
#include "game.h"
#include "battleareamanager.h"
#include "spawn_enemy.h"
#include "explodingbarrel.h"

//============================
//�R���X�g���N�^
//============================
CBattleArea::CBattleArea() :
	m_EnemyList(),
	m_fRadius(500.0f),
	m_pWall(nullptr),
	m_Pos(),
	m_nEnemyNum(0),
	m_bEnd(false),
	m_bEnteredArea(false)
{
	
}

//============================
//�f�X�g���N�^
//============================
CBattleArea::~CBattleArea()
{
	//�ǂɏI�������n��
	if (m_pWall != nullptr)
	{
		m_pWall->SetEnd(true);
		m_pWall =  nullptr;
	}

	//���E������
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
	pGame->GetBarrierManager()->Erase();
}

//============================
//������
//============================
HRESULT CBattleArea::Init()
{
	return S_OK;
}

//============================
//�I������
//============================
void CBattleArea::Uninit()
{
	m_bEnd = true;
}

//============================
//�X�V����
//============================
void CBattleArea::Update()
{
	//���łɃG���A���œG���c���Ă���Ȃ甲����
	if (m_bEnteredArea && m_nEnemyNum > 0)
	{
		return;
	}
	else if (m_bEnteredArea && m_nEnemyNum == 0)	//�G���S�ł���������j��
	{
		//BGM�X�g�b�v
		CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_BATTLE);
		m_bEnd = true;
		return;
	}

	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�v���C���[���G���A�ɓ����Ă��邩���m�F
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
		D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//�v���C���[�ʒu
		float fLength = sqrtf((PlayerPos.x - m_Pos.x) * (PlayerPos.x - m_Pos.x) + (PlayerPos.z - m_Pos.z) * (PlayerPos.z - m_Pos.z));	//xz���ʂ̋������Z�o

		//���m�͈͓��Ȃ�G���A�𐶐�
		if (fLength < RADIUS_ENTEREDAREA)
		{
			//�ǂ̐���
			if (m_pWall == nullptr)
			{
				m_pWall = CCollision_Wall::Create(m_Pos, m_fRadius);
			}

			//�o�g���G���A�ɓ�����
			m_bEnteredArea = true;
			CBattleAreaManager::GetInstance()->SetCurrentBattleArea(this);	//���݂̃G���A�Ƃ��ēo�^

			//�G�l�~�[�̐���
			SpawnEnemy();

			//�M�~�b�N�̐���
			SpawnGimmick();

			//BGM�X�^�[�g
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BATTLE);
		}
	}
}

//============================
//�G�̐���
//============================
void CBattleArea::SpawnEnemy()
{
	//���̓G����
	CSpawn_Enemy::Create(m_Pos, CEnemy::ENEMYTYPE_ENEMY000);
	CSpawn_Enemy::Create(m_Pos + D3DXVECTOR3(150.0f, 0.0f, 150.0f), CEnemy::ENEMYTYPE_ENEMY000);
	CSpawn_Enemy::Create(m_Pos + D3DXVECTOR3(-150.0f, 0.0f, -150.0f), CEnemy::ENEMYTYPE_ENEMY000);
}

//============================
//�M�~�b�N�̐���
//============================
void CBattleArea::SpawnGimmick()
{
	//�M�~�b�N����
	CExplodingBarrel::Create(m_Pos, { 0.0f, 0.0f, 0.0f });
	CExplodingBarrel::Create(m_Pos + D3DXVECTOR3(150.0f, 0.0f, 150.0f), { 0.0f, 0.0f, 0.0f });
}

//============================
//��������
//============================
CBattleArea* CBattleArea::Create(D3DXVECTOR3 pos, CBattleArea* area)
{
	//�|�C���^�p�̕ϐ�
	CBattleArea* pArea = nullptr;
	pArea = area;

	//�p�����[�^�̑��
	pArea->m_Pos = pos;

	//������
	pArea->Init();

	return pArea;
}