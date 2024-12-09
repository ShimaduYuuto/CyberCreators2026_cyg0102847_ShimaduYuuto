//================================
//
//particle_spawn.cpp�ɕK�v�Ȑ錾[particle_spawn.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PARTICLE_SPAWN_H_ //���̃}�N����`������Ă��Ȃ�������
#define _PARTICLE_SPAWN_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//�p�[�e�B�N���G�f�B�^�[�N���X
class CParticle_Spawn
{
public:

	//�p�[�e�B�N�����
	struct ParticleInfo
	{
		int nCreateInterval;	//�����̊Ԋu
		float fMoveValue;		//�ړ���
		float fAttenuationValue;//������
		float fParticleSize;	//�p�[�e�B�N���̃T�C�Y
		D3DXCOLOR Color;		//�p�[�e�B�N���̐F
		int nParticleLife;		//����
	};

	//�֐�
	//�����o�֐�
	CParticle_Spawn();			//�R���X�g���N�^
	~CParticle_Spawn();			//�f�X�g���N�^
	void Update();				//�X�V

	//��������
	static CParticle_Spawn* Create(D3DXVECTOR3 pos); //����

private:
	void Load();	//�ǂݍ��ݏ���

	ParticleInfo m_Info;	//���

	//�p�����[�^�[
	int m_nCount;			//�J�E���g
	D3DXVECTOR3 m_Pos;		//�ʒu
};

#endif