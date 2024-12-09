//================================
//
//impactrange.cpp�ɕK�v�Ȑ錾[impactrange.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _IMPACTRANGE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _IMPACTRANGE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object3D.h"
#include "impactmesh.h"

//�C���p�N�g�͈̔̓N���X
class CImpactRange : public CObject3D
{
public:

	//�萔
	static const float MAX_SIZERATE;		//�T�C�Y�{���̍ő�
	
	//�����o�֐�
	CImpactRange(int nPriority = 3);				//�R���X�g���N�^
	~CImpactRange() override;						//�f�X�g���N�^
	HRESULT Init() override;						//������
	void Uninit() override;							//�I��
	void Update() override;							//�X�V
	void Draw() override;							//�`��
	void Draw(const char* texturepath);				//�����̃e�N�X�`���ŕ`��
	static CImpactRange* Create(D3DXVECTOR3 pos);	//�Ռ��͈̔͂̐���

private:
	CImpactMesh* m_pImpactMesh;	//�C���p�N�g���b�V���̃|�C���^
};

#endif