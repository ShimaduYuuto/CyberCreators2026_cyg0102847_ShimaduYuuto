//======================================
//
//	�I�u�W�F�N�g���b�V���̏���[objectmesh.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "objectmesh.h"
#include "manager.h"
#include "game.h"

//�I�u�W�F�N�g���b�V���N���X�̒萔�̏�����
const D3DXVECTOR3 CObjectMesh::BLOCK = {2, 0, 2};						//�u���b�N��
const D3DXVECTOR3 CObjectMesh::SIZE = { 15000.0f, 100.0f, 10000.0f };	//�T�C�Y

//============================
//�I�u�W�F�N�g���b�V���̃R���X�g���N�^
//============================
CObjectMesh::CObjectMesh(int nPriority) : CObject(nPriority)
{
	//�p�����[�^�̏�����
	m_pos = { 0.0f, 0.0f, 0.0f };	//�ʒu
	m_rot = { 0.0f, 0.0f, 0.0f };	//����
	m_mtxWorld = {};				//���[���h�}�g���b�N�X
	m_pTexture = nullptr;			//�e�N�X�`��
	m_nIndex = 0;					//�ԍ��̐�
	m_nPolygon = 0;					//�|���S���̐�
	m_nVertex = 0;					//���_�̐�
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F�̐ݒ�
}

//============================
//�I�u�W�F�N�g���b�V���̃f�X�g���N�^
//============================
CObjectMesh::~CObjectMesh()
{

}

