////================================
////
////action_enemy000.cpp�ɕK�v�Ȑ錾[action_enemy000.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _ACTION_ENEMY000_H_ //���̃}�N����`������Ă��Ȃ�������
//#define _ACTION_ENEMY000_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`
//
////�w�b�_�[�̃C���N���[�h
//#include "main.h"
//#include "action.h"
//#include "character.h"
//
////�A�N�V�����N���X
//class CAction_Enemy000 : public CAction
//{
//public:
//
//	//�A�N�V�����̗񋓌^
//	typedef enum
//	{
//		ACTION_ENEMY000_NONE = 0,		//�����Ȃ�
//		ACTION_ENEMY000_NORMALATTACK,	//�ʏ�U��
//		ACTION_ENEMY000_MAX,			//�񋓂̍ő�
//	}ACTION_ENEMY000;
//
//	//�����o�֐�
//	CAction_Enemy000();			//�R���X�g���N�^
//	~CAction_Enemy000() override;	//�f�X�g���N�^
//	HRESULT Init() override;	//������
//	void Update() override;		//�X�V
//	static CAction_Enemy000* Create(ACTION_ENEMY000 action_enemy000, CCharacter* character);	//�A�N�V�����̐���
//
//	//�p�����[�^�[�̎擾�Ɛݒ�
//	void SetNextAction(ACTION_ENEMY000 action) { m_NextAction = action; }	//���̃A�N�V�����̐ݒ�
//	virtual void SetNextAction();										//���̃A�N�V�����̐ݒ�
//	ACTION_ENEMY000 GetNextAction() { return m_NextAction; }				//���̃A�N�V�����̎擾
//	CCharacter* GetCharacter() { return m_pCharacter; }					//�L�����N�^�[�̎擾
//
//private:
//
//	ACTION_ENEMY000 m_NextAction;	//���̃A�N�V����
//	CCharacter* m_pCharacter;	//�L�����N�^�[�̃|�C���^
//};
//
//#endif