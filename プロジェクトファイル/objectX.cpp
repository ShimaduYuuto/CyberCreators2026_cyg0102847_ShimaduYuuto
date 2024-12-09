//======================================
//
//	�I�u�W�F�N�gX�̏���[objectX.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "objectX.h"
#include "manager.h"
#include "game.h"

//�I�u�W�F�N�gX�N���X�̒萔�̏�����
const std::string CObjectX::FILEPATH = "data\\MODEL\\Block001.x";

//============================
//�I�u�W�F�N�gX�̃R���X�g���N�^
//============================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	//�p�����[�^�̏�����
	m_rot = { 0.0f, 0.0f, 0.0f };	//����
	m_Scale = { 1.0f, 1.0f, 1.0f };	//�X�P�[��
}

//============================
//�I�u�W�F�N�gX�̃f�X�g���N�^
//============================
CObjectX::~CObjectX()
{

}

//============================
//�I�u�W�F�N�gX�̏�����
//============================
HRESULT CObjectX::Init()
{
	return S_OK;
}

//============================
//�I�u�W�F�N�gX�̏I������
//============================
void CObjectX::Uninit()
{
	//�����̊J��
	if (this != nullptr)
	{
		//����
		SetDeath();
	}
}

//============================
//�I�u�W�F�N�gX�̍X�V
//============================
void CObjectX::Update()
{
	
}

//============================
//�I�u�W�F�N�gX�̕`��
//============================
void CObjectX::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;								//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;												//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;													//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR3 Pos = GetPos();											//�ʒu�̎擾

	//X�t�@�C���̓ǂݍ���
	CXfile* pCXfile = CManager::GetInstance()->GetXfile();

	//���[���h�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pCXfile->GetAddress(pCXfile->Regist(CObjectX::FILEPATH.c_str())).pBuffmat->GetBufferPointer();

	//�e�N�X�`���̐����J�E���g
	int nTextureCount = 0;

	//�}�e���A���̐���������
	for (int nCntMat = 0; nCntMat < (int)pCXfile->GetAddress(pCXfile->Regist(CObjectX::FILEPATH.c_str())).dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`������������
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pCXfile->GetAddress(pCXfile->Regist(CObjectX::FILEPATH.c_str())).pTexture[nTextureCount]);

			//�e�N�X�`���p�̃J�E���g��i�߂�
			nTextureCount++;
		}
		else
		{
			//�e�N�X�`����ݒ肵�Ȃ�
			pDevice->SetTexture(0, NULL);
		}

		//�I�u�W�F�N�gX(�p�[�c)�̕`��
		pCXfile->GetAddress(pCXfile->Regist(CObjectX::FILEPATH.c_str())).pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	//�ʒu�̐ݒ�
	SetPos(Pos);
}

//============================
//�����̃I�u�W�F�N�g�̕`��
//============================
void CObjectX::Draw(const char* pfilepath)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;								//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;												//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;													//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR3 Pos = GetPos();											//�ʒu�̎擾

	//X�t�@�C���̓ǂݍ���
	CXfile* pCXfile = CManager::GetInstance()->GetXfile();

	//���[���h�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pCXfile->GetAddress(pCXfile->Regist(pfilepath)).pBuffmat->GetBufferPointer();

	//�e�N�X�`���̐����J�E���g
	int nTextureCount = 0;

	//�}�e���A���̐���������
	for (int nCntMat = 0; nCntMat < (int)pCXfile->GetAddress(pCXfile->Regist(pfilepath)).dwNumMat; nCntMat++)
	{
		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		//�F��ۑ�
		matDef = pMat[nCntMat].MatD3D;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&matDef);

		//�e�N�X�`������������
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pCXfile->GetAddress(pCXfile->Regist(pfilepath)).pTexture[nTextureCount]);

			//�e�N�X�`���p�̃J�E���g��i�߂�
			nTextureCount++;
		}
		else
		{
			//�e�N�X�`����ݒ肵�Ȃ�
			pDevice->SetTexture(0, NULL);
		}

		//�I�u�W�F�N�gX(�p�[�c)�̕`��
		pCXfile->GetAddress(pCXfile->Regist(pfilepath)).pMesh->DrawSubset(nCntMat);

		//�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

	//�ʒu�̐ݒ�
	SetPos(Pos);
}

//============================
//�I�u�W�F�N�gX�̃N���G�C�g
//============================
CObjectX* CObjectX::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CObjectX* pObjectX;

	//�������̊m��
	pObjectX = new CObjectX;

	//�p�����[�^�̐ݒ�
	pObjectX->SetPos(pos);	//�ʒu�̐ݒ�

	//������
	pObjectX->Init();

	return pObjectX;
}