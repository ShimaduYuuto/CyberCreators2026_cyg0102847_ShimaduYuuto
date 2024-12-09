//======================================
//
//	�O�Ղ̏���[orbit.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "orbit.h"
#include "manager.h"
#include "game.h"

//�O�ՃN���X�̒萔�̏�����
const D3DXVECTOR3 COrbit::BLOCK = { NUM_ORBIT - 1, 1, 0 };			//�u���b�N��
const D3DXVECTOR3 COrbit::SIZE = { 0.0f, 0.0f, 0.0f };				//�T�C�Y

//============================
//�O�Ղ̃R���X�g���N�^
//============================
COrbit::COrbit(int nPriority) : CObjectMesh(nPriority)
{
	//���񂵂ď�����
	for (int i = 0; i < NUM_VTX; i++)
	{
		//���_���̏�����
		m_SaveVtx[i].pos = { 0.0f, 0.0f, 0.0f };
		m_SaveVtx[i].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.7f);
		m_SaveVtx[i].nor = { 0.0f, 0.0, -1.0f };

		if ((i & 1) == 0) //����
		{
			m_SaveVtx[i].tex = { 0.0f, 0.0f };
		}
		else
		{
			m_SaveVtx[i].tex = { 0.0f, 1.0f };
		}
	}

	//���߂Ă̐ݒ肩�̔���
	m_bFirstSet = false;
}

//============================
//�O�Ղ̃f�X�g���N�^
//============================
COrbit::~COrbit()
{

}

//============================
//�O�Ղ̏�����
//============================
HRESULT COrbit::Init()
{
	//������
	CObjectMesh::Init(BLOCK.x, BLOCK.y, SIZE.x, SIZE.y, CObjectMesh::MESHTYPE_WALL);
	return S_OK;
}

//============================
//�O�Ղ̏I������
//============================
void COrbit::Uninit()
{
	//�I������
	CObjectMesh::Uninit();
}

//============================
//�O�Ղ̍X�V
//============================
void COrbit::Update()
{
	//�e�N���X�̒��_�ɔ��f
	for (int i = 0; i < NUM_VTX; i++)
	{
		//�ʒu�ƐF�𔽉f
		CObjectMesh::SetVtxPos(i, m_SaveVtx[i].pos);
		CObjectMesh::SetVtxColor(i, m_SaveVtx[i].col);
	}
}

//============================
//�O�Ղ̕`��
//============================
void COrbit::Draw()
{
	//�e�N���X�ŕ`��
	CObjectMesh::Draw("data\\TEXTURE\\SmashMesh000.png");
}

//================================
//�O�Ղ̃N���G�C�g
//================================
COrbit* COrbit::Create()
{
	//�|�C���^�p�̕ϐ�
	COrbit* pOrbit;

	//�������̊m��
	pOrbit = new COrbit;

	//������
	pOrbit->Init();

	//�p�����[�^�̐ݒ�
	pOrbit->SetPos({ 0.0f, 0.0f, 0.0f });	//�ʒu�̐ݒ�

	//���񂵂ď�����
	for (int i = 0; i < NUM_VTX; i++)
	{
		pOrbit->SetVtxTex(i, pOrbit->m_SaveVtx[i].tex);
	}

	//�|�C���^��Ԃ�
	return pOrbit;
}

//================================
//�O�Ղ̈ʒu�ݒ�
//================================
void COrbit::SetOrbit(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	//�Â����_���X�V
	for (int i = NUM_VTX - 1; i > 1; i--)
	{
		//�擪�ȊO�̒��_�̏����㏑��
		m_SaveVtx[i].pos = m_SaveVtx[i - 2].pos;
	}

	//�擪�̒��_�̈ʒu�X�V
	m_SaveVtx[1].pos = pos1;	//�I�t�Z�b�g���ړ������ʒu����
	m_SaveVtx[0].pos = pos0;	//�O�Ղ��o���e���f���̈ʒu����

	//���߂Đݒ肷��Ȃ�
	if (!m_bFirstSet)
	{
		//�ݒ�ς�
		m_bFirstSet = true;

		//�Â����_���X�V
		for (int i = NUM_VTX - 1; i > 1; i--)
		{
			//���_�̏㏑��
			if ((i & 1) == 0) //����
			{
				m_SaveVtx[i].pos = pos0;
			}
			else //�
			{
				m_SaveVtx[i].pos = pos1;
			}
		}
	}
}