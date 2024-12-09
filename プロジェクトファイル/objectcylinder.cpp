//======================================
//
//	�V�����_�[�I�u�W�F�N�g�̏���[objectcylinder.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "objectcylinder.h"
#include "manager.h"
#include "game.h"

//�I�u�W�F�N�g���b�V���N���X�̒萔�̏�����
const int CObjectCylinder::NUM_CORNER = 20;			//�p�̐�
const float CObjectCylinder::HEIGHT = 50.0f;		//����

//============================
//�I�u�W�F�N�g���b�V���̃R���X�g���N�^
//============================
CObjectCylinder::CObjectCylinder(int nPriority) : CObject(nPriority),
m_Color(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
m_fRadius(0.0f),
m_fRate(1.0f),
m_mtxWorld(),
m_nIndex(),
m_nPolygon(),
m_nVertex(),
m_pIdxBuff(),
m_pVtxBuff(),
m_rot()
{
	//�p�����[�^�̏�����
	m_rot = { 0.0f, 0.0f, 0.0f };	//����
	m_mtxWorld = {};				//���[���h�}�g���b�N�X
	m_nIndex = 0;					//�ԍ��̐�
	m_nPolygon = 0;					//�|���S���̐�
	m_nVertex = 0;					//���_�̐�
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F�̐ݒ�
}

//============================
//�I�u�W�F�N�g���b�V���̃f�X�g���N�^
//============================
CObjectCylinder::~CObjectCylinder()
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
}

//============================
//�I�u�W�F�N�g���b�V���̏�����
//============================
HRESULT CObjectCylinder::Init()
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	m_nIndex = ((NUM_CORNER + 1) * 2);	//�C���f�b�N�X��
	m_nVertex = (NUM_CORNER * 2);		//���_��
	m_nPolygon = (NUM_CORNER * 2);		//�|���S����

	//�f�o�C�X���擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

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

	//�㉺�̐�����
	for (int j = 0; j < 2; j++)
	{
		//�p�̐���������
		for (int i = 0; i < NUM_CORNER; i++)
		{
			//�p�x���Z�o
			float fAngle = (D3DX_PI * 2) * (float)(i / (float)NUM_CORNER);

			//�e�ϐ��ɒl����
			pVtx[i + NUM_CORNER * j].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, HEIGHT - (HEIGHT * j), cosf(fAngle) * m_fRadius);	//�ʒu
			pVtx[i + NUM_CORNER * j].tex = D3DXVECTOR2(1.0f * (i / NUM_CORNER), j);	//UV���W
			pVtx[i + NUM_CORNER * j].nor = D3DXVECTOR3(sinf(fAngle + D3DX_PI) / D3DX_PI,
				0.0f,
				cosf(fAngle + D3DX_PI) / D3DX_PI);	//�@���x�N�g��
			pVtx[i + NUM_CORNER * j].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);				//�F
		}
	}

	//�C���f�b�N�X�̌v�Z�p�̕ϐ�
	nX = 0;
	nHeightCount = 0;
	int nAngleCount = 0;

	//�C���f�b�N�X�̌v�Z
	for (int i = 0; i < m_nIndex; i++)
	{
		//�����̏ꍇ
		if ((i & 1) == 0)
		{
			pIdx[i] = (WORD)(NUM_CORNER + nAngleCount);
		}
		else//��̏ꍇ
		{
			pIdx[i] = (WORD)nAngleCount;
			nAngleCount++;
		}

		//1�T���鎞�ɃJ�E���g�̏�����
		if (nAngleCount == NUM_CORNER)
		{
			nAngleCount = 0;
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
//�I�u�W�F�N�g���b�V���̏I������
//============================
void CObjectCylinder::Uninit()
{
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
void CObjectCylinder::Update()
{

	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�㉺�̐�����
	for (int j = 0; j < 2; j++)
	{
		//�p�̐���������
		for (int i = 0; i < NUM_CORNER; i++)
		{
			//�p�x���Z�o
			float fAngle = (D3DX_PI * 2) * (float)(i / (float)NUM_CORNER);

			//�e�ϐ��ɒl����
			pVtx[i + NUM_CORNER * j].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius * m_fRate, HEIGHT - (HEIGHT * j), cosf(fAngle) * m_fRadius * m_fRate);	//�ʒu
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
//�I�u�W�F�N�g���b�V���̕`��
//============================
void CObjectCylinder::Draw()
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
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

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
void CObjectCylinder::Draw(const char* path)
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
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

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
	pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist(path)));

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertex, 0, m_nPolygon);
}

//================================
//�I�u�W�F�N�g���b�V���̃N���G�C�g
//================================
CObjectCylinder* CObjectCylinder::Create(D3DXVECTOR3 pos, float radius)
{
	//�|�C���^�p�̕ϐ�
	CObjectCylinder* pObject;

	//�������̊m��
	pObject = new CObjectCylinder;

	//�p�����[�^�̐ݒ�
	pObject->SetPos(pos);			//�ʒu�̐ݒ�
	pObject->m_fRadius = radius;	//���a�̐ݒ�

	//������
	pObject->Init();

	return pObject;
}

//================================
//���_�J���[�̐ݒ�
//================================
void CObjectCylinder::SetColor(D3DXCOLOR color)
{
	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�㉺�̐�����
	for (int j = 0; j < 2; j++)
	{
		//�p�̐���������
		for (int i = 0; i < NUM_CORNER; i++)
		{
			pVtx[i + NUM_CORNER * j].col = color;	//�F
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�ϐ��ɕۑ�
	m_Color = color;
}