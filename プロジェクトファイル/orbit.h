//================================
//
//orbit.cpp�ɕK�v�Ȑ錾[orbit.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ORBIT_H_ //���̃}�N����`������Ă��Ȃ�������
#define _ORBIT_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectmesh.h"

//�O�ՃN���X
class COrbit : public CObjectMesh
{
public:

	//�萔�̐錾
	static const std::string FILEPATH;			//�ǂݍ��ރt�@�C��
	static const D3DXVECTOR3 BLOCK;				//�u���b�N��
	static const D3DXVECTOR3 SIZE;				//�T�C�Y
	static const int NUM_ORBIT = 6;			//�O�Ղ̐�
	static const int NUM_VTX = NUM_ORBIT * 2;	//���_�̐�

	//�����o�֐�
	COrbit(int nPriority = 4);	//�R���X�g���N�^
	~COrbit() override;			//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��

	//�O�Ղ̐ݒ�
	void SetOrbit(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);	//�O�Ղ̈ʒu��ݒ�(���_, �I�t�Z�b�g)

	static COrbit* Create();	//����

private:
	//�����o�ϐ�
	VERTEX_3D m_SaveVtx[NUM_VTX];	//���_����ۑ�����ϐ�[���_��]
	bool m_bFirstSet;				//���߂Ă̐ݒ�
};

#endif