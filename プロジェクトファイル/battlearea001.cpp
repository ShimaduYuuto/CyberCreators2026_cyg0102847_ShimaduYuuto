//======================================
//
//	�o�g���G���A�̏���[battlearea001.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "battlearea001.h"
#include "spawn_enemy.h"
#include "explodingbarrel.h"

//============================
//�R���X�g���N�^
//============================
CBattleArea001::CBattleArea001()
{

}

//============================
//�f�X�g���N�^
//============================
CBattleArea001::~CBattleArea001()
{

}

//============================
//�G�̐���
//============================
void CBattleArea001::SpawnEnemy()
{
	//�G����
	CSpawn_Enemy::Create(GetPos(), CEnemy::ENEMYTYPE_ENEMY001);
	CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(150.0f, 0.0f, 150.0f), CEnemy::ENEMYTYPE_ENEMY000);
	CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-150.0f, 0.0f, -150.0f), CEnemy::ENEMYTYPE_ENEMY000);
	CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-0.0f, 0.0f, -150.0f), CEnemy::ENEMYTYPE_ENEMY000);
	CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-150.0f, 0.0f, -300.0f), CEnemy::ENEMYTYPE_ENEMY000);
}

//============================
//�M�~�b�N�̐���
//============================
void CBattleArea001::SpawnGimmick()
{
	//�M�~�b�N����
	CExplodingBarrel::Create(GetPos(), { 0.0f, 0.0f, 0.0f });
	CExplodingBarrel::Create(GetPos() + D3DXVECTOR3(150.0f, 0.0f, 150.0f), { 0.0f, 0.0f, 0.0f });
}