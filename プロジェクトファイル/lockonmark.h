//================================
//
//lockonmark.cpp�ɕK�v�Ȑ錾[lockonmark.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _LOOKONMARK_H_ //���̃}�N����`������Ă��Ȃ�������
#define _LOOKONMARK_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "objectbillboard.h"

//�R���W�����r���[�N���X
class CLockonMark : public CObjectBillboard
{
public:

	//�萔
	static constexpr float SIZE__MARK{ 10.0f };	//�}�[�N�̃T�C�Y

	//�����o�֐�
	CLockonMark();				//�R���X�g���N�^
	~CLockonMark()  override;	//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I������
	void Update() override;			//�X�V����
	void Draw() override;			//�`�揈��

	//����
	static CLockonMark* Create(float radius, D3DXVECTOR3* pos);	//�R���W�����r���[�̐���

	//���b�N�I���̈ʒu���擾
	D3DXVECTOR3 GetLockonPos() { return *m_Pos; }

private:
	float m_fRadius;			//���a
	D3DXVECTOR3* m_Pos;			//�ʒu
};

#endif