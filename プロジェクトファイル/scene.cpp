//======================================
//
//	�V�[���̏���[scene.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "scene.h"
#include "object.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "manager.h"

//�ÓI�����o�̏�����
CScene::MODE CScene::m_Mode = CScene::MODE_TITLE;	//�^�C�g���ɏ�����

//============================
//�V�[���̃R���X�g���N�^
//============================
CScene::CScene()
{
	
}

//============================
//�V�[���̃f�X�g���N�^
//============================
CScene::~CScene()
{

}

//============================
//�V�[���̏�����
//============================
HRESULT CScene::Init()
{
	
	return S_OK;
}

//============================
//�V�[���̏I������
//============================
void CScene::Uninit()
{
	//�S�I�u�W�F�N�g�̊J��
	CObject::ReleaseAll();

	//�T�E���h�̒�~
	CManager::GetInstance()->GetSound()->Stop();
}

//============================
//�V�[���̍X�V����
//============================
void CScene::Update()
{
	
}

//============================
//�V�[���̕`�揈��
//============================
void CScene::Draw()
{
	
}

//============================
//�ǂݍ���
//============================
void CScene::Load()
{

}

//============================
//�V�[���̐���
//============================
CScene* CScene::Create(CScene::MODE mode)
{
	//�����p�̕ϐ�
	CScene* pScene = nullptr;

	//���[�h�̑��
	m_Mode = mode;

	//�����ɉ����ē��I�m��
	switch (mode)
	{
	case CScene::MODE_TITLE:	//�^�C�g��
		pScene = new CTitle();
		break;

	case CScene::MODE_GAME:		//�Q�[��
		pScene = new CGame();
		break;

	case CScene::MODE_RESULT:	//���U���g
		pScene = new CResult();
		break;
	}

	//���������m�ۂ��Ă�����
	if (pScene != nullptr)
	{
		//������
		//pScene->Init();
		pScene->Load();

		return pScene;
	}

	return nullptr;

}