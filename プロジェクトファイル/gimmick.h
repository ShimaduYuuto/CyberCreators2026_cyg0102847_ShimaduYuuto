//================================
//
//gimmick.cpp�ɕK�v�Ȑ錾[gimmick.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GIMMICK_H_ //���̃}�N����`������Ă��Ȃ�������
#define _GIMMICK_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectX.h"
#include "collision.h"

//�M�~�b�N�N���X
class CGimmick : public CObjectX
{
public:

	//�萔
	static const std::string FILEPATH;

	//�����o�֐�
	CGimmick(int nPriority = 3);	//�R���X�g���N�^
	~CGimmick() override;			//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V

	//�R���W�����C���X�^���X
	void SetCollision(CCollision* colision) { m_Collision = colision; }
	CCollision* GetCollision() { return m_Collision; }

private:

	//�����o�ϐ�
	CCollision* m_Collision;
};

#endif