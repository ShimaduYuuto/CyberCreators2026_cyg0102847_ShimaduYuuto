//======================================
//
//	�I�u�W�F�N�g3D�̏���[object3D.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "object3D.h"
#include "manager.h"

//============================
//�I�u�W�F�N�g3D�̃R���X�g���N�^
//============================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	//�|�C���^�̏�����
	m_pVtxBuff = nullptr;

	//�p�����[�^�̏�����
	m_polygon.move = { 0.0f, 0.0f, 0.0f };
	m_polygon.rot = { 0.0f, 0.0f, 0.0f };
	m_polygon.size = { 0.0f, 0.0f, 0.0f };
	m_polygon.fRate = 1.0f;
}

//============================
//�I�u�W�F�N�g3D�̃f�X�g���N�^
//============================
CObject3D::~CObject3D()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//============================
//�I�u�W�F�N�g3D�̏�����
//============================
HRESULT CObject3D::Init()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[1].pos.x = 0.0f;
	pVtx[1].pos.y = 0.0f;
	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = 0.0f;
	pVtx[3].pos.x = 0.0f;
	pVtx[3].pos.y = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//u.v
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================
//�I�u�W�F�N�g3D�̏I������
//============================
void CObject3D::Uninit()
{
	//�����̊J��
	if (this != nullptr)
	{
		//����
		SetDeath();
	}
}

//============================
//�I�u�W�F�N�g3D�̍X�V
//============================
void CObject3D::Update()
{
	//�ʒu�̎擾
	//D3DXVECTOR3 Pos = GetPos();

	////�ړ��ʂ̉��Z
	//Pos += m_polygon.move;

	//VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////���[�J���ϐ��Œ������v�Z
	//float fLength = sqrtf(m_polygon.size.x * m_polygon.size.x + m_polygon.size.z * m_polygon.size.z) * 0.5f * m_polygon.fRate; //�Ίp���̒������Z�o����
	//float fAngle = atan2f(m_polygon.size.x, m_polygon.size.z);//�Ίp���̊p�x���Z�o

	//pVtx[0].pos.x = sinf(m_polygon.rot.z + -(D3DX_PI - fAngle)) * fLength;
	//pVtx[0].pos.z = cosf(m_polygon.rot.z + -fAngle) * fLength;
	//pVtx[1].pos.x = sinf(m_polygon.rot.z + (D3DX_PI - fAngle)) * fLength;
	//pVtx[1].pos.z = cosf(m_polygon.rot.z + fAngle) * fLength;
	//pVtx[2].pos.x = sinf(m_polygon.rot.z + -fAngle) * fLength;
	//pVtx[2].pos.z = cosf(m_polygon.rot.z + -(D3DX_PI - fAngle)) * fLength;
	//pVtx[3].pos.x = sinf(m_polygon.rot.z + fAngle) * fLength;
	//pVtx[3].pos.z = cosf(m_polygon.rot.z + (D3DX_PI - fAngle)) * fLength;

	////���_�o�b�t�@���A�����b�N����
	//m_pVtxBuff->Unlock();

	////�ʒu�̐ݒ�
	//SetPos(Pos);
}

//============================
//�I�u�W�F�N�g3D�̕`��
//============================
void CObject3D::Draw()
{
	//�ʒu�̎擾
	D3DXVECTOR3 Pos = GetPos();

	//�`��p�̕ϐ�
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���[���h�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_polygon.rot.y, m_polygon.rot.x, m_polygon.rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�ʒu�̐ݒ�
	SetPos(Pos);
}

//============================
//�I�u�W�F�N�g3D�̕`��
//============================
void CObject3D::Draw(const char* texturepath)
{
	//�ʒu�̎擾
	D3DXVECTOR3 Pos = GetPos();

	//�e�N�X�`���̓ǂݍ���
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���[���h�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_polygon.rot.y, m_polygon.rot.x, m_polygon.rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist(texturepath)));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�ʒu�̐ݒ�
	SetPos(Pos);
}

//============================
//�I�u�W�F�N�g3D�̃N���G�C�g
//============================
CObject3D* CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�|�C���^�p�̕ϐ�
	CObject3D* pObject;

	//�������̊m��
	pObject = new CObject3D;

	//������
	pObject->Init();
	pObject->SetPos(pos);
	pObject->SetSize(size);

	return pObject;
}