//============================
//�I�u�W�F�N�g���b�V���̏�����
//============================
HRESULT CObjectMesh::Init()
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	m_nIndex = (int)(2 * (BLOCK.x + 1) * BLOCK.z + (BLOCK.z - 1) * 2);	//�C���f�b�N�X��
	m_nVertex = (int)((BLOCK.x + 1) * (BLOCK.z + 1));						//���_��
	m_nPolygon = (int)((BLOCK.x * BLOCK.z) * 2 + (BLOCK.z - 1) * 4);		//�|���S����

	//�f�o�C�X���擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Block00.png",
		&m_pTexture);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nVertex),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx; //�ǉ��̃|�C���^
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	
	int nX = 0;
	int nHeightCount = 0;

	//���_�̐�������
	for (int nCount = 0; nCount < m_nVertex; nCount++)
	{
		//�ʒu�̐ݒ�
		pVtx[nCount].pos = D3DXVECTOR3(SIZE.x * (nX / (float)BLOCK.x) - (SIZE.x * 0.5f), 0.0f, -SIZE.z * (nHeightCount / (float)BLOCK.z) + (SIZE.z * 0.5f));

		//pVtx[nCount].pos.y += 200.0f - nX * 10.0f;

		//�e�N�X�`���̓ǂݍ���
		pVtx[nCount].tex = D3DXVECTOR2(1.0f * (nX / (float)BLOCK.x), 1.0f * (nHeightCount / (float)BLOCK.z));

		nX++;

		if (nX == BLOCK.x + 1)
		{
			nX = 0;
			nHeightCount++;
		}

		//�@���x�N�g���̐ݒ�
		pVtx[nCount].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCount].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�C���f�b�N�X�̌v�Z�p�̕ϐ�
	nX = 0;
	nHeightCount = 0;
	int nX2 = 0;

	//�C���f�b�N�X�̌v�Z
	for (int nCount = 0; nCount < m_nIndex; nCount++)
	{
		//�k�ރ|���S���̏ꍇ�Ƃ���ȊO
		if (nCount == ((int)(BLOCK.x + 1) * 2 + 2) * (nHeightCount + 1) - 2)
		{
			pIdx[nCount] = pIdx[nCount - 1];
		}
		else if (nCount == ((int)(BLOCK.x + 1) * 2 + 2) * (nHeightCount + 1) - 1)
		{
			pIdx[nCount] = pIdx[nCount - 1] + (WORD)BLOCK.x + 2;
			nHeightCount++;
		}
		else
		{
			if (nCount % 2 == 0)//�����̏ꍇ
			{
				pIdx[nCount] = (WORD)(BLOCK.x + 1 + nX);
				nX++;
			}
			else//��̏ꍇ
			{
				pIdx[nCount] = (WORD)nX2;
				nX2++;
			}
		}
	}

	//�|���S���̐�������
	for (int i = 0; i < m_nPolygon; i++)
	{
		//�k�ނȂ�R���e�B�j���[
		if ((pIdx[i] == pIdx[i + 1]) || (pIdx[i + 1] == pIdx[i + 2]))
		{
			continue;
		}

		//�@���x�N�g�����i�[����ϐ�
		D3DXVECTOR3 SurfaceNorVec; //�ʖ@���̃x�N�g��
		D3DXVECTOR3 vecNormal; //���K�������x�N�g��
		D3DXVECTOR3 vector1; //�P�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 vector2; //�Q�ڂ̃x�N�g���̕ۊǗp

		//�C���f�b�N�X���i�[����ϐ�
		WORD index0 = pIdx[i + 0];
		WORD index1 = pIdx[i + 1];
		WORD index2 = pIdx[i + 2];

		//���_���i�[����ϐ�
		VERTEX_3D* vtx0 = pVtx + index0;
		VERTEX_3D* vtx1 = pVtx + index1;
		VERTEX_3D* vtx2 = pVtx + index2;

		//�@���x�N�g���̎Z�o
		if ((i & 1) == 0) //����
		{
			vector1 = vtx1->pos - vtx0->pos;
			vector2 = vtx2->pos - vtx0->pos;
		}
		else //�
		{
			vector1 = vtx2->pos - vtx0->pos;
			vector2 = vtx1->pos - vtx0->pos;
		}

		//�x�N�g���̌v�Z
		D3DXVec3Cross(&SurfaceNorVec, &vector1, &vector2);

		//�x�N�g���̐��K��
		D3DXVec3Normalize(&vecNormal, &SurfaceNorVec);

		//�x�N�g�������Z
		vtx0->nor += vecNormal;
		vtx1->nor += vecNormal;
		vtx2->nor += vecNormal;

		////�ʖ@���x�N�g����ۑ�
		//m_SurfaceNorVec.push_back(vecNormal);
	}

	//���Z�����x�N�g���𐳋K��
	for (int nCount = 0; nCount < m_nVertex; nCount++)
	{
		//�x�N�g���̐��K��
		D3DXVec3Normalize(&pVtx[nCount].nor, &pVtx[nCount].nor);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//============================
//�I�u�W�F�N�g���b�V���̏�����
//============================
HRESULT CObjectMesh::Init(int widthblock, int heightblock, float widthsize, float heightsize, MESHTYPE meshtype)
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	m_nIndex = (int)(2 * (widthblock + 1) * heightblock + (heightblock - 1) * 2);		//�C���f�b�N�X��
	m_nVertex = (int)((widthblock + 1) * (heightblock + 1));							//���_��
	m_nPolygon = (int)((widthblock * heightblock) * 2 + (heightblock - 1) * 4);			//�|���S����

	//�����̏��̑��
	m_block = {(float)widthblock, 0.0f, (float)heightblock};	//�u���b�N��
	m_size = {widthsize, 0.0f, heightsize};		//���b�V���̃T�C�Y

	//�f�o�C�X���擾
	pDevice = CManager::GetInstance()-> GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Block00.png",
		&m_pTexture);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nVertex),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//���_���̌v�Z
	VtxPosCluculation(meshtype);

	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx; //�ǉ��̃|�C���^
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�̌v�Z�p�̕ϐ�
	int nX = 0;
	int nHeightCount = 0;
	int nX2 = 0;

	//�C���f�b�N�X�̌v�Z
	for (int nCount = 0; nCount < m_nIndex; nCount++)
	{
		//�k�ރ|���S���̏ꍇ�Ƃ���ȊO
		if (nCount == ((int)(widthblock + 1) * 2 + 2) * (nHeightCount + 1) - 2)
		{
			pIdx[nCount] = pIdx[nCount - 1];
		}
		else if (nCount == ((int)(widthblock + 1) * 2 + 2) * (nHeightCount + 1) - 1)
		{
			pIdx[nCount] = pIdx[nCount - 1] + (WORD)widthblock + 2;
			nHeightCount++;
		}
		else
		{
			if (nCount % 2 == 0)//�����̏ꍇ
			{
				pIdx[nCount] = (WORD)(widthblock + 1 + nX);
				nX++;
			}
			else//��̏ꍇ
			{
				pIdx[nCount] = (WORD)nX2;
				nX2++;
			}
		}
	}

	//�|���S���̐�������
	for (int i = 0; i < m_nPolygon; i++)
	{
		//�k�ނȂ�R���e�B�j���[
		if ((pIdx[i] == pIdx[i + 1]) || (pIdx[i + 1] == pIdx[i + 2]))
		{
			continue;
		}

		//�@���x�N�g�����i�[����ϐ�
		D3DXVECTOR3 SurfaceNorVec;	//�ʖ@���̃x�N�g��
		D3DXVECTOR3 vecNormal;		//���K�������x�N�g��
		D3DXVECTOR3 vector1;		//�P�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 vector2;		//�Q�ڂ̃x�N�g���̕ۊǗp

		//�C���f�b�N�X���i�[����ϐ�
		WORD index0 = pIdx[i + 0];
		WORD index1 = pIdx[i + 1];
		WORD index2 = pIdx[i + 2];

		//���_���i�[����ϐ�
		VERTEX_3D* vtx0 = pVtx + index0;
		VERTEX_3D* vtx1 = pVtx + index1;
		VERTEX_3D* vtx2 = pVtx + index2;

		//�@���x�N�g���̎Z�o
		if ((i & 1) == 0) //����
		{
			vector1 = vtx1->pos - vtx0->pos;
			vector2 = vtx2->pos - vtx0->pos;
		}
		else //�
		{
			vector1 = vtx2->pos - vtx0->pos;
			vector2 = vtx1->pos - vtx0->pos;
		}

		//�x�N�g���̌v�Z
		D3DXVec3Cross(&SurfaceNorVec, &vector1, &vector2);

		//�x�N�g���̐��K��
		D3DXVec3Normalize(&vecNormal, &SurfaceNorVec);

		//�x�N�g�������Z
		vtx0->nor += vecNormal;
		vtx1->nor += vecNormal;
		vtx2->nor += vecNormal;
	}

	//���Z�����x�N�g���𐳋K��
	for (int nCount = 0; nCount < m_nVertex; nCount++)
	{
		//�x�N�g���̐��K��
		D3DXVec3Normalize(&pVtx[nCount].nor, &pVtx[nCount].nor);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//============================
//���_�̌v�Z
//============================
void CObjectMesh::VtxPosCluculation(MESHTYPE meshtype)
{
	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���[�J���ϐ��錾
	int nWidthCount = 0;
	int nHeightCount = 0;

	//���_�̐�������
	for (int nCount = 0; nCount < m_nVertex; nCount++)
	{
		//�ʒu�̐ݒ�
		switch (meshtype)
		{
			//�t�B�[���h
		case MESHTYPE_FIELD:
			pVtx[nCount].pos = D3DXVECTOR3(m_size.x * (nWidthCount / (float)m_block.x) - (m_size.x * 0.5f), 0.0f, -m_size.z * (nHeightCount / (float)m_block.z) + (m_size.z * 0.5f));

			//�e�N�X�`���̓ǂݍ���
			pVtx[nCount].tex = D3DXVECTOR2(1.0f * (nWidthCount / (float)m_block.x), 1.0f * (nHeightCount / (float)m_block.z));

			//�@���x�N�g���̐ݒ�
			pVtx[nCount].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			break;

			//��
		case MESHTYPE_WALL:
			pVtx[nCount].pos = D3DXVECTOR3(m_size.x * (nWidthCount / (float)m_block.x) - (m_size.x * 0.5f), -m_size.y * (nHeightCount / (float)m_block.y) + (m_size.y * 0.5f), 0.0f);

			//�e�N�X�`���̓ǂݍ���
			pVtx[nCount].tex = D3DXVECTOR2(1.0f * (nWidthCount / (float)m_block.x), 1.0f * (nHeightCount / (float)m_block.y));

			//�@���x�N�g���̐ݒ�
			pVtx[nCount].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			break;
		}

		//�J�E���g�A�b�v
		nWidthCount++;

		//���̃J�E���g�A�b�v
		if (nWidthCount == m_block.x + 1)
		{
			nWidthCount = 0;
			nHeightCount++;
		}

		//���_�J���[�̐ݒ�
		pVtx[nCount].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
//�I�u�W�F�N�g���b�V���̏I������
//============================
void CObjectMesh::Uninit()
{
	//���_�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//�����̊J��
	if (this != nullptr)
	{
		//����
		SetDeath();
	}
}

//============================
//�I�u�W�F�N�g���b�V���̍X�V
//============================
void CObjectMesh::Update()
{
	
}

//============================
//�I�u�W�F�N�g���b�V���̕`��
//============================
void CObjectMesh::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;														//�v�Z�p�}�g���b�N�X
	
	//���[���h�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertex, 0, m_nPolygon);
}

//============================
//�I�u�W�F�N�g���b�V���̕`��
//============================
void CObjectMesh::Draw(const char* pfilepath)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;														//�v�Z�p�}�g���b�N�X
	CTexture* pTexture = CManager::GetInstance()->GetTexture();							//�e�N�X�`���̓ǂݍ���

	//���[���h�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist(pfilepath)));

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertex, 0, m_nPolygon);
}

//================================
//�I�u�W�F�N�g���b�V���̃N���G�C�g
//================================
CObjectMesh* CObjectMesh::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CObjectMesh* pObjectX;

	//�������̊m��
	pObjectX = new CObjectMesh;

	//�p�����[�^�̐ݒ�
	pObjectX->SetPos(pos);	//�ʒu�̐ݒ�

	//������
	pObjectX->Init();

	return pObjectX;
}

