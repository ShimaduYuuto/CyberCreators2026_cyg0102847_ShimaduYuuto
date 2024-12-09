//======================================
//
//	��̏���[sky.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "sky.h"
#include "game.h"
#include "manager.h"

//�萔
const std::string CSky::FILEPATH = "data\\TEXTURE\\sky001.jpg";

//============================
//�R���X�g���N�^
//============================
CSky::CSky(int nPriority) : CObjectDome(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CSky::~CSky()
{

}

//============================
//������
//============================
HRESULT CSky::Init()
{
	//������
	CObjectDome::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CSky::Uninit()
{
	//�I������
	CObjectDome::Uninit();
}

//============================
//�X�V
//============================
void CSky::Update()
{
	CObjectDome::Update();
}

//============================
//�`��
//============================
void CSky::Draw()
{
	//�f�o�C�X�̎擾
	 LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�I�u�W�F�N�g�̕`��
	CObjectDome::Draw(FILEPATH.c_str());

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================
//�N���G�C�g
//============================
CSky* CSky::Create()
{
	//��ނɉ����ē��I�m��
	CSky* pSky = nullptr;

	//�N���G�C�g�̏���
	pSky = new CSky;

	pSky->SetRadius(100.0f);	//���a
	pSky->SetRate(50.0f);
	pSky->SetPos(D3DXVECTOR3(0.0f, -100.0f, 0.0f));

	//������
	pSky->Init();

	//�ݒ肵������Ԃ�
	return pSky;
}