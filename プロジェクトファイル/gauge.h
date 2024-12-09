//================================
//
//gauge.cpp�ɕK�v�Ȑ錾[gauge.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GAUGE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _GAUGE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"

//�Q�[�W�N���X
class CGauge : public CObject2D
{
public:
	//�����o�֐�
	CGauge(int nPriority = 3);	//�R���X�g���N�^
	~CGauge() override;			//�f�X�g���N�^
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
	static CGauge* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float max);	//�Q�[�W�̐���

	//�p�����[�^�[�֘A�̊֐�
	void SetMaxGauge(float max) { m_fMaxGauge = max; }		//�Q�[�W�̍ő��ݒ�
	float GetMaxGauge() { return m_fMaxGauge; }				//�Q�[�W�̍ő���擾
	void SetNowGauge(float value);							//�Q�[�W�̐ݒ�
	float GetNowGauge() { return m_fNowGauge; }				//�Q�[�W�̎擾
	void AddGauge(float value);								//�Q�[�W�̉��Z

private:
	float m_fMaxGauge;		//�Q�[�W�̍ő�l
	float m_fNowGauge;		//���݂̃Q�[�W�̒l
};

#endif