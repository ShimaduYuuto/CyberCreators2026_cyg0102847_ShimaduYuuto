//======================================
//
//	���E�̏���[barriermanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "barriermanager.h"
#include "game.h"
#include "manager.h"

//============================
//�R���X�g���N�^
//============================
CBarrierManager::CBarrierManager()
{
	m_BarrierList.clear();
}

//============================
//�f�X�g���N�^
//============================
CBarrierManager::~CBarrierManager()
{
	m_BarrierList.clear();
}

//============================
//������
//============================
HRESULT CBarrierManager::Init()
{
	//�ǂݍ���
	Load();
	return S_OK;
}

//============================
//�I������
//============================
void CBarrierManager::Uninit()
{
	m_BarrierList.clear();
}

//============================
//�X�V
//============================
void CBarrierManager::Update()
{
	//���X�g�̃G���A���X�V
	for (auto itr : m_BarrierList)
	{
		itr->Update();	//�X�V
	}
}

//============================
//�ǂݍ���
//============================
void CBarrierManager::Load()
{
	m_BarrierList.clear();

	//���E�̐���
	Regist(CBarrier::Create({ 0.0f, 150.0f, 1000.0f }));
	Regist(CBarrier::Create({ 0.0f, 150.0f, 2000.0f }));
	Regist(CBarrier::Create({ 0.0f, 150.0f, 3000.0f }));
}

//============================
//�o�^����
//============================
void CBarrierManager::Regist(CBarrier* area)
{
	//�o�^�ς݂�
	bool bRegisted = false;

	//�������̂����������m�F
	for (auto itr : m_BarrierList)
	{
		if (itr == area)
		{
			bRegisted = true;
			break;
		}
	}

	//�o�^�ς݂Ȃ甲����
	if (bRegisted)
	{
		return;
	}

	//�G�̏���o�^
	m_BarrierList.push_back(area);
}

//============================
//�폜����
//============================
void CBarrierManager::Erase()
{
	//�T�C�Y��0�Ȃ甲����
	if (m_BarrierList.size() == 0)
	{
		return;
	}

	//�o�^�ς݂�
	bool bRegisted = false;

	//�������̂����������m�F
	/*for (auto itr : m_BarrierList)
	{
		if (itr == area)
		{
			bRegisted = true;
			break;
		}
	}*/

	//�o�^����Ă��Ȃ��Ȃ甲����
	if (!bRegisted)
	{
		//return;
	}

	//�G���A�̏����폜
	m_BarrierList.front()->Uninit();
	m_BarrierList.pop_front();
}