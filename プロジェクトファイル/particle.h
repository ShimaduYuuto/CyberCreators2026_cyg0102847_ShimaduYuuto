//================================
//
//particle.cpp�ɕK�v�Ȑ錾[particle.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PARTICLE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _PARTICLE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectbillboard.h"

//�p�[�e�B�N���N���X
class CParticle : public CObjectBillboard
{
public:

	//�萔
	static constexpr int MAX_LIFE = 30;	//�̗͂̍ő�l

	//�����o�֐�
	CParticle(int nPriority = 3);						//�R���X�g���N�^
	~CParticle() override;								//�f�X�g���N�^
	HRESULT Init() override;							//������
	void Uninit() override;								//�I��
	void Update() override;								//�X�V
	void Draw() override;								//�`��
	static CParticle* Create(D3DXVECTOR3 pos);			//Particle�̐���

	//����
	void SetMaxLife(int life) { m_nMaxLife = life; m_nLife = life; }	//�ݒ�
	int GetMaxLife() { return m_nMaxLife; }			//�擾

	//�ʏ�T�C�Y
	void SetNormalSize(float size) { m_fNormalSize = size; }	//�ݒ�

	//������
	void SetAttenuationValue(float value) { m_fAttenuationValue = value; }	//�ݒ�
	float GetAttenuationValue() { return m_fAttenuationValue; }				//�擾
	
private:
	int m_nLife;				//����
	int m_nMaxLife;				//�����̍ő�
	float m_fNormalSize;		//�ʏ�̃T�C�Y
	float m_fAttenuationValue;	//������
};

#endif