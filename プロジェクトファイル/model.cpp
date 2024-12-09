//======================================
//
//	���f���̏���[model.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "model.h"
#include "tree.h"
#include "fence.h"

//============================
//���f���̃N���G�C�g
//============================
CModel* CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL_TYPE type)
{
	//��ނɉ����ē��I�m��
	CModel* pModel = nullptr;

	//�����̃I�u�W�F�N�g�𐶐�
	switch (type)
	{
	case MODEL_TYPE::MODEL_TYPE_TREE:
		pModel = new CTree;
		break;

	case MODEL_TYPE::MODEL_TYPE_FENCE:
		pModel = new CFence;
		break;

	default:
		assert(true);
		break;
	}

	//������
	pModel->Init();

	//�p�����[�^�̐ݒ�
	pModel->SetPos(pos);					//�ʒu
	pModel->SetRot(rot);					//����

	//�ݒ肵������Ԃ�
	return pModel;
}