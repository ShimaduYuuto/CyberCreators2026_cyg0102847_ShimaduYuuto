//======================================
//
//	�t�B�[���h�̏���[field.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "field.h"
#include "manager.h"

//�t�B�[���h�N���X�̒萔�̏�����
const std::string CField::FILEPATH = "data\\MODEL\\Block001.x";		//�e�N�X�`���p�X
const D3DXVECTOR3 CField::BLOCK = { 50.0f, 0, 50.0f };				//�u���b�N��
const D3DXVECTOR3 CField::SIZE = { 10000.0f, -2.0f, 10000.0f };		//�T�C�Y

//============================
//�t�B�[���h�̃R���X�g���N�^
//============================
CField::CField(int nPriority) : CObject(nPriority)
{
	m_nIndex = (int)(2 * (BLOCK.x + 1) * BLOCK.z + (BLOCK.z - 1) * 2);	//�C���f�b�N�X��
	m_nVertex = (int)((BLOCK.x + 1) * (BLOCK.z + 1));					//���_��
	m_nPolygon = (int)((BLOCK.x * BLOCK.z) * 2 + (BLOCK.z - 1) * 4);	//�|���S����
}

//============================
//�t�B�[���h�̃f�X�g���N�^
//============================
CField::~CField()
{

}

//============================
//�t�B�[���h�̏�����
//============================
HRESULT CField::Init()
{
	//���[�J���ϐ�
	//LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾
	//pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//�t�B�[���h���̓ǂݍ���
	Load();

	//pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nVertex),
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_3D,
	//	D3DPOOL_MANAGED,
	//	&m_pVtxBuff,
	//	NULL);

	////�C���f�b�N�X�o�b�t�@�̐���
	//pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndex,
	//	D3DUSAGE_WRITEONLY,
	//	D3DFMT_INDEX16,
	//	D3DPOOL_MANAGED,
	//	&m_pIdxBuff,
	//	NULL);

	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N
	WORD* pIdx; //�ǉ��̃|�C���^
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//int nX = 0;
	//int nZ = 0;

	//���_�̐�������
	//for (int nCount = 0; nCount < m_nVertex; nCount++)
	//{
	//	//�ʒu�̐ݒ�
	//	pVtx[nCount].pos = D3DXVECTOR3(SIZE.x * (nX / (float)BLOCK.x) - (SIZE.x * 0.5f), 0.0f, -SIZE.z * (nZ / (float)BLOCK.z) + (SIZE.z * 0.5f));

	//	//�e�N�X�`���̓ǂݍ���
	//	pVtx[nCount].tex = D3DXVECTOR2(1.0f * (nX / (float)BLOCK.x), 1.0f * (nZ / (float)BLOCK.z));
	//	pVtx[nCount].tex = D3DXVECTOR2(nX, nZ);

	//	nX++;

	//	//Z��i�߂�
	//	if (nX == BLOCK.x + 1)
	//	{
	//		nX = 0;
	//		nZ++;
	//	}

	//	//�@���x�N�g���̐ݒ�
	//	pVtx[nCount].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	//���_�J���[�̐ݒ�
	//	pVtx[nCount].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	//}

	////�C���f�b�N�X�̌v�Z�p�̕ϐ�
	//nX = 0;
	//nZ = 0;
	//int nX2 = 0;

	////�C���f�b�N�X�̌v�Z
	//for (int nCount = 0; nCount < m_nIndex; nCount++)
	//{
	//	//�k�ރ|���S���̏ꍇ�Ƃ���ȊO
	//	if (nCount == ((int)(BLOCK.x + 1) * 2 + 2) * (nZ + 1) - 2)
	//	{
	//		pIdx[nCount] = pIdx[nCount - 1];
	//	}
	//	else if (nCount == ((int)(BLOCK.x + 1) * 2 + 2) * (nZ + 1) - 1)
	//	{
	//		pIdx[nCount] = pIdx[nCount - 1] + (WORD)BLOCK.x + 2;
	//		nZ++;
	//	}
	//	else
	//	{
	//		if (nCount % 2 == 0)//�����̏ꍇ
	//		{
	//			pIdx[nCount] = (WORD)(BLOCK.x + 1 + nX);
	//			nX++;
	//		}
	//		else//��̏ꍇ
	//		{
	//			pIdx[nCount] = (WORD)nX2;
	//			nX2++;
	//		}
	//	}
	//}

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

		//�ʖ@���x�N�g����ۑ�
		m_SurfaceNorVec.push_back(vecNormal);
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
//�t�B�[���h�̏I������
//============================
void CField::Uninit()
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

	//����
	CObject::Uninit();

	//�ʖ@���x�N�g������j��
	m_SurfaceNorVec.clear();
}

