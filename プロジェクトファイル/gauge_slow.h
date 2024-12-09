//================================
//
//gauge_slow.cpp�ɕK�v�Ȑ錾[gauge_slow.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GAUGE_SLOW_H_ //���̃}�N����`������Ă��Ȃ�������
#define _GAUGE_SLOW_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "gauge.h"

//2D�I�u�W�F�N�g�N���X
class CGauge_Slow : public CGauge
{
public:

	//�萔
	static const std::string TEXTUREPATH;		//�ǂݍ��ރt�@�C��

	//�����o�֐�
	CGauge_Slow(int nPriority = 3);				//�R���X�g���N�^
	~CGauge_Slow() override;					//�f�X�g���N�^
	HRESULT Init() override;					//������
	void Uninit() override;						//�I��
	void Update() override;						//�X�V
	void Draw() override;						//�`��
	static CGauge_Slow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float max);	//�X���[�Q�[�W�̐���

private:
	D3DXVECTOR3 m_MaxSize;	//�ő�T�C�X
};

#endif