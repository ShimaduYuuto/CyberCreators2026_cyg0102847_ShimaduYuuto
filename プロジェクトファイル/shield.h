//================================
//
//shield.cpp�ɕK�v�Ȑ錾[shield.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SHIELD_H_ //���̃}�N����`������Ă��Ȃ�������
#define _SHIELD_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "modelparts.h"

//�V�[���h�N���X
class CShield : public CModelparts
{
public:

	//�����o�֐�
	CShield(int nPriority = 3);														//�R���X�g���N�^
	~CShield() override;															//�f�X�g���N�^
	HRESULT Init() override;														//������
	void Uninit() override;															//�I��
	void Update() override;															//�X�V
	void Draw() override;															//�`��
	static CShield* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						//���̐���

private:
};

#endif