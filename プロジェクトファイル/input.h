//================================
//
//input.cpp�ɕK�v�Ȑ錾[input.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _INPUT_H_ //���̃}�N����`������Ă��Ȃ�������
#define _INPUT_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//���͊��N���X
class CInput
{
public:

	//�萔
	static const int MAX_KEY = 256;	//�L�[�̍ő�

	//�����o�֐�
	CInput();
	~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//����������
	virtual void Uninit();		//�I������
	virtual void Update() = 0;	//���͒[�����ƂɎ���

protected:

	//�S���͏����ŋ��L
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//�L�[�{�[�h����
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;

	//�L�[�̓��͏�Ԃ�Ԃ��֐�
	bool GetPress(int nKey);	//�v���X��Ԏ擾
	bool GetTrigger(int nKey);	//�g���K�[��Ԃ��擾
	bool GetRerease(int nKey);	//�����[�X��Ԃ��擾
	bool GetRepeate(int nKey);	//���s�[�g��Ԃ��擾

private:
	BYTE m_aKeyState[MAX_KEY];			//�L�[�̏��
	BYTE m_aKeyStateTrigger[MAX_KEY];	//�L�[�̏��(�g���K�[)
	BYTE m_aKeyStateRerease[MAX_KEY];	//�L�[�̏��(�����[�X)
};

//�W���C�p�b�h����
class CInputJoypad : public CInput
{
public:

	//�萔
	static const int SPEED_KEY = 14;
	static const int JOYPAD_DEADZONE = 1;

	//�L�[�̎��
	typedef enum
	{
		JOYKEY_UP = 0,
		JOYKEY_DOWN,
		JOYKEY_LEFT,
		JOYKEY_RIGHT,
		JOYKEY_START,
		JOYKEY_BACK,
		JOYKEY_L3,
		JOYKEY_R3,
		JOYKEY_LB,
		JOYKEY_RB,
		JOYKEY_LT,
		JOYKEY_RT,
		JOYKEY_A,
		JOYKEY_B,
		JOYKEY_X,
		JOYKEY_Y,
		JOYKEY_MAX
	}JOYKEY;

	//�X�e�B�b�N�̔ԍ�
	typedef enum
	{
		STICKTYPE_LEFT = 0, // ���X�e�B�b�N
		STICKTYPE_RIGHT,	// �E�X�e�B�b�N
		STICKTYPE_MAX
	}STICKTYPE;

	//�X�e�B�b�N�̕���
	typedef enum
	{
		STICKANGLE_UP = 0, // ��
		STICKANGLE_DOWN,   // ��
		STICKANGLE_LEFT,   // ��
		STICKANGLE_RIGHT,  // �E
		STICKANGLE_MAX,
	}STICKANGLE;

	//�X�e�B�b�N�̓��͏��
	typedef struct
	{
		float afTplDiameter[STICKTYPE_MAX];                      // �X�e�B�b�N�̓|���
		float afAngle[STICKTYPE_MAX];                            // �X�e�B�b�N�̊p�x
		bool abAnglePress[STICKTYPE_MAX][STICKANGLE_MAX];        // �X�e�B�b�N�̕����v���X���
		bool abAngleTrigger[STICKTYPE_MAX][STICKANGLE_MAX];      // �X�e�B�b�N�̕����g���K�[���
		bool abAngleRepeat[STICKTYPE_MAX][STICKANGLE_MAX];       // �X�e�B�b�N�̕������s�[�g���
		bool abAngleRelease[STICKTYPE_MAX][STICKANGLE_MAX];      // �X�e�B�b�N�̕��������[�X���
	}STICKINPUT;

	//��{�̏���
	CInputJoypad();
	~CInputJoypad();
	HRESULT Init(void);
	void Uninit() override;
	void Update() override;
	void UpdateStick(XINPUT_STATE* xinput); //�X�e�B�b�N�̍X�V����

