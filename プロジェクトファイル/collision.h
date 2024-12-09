//================================
//
//collision.cpp�ɕK�v�Ȑ錾[collision.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _COLLISION_H_ //���̃}�N����`������Ă��Ȃ�������
#define _COLLISION_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "collision_view.h"

//�R���W�����N���X
class CCollision
{
public:

	//�����o�֐�
	CCollision();	//�R���X�g���N�^
	~CCollision();	//�f�X�g���N�^
	HRESULT Init();	//������
	void Uninit();	//�I������
	void Update(D3DXVECTOR3 offsetpos);	//�X�V����

	//����
	static CCollision* Create(float radius, D3DXVECTOR3 collisionpos);	//�R���W�����̐���

	//�����蔻��̃��[�J���ʒu
	void SetCollisionPos(D3DXVECTOR3 pos) { m_CollisionPos = pos; }	//�ݒ�
	D3DXVECTOR3& GetCollisionPos() { return m_CollisionPos; }		//�擾

	//�����蔻��̃��[���h�ʒu
	D3DXVECTOR3& GetPos() { return m_Pos; }					//�擾

	//�����蔻��̔��a
	void SetRadius(float radius) { m_fRadius = radius; }	//�ݒ�
	float GetRadius() { return m_fRadius; }					//�擾

private:
	float m_fRadius;			//���a
	D3DXVECTOR3 m_Pos;			//���[���h�ʒu
	D3DXVECTOR3 m_CollisionPos;	//���[�J���ʒu

	//�f�o�b�O�p
	CCollision_View* m_pCollisionView;	//�����蔻��̉���
};

#endif