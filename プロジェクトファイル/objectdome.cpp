//======================================
//
//	�V�����_�[�I�u�W�F�N�g�̏���[objectdome.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "objectdome.h"
#include "manager.h"
#include "game.h"

//�I�u�W�F�N�g���b�V���N���X�̒萔�̏�����
const int CObjectDome::NUM_CORNER = 8;			//�p�̐�
const float CObjectDome::HEIGHT = 50.0f;		//����

//============================
//�I�u�W�F�N�g���b�V���̃R���X�g���N�^
//============================
CObjectDome::CObjectDome(int nPriority) : CObject(nPriority),
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
CObjectDome::~CObjectDome()
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

	CObject::Uninit();
}

//============================
//�I�u�W�F�N�g���b�V���̏�����
//============================
HRESULT CObjectDome::Init()
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	m_nIndex = ((NUM_CORNER * 2 + 2) * (NUM_VIRTICAL - 1)) + 2 * (NUM_VIRTICAL - 2);	//�C���f�b�N�X��
	m_nVertex = NUM_CORNER * (NUM_VIRTICAL - 1) + 1;									//���_��(�p�̐�*����+��ԏ�̒��_)
	m_nPolygon = (NUM_CORNER * 2 * ((NUM_VIRTICAL - 1)) + 4 * (NUM_VIRTICAL - 2));		//�|���S����

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

	//��ԏ�̒��_��ʂŏ���������
	pVtx[0].pos = D3DXVECTOR3(0.0f, m_fRadius, 0.0f);
	pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx++;	//���̃|�C���^�ɐi�߂�

	//�㉺�̐�����
	for (int j = 1; j < NUM_VIRTICAL; j++)
	{
		//�{��
		float fHeightRate = 1.0f - ((float)j / (NUM_VIRTICAL - 1));
		float fWidthRate = ((float)j / (NUM_VIRTICAL - 1));

		//�p�̐���������
		for (int i = 0; i < NUM_CORNER; i++)
		{
			//�p�x���Z�o
			float fAngle = (D3DX_PI * 2) * (float)(i / (float)NUM_CORNER);

			//�e�ϐ��ɒl����
			pVtx[i + NUM_CORNER * (j - 1)].pos = D3DXVECTOR3(
				sinf(fAngle) * m_fRadius * cosf(fHeightRate * D3DX_PI * 0.5f),
				sinf(fHeightRate * D3DX_PI * 0.5f) * m_fRadius,
				cosf(fAngle) * m_fRadius * cosf(fHeightRate * D3DX_PI * 0.5f));


			pVtx[i + NUM_CORNER * (j - 1)].tex = D3DXVECTOR2(1.0f * (i / NUM_CORNER), fWidthRate);	//UV���W
			pVtx[i + NUM_CORNER * (j - 1)].nor = D3DXVECTOR3(sinf(fAngle + D3DX_PI) / D3DX_PI,
				0.0f,
				cosf(fAngle + D3DX_PI) / D3DX_PI);	//�@���x�N�g��
			pVtx[i + NUM_CORNER * (j - 1)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);				//�F
		}
	}

	pVtx--;	//�|�C���^�����ɖ߂�

	//�C���f�b�N�X�̌v�Z�p�̕ϐ�
	nX = 0;
	nHeightCount = 0;
	int nAngleCount = 0;

	//�C���f�b�N�X�̌v�Z
	for (int i = 0; i < NUM_VIRTICAL - 1; i++)
	{
		//�J�E���g�̏�����
		nAngleCount = 0;
		int nAddCount = i * (NUM_CORNER * 2 + 4);

		//�k�ނ̌v�Z
		if (i > 0)
		{
			pIdx[nAddCount - 2] = (WORD)1 + ((i - 1) * NUM_CORNER);
			pIdx[nAddCount - 1] = (WORD)1 + ((i - 1) * NUM_CORNER);
		}

		for (int j = 0; j < NUM_CORNER * 2; j++)
		{
			//�����̏ꍇ
			if ((j & 1) == 0)
			{
				pIdx[j + nAddCount] = (WORD)1 + nAngleCount + (i * NUM_CORNER);
			}
			else//��̏ꍇ
			{
				//�ŏ��̎���Ȃ�0��ݒ�
				if (i == 0)
				{
					pIdx[j + nAddCount] = (WORD)0;
				}
				else
				{
					pIdx[j + nAddCount] = (WORD)nAngleCount + NUM_CORNER * (i - 1) + 1;
				}
				
				nAngleCount++;
			}
		}

		//����̍Ō�(��Ŋe�W��̍ŏ���Idx��������)
		pIdx[NUM_CORNER * 2 + nAddCount] = pIdx[0 + nAddCount];
		pIdx[NUM_CORNER * 2 + 1 + nAddCount] = pIdx[1 + nAddCount];
	}

	for (int i = 0; i < m_nIndex; i++)
	{
		int A = (int)pIdx[i];
		A = (int)pIdx[i];
	}

	//�C���f�b�N�X�̌v�Z
	//for (int i = 0; i < m_nIndex; i++)
	//{


	//	//�����̏ꍇ
	//	if ((i & 1) == 0)
	//	{
	//		pIdx[i] = (WORD)(NUM_CORNER + nAngleCount);
	//	}
	//	else//��̏ꍇ
	//	{
	//		pIdx[i] = (WORD)nAngleCount;
	//		nAngleCount++;
	//	}

	//	//1�T���鎞�ɃJ�E���g�̏�����
	//	if (nAngleCount == NUM_CORNER)
	//	{
	//		nAngleCount = 0;
	//	}
	//}

	//�|���S���̐�������
	//for (int i = 0; i < m_nPolygon; i++)
	//{
	//	//�k�ނȂ�R���e�B�j���[
	//	if ((pIdx[i] == pIdx[i + 1]) || (pIdx[i + 1] == pIdx[i + 2]))
	//	{
	//		continue;
	//	}

	//	//�@���x�N�g�����i�[����ϐ�
	//	D3DXVECTOR3 SurfaceNorVec; //�ʖ@���̃x�N�g��
	//	D3DXVECTOR3 vecNormal; //���K�������x�N�g��
	//	D3DXVECTOR3 vector1; //�P�ڂ̃x�N�g���̕ۊǗp
	//	D3DXVECTOR3 vector2; //�Q�ڂ̃x�N�g���̕ۊǗp

	//	//�C���f�b�N�X���i�[����ϐ�
	//	WORD index0 = pIdx[i + 0];
	//	WORD index1 = pIdx[i + 1];
	//	WORD index2 = pIdx[i + 2];

	//	//���_���i�[����ϐ�
	//	VERTEX_3D* vtx0 = pVtx + index0;
	//	VERTEX_3D* vtx1 = pVtx + index1;
	//	VERTEX_3D* vtx2 = pVtx + index2;

	//	//�@���x�N�g���̎Z�o
	//	if ((i & 1) == 0) //����
	//	{
	//		vector1 = vtx1->pos - vtx0->pos;
	//		vector2 = vtx2->pos - vtx0->pos;
	//	}
	//	else //�
	//	{
	//		vector1 = vtx2->pos - vtx0->pos;
	//		vector2 = vtx1->pos - vtx0->pos;
	//	}

	//	//�x�N�g���̌v�Z
	//	D3DXVec3Cross(&SurfaceNorVec, &vector1, &vector2);

	//	//�x�N�g���̐��K��
	//	D3DXVec3Normalize(&vecNormal, &SurfaceNorVec);

	//	//�x�N�g�������Z
	//	vtx0->nor += vecNormal;
	//	vtx1->nor += vecNormal;
	//	vtx2->nor += vecNormal;
	//}

	//���Z�����x�N�g���𐳋K��
	//for (int nCount = 0; nCount < m_nVertex; nCount++)
	//{
	//	//�x�N�g���̐��K��
	//	D3DXVec3Normalize(&pVtx[nCount].nor, &pVtx[nCount].nor);
	//}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//============================