	//�L�[�̓��͏�Ԃ�Ԃ��֐�
	bool GetPress(JOYKEY key);		//�v���X��Ԏ擾
	bool GetTrigger(JOYKEY key);	//�g���K�[��Ԃ��擾
	bool GetRepeate(JOYKEY key);	//���s�[�g��Ԃ��擾
	XINPUT_STATE* GetXInputState(); //�R���g���[���[�̓��͏��̎擾
	STICKINPUT GetStick();			//�X�e�B�b�N�̏����擾
	WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);

private:

	//�����o�֐�
	float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos); //2�_�̊p�x�����߂�֐�

	//�����o�ϐ�
	BYTE m_aKeyState[MAX_KEY];						//�L�[�̏��
	BYTE m_aKeyStateTrigger[MAX_KEY];				//�L�[�̏��(�g���K�[)
	int m_KeyPressCount;							//�L�[�������Ă鎞�Ԃ̃J�E���g
	int m_JoyKeyPressCount;							//�L�[�������Ă鎞�Ԃ̃J�E���g
	WORD m_joykeyState;								//�W���C�p�b�h�̃v���X���
	WORD m_joykeyStateTrigger;						//�W���C�p�b�h�̃g���K�[���
	WORD m_joykeyStateRelease;						//�W���C�p�b�h�̃����[�X���
	WORD m_joykeyStateRepeat;						//�W���C�p�b�h�̃��s�[�g���
	int m_Time;										//���Ԃ��v��
	WORD m_Strength;								// �U���̋��� (0 �` 65535)
	D3DXVECTOR3 m_joykeyStickPos;					// �X�e�B�b�N�̌X��
	bool m_bAngle[STICKTYPE_MAX][STICKANGLE_MAX];	//�X�e�B�b�N�̓��͏��
	DWORD m_aStickCurrentTime[STICKTYPE_MAX][STICKANGLE_MAX]; //�X�e�B�b�N�̌��݂̎���
	DWORD m_aStickExecLastTime[STICKTYPE_MAX][STICKANGLE_MAX]; //�X�e�B�b�N�̌��݂̎���
	STICKINPUT m_stick;								//�X�e�B�b�N�̓��͏��
	XINPUT_STATE m_XInput;							// ���͏��
	XINPUT_STATE m_joykeyCurrentTime;				// �R���g���[���[�̌��݂̎���
	XINPUT_STATE m_joykeyExecLastTime;				// �R���g���[���[�̍Ō�ɐ^��Ԃ�������
	XINPUT_STATE m_joykeyInput;						// �R���g���[���[�̓��͏��
	XINPUT_VIBRATION m_joykeyMoter;					// �R���g���[���[�̃��[�^�[
	WORD m_Button;									//�{�^���̔���
	WORD m_OldButton;								//�Â��{�^���̔���
};

//�}�E�X����
class CInputMouse : public CInput
{
public:
	//�}�E�X�̃{�^���̎�ޗ񋓌^
	typedef enum
	{
		MOUSEBUTTON_LEFT = 0,	//���N���b�N
		MOUSEBUTTON_RIGHT,		//�E�N���b�N
		MOUSEBUTTON_WHEEL,		//�z�C�[��(��������)
		MOUSEBUTTON_MAX,		//�񋓂̍ő�
	}MOUSEBUTTON;

	//��{�̏���
	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit() override;
	void Update() override;

	//�擾�p
	bool GetPress(MOUSEBUTTON nKey);	//�v���X
	bool GetTrigger(MOUSEBUTTON nKey);	//�g���K�[
	bool GetRerease(MOUSEBUTTON nKey);	//�����[�X
	D3DXVECTOR3 GetMove();				//�ړ���
	D3DXVECTOR2 GetPos();				//�ʒu

private:

	DIMOUSESTATE m_zdiMouseState;						//�}�E�X���
	DIMOUSESTATE m_aMouseState;							//�}�E�X�̃v���X���
	DIMOUSESTATE m_aMouseStateTrigger;					//�}�E�X�̃g���K�[���
	DIMOUSESTATE m_aMouseStateRerease;					//�}�E�X�̃����[�X���
	POINT m_Point;										//�|�C���g�̕ۑ�
};

#endif