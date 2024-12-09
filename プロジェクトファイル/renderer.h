//================================
//
//renderer.cpp�ɕK�v�Ȑ錾[renderer.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _RENDERER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _RENDERER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//�����_���[�N���X
class CRenderer
{
public:
	CRenderer();								//�R���X�g���N�^
	~CRenderer();								//�f�X�g���N�^
	HRESULT Init(HWND hWnd, BOOL bWindow);		//������
	void Uninit();								//�I��
	void Update();								//�X�V
	void Draw();								//�`��
	LPDIRECT3DDEVICE9 GetDevice();				//�RD�f�o�C�X�̎擾
private:
	LPDIRECT3D9 m_pD3D;							//Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;				//Direct3D�f�o�C�X
};

#endif