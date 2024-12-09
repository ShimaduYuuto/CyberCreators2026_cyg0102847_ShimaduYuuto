//======================================
//
//	input�̏���[input.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "input.h"

//*****************************************************************
//CInput�N���X�̏���
//*****************************************************************

//�ÓI�����o������
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//============================
//�C���v�b�g�̃R���X�g���N�^
//============================
CInput::CInput()
{

}

//============================
//�C���v�b�g�̃f�X�g���N�^
//============================
CInput::~CInput()
{

}

//============================
//�����ݒ�(DirectInput�̐���)
//============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//null�|�C���^���̊m�F
	if (m_pInput == nullptr)
	{
		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//============================
//�j������(DirectInput�̔j��)
//============================
void CInput::Uninit()
{
	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

	//���̓f�o�C�X�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire(); //�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//============================
//�X�V����
//============================
void CInput::Update()
{

}

//*****************************************************************
//CInputKeyboard�N���X�̏���
//*****************************************************************

//============================
//�L�[�{�[�h�̃R���X�g���N�^
//============================
CInputKeyboard::CInputKeyboard()
{
	//�L�[�̐���������
	for (int i = 0; i < MAX_KEY; i++)
	{
		//�L�[�̏�Ԃ�������
		m_aKeyState[i] = {};
		m_aKeyStateTrigger[i] = {};
		m_aKeyStateRerease[i] = {};
	}
}

//============================
//�L�[�{�[�h�̃f�X�g���N�^
//============================
CInputKeyboard::~CInputKeyboard()
{

}

//============================
//�����ݒ�(DirectInput�̐���)
//============================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();
	return S_OK;
}

//============================
//�j������
//============================
void CInputKeyboard::Uninit()
{
	//DirectInput�̔j��
	CInput::Uninit();
}

//============================
//�X�V����
//============================
void CInputKeyboard::Update()
{
	BYTE aKeyState[MAX_KEY]; //�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //�L�[�{�[�h�̃g���K�[����ۑ�
			m_aKeyStateRerease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey]; //�L�[�{�[�h�̃����[�X����ۑ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire(); //�L�[�{�[�h�ւ̃A�N�Z�X��
	}
}

