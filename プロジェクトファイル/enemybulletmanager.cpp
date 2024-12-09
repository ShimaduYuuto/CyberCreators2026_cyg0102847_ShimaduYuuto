//======================================
//
//	�G�l�~�[�e�̊Ǘ������鏈��[enemybulletmanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "enemybulletmanager.h"
#include "manager.h"

//============================
//�R���X�g���N�^
//============================
CEnemyBulletManager::CEnemyBulletManager() :
	m_apManager()
{
	m_apManager.clear();
}

//============================
//�f�X�g���N�^
//============================
CEnemyBulletManager::~CEnemyBulletManager()
{

}

//============================
//������
//============================
HRESULT CEnemyBulletManager::Init()
{
	return S_OK;
}

//============================
//�I������
//============================
void CEnemyBulletManager::Uninit()
{
	m_apManager.clear();
}

//============================
//�o�^����
//============================
void CEnemyBulletManager::Regist(CEnemyBullet* enemybullet)
{
	//�G�̏���o�^
	m_apManager.push_back(enemybullet);
}

//============================
//�폜����
//============================
void CEnemyBulletManager::Erase(CEnemyBullet* enemybullet)
{
	//�T�C�Y��0�Ȃ甲����
	if (m_apManager.size() == 0)
	{
		return;
	}
	//�G�̏����폜
	m_apManager.remove(enemybullet);
}