//============================
//�t�B�[���h�̍X�V
//============================
void CField::Update()
{

}

//============================
//�t�B�[���h�̓����蔻��
//============================
bool CField::MeshCollision(D3DXVECTOR3& pos)
{
	//�Ԃ��p�̕ϐ�
	bool bHit = false;	//�����������̔���
	int nCnt = 0;		//���b�V���̃J�E���g

	float PlayerHeight = pos.y;	//�L�����N�^�[�̍���

	//���b�V���p�ϐ�
	WORD* pIdx; //�ǉ��̃|�C���^
	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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
		D3DXVECTOR3 vector1; //1�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 vector2; //2�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 vector3; //3�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 playervector1; //1�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 playervector2; //2�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 playervector3; //3�ڂ̃x�N�g���̕ۊǗp 
		D3DXVECTOR3 Vec1; //1�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 Vec2; //2�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 Vec3; //3�ڂ̃x�N�g���̕ۊǗp 

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
			//�|���S���̃x�N�g�����v�Z
			vector1 = vtx2->pos - vtx0->pos;
			vector2 = vtx1->pos - vtx2->pos;
			vector3 = vtx0->pos - vtx1->pos;

			//�v���C���[�̃x�N�g�����v�Z
			playervector1 = pos - vtx0->pos;
			playervector2 = pos - vtx2->pos;
			playervector3 = pos - vtx1->pos;
		}
		else //�
		{
			//�|���S���̃x�N�g�����v�Z
			vector1 = vtx1->pos - vtx0->pos;
			vector2 = vtx2->pos - vtx1->pos;
			vector3 = vtx0->pos - vtx2->pos;

			//�v���C���[�̃x�N�g�����v�Z
			playervector1 = pos - vtx0->pos;
			playervector2 = pos - vtx1->pos;
			playervector3 = pos - vtx2->pos;
		}

		//�x�N�g���̌v�Z
		D3DXVec3Cross(&Vec1, &playervector1, &vector1);
		D3DXVec3Cross(&Vec2, &playervector2, &vector2);
		D3DXVec3Cross(&Vec3, &playervector3, &vector3);

		//�x�N�g���̐��K��
		D3DXVec3Normalize(&Vec1, &Vec1);
		D3DXVec3Normalize(&Vec2, &Vec2);
		D3DXVec3Normalize(&Vec3, &Vec3);

		//�|���S���̒��ɂ�����F��ω�
		if (Vec1.y >= 0.0f && Vec2.y >= 0.0f && Vec3.y >= 0.0f)
		{
			//���ς̌v�Z���獂�����Z�o
			PlayerHeight = MeshIPCluculation(pos - vtx0->pos, m_SurfaceNorVec[nCnt]) + vtx0->pos.y;

			//���݂̍����̕������Ȃ�␳
			if (PlayerHeight >= pos.y)
			{
				//���������킹��
				pos.y = PlayerHeight;
				bHit = true;
			}

			//�v�Z�����𔲂���
			break;
		}

		//�J�E���g�A�b�v
		nCnt++;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	//������Ԃ�
	return bHit;
}

