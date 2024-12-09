//================================
//
//collision_wall.cpp�ɕK�v�Ȑ錾[collision_wall.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _COLLISION_WALL_H_ //���̃}�N����`������Ă��Ȃ�������
#define _COLLISION_WALL_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectcylinder.h"

//�R���W�����E�H�[���N���X
class CCollision_Wall : public CObjectCylinder
{
public:

	//�萔�̐錾
	static const std::string FILEPATH;	//�ǂݍ��ރt�@�C��
	static const int NUM_CORNER;		//�~���̐�
	static const float HEIGHT;			//����
	static constexpr float ADD_ALPHA{ 0.03f };	//���Z���郿�l

	//�����o�֐�
	CCollision_Wall(int nPriority = 3);		//�R���X�g���N�^
	~CCollision_Wall() override;			//�f�X�g���N�^
	HRESULT Init() override;				//������
	void Uninit() override;					//�I��
	void Update() override;					//�X�V
	void Draw() override;					//�`��

	//�����蔻���Ԃ�
	bool GetHit(D3DXVECTOR3& pos, float radius);

	//�I������
	void SetEnd(bool end) { m_bEnd = end; }	//�ݒ�

	//����
	static CCollision_Wall* Create(D3DXVECTOR3 pos, float radius);

private:
	float m_fAlpha;	//���l
	bool m_bEnd;	//�I����
};

#endif