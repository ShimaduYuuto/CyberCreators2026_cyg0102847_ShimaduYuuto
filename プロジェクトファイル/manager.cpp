//======================================
//
//	�}�l�[�W���[�̏���[manager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "manager.h"
#include "object.h"
#include "renderer.h"

//============================
//�}�l�[�W���[�̃R���X�g���N�^
//============================
CManager::CManager() :
	m_pCamera(nullptr),
	m_pFade(nullptr),
	m_pJoypad(nullptr),
	m_pKeyboard(nullptr),
	m_pLight(nullptr),
	m_pMouse(nullptr),
	m_pRenderer(nullptr),
	m_pScene(nullptr),
	m_pSound(nullptr),
	m_pTexture(nullptr),
	m_pXfile(nullptr)
{
	
}

//============================
//�}�l�[�W���[�̃f�X�g���N�^
//============================
CManager::~CManager()
{

}

//============================
//�}�l�[�W���[�̏���������
//============================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[�̐���
	m_pRenderer = new CRenderer();		//����
	m_pRenderer->Init(hWnd, bWindow);	//������

	//�L�[�{�[�h�f�o�C�X�̐���
	m_pKeyboard = new CInputKeyboard();				//����
	if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))	//������
	{
		return E_FAIL;
	}

	//�}�E�X�f�o�C�X�̐���
	m_pMouse = new CInputMouse();					//����
	if (FAILED(m_pMouse->Init(hInstance, hWnd)))	//������
	{
		return E_FAIL;
	}

	//�W���C�p�b�h�̐���
	m_pJoypad = new CInputJoypad();
	//�W���C�p�b�h�̏���������
	if (FAILED(m_pJoypad->Init()))
	{
		return E_FAIL;
	}

	//�T�E���h�̐���
	m_pSound = new CSound();
	m_pSound->Init(hWnd);

	//�J�����̐���
	m_pCamera = new CCamera();	//�������m��
	m_pCamera->Init();			//������

	//���C�g�̐���
	m_pLight = new CLight();	//�������m��
	m_pLight->Init();			//������

	//�t�F�[�h�̐���
	m_pFade = new CFade();		//�������m��
	m_pFade->Init();			//�����ݒ�

	//�e�N�X�`���Ǘ��N���X�̐���
	m_pTexture = new CTexture();	//�������m��

	//X�t�@�C���̊Ǘ�
	m_pXfile = new CXfile();		//�������̊m��

	return S_OK;
}

//============================
//�}�l�[�W���[�̏I������
//============================
void CManager::Uninit()
{
	//�t�F�[�h�̃C���X�^���X���g�p���Ȃ�
	if (m_pFade != nullptr)
	{
		//�I��������ɊJ��
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	//�S�I�u�W�F�N�g�̊J��
	CObject::ReleaseAll();

	//�V�[���̃C���X�^���X���g�p���Ȃ�
	if (m_pScene != nullptr)
	{
		//�I��������ɊJ��
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//�e�N�X�`���̃C���X�^���X���g�p���Ȃ�
	if (m_pTexture != nullptr)
	{
		//�I��������ɊJ��
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//X�t�@�C���̃C���X�^���X���g�p���Ȃ�
	if (m_pXfile != nullptr)
	{
		//�I��������ɊJ��
		m_pXfile->Unload();
		delete m_pXfile;
		m_pXfile = nullptr;
	}

	//�����_���[�̃C���X�^���X���g�p���Ȃ�
	if (m_pRenderer != nullptr)
	{
		//�I��������ɊJ��
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//�L�[�{�[�h�̃C���X�^���X���g�p���Ȃ�
	if (m_pKeyboard != nullptr)
	{
		//�I��������ɊJ��
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	//�}�E�X�̃C���X�^���X���g�p���Ȃ�
	if (m_pMouse != nullptr)
	{
		//�I��������ɊJ��
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	//�W���C�p�b�h�̃C���X�^���X���g�p���Ȃ�
	if (m_pJoypad != nullptr)
	{
		//�I��������ɊJ��
		m_pJoypad->Uninit();
		delete m_pJoypad;
		m_pJoypad = nullptr;
	}

	//�T�E���h�̃C���X�^���X���g�p���Ȃ�
	if (m_pSound != nullptr)
	{
		//�I��������ɊJ��
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	//�J�����̃C���X�^���X���g�p���Ȃ�
	if (m_pCamera != nullptr)
	{
		//�I��������ɊJ��
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	//���C�g�̃C���X�^���X���g�p���Ȃ�
	if (m_pLight != nullptr)
	{
		//�I��������ɊJ��
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
}

//============================
//�}�l�[�W���[�̍X�V����
//============================
void CManager::Update()
{
	//�����_���[�̍X�V����
	m_pRenderer->Update();

	//�L�[�{�[�h�̍X�V����
	m_pKeyboard->Update();

	//�W���C�p�b�h�̍X�V����
	m_pJoypad->Update();

	//�}�E�X�̍X�V����
	m_pMouse->Update();

	//�V�[���̍X�V����
	m_pScene->Update();

	//�J�����̍X�V����
	m_pCamera->Update();

	//�t�F�[�h�̍X�V����
	m_pFade->Update();
}

//============================
//�}�l�[�W���[�̕`�揈��
//============================
void CManager::Draw()
{
	//�����_���[�̕`�揈��
	m_pRenderer->Draw();
}

//============================
//�����_���[�̎擾
//============================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

//============================
//�T�E���h�̎擾
//============================
CSound* CManager::GetSound()
{
	return m_pSound;
}

//============================
//�L�[�{�[�h�̎擾
//============================
CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//============================
//�W���C�p�b�h�̎擾
//============================
CInputJoypad* CManager::GetJoypad()
{
	return m_pJoypad;
}

//============================
//�W���C�p�b�h�̎擾
//============================
CInputMouse* CManager::GetMouse()
{
	return m_pMouse;
}

//============================
//�J�����̎擾
//============================
CCamera* CManager::GetCamera()
{
	//�r���[����Ԃ�
	return m_pCamera;
}

//============================
//���C�g�̎擾
//============================
CLight* CManager::GetLight()
{
	//���C�g�̏���Ԃ�
	return m_pLight;
}

//============================
//�e�N�X�`���̎擾
//============================
CTexture* CManager::GetTexture()
{
	//�e�N�X�`���̏���Ԃ�
	return m_pTexture;
}

//============================
//X�t�@�C���̎擾
//============================
CXfile* CManager::GetXfile()
{
	//X�t�@�C���̏���Ԃ�
	return m_pXfile;
}

//============================
//�t�F�[�h�̎擾
//============================
CFade* CManager::GetFade()
{
	//�t�F�[�h�̏���Ԃ�
	return m_pFade;
}

//============================
//�V�[���̎擾
//============================
CScene* CManager::GetScene()
{
	//�V�[���̏���Ԃ�
	return m_pScene;
}

//============================
//�V�[���̐ݒ�
//============================
void CManager::SetScene(CScene::MODE mode)
{

	//���݂̃V�[���̏I������
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//���̃V�[������
	m_pScene = CScene::Create(mode);
}

//============================
//�f�o�b�O�v���b�N�̐ݒ�
//============================
void CManager::SetFPS(int fps)
{
	//m_nFPSCount = fps;
}