//============================
//�t�B�[���h�̓����蔻��
//============================
bool CField::MeshCollision(D3DXVECTOR3& pos, D3DXVECTOR3& rot)
{
	//�Ԃ��p�̕ϐ�
	bool bHit = false;	//�����������̔���
	int nCnt = 0;		//���b�V���̃J�E���g

	float PlayerHeight = pos.y;	//�L�����N�^�[�̍���

	//���b�V���p�ϐ�
	WORD* pIdx; //�ǉ��̃|�C���^
	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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
		D3DXVECTOR3 vector1; //1�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 vector2; //2�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 vector3; //3�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 playervector1; //1�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 playervector2; //2�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 playervector3; //3�ڂ̃x�N�g���̕ۊǗp 
		D3DXVECTOR3 Vec1; //1�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 Vec2; //2�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 Vec3; //3�ڂ̃x�N�g���̕ۊǗp 

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
			//�|���S���̃x�N�g�����v�Z
			vector1 = vtx2->pos - vtx0->pos;
			vector2 = vtx1->pos - vtx2->pos;
			vector3 = vtx0->pos - vtx1->pos;

			//�v���C���[�̃x�N�g�����v�Z
			playervector1 = pos - vtx0->pos;
			playervector2 = pos - vtx2->pos;
			playervector3 = pos - vtx1->pos;
		}
		else //�
		{
			//�|���S���̃x�N�g�����v�Z
			vector1 = vtx1->pos - vtx0->pos;
			vector2 = vtx2->pos - vtx1->pos;
			vector3 = vtx0->pos - vtx2->pos;

			//�v���C���[�̃x�N�g�����v�Z
			playervector1 = pos - vtx0->pos;
			playervector2 = pos - vtx1->pos;
			playervector3 = pos - vtx2->pos;
		}

		//�x�N�g���̌v�Z
		D3DXVec3Cross(&Vec1, &playervector1, &vector1);
		D3DXVec3Cross(&Vec2, &playervector2, &vector2);
		D3DXVec3Cross(&Vec3, &playervector3, &vector3);

		//�x�N�g���̐��K��
		D3DXVec3Normalize(&Vec1, &Vec1);
		D3DXVec3Normalize(&Vec2, &Vec2);
		D3DXVec3Normalize(&Vec3, &Vec3);

		//�|���S���̒��ɂ�����F��ω�
		if (Vec1.y >= 0.0f && Vec2.y >= 0.0f && Vec3.y >= 0.0f)
		{
			//���ς̌v�Z���獂�����Z�o
			PlayerHeight = MeshIPCluculation(pos - vtx0->pos, m_SurfaceNorVec[nCnt]) + vtx0->pos.y;

			//���������킹��
			pos.y = PlayerHeight;
			bHit = true;

			//���������킹��
			rot = m_SurfaceNorVec[nCnt];

			//�v�Z�����𔲂���
			break;
		}

		//�J�E���g�A�b�v
		nCnt++;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	//������Ԃ�
	return bHit;
}

//=================================
//�t�B�[���h�̈ʒu�ɕϊ�
//=================================
D3DXVECTOR3 CField::ConvertMeshPos(D3DXVECTOR3 pos)
{
	//�v�Z�ɕK�v�ȕϐ�
	float PlayerHeight = pos.y;	//�L�����N�^�[�̍���
	int nCnt = 0;		//���b�V���̃J�E���g

	//���b�V���p�ϐ�
	WORD* pIdx; //�ǉ��̃|�C���^
	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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
		D3DXVECTOR3 vector1; //1�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 vector2; //2�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 vector3; //3�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 playervector1; //1�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 playervector2; //2�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 playervector3; //3�ڂ̃x�N�g���̕ۊǗp 
		D3DXVECTOR3 Vec1; //1�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 Vec2; //2�ڂ̃x�N�g���̕ۊǗp
		D3DXVECTOR3 Vec3; //3�ڂ̃x�N�g���̕ۊǗp 

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
			//�|���S���̃x�N�g�����v�Z
			vector1 = vtx2->pos - vtx0->pos;
			vector2 = vtx1->pos - vtx2->pos;
			vector3 = vtx0->pos - vtx1->pos;

			//�v���C���[�̃x�N�g�����v�Z
			playervector1 = pos - vtx0->pos;
			playervector2 = pos - vtx2->pos;
			playervector3 = pos - vtx1->pos;
		}
		else //�
		{
			//�|���S���̃x�N�g�����v�Z
			vector1 = vtx1->pos - vtx0->pos;
			vector2 = vtx2->pos - vtx1->pos;
			vector3 = vtx0->pos - vtx2->pos;

			//�v���C���[�̃x�N�g�����v�Z
			playervector1 = pos - vtx0->pos;
			playervector2 = pos - vtx1->pos;
			playervector3 = pos - vtx2->pos;
		}

		//�x�N�g���̌v�Z
		D3DXVec3Cross(&Vec1, &playervector1, &vector1);
		D3DXVec3Cross(&Vec2, &playervector2, &vector2);
		D3DXVec3Cross(&Vec3, &playervector3, &vector3);

		//�x�N�g���̐��K��
		D3DXVec3Normalize(&Vec1, &Vec1);
		D3DXVec3Normalize(&Vec2, &Vec2);
		D3DXVec3Normalize(&Vec3, &Vec3);

		//�|���S���̒��ɂ�����F��ω�
		if (Vec1.y >= 0.0f && Vec2.y >= 0.0f && Vec3.y >= 0.0f)
		{
			//���ς̌v�Z���獂�����Z�o
			PlayerHeight = MeshIPCluculation(pos - vtx0->pos, m_SurfaceNorVec[nCnt]) + vtx0->pos.y;

			//���������킹��
			pos.y = PlayerHeight;

			//�v�Z�����𔲂���
			break;
		}

		//�J�E���g�A�b�v
		nCnt++;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	//������Ԃ�
	return pos;
}

