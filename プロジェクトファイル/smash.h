////================================
////
////smash.cpp�ɕK�v�Ȑ錾[smash.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _SMASH_H_ //���̃}�N����`������Ă��Ȃ�������
//#define _SMASH_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`
//
////�w�b�_�[�̃C���N���[�h
//#include "action_player.h"
//#include "impactrange.h"
//
////�m�[�}���A�^�b�N�N���X
//class CSmash : public CAction_Player
//{
//public:
//
//	//�萔
//	static const int DELAY_TIME = 20;	//�x���̎���
//	static const int ADD_SLOWTIME = 60;	//�ǉ��̃X���[����
//
//	//�����o�֐�
//	CSmash();						//�R���X�g���N�^
//	~CSmash()  override;			//�f�X�g���N�^
//	HRESULT Init()  override;		//������
//	void Update()  override;		//�X�V
//
//	//�擾�p
//	bool GetHit() { return m_bHit; }//�����蔻��
//
//private:
//	CImpactRange* m_pImpact;	//�X�}�b�V���͈̔�
//	bool m_bAttack;				//�U����������
//	bool m_bHit;				//�U��������������
//	int m_nDelayCount;			//�x�点�鎞��
//	int m_nSlowTime;			//�X���E�̎���
//};
//
//#endif