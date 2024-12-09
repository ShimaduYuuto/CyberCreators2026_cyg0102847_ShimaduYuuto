//======================================
//
//	�J�����̏���[camera.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "camera.h"
#include "manager.h"
#include "main.h"
#include "player.h"
#include "game.h"

//�萔�̐ݒ�
const float CCamera::LENGTH_NORMAL = 400.0f;				//�ʏ�J�����̋���
const float CCamera::LENGTH_SLOW = LENGTH_NORMAL * 0.7f;	//�X���[�J�����̋���

//============================
//�J�����̃R���X�g���N�^
//============================
CCamera::CCamera()
{

}

//============================
//�J�����̃f�X�g���N�^
//============================
CCamera::~CCamera()
{

}

//============================
//�J�����̏�����
//============================
HRESULT CCamera::Init()
{
	//�����o�ϐ��̏����ݒ�
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���_�̏�����
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�����_�̏�����
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//��x�N�g���̏�����
	m_mtxProjection = {};							//�v���W�F�N�V�����}�g���b�N�X�̏�����
	m_mtxView = {};									//�r���[�}�g���b�N�X�̏�����
	m_Viewport.X = 0;
	m_Viewport.Y = 0;
	m_Viewport.Width = SCREEN_WIDTH;
	m_Viewport.Height = SCREEN_HEIGHT;
	m_Viewport.MaxZ = 1.0f;
	m_Viewport.MinZ = 0.0f;
	m_fShakeFrameCount = 0.0f;
	m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);
	m_rot.x = 0.0f;
	m_fLength = LENGTH_NORMAL;

	return S_OK;
}

//============================
//�J�����̏I������
//============================
void CCamera::Uninit()
{
	
}

//============================
//�J�����̍X�V����
//============================
void CCamera::Update()
{
	//���[�h�̎擾
	CScene::MODE Mode = CManager::GetInstance()->GetScene()->GetMode();

	//�V�[���ɂ���ď�����ύX
	switch (Mode)
	{
	case CScene::MODE_TITLE:	//�^�C�g��
		break;

	case CScene::MODE_GAME:		//�Q�[��

		{
			//�Q�[���V�[���̃v���C���[�̈ʒu���擾
			CGame* pGame = nullptr;
			pGame = (CGame*)CManager::GetInstance()->GetScene();	//�Q�[���V�[���̎擾

			//�v���C���[�̈ʒu�𒍎��_�ɑ��
			m_posR = pGame->GetGamePlayer()->GetPos();				//�v���C���[�̈ʒu�𒍎��_�ɑ��
			//m_posV.y = pGame->GetGamePlayer()->GetPos().y + 50.0f;
			

			//�}�E�X�̈ړ��ʂŌ�����ύX
			{
				//�}�E�X�̈ړ��ʂ̎擾
				D3DXVECTOR3 MouseMove = CManager::GetInstance()->GetMouse()->GetMove();

				//�J�����ɔ��f
				m_rot.y += MouseMove.x / 100.0f;
				m_rot.x -= MouseMove.y / 500.0f;
			}

			//�����̕␳
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}

			if (m_rot.x > D3DX_PI * 0.4f)
			{
				m_rot.x = D3DX_PI * 0.4f;
			}
			if (m_rot.x < D3DX_PI * -0.4f)
			{
				m_rot.x = D3DX_PI * -0.4f;
			}

			//���Ԃ̏�Ԃɉ����ċ�����ύX
			if (pGame->GetTime()->GetTimeState() == pGame->GetTime()->TIME_SLOW)
			{
				m_fLength -= 0.03f * m_fLength;

				if (m_fLength < LENGTH_SLOW)
				{
					m_fLength = LENGTH_SLOW;
				}
			}
			else
			{
				m_fLength += 0.03f * m_fLength;

				if (m_fLength > LENGTH_NORMAL)
				{
					m_fLength = LENGTH_NORMAL;
				}
			}

			//�����_�̍X�V
			/*m_posR.y = sinf(m_rot.x) * LENGTH_POSR;
			m_posR.x = sinf(m_rot.y + D3DX_PI) * cosf(m_rot.x) * LENGTH_POSR;
			m_posR.z = cosf(m_rot.y + D3DX_PI) * cosf(m_rot.x) * LENGTH_POSR;
			m_posR += pGame->GetGamePlayer()->GetPos();*/

			//m_posR.y = -sinf(m_rot.x + D3DX_PI) * LENGTH_POSR;
			//m_posR.x = sinf(m_rot.y) * cosf(m_rot.x + D3DX_PI) * LENGTH_POSR;
			//m_posR.z = cosf(m_rot.y) * cosf(m_rot.x + D3DX_PI) * LENGTH_POSR;
			//m_posR += pGame->GetGamePlayer()->GetPos();
			
			//���_�̍X�V(���܂ł̂��)
			/*m_posV.y = m_posR.y + -sinf(m_rot.x) * m_fLength;
			m_posV.x = m_posR.x + sinf(m_rot.y + D3DX_PI) * cosf(m_rot.x) * m_fLength;
			m_posV.z = m_posR.z + cosf(m_rot.y + D3DX_PI) * cosf(m_rot.x) * m_fLength;*/

			m_posV.y =/* m_posR.y + */-sinf(m_rot.x) * m_fLength;
			m_posV.x =/* m_posR.x + */sinf(m_rot.y + D3DX_PI) * cosf(m_rot.x) * m_fLength;
			m_posV.z =/* m_posR.z + */cosf(m_rot.y + D3DX_PI) * cosf(m_rot.x) * m_fLength;
			m_posV += pGame->GetGamePlayer()->GetPos();

			//���_�̍X�V
			D3DXVECTOR3 PosVLength = pGame->GetGamePlayer()->GetPos() - m_posR;
			PosVLength = m_posR - pGame->GetGamePlayer()->GetPos();
			float fAngleY = atan2f(PosVLength.x, PosVLength.z);	//y���̊p�x���Z�o
			float fAngleX = atan2f(PosVLength.z, PosVLength.y);	//x���̊p�x���Z�o
			float fAngleZ = atan2f(PosVLength.x, PosVLength.y);	//z���̊p�x���Z�o

			//m_posV.y = cosf(fAngleX/* + D3DX_PI * 0.5f*/)/* * cosf(fAngleY)*/ * m_fLength;
			//m_posV.y = pGame->GetGamePlayer()->GetPos().y;
			//m_posV.x = sinf(fAngleY)/* * sinf(fAngleX)*/ * m_fLength;
			//m_posV.z = cosf(fAngleY)/* * sinf(fAngleX)*/ * m_fLength;

			//m_posV.y = m_fLength * cos(fAngleX) * sin(fAngleZ);
			//m_posV.x = m_fLength * cos(fAngleX) * cos(fAngleZ);
			//m_posV.z = m_fLength * sin(fAngleX);
			//m_posV += pGame->GetGamePlayer()->GetPos();
		}
		
		break;

	case CScene::MODE_RESULT:	//���U���g
		break;
	};
}

