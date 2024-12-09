//======================================
//
//	�o�g���G���A�̏���[battlearea002.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "battlearea002.h"
#include "spawn_enemy.h"
#include "explodingbarrel.h"

//============================
//�R���X�g���N�^
//============================
CBattleArea002::CBattleArea002()
{

}

//============================
//�f�X�g���N�^
//============================
CBattleArea002::~CBattleArea002()
{

}

//============================
//�G�̐���
//============================
void CBattleArea002::SpawnEnemy()
{
	//�G����
	CSpawn_Enemy::Create(GetPos(), CEnemy::ENEMYTYPE_ENEMY003);
	CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(150.0f, 0.0f, 150.0f), CEnemy::ENEMYTYPE_ENEMY003);
	CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-150.0f, 0.0f, -150.0f), CEnemy::ENEMYTYPE_ENEMY003);
	CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-0.0f, 0.0f, -150.0f), CEnemy::ENEMYTYPE_ENEMY003);
	CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-150.0f, 0.0f, -300.0f), CEnemy::ENEMYTYPE_ENEMY003);
}

//============================
//�M�~�b�N�̐���
//============================
void CBattleArea002::SpawnGimmick()
{
	//�M�~�b�N����
	CExplodingBarrel::Create(GetPos(), { 0.0f, 0.0f, 0.0f });
	CExplodingBarrel::Create(GetPos() + D3DXVECTOR3(150.0f, 0.0f, 150.0f), { 0.0f, 0.0f, 0.0f });
}