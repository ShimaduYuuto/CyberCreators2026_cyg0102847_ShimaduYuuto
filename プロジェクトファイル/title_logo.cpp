//======================================
//
//	���S�̏���[title_logo.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "title_logo.h"

//�萔
const std::string CTitle_Logo::TEXTURE_PATH = "data\\TEXTURE\\title001.png";

//============================
//���S�̃R���X�g���N�^
//============================
CTitle_Logo::CTitle_Logo(int nPriority) : CObject2D(nPriority)
{

}

//============================
//���S�̃f�X�g���N�^
//============================
CTitle_Logo::~CTitle_Logo()
{

}

//============================
//���S�̏�����
//============================
HRESULT CTitle_Logo::Init()
{
	//������
	CObject2D::Init();

	return S_OK;
}

//============================
//���S�̏I������
//============================
void CTitle_Logo::Uninit()
{
	CObject2D::Uninit();
}

//============================
//���S�̍X�V
//============================
void CTitle_Logo::Update()
{
	CObject2D::Update();
}

//============================
//���S�̕`��
//============================
void CTitle_Logo::Draw()
{
	//�`�揈��
	CObject2D::Draw(TEXTURE_PATH.c_str());
}

//============================
//���S�̃N���G�C�g
//============================
CTitle_Logo* CTitle_Logo::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CTitle_Logo* pTitle_Logo;

	//�������̊m��
	pTitle_Logo = new CTitle_Logo;

	//������
	pTitle_Logo->Init();
	pTitle_Logo->SetPos(pos);	//�ʒu
	pTitle_Logo->SetSize({WIDTH, HEIGHT, 0.0f});	//�T�C�Y

	return pTitle_Logo;
}