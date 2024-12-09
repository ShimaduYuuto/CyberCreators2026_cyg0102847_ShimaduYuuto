//======================================
//
//	�C���p�N�g���b�V���̏���[impactmesh.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "impactmesh.h"
#include "manager.h"
#include "game.h"

//�I�u�W�F�N�g���b�V���N���X�̒萔�̏�����
const std::string CImpactMesh::FILEPATH = "data\\TEXTURE\\SmashMesh000.png";//�e�N�X�`���p�X
const int CImpactMesh::NUM_CORNER = 20;										//�p�̐�
const float CImpactMesh::HEIGHT = 50.0f;									//����

//============================
//�R���X�g���N�^
//============================
CImpactMesh::CImpactMesh(int nPriority) : CObjectCylinder(nPriority)
{
	
}

//============================
//�f�X�g���N�^
//============================
CImpactMesh::~CImpactMesh()
{
	
}

//============================
//������
//============================
HRESULT CImpactMesh::Init()
{
	//���̏�����
	CObjectCylinder::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CImpactMesh::Uninit()
{
	//�����̊J��
	CObjectCylinder::Uninit();
}

//============================
//�X�V
//============================
void CImpactMesh::Update()
{
	//�X�V
	CObjectCylinder::Update();
}

//============================
//�`��
//============================
void CImpactMesh::Draw()
{
	//�`�揈��
	CObjectCylinder::Draw(FILEPATH.c_str());
}

//================================
//�N���G�C�g
//================================
CImpactMesh* CImpactMesh::Create(D3DXVECTOR3 pos, float radius)
{
	//�|�C���^�p�̕ϐ�
	CImpactMesh* pObject;

	//�������̊m��
	pObject = new CImpactMesh;

	//�p�����[�^�̐ݒ�
	pObject->SetPos(pos);			//�ʒu�̐ݒ�
	pObject->SetRadius(radius);	//���a�̐ݒ�

	//������
	pObject->Init();

	return pObject;
}