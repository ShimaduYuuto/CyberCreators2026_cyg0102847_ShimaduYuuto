//======================================
//
//	�o�g���G���A�̏���[battlearea000.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "battlearea000.h"
#include "spawn_enemy.h"
#include "explodingbarrel.h"

//============================
//�R���X�g���N�^
//============================
CBattleArea000::CBattleArea000()
{

}

//============================
//�f�X�g���N�^
//============================
CBattleArea000::~CBattleArea000()
{
	
}

//============================
//�G�̐���
//============================
void CBattleArea000::SpawnEnemy()
{
	//�G����
	CSpawn_Enemy::Create(GetPos(), CEnemy::ENEMYTYPE_ENEMY001);
	//CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(150.0f, 0.0f, 150.0f), CEnemy::ENEMYTYPE_ENEMY000);
	//CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-150.0f, 0.0f, -150.0f), CEnemy::ENEMYTYPE_ENEMY000);
	//CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-0.0f, 0.0f, -150.0f), CEnemy::ENEMYTYPE_ENEMY000);
	//CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-150.0f, 0.0f, -300.0f), CEnemy::ENEMYTYPE_ENEMY000);
}

//============================
//�M�~�b�N�̐���
//============================
void CBattleArea000::SpawnGimmick()
{
	//�M�~�b�N����
	CExplodingBarrel::Create(GetPos(), { 0.0f, 0.0f, 0.0f });
	CExplodingBarrel::Create(GetPos() + D3DXVECTOR3(150.0f, 0.0f, 150.0f), { 0.0f, 0.0f, 0.0f });
}