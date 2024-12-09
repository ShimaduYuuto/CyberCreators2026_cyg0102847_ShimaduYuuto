//======================================
//
//	�C���p�N�g�͈̔͏���[impactrange.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "impactrange.h"
#include "manager.h"

//�萔�̏�����
const float CImpactRange::MAX_SIZERATE = 50.0f;

//============================
//�R���X�g���N�^
//============================
CImpactRange::CImpactRange(int nPriority) : CObject3D(nPriority),m_pImpactMesh(nullptr)
{
	
}

//============================
//�f�X�g���N�^
//============================
CImpactRange::~CImpactRange()
{
	
}

//============================
//������
//============================
HRESULT CImpactRange::Init()
{
	//������
	CObject3D::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CImpactRange::Uninit()
{
	if (m_pImpactMesh != nullptr)
	{
		m_pImpactMesh->Uninit();
		m_pImpactMesh = nullptr;
	}

	//�I������
	CObject3D::Uninit();
}

//============================
//�X�V
//============================
void CImpactRange::Update()
{
	//���݂̃T�C�Y�̔{�����擾
	float fRate = GetRate();

	//�ő�{������Ȃ��Ȃ�
	if (fRate < MAX_SIZERATE)
	{
		//�{�������Z
		fRate += 0.3f;

		//�ő�{���𒴂�����
		if (fRate > MAX_SIZERATE)
		{
			fRate = MAX_SIZERATE;
		}
	}
	

	//�{���̐ݒ�
	SetRate(fRate);

	//�X�V����
	CObject3D::Update();

	//���b�V���{���̐ݒ�
	if (m_pImpactMesh != nullptr)
	{
		m_pImpactMesh->SetRate(fRate);
	}
}

//============================
//�`��
//============================
void CImpactRange::Draw()
{
	//�`�揈��
	CObject3D::Draw("data\\TEXTURE\\circle000.png");
}

//============================
//�`��
//============================
void CImpactRange::Draw(const char* texturepath)
{
	//�`�揈��
	CObject3D::Draw(texturepath);
}

//============================
//�N���G�C�g
//============================
CImpactRange* CImpactRange::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CImpactRange* pObject;

	//�������̊m��
	pObject = new CImpactRange;

	//������
	pObject->Init();

	//�p�����[�^�̐ݒ�
	pObject->SetPos(pos);	//�ʒu
	pObject->SetSize({ 10.0f, 0.0f, 10.0f });

	pObject->m_pImpactMesh = CImpactMesh::Create(pos, 10.0f * 0.5f);

	return pObject;
}