////================================
////
////action_enemy001.cpp�ɕK�v�Ȑ錾[action_enemy001.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _ACTION_ENEMY001_H_ //���̃}�N����`������Ă��Ȃ�������
//#define _ACTION_ENEMY001_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`
//
////�w�b�_�[�̃C���N���[�h
//#include "main.h"
//#include "action.h"
//#include "character.h"
//
////�A�N�V�����N���X
//class CAction_Enemy001 : public CAction
//{
//public:
//
//	//�A�N�V�����̗񋓌^
//	typedef enum
//	{
//		ACTION_ENEMY001_NONE = 0,		//�����Ȃ�
//		ACTION_ENEMY001_SPAWN_SHIELD,	//���̃X�|�[��
//		ACTION_ENEMY001_ATTACK,			//�U��
//		ACTION_ENEMY001_MAX,			//�񋓂̍ő�
//	}ACTION_ENEMY001;
//
//	//�����o�֐�
//	CAction_Enemy001();			//�R���X�g���N�^
//	~CAction_Enemy001() override;	//�f�X�g���N�^
//	HRESULT Init() override;	//������
//	void Update() override;		//�X�V
//	static CAction_Enemy001* Create(ACTION_ENEMY001 action_enemy001, CCharacter* character);	//�A�N�V�����̐���
//
//	//�p�����[�^�[�̎擾�Ɛݒ�
//	void SetNextAction(ACTION_ENEMY001 action) { m_NextAction = action; }	//���̃A�N�V�����̐ݒ�
//	virtual void SetNextAction();											//���̃A�N�V�����̐ݒ�
//	ACTION_ENEMY001 GetNextAction() { return m_NextAction; }				//���̃A�N�V�����̎擾
//	ACTION_ENEMY001 GetNowAction() { return m_NowAction; }					//���݂̃A�N�V�����̎擾
//	CCharacter* GetCharacter() { return m_pCharacter; }						//�L�����N�^�[�̎擾
//
//private:
//
//	ACTION_ENEMY001 m_NowAction;	//���݂̃A�N�V����
//	ACTION_ENEMY001 m_NextAction;	//���̃A�N�V����
//	CCharacter* m_pCharacter;	//�L�����N�^�[�̃|�C���^
//};
//
//#endif