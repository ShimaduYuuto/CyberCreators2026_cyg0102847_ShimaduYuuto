//================================
//
//sky.cpp�ɕK�v�Ȑ錾[sky.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SKY_H_ //���̃}�N����`������Ă��Ȃ�������
#define _SKY_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectdome.h"

//��N���X
class CSky : public CObjectDome
{
public:

	//�萔
	static const std::string FILEPATH;

	//�����o�֐�
	CSky(int nPriority = 3);			//�R���X�g���N�^
	~CSky() override;					//�f�X�g���N�^
	HRESULT Init() override;				//������
	void Uninit() override;					//�I��
	void Update() override;					//�X�V
	void Draw() override;					//�`��
	static CSky* Create();					//��̐���

};

#endif