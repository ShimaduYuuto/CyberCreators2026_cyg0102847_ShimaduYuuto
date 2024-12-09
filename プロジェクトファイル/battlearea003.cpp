//======================================
//
//	�o�g���G���A�̏���[battlearea003.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "battlearea003.h"
#include "spawn_enemy.h"
#include "explodingbarrel.h"

//============================
//�R���X�g���N�^
//============================
CBattleArea003::CBattleArea003()
{

}

//============================
//�f�X�g���N�^
//============================
CBattleArea003::~CBattleArea003()
{

}

//============================
//�G�̐���
//============================
void CBattleArea003::SpawnEnemy()
{
	//�G����
	CSpawn_Enemy::Create(GetPos(), CEnemy::ENEMYTYPE_ENEMY002);
}

//============================
//�M�~�b�N�̐���
//============================
void CBattleArea003::SpawnGimmick()
{
	//�M�~�b�N����
	CExplodingBarrel::Create(GetPos(), { 0.0f, 0.0f, 0.0f });
	CExplodingBarrel::Create(GetPos() + D3DXVECTOR3(150.0f, 0.0f, 150.0f), { 0.0f, 0.0f, 0.0f });
}