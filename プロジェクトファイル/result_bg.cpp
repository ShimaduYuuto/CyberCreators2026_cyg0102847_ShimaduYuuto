//======================================
//
//	�w�i�̏���[result_bg.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "result_bg.h"

//�萔
const std::string CResult_Bg::TEXTURE_PATH = "data\\TEXTURE\\result001.png";

//============================
//�w�i�̃R���X�g���N�^
//============================
CResult_Bg::CResult_Bg(int nPriority) : CObject2D(nPriority)
{

}

//============================
//�w�i�̃f�X�g���N�^
//============================
CResult_Bg::~CResult_Bg()
{

}

//============================
//�w�i�̏�����
//============================
HRESULT CResult_Bg::Init()
{
	//������
	CObject2D::Init();

	return S_OK;
}

//============================
//�w�i�̏I������
//============================
void CResult_Bg::Uninit()
{
	CObject2D::Uninit();
}

//============================
//�w�i�̍X�V
//============================
void CResult_Bg::Update()
{
	CObject2D::Update();
}

//============================
//�w�i�̕`��
//============================
void CResult_Bg::Draw()
{
	//�`�揈��
	CObject2D::Draw(TEXTURE_PATH.c_str());
}

//============================
//�w�i�̃N���G�C�g
//============================
CResult_Bg* CResult_Bg::Create()
{
	//�|�C���^�p�̕ϐ�
	CResult_Bg* pResult_Bg;

	//�������̊m��
	pResult_Bg = new CResult_Bg;

	//������
	pResult_Bg->Init();
	pResult_Bg->SetPos({640.0f, 360.0f, 0.0f});	//�ʒu
	pResult_Bg->SetSize({ WIDTH, HEIGHT, 0.0f });	//�T�C�Y

	return pResult_Bg;
}