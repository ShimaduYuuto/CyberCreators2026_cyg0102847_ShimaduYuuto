//======================================
//
//	�Q�[���̏���[game.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "game.h"
#include "manager.h"
#include "object2D.h"
#include "player.h"
#include "enemy.h"
#include "explodingbarrel.h"
#include "objectdome.h"
#include "spawn_enemy.h"
#include "sky.h"
#include "battleareamanager.h"
#include "model.h"

//============================
//�Q�[���̃R���X�g���N�^
//============================
CGame::CGame() :
	m_pPlayer(nullptr),
	m_pField(nullptr),
	m_pTime(nullptr),
	m_pEnemyManager(nullptr),
	m_pLockon(nullptr),
	m_pGimmickManager(nullptr),
	m_pExplosionManager(nullptr),
	m_bClear(false),
	m_bDirectioning(false)
{
	
}

//============================
//�Q�[���̃f�X�g���N�^
//============================
CGame::~CGame()
{
	//�t�H�O�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
}

//============================
//�Q�[���̏�����
//============================
HRESULT CGame::Init()
{
	//�v���C���[�̐���
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create();
	}

	//field�̐���
	if (m_pField == nullptr)
	{
		m_pField = CField::Create({ 0.0f, 0.0f, 0.0f });
	}

	//�^�C���̐���
	if (m_pTime == nullptr)
	{
		m_pTime = new CTime;
	}

	//�G�l�~�[�}�l�[�W���[�̐���
	if (m_pEnemyManager == nullptr)
	{
		m_pEnemyManager = new CEnemyManager;
	}

	//�M�~�b�N�}�l�[�W���[�̐���
	if (m_pGimmickManager == nullptr)
	{
		m_pGimmickManager = new CGimmickManager;
	}

	//�����}�l�[�W���[�̐���
	if (m_pExplosionManager == nullptr)
	{
		m_pExplosionManager = new CExplosionManager;
	}

	//�G�l�~�[�e�}�l�[�W���[�̐���
	if (m_pEnemyBulletManager == nullptr)
	{
		m_pEnemyBulletManager = new CEnemyBulletManager;
	}

	//���E�}�l�[�W���[�̐���
	if (m_pBarrierManager == nullptr)
	{
		m_pBarrierManager = new CBarrierManager;
		m_pBarrierManager->Init();
	}

	//�o�g���G���A�̏�����
	CBattleAreaManager::GetInstance()->Init();

	//CExplodingBarrel::Create({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	CSky::Create();
	ModelLoad();

	//�t�H�O�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);					//�L��
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);		//�t�H�O���[�h�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.1f));	//�F�̐ݒ�
	float m_fFogDensity = 0.0005f;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fFogDensity));
	
	return S_OK;
}

//============================
//�Q�[���̏I������
//============================
void CGame::Uninit()
{
	//�������̔j��
	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}

	//�������̔j��
	if (m_pField != nullptr)
	{
		m_pField = nullptr;
	}

	//�������̔j��
	if (m_pTime != nullptr)
	{
		m_pTime = nullptr;
	}

	//�������̔j��
	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager = nullptr;
	}

	//�������̔j��
	if (m_pGimmickManager != nullptr)
	{
		delete m_pGimmickManager;
		m_pGimmickManager = nullptr;
	}

	//�������̔j��
	if (m_pExplosionManager != nullptr)
	{
		delete m_pExplosionManager;
		m_pExplosionManager = nullptr;
	}

	//�������̔j��
	if (m_pEnemyBulletManager != nullptr)
	{
		delete m_pEnemyBulletManager;
		m_pEnemyBulletManager = nullptr;
	}

	//�������̔j��
	if (m_pBarrierManager != nullptr)
	{
		delete m_pBarrierManager;
		m_pBarrierManager = nullptr;
	}

	//�������̔j��
	if (m_pLockon != nullptr)
	{
		m_pLockon = nullptr;
	}

	//�o�g���G���A�̏�����
	CBattleAreaManager::GetInstance()->Uninit();

	//�I������
	CScene::Uninit();
}

//============================
//�Q�[���̍X�V����
//============================
void CGame::Update()
{
	//���Ԃ̍X�V
	m_pTime->Update();

	//�G���A�}�l�[�W���[�X�V
	CBattleAreaManager::GetInstance()->Update();

	//���b�N�I���̍X�V
	if (m_pLockon != nullptr)
	{
		m_pLockon->Update();
	}

	//�G�̐���
#if _DEBUG
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_1))
	{
		CSpawn_Enemy::Create({ 0.0f, 10.0f, 0.0f }, CEnemy::ENEMYTYPE_ENEMY000);
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_2))
	{
		CEnemy::Create({ 0.0f, 0.0f, 0.0f }, CEnemy::ENEMYTYPE_ENEMY001);
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_3))
	{
		CExplodingBarrel::Create({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	}
#endif

	//�}�l�[�W���[�̃C���X�^���X���擾
	CManager* pManager = CManager::GetInstance();

	//�t�F�[�h���I����Ă�����X�V
	if (CManager::GetInstance()->GetFade()->GetEnd())
	{
		//�G���^�[�ŉ�ʑJ��
		if (pManager->GetKeyboard()->GetTrigger(DIK_RETURN) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_A) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_START) || m_bClear)
		{
			//�Q�[���ɉ�ʑJ��
			pManager->GetFade()->SetFade(CScene::MODE_RESULT);
		}
	}
	
}

//============================
//�Q�[���̕`�揈��
//============================
void CGame::Draw()
{
	
}

//============================
//�Q�[���̓ǂݍ���
//============================
void CGame::Load()
{

}

//============================
//���b�N�I���̐ݒ�
//============================
void CGame::SetLockon(bool lockon)
{
	//���b�N�I���̔���
	if (lockon)
	{
		//���b�N�I�����Ă��Ȃ��Ȃ琶��
		if (m_pLockon != nullptr)
		{
			return;
		}

		//����
		m_pLockon = CLockon::Create();
	}
	else //�����ꍇ
	{
		//���b�N�I�����Ă�Ȃ����
		if (m_pLockon == nullptr)
		{
			return;
		}

		//����
		m_pLockon->Uninit();
		m_pLockon = nullptr;
	}
}

//============================
//���f���̓ǂݍ���
//============================
void CGame::ModelLoad()
{
	//���[�J���ϐ��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen("data\\FILE\\model.bin", "rb");

	//�t�@�C���ɏ��������o��
	if (pFile != NULL)
	{
		//�ǂݍ��ݗp�̕ϐ�
		int nModelNum = 0;

		//���f���̐�
		fread(&nModelNum, sizeof(int), 1, pFile);

		//�z�u�������f���̐��������������o��
		for (int i = 0; i < nModelNum; i++)
		{
			//�ǂݍ��ݗp�ϐ�
			D3DXVECTOR3 Pos;
			D3DXVECTOR3 Rot;
			CModel::MODEL_TYPE Type;

			//���f���̏��
			fread(&Pos, sizeof(D3DXVECTOR3), 1, pFile);			//�ʒu
			fread(&Rot, sizeof(D3DXVECTOR3), 1, pFile);			//����
			fread(&Type, sizeof(CModel::MODEL_TYPE), 1, pFile);	//���

			//����
			CModel::Create(Pos, Rot, Type);
		}

		//�t�@�C�������
		fclose(pFile);
	}
}