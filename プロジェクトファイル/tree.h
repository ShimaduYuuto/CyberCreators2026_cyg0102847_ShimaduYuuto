//================================
//
//tree.cpp�ɕK�v�Ȑ錾[tree.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TREE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _TREE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "model.h"

//�c���[�N���X
class CTree : public CModel
{
public:

	//�e�N�X�`���p�X
	static const std::string MODEL_PATH;

	//�`��
	void Draw() override;
};

#endif