//================================
//
//light.cpp�ɕK�v�Ȑ錾[light.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _LIGHT_H_ //���̃}�N����`������Ă��Ȃ�������
#define _LIGHT_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//���C�g�N���X
class CLight
{
public:

	//�萔
	static const int MAX_LIGHT = 3;		//���C�g�̍ő吔

	//�����o�֐�
	CLight();							//�R���X�g���N�^
	~CLight();							//�f�X�g���N�^
	HRESULT Init();						//������
	void Uninit();						//�I��
	void Update();						//�X�V
private:

	//�����o�ϐ�
	D3DLIGHT9 m_aLight[MAX_LIGHT];		//���C�g�\����
};

#endif