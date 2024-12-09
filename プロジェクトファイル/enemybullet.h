//================================
//
//enemybullet.cpp�ɕK�v�Ȑ錾[enemybullet.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMYBULLET_H_ //���̃}�N����`������Ă��Ȃ�������
#define _ENEMYBULLET_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectX.h"
#include "collision.h"

//�{�X�̒e�N���X
class CEnemyBullet : public CObjectX
{
public:

	//�萔
	static const std::string FILEPATH;				//�p�X
	static constexpr float COLLISION_RADIUS{10.0f};	//�����蔻��̔��a

	//�����o�֐�
	CEnemyBullet(int nPriority = 3);				//�R���X�g���N�^
	~CEnemyBullet() override;						//�f�X�g���N�^
	HRESULT Init() override;						//������
	void Uninit() override;							//�I��
	void Update() override;							//�X�V
	void Draw() override;							//�`��
	static CEnemyBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//����

	//�ړ���
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }	//�ݒ�
	D3DXVECTOR3& GetMove() { return m_Move; }			//�擾

	//�T�C�Y�{��
	void SetSizeRate(float rate) { m_fSizeRate = rate; }	//�ݒ�
	float& GetSizeRate() { return m_fSizeRate; }			//�擾
	void AddSizeRate(float rate) { m_fSizeRate += rate; }	//���Z

	//���˂�����
	void SetReflection(bool reflection) { m_bReflection = reflection; }	//�ݒ�
	bool GetReflection() { return m_bReflection; }						//�擾

	//���˂����鏈��
	void Reflection();	//���ˏ���

	//�����ꂽ��
	void SetShooting(bool shooting) { m_bShooting = shooting; }	//�ݒ�
	bool GetShooting() { return m_bShooting; }					//�擾

	//�����蔻��
	CCollision* GetCollision() { return m_Collision; }		//�擾

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_Move;			//�ړ���
	float m_fSizeRate;			///�T�C�Y�{��
	bool m_bReflection;			//���˂�����
	bool m_bShooting;			//�����ꂽ��
	CCollision* m_Collision;	//�����蔻��
};

#endif