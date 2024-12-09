//======================================
//
//	�I�u�W�F�N�g2D�̏���[object2D.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"
#include "manager.h"

//============================
//�I�u�W�F�N�g2D�̃R���X�g���N�^
//============================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	//�|�C���^�̏�����
	m_pVtxBuff = nullptr;

	//�p�����[�^�̏�����
	m_polygon.move = { 0.0f, 0.0f, 0.0f };
	m_polygon.rot = { 0.0f, 0.0f, 0.0f };
	m_polygon.size = { 100.0f, 0.0f, 100.0f };
}

//============================
//�I�u�W�F�N�g2D�̃f�X�g���N�^
//============================
CObject2D::~CObject2D()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//============================
//�I�u�W�F�N�g2D�̏�����
//============================
HRESULT CObject2D::Init()
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx; //�ǉ����̃|�C���^

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
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
//�I�u�W�F�N�g2D�̏I������
//============================
void CObject2D::Uninit()
{
	//�����̊J��
	if (this != nullptr)
	{
		//����
		SetDeath();
	}
}

//============================
//�I�u�W�F�N�g2D�̍X�V
//============================
void CObject2D::Update()
{
	//�ʒu�̎擾
	D3DXVECTOR3 Pos = GetPos();

	//�ړ��ʂ̉��Z
	Pos += m_polygon.move;

	VERTEX_2D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���[�J���ϐ��Œ������v�Z
	float fLength = sqrtf(m_polygon.size.x * m_polygon.size.x + m_polygon.size.y * m_polygon.size.y) * 0.5f; //�Ίp���̒������Z�o����
	float fAngle = atan2f(m_polygon.size.x, m_polygon.size.y);//�Ίp���̊p�x���Z�o

	//���_���̍X�V
	pVtx[0].pos.x = Pos.x + sinf(m_polygon.rot.z + -(D3DX_PI - fAngle)) * fLength;
	pVtx[0].pos.y = Pos.y + cosf(m_polygon.rot.z + -(D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.x = Pos.x + sinf(m_polygon.rot.z + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.y = Pos.y + cosf(m_polygon.rot.z + (D3DX_PI - fAngle)) * fLength;
	pVtx[2].pos.x = Pos.x + sinf(m_polygon.rot.z + -fAngle) * fLength;
	pVtx[2].pos.y = Pos.y + cosf(m_polygon.rot.z + -fAngle) * fLength;
	pVtx[3].pos.x = Pos.x + sinf(m_polygon.rot.z + fAngle) * fLength;
	pVtx[3].pos.y = Pos.y + cosf(m_polygon.rot.z + fAngle) * fLength;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�ʒu�̐ݒ�
	SetPos(Pos);
}

//============================
//�I�u�W�F�N�g2D�̊����X�V
//============================
void CObject2D::Update(float max, float value)
{
	//���[�J���ϐ�
	float fRate = value / max;	//�|���S���̊���
	VERTEX_2D* pVtx;			//�ǉ����̃|�C���^
	D3DXVECTOR3 Pos = GetPos();	//�ʒu�̎擾

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̍X�V
	pVtx[0].pos.x = Pos.x - (m_polygon.size.x * 0.5f);
	pVtx[0].pos.y = Pos.y - (m_polygon.size.y * 0.5f);
	pVtx[1].pos.x = Pos.x + (m_polygon.size.x * fRate) - (m_polygon.size.x * 0.5f);
	pVtx[1].pos.y = Pos.y - (m_polygon.size.y * 0.5f);
	pVtx[2].pos.x = Pos.x - (m_polygon.size.x * 0.5f);
	pVtx[2].pos.y = Pos.y + (m_polygon.size.y * 0.5f);
	pVtx[3].pos.x = Pos.x + (m_polygon.size.x * fRate) - (m_polygon.size.x * 0.5f);
	pVtx[3].pos.y = Pos.y + (m_polygon.size.y * 0.5f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f * fRate, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f * fRate, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�ʒu�̐ݒ�
	SetPos(Pos);
}

//============================
//�I�u�W�F�N�g2D�̕`��
//============================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//���e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================
//�I�u�W�F�N�g2D�̕`��
//============================
void CObject2D::Draw(const char* texturepath)
{
	//�e�N�X�`���̓ǂݍ���
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist(texturepath)));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//���e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================
//�I�u�W�F�N�g2D�̃N���G�C�g
//============================
CObject2D* CObject2D::Create()
{
	//�|�C���^�p�̕ϐ�
	CObject2D* pObject;

	//�������̊m��
	pObject = new CObject2D;

	//������
	pObject->Init();

	return pObject;
}

//============================
//�F�̐ݒ�
//============================
void CObject2D::SetColor(D3DXCOLOR color)
{
	//���g���Ȃ��Ȃ甲����
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	VERTEX_2D* pVtx; //�ǉ����̃|�C���^

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
//�e�N�X�`���̍��W�ݒ�
//============================
void CObject2D::SetTextureUV(float u1, float u2, float v1, float v2)
{
	VERTEX_2D* pVtx; //�ǉ����̃|�C���^

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