//================================
//
//model.cpp�ɕK�v�Ȑ錾[model.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _MODEL_H_ //���̃}�N����`������Ă��Ȃ�������
#define _MODEL_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectX.h"

//���f���N���X
class CModel : public CObjectX
{
public:

	//���f���̎��
	typedef enum
	{
		MODEL_TYPE_NONE = 0,
		MODEL_TYPE_TREE,
		MODEL_TYPE_FENCE,
		MODEL_TYPE_MAX
	}MODEL_TYPE;

	//�����o�֐�
	CModel(int nPriority = 3) {};												//�R���X�g���N�^
	~CModel() override {};														//�f�X�g���N�^
	static CModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL_TYPE type);	//���f���̐���
};

#endif