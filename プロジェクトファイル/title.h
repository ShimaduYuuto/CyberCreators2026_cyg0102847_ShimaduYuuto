//================================
//
//title.cpp�ɕK�v�Ȑ錾[title.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TITLE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _TITLE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "scene.h"

//�^�C�g���N���X
class CTitle : public CScene
{
public:

	//�����o�֐�
	CTitle();						//�R���X�g���N�^
	~CTitle() override;				//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��

private:

};

#endif