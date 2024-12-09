//======================================
//
//	�M�~�b�N�̊Ǘ������鏈��[gimmickmanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "gimmickmanager.h"
#include "manager.h"

//============================
//�R���X�g���N�^
//============================
CGimmickManager::CGimmickManager() :
	m_apManager()
{
	m_apManager.clear();
}

//============================
//�f�X�g���N�^
//============================
CGimmickManager::~CGimmickManager()
{
	m_apManager.clear();
}

//============================
//������
//============================
HRESULT CGimmickManager::Init()
{
	return S_OK;
}

//============================
//�I������
//============================
void CGimmickManager::Uninit()
{
	m_apManager.clear();
}

//============================
//�o�^����
//============================
void CGimmickManager::Regist(CGimmick* gimmick)
{
	//�G�̏���o�^
	m_apManager.push_back(gimmick);
}

//============================
//�폜����
//============================
void CGimmickManager::Erase(CGimmick* gimmick)
{
	//�T�C�Y��0�Ȃ甲����
	if (m_apManager.size() == 0)
	{
		return;
	}

	//�o�^�ς݂�
	bool bRegisted = false;

	//�������̂����������m�F
	for (auto itr : m_apManager)
	{
		if (itr == gimmick)
		{
			bRegisted = true;
			break;
		}
	}

	//�o�^����Ă��Ȃ��Ȃ甲����
	if (!bRegisted)
	{
		return;
	}

	//�M�~�b�N�̏����폜
	m_apManager.remove(gimmick);
}