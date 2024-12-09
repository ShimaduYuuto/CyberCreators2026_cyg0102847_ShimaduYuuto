//======================================
//
//	エネミースポーン処理[spawn_enemy.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "spawn_enemy.h"
#include "battleareamanager.h"

//============================
//コンストラクタ
//============================
CSpawn_Enemy::CSpawn_Enemy(int nPriority) : CObject(nPriority),
	m_nCount(0),
	m_pPaticleManager(nullptr),
	m_EnemyType()
{
	//敵の数を減らす
	if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
	{
		CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->AddEnemyNum();
	}
}

//============================
//デストラクタ
//============================
CSpawn_Enemy::~CSpawn_Enemy()
{
	if (m_pPaticleManager != nullptr)
	{
		delete m_pPaticleManager;
		m_pPaticleManager = nullptr;
	}
}

//============================
//初期化
//============================
HRESULT CSpawn_Enemy::Init()
{
	m_pPaticleManager = CParticle_Spawn::Create(GetPos());
	return S_OK;
}

//============================
//終了
//============================
void CSpawn_Enemy::Uninit()
{
	CObject::Uninit();
}

//============================
//更新
//============================
void CSpawn_Enemy::Update()
{
	//パーティクルマネージャーの更新
	m_pPaticleManager->Update();

	m_nCount++;

	if (m_nCount > SPAWN_TIME)
	{
		CEnemy::Create(GetPos(), m_EnemyType);
		Uninit();
	}
}

//============================
//生成
//============================
CSpawn_Enemy* CSpawn_Enemy::Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type)
{
	//ポインタ用の変数
	CSpawn_Enemy* pObject;

	//メモリの確保
	pObject = new CSpawn_Enemy();

	//パラメータの設定
	pObject->SetPos(pos);		//位置の設定
	pObject->m_EnemyType = type;//種類

	//初期化
	pObject->Init();

	return pObject;
}