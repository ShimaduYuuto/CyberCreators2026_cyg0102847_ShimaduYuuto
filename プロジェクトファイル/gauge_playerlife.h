//================================
//
//gauge_playerlife.cpp�ɕK�v�Ȑ錾[gauge_playerlife.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GAUGE_PLAYERLIFE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _GAUGE_PLAYERLIFE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "gauge.h"

//�v���C���[���C�t�Q�[�W�N���X
class CGauge_PlayerLife : public CObject2D
{
public:

	//�萔
	static const D3DXVECTOR3 POS;	//�ʒu
	static const D3DXVECTOR3 SIZE;	//�T�C�Y

	//�����o�֐�
	CGauge_PlayerLife(int nPriority = 3);	//�R���X�g���N�^
	~CGauge_PlayerLife() override;			//�f�X�g���N�^
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
	static CGauge_PlayerLife* Create(float max);	//�Q�[�W�̐���

	//�Q�[�W�̎擾
	CGauge* GetGauge() { return m_pGauge; }

private:

	//�����o�֐�
	void SetGauge(float max);	//�Q�[�W�̐ݒ�

	CGauge* m_pGauge;	//�Q�[�W�̃|�C���^
};

#endif