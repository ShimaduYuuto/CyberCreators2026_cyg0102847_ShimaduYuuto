//================================
//
//time.cpp�ɕK�v�Ȑ錾[time.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TIME_H_ //���̃}�N����`������Ă��Ȃ�������
#define _TIME_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//���Ԃ̃N���X
class CTime
{
public:

	//�萔�̏�����
	static const float SLOWRATE;	//�X���E���̔{��

	//���Ԃ̗񋓌^
	typedef enum
	{
		TIME_NORMAL = 0,	//�ʏ�̏��
		TIME_SLOW,			//�x���Ȃ��Ă�����
		TIME_MAX,			//�񋓌^�̍ő�
	}TIME;

	//�����o�֐�
	CTime();										//�R���X�g���N�^
	~CTime();										//�f�X�g���N�^
	HRESULT Init();									//������
	void Update();									//�X�V
	void SetTimeState(TIME state);					//���Ԃ̏�Ԃ�ݒ�
	TIME GetTimeState() { return m_TimeState; }		//���Ԃ̏�Ԃ��擾
	void SetTimer(int time);						//�^�C�}�[�̐ݒ�
	void SetStateTimer(TIME state, int time);		//��Ԃ̃^�C�}�[��ݒ�
	bool GetEndTimer() { return m_bEndTimer; }		//�^�C�}�[�̏I������

	//�e���v���[�g
	template <typename T>T GetValue(const T value)
	{
		//�ϐ��ɒl����
		T Value = value;

		//���Ԃ��X���[��ԂȂ�l��ω�
		if (m_TimeState == TIME_SLOW)
		{
			Value = value * SLOWRATE;
		}

		return Value;
	};	//���E�̏�Ԃɉ����Ēl��Ԃ�

private:
	TIME m_TimeState;			//���Ԃ̏��
	int m_nTimeCount;			//���Ԃ̃J�E���g
	bool m_bEndTimer;			//�^�C�}�[�̏I������
};

#endif