//======================================
//
//	�����̊Ǘ������鏈��[explosionmanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "explosionmanager.h"
#include "manager.h"

//============================
//�R���X�g���N�^
//============================
CExplosionManager::CExplosionManager() :
	m_apManager()
{
	m_apManager.clear();
}

//============================
//�f�X�g���N�^
//============================
CExplosionManager::~CExplosionManager()
{

}

//============================
//������
//============================
HRESULT CExplosionManager::Init()
{
	return S_OK;
}

//============================
//�I������
//============================
void CExplosionManager::Uninit()
{
	m_apManager.clear();
}

//============================
//�o�^����
//============================
void CExplosionManager::Regist(CExplosion* explosion)
{
	//�G�̏���o�^
	m_apManager.push_back(explosion);
}

//============================
//�폜����
//============================
void CExplosionManager::Erase(CExplosion* explosion)
{
	//�T�C�Y��0�Ȃ甲����
	if (m_apManager.size() == 0)
	{
		return;
	}
	//�G�̏����폜
	m_apManager.remove(explosion);
}