//�I�u�W�F�N�g���b�V���̏I������
//============================
void CObjectDome::Uninit()
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
void CObjectDome::Update()
{
	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	int nX = 0;
	int nHeightCount = 0;

	//��ԏ�̒��_��ʂŏ���������
	pVtx[0].pos = D3DXVECTOR3(0.0f, m_fRadius * m_fRate, 0.0f);
	pVtx++;	//���̃|�C���^�ɐi�߂�

	//�㉺�̐�����
	for (int j = 1; j < NUM_VIRTICAL; j++)
	{
		//�{��
		float fHeightRate = 1.0f - ((float)j / (NUM_VIRTICAL - 1));
		float fWidthRate = ((float)j / (NUM_VIRTICAL - 1));

		//�p�̐���������
		for (int i = 0; i < NUM_CORNER; i++)
		{
			//�p�x���Z�o
			float fAngle = (D3DX_PI * 2) * (float)(i / (float)NUM_CORNER);

			//�e�ϐ��ɒl����
			pVtx[i + NUM_CORNER * (j - 1)].pos = D3DXVECTOR3(
				sinf(fAngle) * m_fRadius * cosf(fHeightRate * D3DX_PI * 0.5f) * m_fRate,
				sinf(fHeightRate * D3DX_PI * 0.5f) * m_fRadius * m_fRate,
				cosf(fAngle) * m_fRadius * cosf(fHeightRate * D3DX_PI * 0.5f) * m_fRate);
		}
	}

	pVtx--;	//�|�C���^�����ɖ߂�

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
//�I�u�W�F�N�g���b�V���̕`��
//============================
void CObjectDome::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;														//�v�Z�p�}�g���b�N�X
	CTexture* pTexture = CManager::GetInstance()->GetTexture();							//�e�N�X�`���̓ǂݍ���

	//�J�����O���@��ύX
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

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

	//�J�����O���@��ύX
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//============================
//�I�u�W�F�N�g���b�V���̕`��
//============================
void CObjectDome::Draw(const char* path)
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
CObjectDome* CObjectDome::Create(D3DXVECTOR3 pos, float radius)
{
	//�|�C���^�p�̕ϐ�
	CObjectDome* pObject;

	//�������̊m��
	pObject = new CObjectDome;

	//�p�����[�^�̐ݒ�
	pObject->SetPos(pos);			//�ʒu�̐ݒ�
	pObject->m_fRadius = radius;	//���a�̐ݒ�

	//������
	pObject->Init();

	return pObject;
}