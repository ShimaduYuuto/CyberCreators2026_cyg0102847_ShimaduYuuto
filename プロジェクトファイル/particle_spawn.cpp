//======================================
//
//	�p�[�e�B�N���G�f�B�^�[�̕`��[particle_spawn.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "particle_spawn.h"
#include "particle.h"
#include "manager.h"

//============================
//�R���X�g���N�^
//============================
CParticle_Spawn::CParticle_Spawn() :
	m_Info(),
	m_nCount(0)
{
	//�ǂݍ���
	Load();
}

//============================
//�f�X�g���N�^
//============================
CParticle_Spawn::~CParticle_Spawn()
{
	
}

//============================
//�X�V����
//============================
void CParticle_Spawn::Update()
{
	//���Ԋu���ƂɃp�[�e�B�N���𐶐�
	m_nCount++;

	if (m_nCount >= m_Info.nCreateInterval)
	{
		CParticle* pParticle = CParticle::Create(m_Pos);
		pParticle->SetMaxLife(m_Info.nParticleLife);
		pParticle->SetNormalSize(m_Info.fParticleSize);
		pParticle->SetAttenuationValue(m_Info.fAttenuationValue);
		pParticle->SetColor(m_Info.Color);

		std::random_device rd;          // �V�[�h������
		std::mt19937 gen(rd());         // �����Z���k�E�c�C�X�^�����G���W��

		// �����^�̈�l���z���w��
		std::uniform_int_distribution<> dist(-314, 314); // -314�`314�͈̔�
		float fRandom = dist(gen) * 0.01f;

		pParticle->SetMove({ sinf(fRandom) * m_Info.fMoveValue, 0.0f, cosf(fRandom) * m_Info.fMoveValue });

		m_nCount = 0;
	}
}

//============================
//�ǂݍ��ݏ���
//============================
void CParticle_Spawn::Load()
{
	//���[�J���ϐ��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen("data\\FILE\\Particle000.bin", "rb");

	//�t�@�C���ɏ��������o��
	if (pFile != NULL)
	{
		//�f�[�^�̋L�^
		fread(&m_Info, sizeof(ParticleInfo), 1, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
}

//============================
//�p�[�e�B�N���̃N���G�C�g
//============================
CParticle_Spawn* CParticle_Spawn::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CParticle_Spawn* pObject;

	//�������̊m��
	pObject = new CParticle_Spawn;

	//�p�����[�^�̐ݒ�
	pObject->m_Pos = pos;	//�ʒu�̐ݒ�

	return pObject;
}