//======================================
//
//	�ǂ̏���[collision_wall.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "collision_wall.h"
#include "manager.h"
#include "game.h"

//�萔�̏�����
const std::string CCollision_Wall::FILEPATH = "data\\TEXTURE\\SmashMesh000.png";//�e�N�X�`���p�X
const int CCollision_Wall::NUM_CORNER = 20;										//�p�̐�
const float CCollision_Wall::HEIGHT = 50.0f;									//����

//============================
//�R���X�g���N�^
//============================
CCollision_Wall::CCollision_Wall(int nPriority) : CObjectCylinder(nPriority), m_bEnd(false), m_fAlpha(0.0f)
{

}

//============================
//�f�X�g���N�^
//============================
CCollision_Wall::~CCollision_Wall()
{

}

//============================
//������
//============================
HRESULT CCollision_Wall::Init()
{
	//���̏�����
	CObjectCylinder::Init();
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	//���_�𓧖���

	return S_OK;
}

//============================
//�I������
//============================
void CCollision_Wall::Uninit()
{
	//�����̊J��
	CObjectCylinder::Uninit();
}

//============================
//�X�V
//============================
void CCollision_Wall::Update()
{
	//�����x�����X�ɕs�����ɂ��鏈��
	if (m_fAlpha < 1.0f && !m_bEnd)
	{
		m_fAlpha += ADD_ALPHA;	//���Z

		if (m_fAlpha > 1.0f)	//�␳
		{
			m_fAlpha = 1.0f;
		}

		//���_�̐F��ݒ�
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));
	}
	else if (m_bEnd)
	{
		m_fAlpha -= ADD_ALPHA;	//���Z

		if (m_fAlpha <= 0.0f)	//�␳
		{
			m_fAlpha = 0.0f;
			Uninit();
			return;
		}

		//���_�̐F��ݒ�
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));
	}

	//�X�V
	CObjectCylinder::Update();
}

//============================
//�`��
//============================
void CCollision_Wall::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���C�g���I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�J�����O���@��ύX
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//�`�揈��
	CObjectCylinder::Draw(FILEPATH.c_str());

	//�J�����O���@��ύX
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//���C�g���I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//================================
//�N���G�C�g
//================================
CCollision_Wall* CCollision_Wall::Create(D3DXVECTOR3 pos, float radius)
{
	//�|�C���^�p�̕ϐ�
	CCollision_Wall* pObject;

	//�������̊m��
	pObject = new CCollision_Wall;

	//�p�����[�^�̐ݒ�
	pObject->SetPos(pos);			//�ʒu�̐ݒ�
	pObject->SetRadius(radius);	//���a�̐ݒ�

	//������
	pObject->Init();

	return pObject;
}

//================================
//�ǂ̓����蔻�茋�ʂ�Ԃ�
//================================
bool CCollision_Wall::GetHit(D3DXVECTOR3& pos, float radius)
{
	//�Ԃ�l�p�̕ϐ�
	bool bHit = false;

	//�v�Z�p�̕ϐ���錾
	D3DXVECTOR3 WallPos = GetPos();		//�ǂ̈ʒu
	float fWallRadius = GetRadius();	//�ǂ̔��a
	D3DXVECTOR3 TargetPos = pos;		//�^�[�Q�b�g�ʒu
	float fTargetRadius = radius;		//�^�[�Q�b�g���a

	//���S�_����̋������Z�o
	D3DXVECTOR3 Vec3Length = WallPos - TargetPos;	//�ʒu
	float fLength = sqrtf(Vec3Length.x * Vec3Length.x + Vec3Length.z * Vec3Length.z);	//�������Z�o
	float fAngle = atan2f(Vec3Length.x, Vec3Length.z);									//�p�x���Z�o

	//�ǂ��O���ɂ��邩�𔻒�
	if (fWallRadius <= fLength + radius)
	{
		//�~�̓����ɕ␳
		pos.x = sinf(fAngle + D3DX_PI) * (fWallRadius - radius) + WallPos.x;
		pos.z = cosf(fAngle + D3DX_PI) * (fWallRadius - radius) + WallPos.z;

		//�q�b�g����
		bHit = true;
	}

	//�����Ԃ�
	return bHit;
}