//========================================
//�L�[�{�[�h�̃v���X�����擾
//========================================
bool CInputKeyboard::GetPress(int nKey)
{
	return((m_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//========================================
//�L�[�{�[�h�̃g���K�[�����擾
//========================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//========================================
//�L�[�{�[�h�̃����[�X�����擾
//========================================
bool CInputKeyboard::GetRerease(int nKey)
{
	return((m_aKeyStateRerease[nKey] & 0x80) != 0) ? true : false;
}

//*****************************************************************
//CInputJoypad�N���X�̏���
//*****************************************************************

//============================
//�W���C�p�b�h�̃R���X�g���N�^
//============================
CInputJoypad::CInputJoypad()
{
	
}

//============================
//�W���C�p�b�h�̃f�X�g���N�^
//============================
CInputJoypad::~CInputJoypad()
{

}

//============================
//�W���C�p�b�h�̃f�X�g���N�^
//============================
HRESULT CInputJoypad::Init()
{
	//�������̃N���A
	memset(&m_aKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_aKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//XInput�̃X�e�[�g�ݒ�(�L���ɂ���)
	XInputEnable(true);

	// �R���g���[���[�̐U������̂O�N���A
	ZeroMemory(&m_joykeyMoter, sizeof(XINPUT_VIBRATION));

	// �U������p�̏�����
	m_Time = 0;
	m_Strength = 0;

	return S_OK;
}

//============================
//�W���C�p�b�h�̏I������
//============================
void CInputJoypad::Uninit()
{
	//XInput�̃X�e�[�g��ݒ�
	XInputEnable(false);
}

//============================
//�W���C�p�b�h�̍X�V����
//============================
void CInputJoypad::Update()
{
	XINPUT_STATE joykeystate; //�W���C�p�b�h�̓��͏��

	//�W���C�p�b�h�̏����擾
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{
		//�X�e�B�b�N�̍X�V
		UpdateStick(&joykeystate);

		joykeystate.Gamepad.wButtons |= GetJoypadStick(joykeystate.Gamepad.sThumbLX, joykeystate.Gamepad.sThumbLY, JOYPAD_DEADZONE);

		WORD Button = joykeystate.Gamepad.wButtons;
		WORD OldButton = m_joykeyState;

		m_joykeyStateTrigger = Button & ~OldButton;    // �g���K�[����
		m_joykeyStateRelease = ~Button & OldButton;    // �����[�X����

		// ���݂̎��Ԃ��擾����
		m_joykeyCurrentTime.Gamepad.wButtons = timeGetTime();

		if (joykeystate.Gamepad.wButtons && ((m_joykeyCurrentTime.Gamepad.wButtons - m_joykeyExecLastTime.Gamepad.wButtons) > SPEED_KEY))
		{
			// �Ō�ɐ^��Ԃ������Ԃ�ۑ�
			m_joykeyExecLastTime.Gamepad.wButtons = m_joykeyCurrentTime.Gamepad.wButtons;

			// �L�[�{�[�h�̃��s�[�g����ۑ�
			m_joykeyStateRepeat = joykeystate.Gamepad.wButtons;
		}
		else
		{
			// �L�[�{�[�h�̃��s�[�g����ۑ�
			m_joykeyStateRepeat = 0;
		}

		m_joykeyState = joykeystate.Gamepad.wButtons;  // �v���X����
	}
}

//============================
//�W���C�p�b�h�̃v���X�����擾
//============================
bool CInputJoypad::GetPress(JOYKEY key)
{
	return m_joykeyState & (0x01 << key);
}

//============================
//�W���C�p�b�h�̃g���K�[�����擾
//============================
bool CInputJoypad::GetTrigger(JOYKEY key)
{
	return m_joykeyStateTrigger & (0x01 << key);
}

//===========================================================================================================================================================================================
//�X�e�B�b�N�̍X�V����
//===========================================================================================================================================================================================
void CInputJoypad::UpdateStick(XINPUT_STATE* xinput)
{
	for (int nCntStick = 0; nCntStick < STICKTYPE_MAX; nCntStick++)
	{
		float fX, fY; //�X�e�B�b�N��X���AY��
	
		switch (nCntStick)
		{
		case STICKTYPE_LEFT:
			fX = (xinput->Gamepad.sThumbLX);
			fY = (xinput->Gamepad.sThumbLY);
			break;
		case STICKTYPE_RIGHT:
			fX = (xinput->Gamepad.sThumbRX);
			fY = (xinput->Gamepad.sThumbRY);
			break;
		}
	
		//�p�x���擾
		m_stick.afAngle[nCntStick] = FindAngle(D3DXVECTOR3(fX, fY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;
	
		//�X�e�B�b�N�̓|������擾
		m_stick.afTplDiameter[nCntStick] = fabsf(fX);
	
		if (m_stick.afTplDiameter[nCntStick] < fabsf(fY))
		{
			m_stick.afTplDiameter[nCntStick] = fabsf(fY);
		}
	
		m_stick.afTplDiameter[nCntStick] /= 32768.0f; //�|���Ă����Ԃ̏����l
	
		//�������̓t���O��������
		for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
		{
			m_bAngle[nCntStick][nCntAngle] = false;
		}
	
		if (m_stick.afTplDiameter[nCntStick] > 0.1f)
		{
			//�p�x���l�����ŏ�Ɉʒu���鎞�A��t���O��^�ɂ���
			if ((m_stick.afAngle[nCntStick] < D3DX_PI * -0.75) || (m_stick.afAngle[nCntStick] > D3DX_PI * 0.75))
			{
				m_bAngle[nCntStick][STICKANGLE_UP] = true;
			}
	
			//�p�x���l�����ŉ��Ɉʒu���鎞�A���t���O��^�ɂ���
			else if ((m_stick.afAngle[nCntStick] > D3DX_PI * -0.25) && (m_stick.afAngle[nCntStick] < D3DX_PI * 0.25))
			{
				m_bAngle[nCntStick][STICKANGLE_DOWN] = true;
			}
	
			//�p�x���l�����ō��Ɉʒu���鎞�A���t���O��^�ɂ���
			else if ((m_stick.afAngle[nCntStick] > D3DX_PI * -0.75) && (m_stick.afAngle[nCntStick] < D3DX_PI * -0.25))
			{
				m_bAngle[nCntStick][STICKANGLE_LEFT] = true;
			}
	
			//�p�x���l�����ŉE�Ɉʒu���鎞�A�E�t���O��^�ɂ���
			else if ((m_stick.afAngle[nCntStick] > D3DX_PI * 0.25) && (m_stick.afAngle[nCntStick] < D3DX_PI * 0.75))
			{
				m_bAngle[nCntStick][STICKANGLE_RIGHT] = true;
			}
		}
	
		//�p�x�ɉ��������͏���
		for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
		{
			//�X�e�B�b�N�̃g���K�[����ۑ�
			m_stick.abAngleTrigger[nCntStick][nCntAngle] = !m_stick.abAnglePress[nCntStick][nCntAngle] && m_bAngle[nCntStick][nCntAngle];
	
			//�X�e�B�b�N�̃����[�X����ۑ�
			m_stick.abAngleRelease[nCntStick][nCntAngle] = m_stick.abAnglePress[nCntStick][nCntAngle] && !m_bAngle[nCntStick][nCntAngle];
	
			//���݂̎��Ԃ��擾
			m_aStickCurrentTime[nCntStick][nCntAngle] = timeGetTime();
	
			if (m_bAngle[nCntStick][nCntAngle] && ((m_aStickCurrentTime[nCntStick][nCntAngle] - m_aStickExecLastTime[nCntStick][nCntAngle]) > SPEED_KEY))
			{
				//�Ō�ɐ^��Ԃ������Ԃ�ۑ�
				m_aStickExecLastTime[nCntStick][nCntAngle] = m_aStickCurrentTime[nCntStick][nCntAngle];
	
				//�X�e�B�b�N�̃��s�[�g����ۑ�
				m_stick.abAngleRepeat[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
			}
			else
			{
				//�X�e�B�b�N�̃��s�[�g����ۑ�
				m_stick.abAngleRepeat[nCntStick][nCntAngle] = 0;
			}
	
			//�X�e�B�b�N�̃v���X����ۑ�
			m_stick.abAnglePress[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
		}
	}
}

//===========================================================================================================================================================================================
//2�_�̊p�x�����߂�
//===========================================================================================================================================================================================
float CInputJoypad::FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	float fAngle; //�p�x

	fAngle = atan2f(TargetPos.y - pos.y, TargetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1.0f;

	return fAngle;
}

//===========================================================================================================================================================================================
// �X�e�B�b�N�̓��͂�����p�b�h�t���O�ɕϊ�
//===========================================================================================================================================================================================
WORD CInputJoypad::GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}

//==========================================================================================
// �R���g���[���[�̓��͏��̎擾
//==========================================================================================
XINPUT_STATE* CInputJoypad::GetXInputState(void)
{
	return &m_XInput;
}

//==========================================================================================
// �X�e�B�b�N�̓��͏����擾
//==========================================================================================
CInputJoypad::STICKINPUT CInputJoypad::GetStick(void)
{
	return m_stick;
}

//*****************************************************************
//CInputmouse�N���X�̏���
//*****************************************************************

//============================
//�}�E�X�̃R���X�g���N�^
//============================
CInputMouse::CInputMouse() : 
	m_aMouseState(),
	m_aMouseStateTrigger(),
	m_aMouseStateRerease(),
	m_Point(),
	m_zdiMouseState()
{

}

//============================
//�}�E�X�̃f�X�g���N�^
//============================
CInputMouse::~CInputMouse()
{

}

//============================
//�}�E�X�̏�����
//============================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT ret = S_FALSE;

	if (m_pInput == NULL)
	{
		return E_FAIL;
	}

	// �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
	ret = m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL);
	if (FAILED(ret)) {
		// �f�o�C�X�̍쐬�Ɏ��s
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	ret = m_pDevice->SetDataFormat(&c_dfDIMouse);	// �}�E�X�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
	if (FAILED(ret)) {
		// �f�[�^�t�H�[�}�b�g�Ɏ��s
		return E_FAIL;
	}

	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	ret = m_pDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(ret)) {
		// ���[�h�̐ݒ�Ɏ��s
		return E_FAIL;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	ret = m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if (FAILED(ret))
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return E_FAIL;
	}

	// ���͐���J�n
	m_pDevice->Acquire();

	return S_OK;
}

//============================
//�}�E�X�̏I������
//============================
void CInputMouse::Uninit()
{
	//���̓f�o�C�X�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire(); //�}�E�X�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//============================
//�X�V����
//============================
void CInputMouse::Update()
{
	DIMOUSESTATE aMouseState; //�}�E�X�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aMouseState), &aMouseState)))
	{
		for (nCntKey = 0; nCntKey < MOUSEBUTTON_MAX; nCntKey++)
		{
			m_aMouseStateTrigger.rgbButtons[nCntKey] = (m_aMouseState.rgbButtons[nCntKey] ^ aMouseState.rgbButtons[nCntKey]) & aMouseState.rgbButtons[nCntKey];	//�}�E�X�̃g���K�[����ۑ�
			m_aMouseStateRerease.rgbButtons[nCntKey] = (m_aMouseState.rgbButtons[nCntKey] ^ aMouseState.rgbButtons[nCntKey]) & ~aMouseState.rgbButtons[nCntKey];//�}�E�X�̃����[�X����ۑ�
			m_aMouseState.rgbButtons[nCntKey] = aMouseState.rgbButtons[nCntKey];																				//�}�E�X�̃v���X����ۑ�
		}

		//�}�E�X���̍X�V
		m_aMouseState = aMouseState;
	}
	else
	{
		m_pDevice->Acquire(); //�}�E�X�ւ̃A�N�Z�X��
	}
}

//========================================
//�}�E�X�̃v���X�����擾
//========================================
bool CInputMouse::GetPress(MOUSEBUTTON nKey)
{
	return((m_aMouseState.rgbButtons[nKey] & 0x80) != 0) ? true : false;
}

//========================================
//�}�E�X�̃g���K�[�����擾
//========================================
bool CInputMouse::GetTrigger(MOUSEBUTTON nKey)
{
	return((m_aMouseStateTrigger.rgbButtons[nKey] & 0x80) != 0) ? true : false;
}

//========================================
//�}�E�X�̃����[�X�����擾
//========================================
bool CInputMouse::GetRerease(MOUSEBUTTON nKey)
{
	return((m_aMouseStateRerease.rgbButtons[nKey] & 0x80) != 0) ? true : false;
}

//========================================
//�}�E�X�̈ړ��ʂ��擾
//========================================
D3DXVECTOR3 CInputMouse::GetMove()
{
	//�ړ��ʂ̎擾
	D3DXVECTOR3 Move = D3DXVECTOR3((float)m_aMouseState.lX, (float)m_aMouseState.lY, (float)m_aMouseState.lZ);
	return Move;
}

//========================================
//�}�E�X�̈ʒu���擾
//========================================
D3DXVECTOR2 CInputMouse::GetPos()
{
	//�ʒu�̎擾
	GetCursorPos(&m_Point);

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &m_Point);

	//�ϐ��ɑ��
	D3DXVECTOR2 Pos = D3DXVECTOR2((float)m_Point.x, (float)m_Point.y);
	return Pos;
}