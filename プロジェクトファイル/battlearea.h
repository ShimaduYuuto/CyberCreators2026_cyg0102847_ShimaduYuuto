//================================
//
//battlearea.cpp�ɕK�v�Ȑ錾[battlearea.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREA_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BATTLEAREA_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "collision_wall.h"
#include "enemy.h"

//�o�g���G���A�̃N���X
class CBattleArea
{
public:

	static constexpr float RADIUS_ENTEREDAREA{ 150.0f };	//�G���A�ɓ������������m���锼�a

	//�����o�֐�
	CBattleArea();		//�R���X�g���N�^
	virtual ~CBattleArea();		//�f�X�g���N�^
	virtual HRESULT Init();		//������
	virtual void Uninit();		//�I��
	virtual void Update();		//�X�V

	//����
	static CBattleArea* Create(D3DXVECTOR3 pos, CBattleArea* area);

	//�X�e�[�W�̕�
	CCollision_Wall* GetWall() { return m_pWall; }	//�擾

	//�I������
	bool GetEnd() { return m_bEnd; }	//�擾

	//���������鏈��
	virtual void SpawnEnemy();	//�G�l�~�[
	virtual void SpawnGimmick();//�M�~�b�N

	//�ʒu
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }	//�ݒ�
	D3DXVECTOR3& GetPos() { return m_Pos; }			//�擾

	//�G�̐�
	void AddEnemyNum() { m_nEnemyNum++; }//�G�̐��𑝂₷
	void DecrementEnemyNum() { if (m_nEnemyNum > 0) { m_nEnemyNum--; } }//�G�̐������炷

private:

	//�����o�ϐ�
	D3DXVECTOR3 m_Pos;				//�ʒu
	float m_fRadius;				//�X�e�[�W�̔��a
	CCollision_Wall* m_pWall;		//�X�e�[�W�̕�
	std::list<CEnemy*> m_EnemyList;	//�G�̃��X�g
	bool m_bEnteredArea;			//�G���A�ɓ�������
	int m_nEnemyNum;				//�G�̐�
	bool m_bEnd;					//�I��������
};

#endif