//================================
//���_�̈ʒu�ݒ�
//================================
void CObjectMesh::SetVtxPos(int index, D3DXVECTOR3 pos)
{
	//���_��񂪖����Ȃ�֐��𔲂���
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	//���_�p�̃��[�J���ϐ�
	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�Ɉʒu��ݒ�
	pVtx[index].pos = pos;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================
//���_�̐F�ݒ�
//================================
void CObjectMesh::SetVtxColor(int index, D3DXCOLOR color)
{
	//���_��񂪖����Ȃ�֐��𔲂���
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	//���_�p�̃��[�J���ϐ�
	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�Ɉʒu��ݒ�
	pVtx[index].col = color;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================
//���_�̐F�ݒ�
//================================
void CObjectMesh::SetVtxTex(int index, D3DXVECTOR2 tex)
{
	//���_��񂪖����Ȃ�֐��𔲂���
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	//���_�p�̃��[�J���ϐ�
	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�Ɉʒu��ݒ�
	pVtx[index].tex = tex;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================
//�|���S���̐F�ݒ�
//================================
void CObjectMesh::SetColor(D3DXCOLOR color)
{
	//���_��񂪖����Ȃ�֐��𔲂���
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	//�F��ݒ�
	m_Color = color;

	//���_�p�̃��[�J���ϐ�
	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_����������
	for (int i = 0; i < m_nVertex; i++)
	{
		//���_�Ɉʒu��ݒ�
		pVtx[i].col = color;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}