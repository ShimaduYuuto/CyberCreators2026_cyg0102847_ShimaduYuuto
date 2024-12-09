//================================
//
//spawn_enemy.cpp�ɕK�v�Ȑ錾[spawn_enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SPAWN_ENEMY_H_ //���̃}�N����`������Ă��Ȃ�������
#define _SPAWN_ENEMY_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object.h"
#include "enemy.h"
#include "particle_spawn.h"

//�X�|�[���G�l�~�[�N���X
class CSpawn_Enemy : public CObject
{
public:

	static constexpr int SPAWN_TIME{ 30 };

	//�����o�֐�
	CSpawn_Enemy(int nPriority = 2);					//�R���X�g���N�^
	~CSpawn_Enemy() override;							//�f�X�g���N�^
	HRESULT Init() override;							//������
	void Uninit() override;								//�I��
	void Update() override;								//�X�V
	void Draw() override {};							//�`��
	static CSpawn_Enemy* Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type);	//�G�X�|�[���̐���

private:
	int m_nCount;						//�J�E���g�p
	CParticle_Spawn* m_pPaticleManager;	//�p�[�e�B�N���}�l�[�W���[
	CEnemy::ENEMYTYPE m_EnemyType;		//�G�̎��
};

#endif