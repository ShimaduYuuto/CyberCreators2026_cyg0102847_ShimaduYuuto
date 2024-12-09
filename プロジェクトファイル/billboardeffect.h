//================================
//
//billboardeffect.cpp�ɕK�v�Ȑ錾[billboardeffect.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BILLBOARDEFFECT_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BILLBOARDEFFECT_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectbillboard.h"
#include "animation.h"

//�r���{�[�h�G�t�F�N�g�N���X
class CBillboardEffect : public CObjectBillboard
{
public:
	//�����o�֐�
	CBillboardEffect();				//�R���X�g���N�^
	~CBillboardEffect()  override;	//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I������
	void Update() override;			//�X�V����
	void Draw() override;			//�`�揈��

	
private:
	CAnimation m_Anim;
};

#endif