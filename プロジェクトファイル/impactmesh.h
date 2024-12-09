//================================
//
//objectmesh.cpp�ɕK�v�Ȑ錾[objectmesh.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _IMPACTMASH_H_ //���̃}�N����`������Ă��Ȃ�������
#define _IMPACTMASH_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectcylinder.h"

//�C���p�N�g���b�V���N���X
class CImpactMesh : public CObjectCylinder
{
public:

	//�萔�̐錾
	static const std::string FILEPATH;	//�ǂݍ��ރt�@�C��
	static const int NUM_CORNER;		//�~���̐�
	static const float HEIGHT;			//����

	//�����o�֐�
	CImpactMesh(int nPriority = 3);		//�R���X�g���N�^
	~CImpactMesh() override;			//�f�X�g���N�^
	HRESULT Init() override;			//������
	void Uninit() override;				//�I��
	void Update() override;				//�X�V
	void Draw() override;				//�`��

	//����
	static CImpactMesh* Create(D3DXVECTOR3 pos, float radius);	
};

#endif