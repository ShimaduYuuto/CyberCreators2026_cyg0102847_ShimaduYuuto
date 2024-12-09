//================================
//
//collision_view.cpp�ɕK�v�Ȑ錾[collision_view.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _COLLISION_VIEW_H_ //���̃}�N����`������Ă��Ȃ�������
#define _COLLISION_VIEW_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "objectbillboard.h"

//�R���W�����r���[�N���X
class CCollision_View  : public CObjectBillboard
{
public:
	//�����o�֐�
	CCollision_View();				//�R���X�g���N�^
	~CCollision_View()  override;	//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I������
	void Update() override;			//�X�V����
	void Draw() override;			//�`�揈��

	//����
	static CCollision_View* Create(float radius, D3DXVECTOR3* pos);	//�R���W�����r���[�̐���

private:
	float m_fRadius;			//���a
	D3DXVECTOR3* m_Pos;			//�ʒu
};

#endif