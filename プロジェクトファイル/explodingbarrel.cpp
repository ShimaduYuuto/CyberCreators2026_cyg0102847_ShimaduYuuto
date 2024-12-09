//======================================
//
//	�����M�̏���[explodingbarrel.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "explodingbarrel.h"
#include "explosion.h"
#include "manager.h"

//�萔
const std::string CExplodingBarrel::FILEPATH = "data\\MODEL\\ExplodingBarrel000.x";

//============================
//�R���X�g���N�^
//============================
CExplodingBarrel::CExplodingBarrel(int nPriority) : CGimmick(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CExplodingBarrel::~CExplodingBarrel()
{
	
}

//============================
//������
//============================
HRESULT CExplodingBarrel::Init()
{
	//������
	CGimmick::Init();

	GetCollision()->SetRadius(40.0f);

	return S_OK;
}

//============================
//�I������
//============================
void CExplodingBarrel::Uninit()
{
	//�J������h�炷
	CManager::GetInstance()->GetCamera()->SetShake(30, 20);	//�q�b�g���J������h�炷

	//�����̐���
	CExplosion::Create(GetPos());

	//�I������
	CGimmick::Uninit();
}

//============================
//�X�V
//============================
void CExplodingBarrel::Update()
{
	//����ł����甲����
	if (CObject::GetDeath())
	{
		return;
	}

	//�Q�[���I�u�W�F�N�g�̋��ʏ����X�V
	CGimmick::Update();
}

//============================
//�`��
//============================
void CExplodingBarrel::Draw()
{
	//�I�u�W�F�N�g�̕`��
	CObjectX::Draw(FILEPATH.c_str());
}

//============================
//�N���G�C�g
//============================
CExplodingBarrel* CExplodingBarrel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//��ނɉ����ē��I�m��
	CExplodingBarrel* pExplodingBarrel = NULL;

	//�N���G�C�g�̏���
	pExplodingBarrel = new CExplodingBarrel;

	//������
	pExplodingBarrel->Init();

	//�p�����[�^�̐ݒ�
	pExplodingBarrel->SetPos(pos);		//�ʒu
	pExplodingBarrel->SetRot(rot);		//����

	//�ݒ肵������Ԃ�
	return pExplodingBarrel;
}