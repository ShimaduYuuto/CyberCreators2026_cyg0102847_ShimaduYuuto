//======================================
//
//	��̏���[shadow.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "shadow.h"
#include "game.h"
#include "manager.h"

//�萔
const std::string CShadow::FILEPATH = "data\\TEXTURE\\effect000.jpg";
const D3DXCOLOR CShadow::COLOR = { 1.0f, 1.0f, 1.0f, 0.5f };

//============================
//�R���X�g���N�^
//============================
CShadow::CShadow(int nPriority) : CObject3D(nPriority),
	m_TargetPos(),
	m_quat(),
	m_mtxRot(),
	m_fValueRor(),
	m_vecAxis()
{

}

//============================
//�f�X�g���N�^
//============================
CShadow::~CShadow()
{
	//�|�C���^��null
	if (m_TargetPos != nullptr)
	{
		m_TargetPos = nullptr;
	}
}

//============================
//������
//============================
HRESULT CShadow::Init()
{
	//������
	CObject3D::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CShadow::Uninit()
{
	//�I������
	CObject3D::Uninit();
}

//============================
//�X�V
//============================
void CShadow::Update()
{
	//�ʒu�̍X�V
	D3DXVECTOR3 Pos = *m_TargetPos;				//�^�[�Q�b�g�̈ʒu���擾
	D3DXVECTOR3 Rot = GetRot();					//����
	D3DXVECTOR3 QuotRot = {0.0f, 1.0f, 0.0f};	//�N�H�[�^�j�I���̌���
	D3DXVECTOR3 CameraRot = { 0.0f, 0.0f, 0.0f };//�J�����̌���
	D3DXVECTOR3 normalizedNormal;

	Pos.y = 0.01f;		//���������ύX

	//�Q�[���V�[���Ȃ�t�B�[���h�̍����Ɉʒu��␳
	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
		pGame->GetGameField()->MeshCollision(Pos, Rot);
		//Rot.x *= -1.0f;
		Pos.y += 1.0f;												//���܂�Ȃ��悤�ɏ���������������
		Rot.y = 0.0f;
		normalizedNormal *= D3DX_PI;
		//Rot.x = normalizedNormal.x/* + D3DX_PI * 0.5f*/;
		//Rot.z = normalizedNormal.z/* + D3DX_PI * 0.5f*/;
	}

	//�N�H�[�^�j�I���̐ݒ�
	//m_vecAxis = QuotRot;
	//m_fValueRor = acos(D3DXVec3Dot(&CameraRot, &m_vecAxis));
	
	//�ʒu�ƌ�����ݒ�
	SetPos(Pos);
	SetRot(Rot);

	CObject3D::Update();
}

//============================
//�`��
//============================
void CShadow::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//Z�̔�r���@�ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�t�H�O�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//�I�u�W�F�N�g�̕`��
	CObject3D::Draw(FILEPATH.c_str());

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Z�̔�r���@�ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Z�o�b�t�@�ɏ�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�t�H�O�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//�ʒu�̎擾
	//D3DXVECTOR3 Pos = GetPos();

	////�e�N�X�`���̓ǂݍ���
	//CTexture* pTexture = CManager::GetInstance()->GetTexture();

	//D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	//LPDIRECT3DDEVICE9 pDevice;

	////�f�o�C�X�̎擾
	//pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	////���[���h�̏�����
	//D3DXMatrixIdentity(&GetMtx());

	////�N�H�[�^�j�I���̏�����
	//m_quat = { 0.0f, 0.0f, 0.0f, 1.0f };

	//D3DXQuaternionRotationAxis(&m_quat, &m_vecAxis, m_fValueRor);   // �N�H�[�^�j�I���쐬
	//D3DXMatrixRotationQuaternion(&m_mtxRot, &m_quat);

	////�����𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_polygon.rot.y, m_polygon.rot.x, m_polygon.rot.z);

	//D3DXMatrixMultiply(&GetMtx(), &GetMtx(), &mtxRot);

	////�ʒu�𔽉f
	//D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);

	//D3DXMatrixMultiply(&GetMtx(), &GetMtx(), &mtxTrans);

	////���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &GetMtx());

	////���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	////���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_3D);

	////�e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist(texturepath)));

	////�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	////�ʒu�̐ݒ�
	//SetPos(Pos);
}

//============================
//�N���G�C�g
//============================
CShadow* CShadow::Create(D3DXVECTOR3* pos, float radius)
{
	//��ނɉ����ē��I�m��
	CShadow* pShadow = nullptr;

	//�N���G�C�g�̏���
	pShadow = new CShadow;

	//������
	pShadow->Init();

	pShadow->SetSize(D3DXVECTOR3(radius * 2.0f, 0.0f, radius * 2.0f), CObject3D::TYPE_FLOOR);	//�T�C�Y
	pShadow->SetRate(1.0f);												//�T�C�Y�{��
	pShadow->SetPos(D3DXVECTOR3(pos->x, 1.0f, pos->z));					//�ʒu
	pShadow->m_TargetPos = pos;											//�Ώۂ̈ʒu
	pShadow->SetColor(COLOR);											//�F�̐ݒ�

	//�ݒ肵������Ԃ�
	return pShadow;
}