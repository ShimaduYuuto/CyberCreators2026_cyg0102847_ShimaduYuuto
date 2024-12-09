//======================================
//
//	�G�l�~�[�̊Ǘ������鏈��[enemymanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "enemymanager.h"
#include "manager.h"

//============================
//�R���X�g���N�^
//============================
CEnemyManager::CEnemyManager():
	m_apManager()
{
	m_apManager.clear();
}

//============================
//�f�X�g���N�^
//============================
CEnemyManager::~CEnemyManager()
{

}

//============================
//������
//============================
HRESULT CEnemyManager::Init()
{
	return S_OK;
}

//============================
//�I������
//============================
void CEnemyManager::Uninit()
{
	m_apManager.clear();
}

//============================
//�o�^����
//============================
void CEnemyManager::Regist(CEnemy* enemy)
{
	//�G�̏���o�^
	m_apManager.push_back(enemy);
}

//============================
//�폜����
//============================
void CEnemyManager::Erase(CEnemy* enemy)
{
	//�T�C�Y��0�Ȃ甲����
	if (m_apManager.size() == 0)
	{
		return;
	}
	//�G�̏����폜
	m_apManager.remove(enemy);
}