//================================
//
//sound.cpp�ɕK�v�Ȑ錾[sound.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SOUND_H_ //���̃}�N����`������Ă��Ȃ�������
#define _SOUND_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//�T�E���h�N���X
class CSound
{
public:
	//�T�E���h�̗񋓌^
	typedef enum
	{
		SOUND_LABEL_BGM = 0,	//BGM
		SOUND_LABEL_BATTLE,		//�o�g��
		SOUND_LABEL_ATTACK,		//�U��
		SOUND_LABEL_STICK,		//����t��
		SOUND_LABEL_MAX,		//�ő�l
	}SOUND_LABEL;

	//*****************************************************************************
	// �T�E���h���̍\���̒�`
	//*****************************************************************************
	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;			// ���[�v�J�E���g
		float Volume;			// ����
	} SOUNDINFO;

	//�萔
	static const SOUNDINFO SOUND_INFO[SOUND_LABEL_MAX];

	//�����o�֐�
	CSound();								//�R���X�g���N�^
	~CSound();								//�f�X�g���N�^
	HRESULT Init(HWND hWnd);				//������
	void Uninit(void);						//�I������
	HRESULT PlaySound(SOUND_LABEL label);	//�T�E���h�𗬂�
	void Stop(SOUND_LABEL label);			//�T�E���h������~�߂�
	void Stop(void);						//�S�ẴT�E���h���~�߂�
private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif