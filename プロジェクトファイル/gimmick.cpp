//======================================
//
//	�M�~�b�N�̏���[gimmick.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "gimmick.h"
#include "manager.h"
#include "game.h"

//============================
//�R���X�g���N�^
//============================
CGimmick::CGimmick(int nPriority) : CObjectX(nPriority),
m_Collision(nullptr)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//�}�l�[�W���[�ɓo�^
	pGame->GetGimmickManager()->Regist(this);
}

//============================
//�f�X�g���N�^
//============================
CGimmick::~CGimmick()
{
	//�Q�[���V�[���̎擾
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//�}�l�[�W���[����폜
	if (pGame->GetGimmickManager() != nullptr)
	{
		pGame->GetGimmickManager()->Erase(this);
	}	

	//�����蔻��̏���
	if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}
}

//============================
//������
//============================
HRESULT CGimmick::Init()
{
	//������
	CObjectX::Init();

	//�����蔻��̐���
	if (m_Collision == nullptr)
	{
		m_Collision = CCollision::Create(20.0f, D3DXVECTOR3(0.0f, 30.0f, 0.0f));
	}

	return S_OK;
}

//============================
//�I������
//============================
void CGimmick::Uninit()
{
	//�����蔻��̏���
	/*if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}*/

	//������
	CObjectX::Uninit();
}

//============================
//�X�V
//============================
void CGimmick::Update()
{
	//�Q�[���I�u�W�F�N�g�̋��ʏ����X�V
	CObjectX::Update();
	m_Collision->Update(GetPos());
}