//================================
//
//manager.cpp�ɕK�v�Ȑ錾[manager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _MANAGER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _MANAGER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "xfile.h"
#include "fade.h"
#include "scene.h"
#include "time.h"
#include "debugproc.h"

//�}�l�[�W���[�N���X
class CManager
{

private:

	//�����o�֐�
	CManager();								//�R���X�g���N�^

public:

	//�����o�֐�
	~CManager();							//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		//������
	void Uninit();							//�I������
	void Update();							//�X�V����
	void Draw();							//�`�揈��

	//�C���X�^���X�̐���
	static CManager* GetInstance()
	{
		static CManager instance;	//�ÓI�C���X�^���X
		return &instance;
	}

	CRenderer* GetRenderer();		//�����_���[�̎擾
	CSound* GetSound();				//�V�[���̎擾
	CInputKeyboard* GetKeyboard();	//�L�[�{�[�h�̎擾
	CInputJoypad* GetJoypad();		//�W���C�p�b�h�̎擾
	CInputMouse* GetMouse();		//�}�E�X�̎擾
	CCamera* GetCamera();			//�r���[���̎擾
	CLight* GetLight();				//���C�g�̏��
	CTexture* GetTexture();			//�e�N�X�`���̏��
	CXfile* GetXfile();				//X�t�@�C���̎擾
	CFade* GetFade();				//�t�F�[�h�̎擾
	CScene* GetScene();				//�V�[���̎擾
	void SetScene(CScene::MODE mode);//�V�[���̐ݒ�

	//FPS�̐ݒ�Ǝ擾
	void SetFPS(int fps);			//�ݒ�

private:

	//�����o�ϐ�
	CRenderer* m_pRenderer;				//�����_���[�̃C���X�^���X
	CInputKeyboard* m_pKeyboard;		//�L�[�{�[�h�̃C���X�^���X
	CInputJoypad* m_pJoypad;			//�W���C�p�b�h�̃C���X�^���X
	CInputMouse* m_pMouse;				//�}�E�X�̃C���X�^���X
	CSound* m_pSound;					//�T�E���h�̃C���X�^���X
	CCamera* m_pCamera;					//�r���[���̃C���X�^���X
	CLight* m_pLight;					//���C�g���̃C���X�^���X
	CTexture* m_pTexture;				//�e�N�X�`���̃C���X�^���X
	CXfile* m_pXfile;					//X�t�@�C���̃C���X�^���X
	CFade* m_pFade;						//�t�F�[�h�̃C���X�^���X
	CScene* m_pScene;					//�V�[���̃C���X�^���X
};

#endif