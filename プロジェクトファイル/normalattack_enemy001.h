////================================================================
////
////normalattack_enemy001.cpp�ɕK�v�Ȑ錾[normalattack_enemy001.h]
////Author:yuuto shimadu
//// 
////=================================================================
//
//#ifndef _NORMALATTACK_ENEMY001_H_ //���̃}�N����`������Ă��Ȃ�������
//#define _NORMALATTACK_ENEMY001_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`
//
////�w�b�_�[�̃C���N���[�h
//#include "action_enemy001.h"
//
////�m�[�}���A�^�b�N�N���X
//class CNormalAttack_Enemy001 : public CAction_Enemy001
//{
//public:
//
//	//�萔
//	static const int END_TIME = 100;		//�I���܂ł̎���
//	static const float ATTACK_RANGE;		//�U���͈̔�
//	static const int START_COLLISION = 45;	//�R���W�����̔�����n�߂�J�E���g
//	static const int DAMAGE_VALUE = 1;		//�_���[�W��
//
//	//�����o�֐�
//	CNormalAttack_Enemy001();				//�R���X�g���N�^
//	~CNormalAttack_Enemy001()  override;	//�f�X�g���N�^
//	HRESULT Init()  override;				//������
//	void Update()  override;				//�X�V
//
//private:
//	float m_fEndCount;	//�I���J�E���g
//	bool m_bHit;		//����������
//};
//
//#endif