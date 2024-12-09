//================================
//
//game_character.cpp�ɕK�v�Ȑ錾[game_character.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GAME_CHARACTER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _GAME_CHARACTER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "character.h"

//�L�����N�^�[�N���X
class CGame_Character : public CCharacter
{
public:

	//�萔
	static const float GRAVITY;					//�d�͂̋���
	static constexpr float SIZE_RADIUS{ 30.0f };//�T�C�Y�̔��a

	//�����o�֐�
	CGame_Character(int nPriority = 3);			//�R���X�g���N�^
	~CGame_Character() override;				//�f�X�g���N�^
	HRESULT Init() override;					//������
	void Uninit() override;						//�I��
	void Update() override;						//�X�V
	void Draw() override;								//�`��

	void UpdatePos() override;							//�ʒu�̍X�V
	//void UpdateRot();									//�����̍X�V
	virtual D3DXVECTOR3 GravityMove(D3DXVECTOR3 move);	//�d�͂̏���

	//�������
	void SetOnStand(bool onstand) { m_bOnStand = onstand; }						//�ݒ�
	bool GetOnStand() { return m_bOnStand; }									//�擾

	//�T�C�Y�̔��a
	void SetSizeRadius(float radius) { m_fRadiusSize = radius; }				//�ݒ�
	float GetSizeRadius() { return m_fRadiusSize; }								//�擾

	//�_���[�W����
	virtual bool SetDamage(int damage);											//�ݒ�

	//�d�͂��󂯂邩
	void SetEnableGravity(bool enable) { m_bEnableGravity = enable; }			//�ݒ�
	bool GetEnableGravity() { return m_bEnableGravity; }						//�擾

	//������ї�
	void SetBlowValue(D3DXVECTOR3 value) { m_BlowValue = value; }				//�ݒ�
	D3DXVECTOR3 GetBlowValue() { return m_BlowValue; }							//�擾

	//���łɒ���t������
	void SetEnteredStick(bool enter) { m_bEnteredStick = enter; }	//�ݒ�
	bool GetEnteredStick() { return m_bEnteredStick; }				//�擾

private:

	//�����o�ϐ�
	int m_nLife;							//�̗�
	bool m_bOnStand;						//�����Ă��邩
	float m_fRadiusSize;					//�T�C�Y�̔��a
	bool m_bEnableGravity;					//�d�͂��󂯂邩
	D3DXVECTOR3 m_BlowValue;				//������т̗�
	bool m_bEnteredStick;					//��x�ł�
};

#endif