//============================
//�J�����̐ݒ菈��
//============================
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�J�����ɕ`�悷�鋗��
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		20000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�h��̑傫���̐ݒ�
	D3DXVECTOR3 adjust = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�h��̃J�E���g���c���Ă���Ȃ珈��
	if (m_fShakeFrameCount > 0.0f)
	{
		//�f�N�������g
		m_fShakeFrameCount--;
		
		//�h��̑傫���̐ݒ�
		adjust = D3DXVECTOR3(rand() % (int)m_fShakeMagnitude, rand() % (int)m_fShakeMagnitude, 0.0f);
	}

	//�J�����̗h�ꂽ���̕ϐ�
	D3DXVECTOR3 ShakePosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 ShakePosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�J�����̗h�ꂽ���̈ʒu
	ShakePosV = m_posV + adjust;
	ShakePosR = m_posR + adjust;

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&ShakePosV, //���_
		&ShakePosR, //�����_
		&m_vecU);//������̃x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	pDevice->SetViewport(&m_Viewport);
}

//============================
//�J�����ɉf���Ă��邩��Ԃ�
//============================
bool CCamera::GetViewObject(D3DXMATRIX mtx)
{
	//�Ԃ��p�̕ϐ�
	bool bScreen = false;

	D3DXVECTOR3 ScreenPos, MtxPos;
	ScreenPos = MtxPos = { 0.0f, 0.0f, 0.0f };
	
	D3DXVec3Project(
		&ScreenPos,
		&MtxPos,
		&m_Viewport,
		&m_mtxProjection,
		&m_mtxView,
		&mtx
	);

	//��ʂ͈͓̔��ɂ���Ȃ�
	if (ScreenPos.x >= 0.0f && ScreenPos.x <= SCREEN_WIDTH
		&& ScreenPos.y >= 0.0f && ScreenPos.y <= SCREEN_HEIGHT)
	{
		bScreen = true;
	}

	return bScreen;
}

//============================
//�J�����ɉf���Ă��邩��Ԃ�
//============================
bool CCamera::GetViewObject(D3DXVECTOR3 pos)
{
	//�Ԃ��p�̕ϐ�
	bool bScreen = false;

	D3DXVECTOR3 ScreenPos, MtxPos;
	ScreenPos = MtxPos = { 0.0f, 0.0f, 0.0f };
	D3DXMATRIX mtx;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtx, pos.x, pos.y, pos.z);

	D3DXVec3Project(
		&ScreenPos,
		&MtxPos,
		&m_Viewport,
		&m_mtxProjection,
		&m_mtxView,
		&mtx
	);

	//��ʂ͈͓̔��ɂ���Ȃ�
	if (ScreenPos.x >= 0.0f && ScreenPos.x <= SCREEN_WIDTH
		&& ScreenPos.y >= 0.0f && ScreenPos.y <= SCREEN_HEIGHT)
	{
		bScreen = true;
	}

	return bScreen;
}

//============================
//�J�����̗h��̐ݒ�
//============================
void CCamera::SetShake(float frame, float magnitude)
{
	//�p�����[�^�̐ݒ�
	m_fShakeFrameCount = frame;		//�t���[���J�E���g
	m_fShakeMagnitude = magnitude;	//�h��̑傫��
}