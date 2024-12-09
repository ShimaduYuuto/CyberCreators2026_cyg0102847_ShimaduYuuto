//======================================
//
//	�����蔻��̈ʒu[collision.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "collision.h"

//============================
//�R���X�g���N�^
//============================
CCollision::CCollision() : 
	m_CollisionPos(),
	m_fRadius(),
	m_Pos()
{

}

//============================
//�f�X�g���N�^
//============================
CCollision::~CCollision()
{

}

//============================
//������
//============================
HRESULT CCollision::Init()
{
#if _DEBUG
	//�����蔻��̉���
	m_pCollisionView = CCollision_View::Create(m_fRadius, &m_Pos);
#endif

	return S_OK;
}

//============================
//�I������
//============================
void CCollision::Uninit()
{

#if _DEBUG
	//�����蔻������̏���
	if (m_pCollisionView != nullptr)
	{
		m_pCollisionView->Uninit();
		m_pCollisionView = nullptr;
	}
#endif

	//��������
	delete this;
}

//============================
//�X�V����
//============================
void CCollision::Update(D3DXVECTOR3 offsetpos)
{
	//�ʒu���Z�o
	m_Pos = offsetpos + m_CollisionPos;
#if _DEBUG
	m_pCollisionView->SetSize({ m_fRadius * 2.0f, m_fRadius * 2.0f, 0.0f });
	m_pCollisionView->Update();
#endif
}

//============================
//�N���G�C�g
//============================
CCollision* CCollision::Create(float radius, D3DXVECTOR3 collisionpos)
{
	//�|�C���^�p�̕ϐ�
	CCollision* pCollision = nullptr;
	pCollision = new CCollision;

	//�p�����[�^�̑��
	pCollision->m_fRadius = radius;
	pCollision->m_CollisionPos = collisionpos;

	//������
	pCollision->Init();

	return pCollision;
}