////================================
////
////battlemanager.cpp�ɕK�v�Ȑ錾[battlemanager.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _BATTLEMANAGER_H_ //���̃}�N����`������Ă��Ȃ�������
//#define _BATTLEMANAGER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`
//
////�w�b�_�[�̃C���N���[�h
//#include "main.h"
//#include "collision_wall.h"
//#include "enemy.h"
//#include "explodingbarrel.h"
//
////�o�g���}�l�[�W���[�̃N���X
//class CBattleManager
//{
//public:
//
//	//�o�g���X�e�[�W���
//	struct BattleInfo
//	{
//		D3DXVECTOR3 StagePos;			//�X�e�[�W�ʒu
//		float fRadius;					//�X�e�[�W�̔��a
//		std::list<CEnemy*> EnemyList;	//�G�̃��X�g
//	};
//
//	//�����o�֐�
//	CBattleManager();			//�R���X�g���N�^
//	~CBattleManager();			//�f�X�g���N�^
//	HRESULT Init();				//������
//	void Uninit();				//�I��
//
//private:
//	std::list<BattleInfo*> a;
//};
//
//#endif