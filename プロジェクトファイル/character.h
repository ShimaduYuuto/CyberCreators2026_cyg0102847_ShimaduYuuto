//================================
//
//character.cpp�ɕK�v�Ȑ錾[character.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _CHARACTER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _CHARACTER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "object.h"
#include "modelparts.h"
#include "shadow.h"

//�L�����N�^�[�N���X
class CCharacter : public CObject
{
public:

	//�萔
	static const float ROTATE_SPEED;			//��]�̑��x
	static const int DAMAGE_TIME{5};			//�_���[�W��Ԃ̎���
	static const int INTERPOLATION_FRAME{3};	//���[�V�����̕�ԃJ�E���g
	static const float GRAVITY;					//�d�͂̋���
	static constexpr float SIZE_RADIUS{30.0f};	//�T�C�Y�̔��a

	//�L�����N�^�[�̎��
	typedef enum
	{
		CHARACTER_TYPE_NONE = 0,//����
		CHARACTER_TYPE_PLAYER,	//�v���C���[
		CHARACTER_TYPE_ENEMY,	//�G
		CHARACTER_TYPE_MAX,		//�񋓂̍ő�
	}CHARACTER_TYPE;

	//�L�[�̍\����
	struct Key
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 rot;	//����
		Key() : pos(), rot()
		{

		}
	};

	//�L�[�Z�b�g�̍\����
	struct KeySet
	{
		int nFrame;				//���[�V�����̃t���[����
		std::vector<Key> Key;	//�e�L�[�̏��
		KeySet() : nFrame(0), Key()
		{

		}
	};
	
	//���[�V�������̍\����
	struct Motion
	{
		bool bLoop;					//���[�V���������[�v���邩
		int nNumKey;				//�L�[�̎��
		std::vector<KeySet> KeySet;	//�e�L�[�̐ݒ�
		Motion() : bLoop(false), nNumKey(0), KeySet()
		{

		}
	};

	//�p�[�c���̍\����
	struct PartsInfo
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 rot;	//����
		PartsInfo() : pos(), rot()
		{

		}
	};

	//�����o�֐�
	CCharacter(int nPriority = 3);						//�R���X�g���N�^
	virtual ~CCharacter() override;						//�f�X�g���N�^
	virtual HRESULT Init() override;					//������
	virtual void Uninit() override;						//�I��
	virtual void Update() override;						//�X�V
	void Draw() override;								//�`��

	virtual void UpdatePos();							//�ʒu�̍X�V
	void UpdateRot();									//�����̍X�V
	virtual D3DXVECTOR3 GravityMove(D3DXVECTOR3 move);	//�d�͂̏���
	
	//�p�����[�^�֘A�̊֐�
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }								//�����̐ݒ�
	D3DXVECTOR3& GetRot() {return m_Rot;}										//�����̎擾
	void SetLife(int life) {m_nLife = life;}									//�̗͂̐ݒ�
	int& GetLife() { return m_nLife; }											//�̗͂��擾

	//�ړ���
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }							//�ݒ�
	void AddMove(D3DXVECTOR3 move) { m_Move += move; }							//�ǉ�
	D3DXVECTOR3& GetMove() { return m_Move; }									//�擾

	//�ړI�̌���
	void SetGoalRot(D3DXVECTOR3 goalrot);										//�ݒ�
	D3DXVECTOR3& GetGoalRot() { return m_GoalRot; }								//�擾

	//�O��̈ʒu
	void SetOldPos(D3DXVECTOR3 oldpos) { m_OldPos = oldpos; }					//�ݒ�
	D3DXVECTOR3& GetOldPos() { return m_OldPos; }								//�擾

	//�������
	void SetOnStand(bool onstand) { m_bOnStand = onstand; }						//�ݒ�
	bool GetOnStand() { return m_bOnStand; }									//�擾

	//���
	void SetCharacterType(CHARACTER_TYPE type) { m_CharacterType = type; }		//�ݒ�

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

	//���[�V����
	void SetMotionInfo(const char* motionfilename);								//���[�V�������̐ݒ�
	void SetMotion(int motion);													//���[�V�����̐ݒ�
	int GetMotionState() { return m_MotionState; }								//���[�V������Ԃ̎擾
	void UpdateMotion();														//���[�V�����̍X�V������֐�
	CModelparts* GetModelParts(int index) { return m_apModel[index]; }			//���f���p�[�c�̎擾

	//�ʒu�̐ݒ�
	void SetPos(D3DXVECTOR3 pos) override
	{
		CObject::SetPos(pos);
		m_OldPos = pos;
	}

private:

	//�����o�֐�
	float AddRot(float addrot);		//�����̉��Z������֐�

	//�����o�ϐ�
	CHARACTER_TYPE m_CharacterType;			//���
	int m_nLife;							//�̗�
	D3DXVECTOR3 m_OldPos;					//�O��̈ʒu
	D3DXVECTOR3 m_Move;						//�ړ���
	D3DXVECTOR3 m_Rot;						//����
	D3DXVECTOR3 m_GoalRot;					//�ړI�̌���
	D3DXMATRIX m_mtxWorld;					//�}�g���b�N�X
	bool m_bOnStand;						//�����Ă��邩
	float m_fRadiusSize;					//�T�C�Y�̔��a
	bool m_bEnableGravity;					//�d�͂��󂯂邩
	D3DXVECTOR3 m_BlowValue;				//������т̗�
	bool m_bEnteredStick;					//��x�ł�����t������
	CShadow* m_pShadow;						//�e�̃|�C���^

	//���[�V�����̕ϐ�
	int m_MotionState;						//���݂̃��[�V�����̏��
	int m_nMotionCount;						//���[�V�����L�[�̃J�E���g
	float m_fFrameCount;					//���[�V�����t���[���̃J�E���g
	bool m_bChangeMotion;					//���[�V������؂�ւ��邩�̕ϐ�
	float m_fInterpolationCount;			//���`��Ԃ̃J�E���g
	float m_bInterpolationEnd;				//���`�ۊǂ��I����Ă��邩
	std::vector<PartsInfo> m_InterpolationInfo;		//�p�[�c�̏��
	std::vector<Motion> m_Motion;			//���[�V�������
	std::vector<CModelparts*> m_apModel;	//�v���C���[�̃p�[�c[�p�[�c��]
	std::vector<PartsInfo> m_PartsInfo;		//�p�[�c�̏��
};

#endif