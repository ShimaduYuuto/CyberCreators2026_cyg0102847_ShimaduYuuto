//================================
//
//fence.cpp�ɕK�v�Ȑ錾[fence.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _FENCE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _FENCE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "model.h"

//�t�F���X�N���X
class CFence : public CModel
{
public:

	//�e�N�X�`���p�X
	static const std::string MODEL_PATH;

	//�`��
	void Draw() override;
};

#endif