//============================
//�F�̐ݒ�
//============================
void CObject3D::SetColor(D3DXCOLOR color)
{
	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
//�T�C�Y�̐ݒ�
//============================
void CObject3D::SetSize(D3DXVECTOR3 size, TYPE type)
{
	//�T�C�Y�̐ݒ�
	m_polygon.size = size;

	//�v�Z�p�̕ϐ�
	float fLength = 0.0f;	//�Ίp���̒������Z�o����
	float fAngle = 0.0f;	//�Ίp���̊p�x���Z�o

	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�v�Z�̕ύX
	switch (type)
	{
	case TYPE_FLOOR:
		fLength = sqrtf(m_polygon.size.x * m_polygon.size.x + m_polygon.size.z * m_polygon.size.z) * 0.5f * m_polygon.fRate; //�Ίp���̒������Z�o����
		fAngle = atan2f(m_polygon.size.x, m_polygon.size.z);	//�Ίp���̊p�x���Z�o

		//�|���S���̃T�C�Y
		pVtx[0].pos.x = sinf(m_polygon.rot.y + (D3DX_PI - fAngle)) * fLength;
		pVtx[0].pos.z = cosf(m_polygon.rot.y + (D3DX_PI - fAngle)) * fLength;
		pVtx[1].pos.x = sinf(m_polygon.rot.y + -(D3DX_PI - fAngle)) * fLength;
		pVtx[1].pos.z = cosf(m_polygon.rot.y + -(D3DX_PI - fAngle)) * fLength;
		pVtx[2].pos.x = sinf(m_polygon.rot.y + fAngle) * fLength;
		pVtx[2].pos.z = cosf(m_polygon.rot.y + fAngle) * fLength;
		pVtx[3].pos.x = sinf(m_polygon.rot.y + -fAngle) * fLength;
		pVtx[3].pos.z = cosf(m_polygon.rot.y + -fAngle) * fLength;
	break;

	case TYPE_WALL:
		fLength = sqrtf(m_polygon.size.x * m_polygon.size.x + m_polygon.size.y * m_polygon.size.y) * 0.5f * m_polygon.fRate; //�Ίp���̒������Z�o����
		fAngle = atan2f(m_polygon.size.x, m_polygon.size.y);	//�Ίp���̊p�x���Z�o

		//�|���S���̃T�C�Y
		pVtx[0].pos.x = sinf(m_polygon.rot.z + -(D3DX_PI - fAngle)) * fLength;
		pVtx[0].pos.y = cosf(m_polygon.rot.z + -(D3DX_PI - fAngle)) * -fLength;
		pVtx[1].pos.x = sinf(m_polygon.rot.z + (D3DX_PI - fAngle)) * fLength;
		pVtx[1].pos.y = cosf(m_polygon.rot.z + (D3DX_PI - fAngle)) * -fLength;
		pVtx[2].pos.x = sinf(m_polygon.rot.z + -fAngle) * fLength;
		pVtx[2].pos.y = cosf(m_polygon.rot.z + -fAngle) * -fLength;
		pVtx[3].pos.x = sinf(m_polygon.rot.z + fAngle) * fLength;
		pVtx[3].pos.y = cosf(m_polygon.rot.z + fAngle) * -fLength;
	break;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
//�|���S���̌v�Z
//============================
void CObject3D::Calculation(D3DXVECTOR3 rot, TYPE type)
{
	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�v�Z�̕ύX
	switch (type)
	{
	case TYPE_FLOOR:
		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		break;

	case TYPE_WALL:

		{
			//�p�x�̍ő���P�Ƃ����������Z�o
			float fNorVec = rot.y / D3DX_PI;

			//�@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(sinf(fNorVec), 0.0f,cosf(fNorVec));
			pVtx[1].nor = D3DXVECTOR3(sinf(fNorVec), 0.0f,cosf(fNorVec));
			pVtx[2].nor = D3DXVECTOR3(sinf(fNorVec), 0.0f,cosf(fNorVec));
			pVtx[3].nor = D3DXVECTOR3(sinf(fNorVec), 0.0f,cosf(fNorVec));
				
		}
		
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
//�e�N�X�`���̍��W�ݒ�
//============================
void CObject3D::SetTextureUV(float u1, float u2, float v1, float v2)
{
	VERTEX_3D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(u1, v1);//u.v
	pVtx[1].tex = D3DXVECTOR2(u2, v1);
	pVtx[2].tex = D3DXVECTOR2(u1, v2);
	pVtx[3].tex = D3DXVECTOR2(u2, v2);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}