//===================================
//���ς̌v�Z���ʂ�Ԃ�
//===================================
float CField::MeshIPCluculation(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2)
{
	//���ό�̍������i�[����ϐ�
	float Vec1_y = 0.0f;

	//���ς̌v�Z���ʂ��獂�����Z�o
	Vec1_y = (-(vec1.x * vec2.x) - (vec1.z * vec2.z)) / vec2.y;

	//������Ԃ�
	return Vec1_y;
}

//===================================
//���̔���
//===================================
D3DXVECTOR3 CField::WidthCollision(D3DXVECTOR3 pos)
{
	//�Ԃ��p�̈ʒu
	D3DXVECTOR3 Pos = pos;

	//���̔���
	if (Pos.x < GetPos().x + COLLISION_WIDTH * -0.5f + 30.0f)
	{
		Pos.x = GetPos().x + COLLISION_WIDTH * -0.5f + 30.0f;
	}
	//�E�̔���
	else if (Pos.x > GetPos().x + COLLISION_WIDTH * 0.5f - 30.0f)
	{
		Pos.x = GetPos().x + COLLISION_WIDTH * 0.5f - 30.0f;
	}

	return Pos;
}

//============================
//�t�B�[���h�̕`��
//============================
void CField::Draw()
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
	pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\FieldTexture000.png")));
	

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertex, 0, m_nPolygon);
}

//================================
//�t�B�[���h�̃N���G�C�g
//================================
CField* CField::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CField* pObjectX;

	//�������̊m��
	pObjectX = new CField;

	//�p�����[�^�̐ݒ�
	pObjectX->SetPos(pos);	//�ʒu�̐ݒ�

	//������
	pObjectX->Init();

	return pObjectX;
}

//============================
//�t�B�[���h�̓ǂݍ���
//============================
void CField::Load()
{
	//���[�J���ϐ��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen("data\\FILE\\Field.bin", "rb");

	//�t�@�C���ɏ��������o��
	if (pFile != NULL)
	{
		//���[�J���ϐ�
		LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
		pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

		//�f�[�^�̋L�^
		fread(&m_nVertex, sizeof(int), 1, pFile);	//���_��
		fread(&m_nIndex, sizeof(int), 1, pFile);	//�ԍ�
		fread(&m_nPolygon, sizeof(int), 1, pFile);	//�|���S����

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

		//���b�V���p�ϐ�
		WORD* pIdx; //�ǉ��̃|�C���^
		VERTEX_3D* pVtx; //�ǉ����̃|�C���^

		//�C���f�b�N�X�o�b�t�@�����b�N
		m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		fread(pVtx, sizeof(VERTEX_3D), m_nVertex, pFile);	//���_�o�b�t�@
		fread(pIdx, sizeof(WORD), m_nIndex, pFile);	//�C���f�b�N�X�o�b�t�@

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();

		//�C���f�b�N�X�o�b�t�@�̃A�����b�N
		m_pIdxBuff->Unlock();

		//�t�@�C�������
		fclose(pFile);
	}
}