//======================================
//
//	X�t�@�C���̊Ǘ�[xfile.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "xfile.h"
#include "manager.h"

//�ÓI�����o�ϐ��̏�����
std::map<std::string, CXfile::XFileInfo> CXfile::m_pXfilemap = {};	//X�t�@�C���̏��

//============================
//X�t�@�C���̃R���X�g���N�^
//============================
CXfile::CXfile()
{
	
}

//============================
//X�t�@�C���̃f�X�g���N�^
//============================
CXfile::~CXfile()
{

}

//============================
//X�t�@�C���̔j��
//============================
void CXfile::Unload()
{
	//�S�Ă�X�t�@�C���̔ԍ��ƃp�X��j��
	m_pXfilemap.erase(m_pXfilemap.begin(), m_pXfilemap.end());
}

//============================
//X�t�@�C���̓o�^
//============================
int CXfile::Regist(const char* pXfileName)
{
	//X�t�@�C�������݂��Ă��Ȃ�������
	if (m_pXfilemap.count(pXfileName) == NULL)		//1������������O
	{
		//�����ꎞ�I�ɕێ�����ϐ�
		CXfile::XFileInfo pObjectInfo = {NULL};		//�I�u�W�F�N�g�̏��
		pObjectInfo.nIndex = m_pXfilemap.size();	//�v�f��

		//�f�o�C�X�̐錾
		LPDIRECT3DDEVICE9 pDevice;

		//�f�o�C�X�̎擾
		pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(pXfileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&pObjectInfo.pBuffmat,
			NULL,
			&pObjectInfo.dwNumMat,
			&pObjectInfo.pMesh);

		D3DXMATERIAL* pMat; //�}�e���A���ւ̃|�C���^

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)pObjectInfo.pBuffmat->GetBufferPointer();

		//�}�e���A���̐���������
		for (int nCntMat = 0; nCntMat < (int)pObjectInfo.dwNumMat; nCntMat++)
		{
			//�e�N�X�`�������݂���
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���ǂݍ��ݗp
				LPDIRECT3DTEXTURE9 pTexture;

				//�e�N�X�`����ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&pTexture);

				//�e�N�X�`���̃������m��
				pObjectInfo.pTexture.push_back(pTexture);
			}
		}

		//�T�C�Y�̓ǂݍ���
		LoadSize(pObjectInfo);

		//�}�b�v�̐���
		m_pXfilemap[pXfileName] = { pObjectInfo };
	}

	//X�t�@�C���̒l��Ԃ�
	return m_pXfilemap[pXfileName].nIndex;
}

//============================
//�T�C�Y�̓ǂݍ���
//============================
void CXfile::LoadSize(XFileInfo& pfileinfo)
{
	//�l�̏�����
	pfileinfo.aSize.Max = { 0.0f, 0.0f, 0.0f };
	pfileinfo.aSize.Min = { 0.0f, 0.0f, 0.0f };

	//���_����ǂݍ��ނ��߂̃��[�J���ϐ��錾
	int nNumVtx;			//���_��
	DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = pfileinfo.pMesh->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(pfileinfo.pMesh->GetFVF());
	//���_�o�b�t�@�̃��b�N
	pfileinfo.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//���_�̐���������
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//���_���W���r���ă��f���̍ŏ��l�ő�l���擾
		//X���W
		if (vtx.x > pfileinfo.aSize.Max.x)
		{
			pfileinfo.aSize.Max.x = vtx.x;
		}
		else if (vtx.x < pfileinfo.aSize.Min.x)
		{
			pfileinfo.aSize.Min.x = vtx.x;
		}

		//Y���W
		if (vtx.y > pfileinfo.aSize.Max.y)
		{
			pfileinfo.aSize.Max.y = vtx.y;
		}
		else if (vtx.y < pfileinfo.aSize.Min.y)
		{
			pfileinfo.aSize.Min.y = vtx.y;
		}

		//Z���W
		if (vtx.z > pfileinfo.aSize.Max.z)
		{
			pfileinfo.aSize.Max.z = vtx.z;
		}
		else if (vtx.z < pfileinfo.aSize.Min.z)
		{
			pfileinfo.aSize.Min.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	//���_�o�b�t�@�̃A�����b�N
	pfileinfo.pMesh->UnlockVertexBuffer();
}

//============================
//X�t�@�C���̎擾
//============================
CXfile::XFileInfo CXfile::GetAddress(int nIdx)
{
	//X�t�@�C���̐���������
	for (auto& iter : m_pXfilemap)
	{
		//�����ƒl����v�����Ȃ�
		if (iter.second.nIndex == nIdx)
		{
			//X�t�@�C���̃p�X��Ԃ�
			return iter.second;
		}
	}

	//X�t�@�C�������݂��Ȃ�
	return {};
}